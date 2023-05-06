#include "front/semantic.h"

#include <cassert>

using ir::Function;
using ir::Instruction;
using ir::Operand;
using ir::Operator;

#define TODO assert(0 && "TODO");

#define GET_CHILD_PTR(node, type, index)                     \
    auto node = dynamic_cast<type *>(root->children[index]); \
    assert(node);
#define ANALYSIS(node, type, index)                          \
    auto node = dynamic_cast<type *>(root->children[index]); \
    assert(node);                                            \
    analysis##type(node, buffer);
#define COPY_EXP_NODE(from, to)              \
    to->is_computable = from->is_computable; \
    to->v = from->v;                         \
    to->t = from->t;

// 这个函数返回一个指向字符串和 IR 函数对应的 map 的指针。这个 map 存储了一些内置函数，比如 getint、putint 等等。
map<std::string, ir::Function *> *frontend::get_lib_funcs()
{
    static map<std::string, ir::Function *> lib_funcs = {
        {"getint", new Function("getint", Type::Int)},
        {"getch", new Function("getch", Type::Int)},
        {"getfloat", new Function("getfloat", Type::Float)},
        {"getarray", new Function("getarray", {Operand("arr", Type::IntPtr)}, Type::Int)},
        {"getfarray", new Function("getfarray", {Operand("arr", Type::FloatPtr)}, Type::Int)},
        {"putint", new Function("putint", {Operand("i", Type::Int)}, Type::null)},
        {"putch", new Function("putch", {Operand("i", Type::Int)}, Type::null)},
        {"putfloat", new Function("putfloat", {Operand("f", Type::Float)}, Type::null)},
        {"putarray", new Function("putarray", {Operand("n", Type::Int), Operand("arr", Type::IntPtr)}, Type::null)},
        {"putfarray", new Function("putfarray", {Operand("n", Type::Int), Operand("arr", Type::FloatPtr)}, Type::null)},
    };
    return &lib_funcs;
}
// 这个函数的作用是向符号表中添加一个新的作用域，参数 node 表示这个作用域对应的语法树节点。
void frontend::SymbolTable::add_scope(Block *node)
{
    ScopeInfo scope_info;                                                  // 生成一个新的作用域
    scope_info.cnt = scope_stack.empty() ? 0 : scope_stack.back().cnt + 1; // 得到新的作用域的cnt
    scope_info.name = "block_" + std::to_string(scope_info.cnt);           // 得到新的作用域的name
    for (auto &&item : scope_stack.back().table)                           // 将之前作用域的变量名重新命名，以便于在不同的作用域中识别同名的变量。
    {
        string new_name = get_scoped_name(item.first);
        STE new_ste = item.second;
        scope_info.table.insert(std::make_pair(new_name, new_ste));
    }
    scope_stack.push_back(scope_info); // 将新的作用域压入作用域栈
}
// 这个函数的作用是退出当前作用域，在符号表中删除当前作用域对应的内容。
void frontend::SymbolTable::exit_scope()
{
    scope_stack.pop_back();
}
// 这个函数的作用是根据一个标识符 id 获取它在符号表中的作用域限定名。例如，如果 id 是 "x"，而在当前作用域中已经有了一个同名变量，则返回 "scope_x"。
string frontend::SymbolTable::get_scoped_name(string id) const
{
    const auto &current_scope = scope_stack.back();
    if (current_scope.table.find(id) != current_scope.table.end())
    {
        return "scope_" + std::to_string(current_scope.cnt) + "_" + id;
    }
    else
    {
        return id + "_scope_" + std::to_string(current_scope.cnt);
    }
}
// 这个函数的作用是根据一个标识符 id 获取它对应的操作数。如果这个标识符是一个变量，则返回一个寄存器或栈上的位置，如果是一个常量，则返回它的值。
// 在当前作用域查找这个标识符是否已经定义，如果已经定义，则返回它的操作数。
// 如果当前作用域没有定义这个标识符，则递归地在外层作用域中查找，直到找到或者到全局作用域为止。
// 如果全局作用域也没有定义这个标识符，则说明这是一个未声明的标识符，需要报错并返回一个错误的操作数。
Operand frontend::SymbolTable::get_operand(string id) const
{
    const auto &current_scope = scope_stack.back();
    auto it = current_scope.table.find(id);

    if (it != current_scope.table.end())
    { // 标识符在当前作用域中定义
        return it->second.operand;
    }
    else
    { // 标识符在当前作用域中未定义，需要在外层作用域中查找
        for (auto it = scope_stack.rbegin() + 1; it != scope_stack.rend(); ++it)
        {
            auto it2 = it->table.find(id);
            if (it2 != it->table.end())
            { // 找到了定义，生成新的操作数并返回
                Operand new_operand;
                new_operand.type = it2->second.operand.type;
                new_operand.type = it2->second.operand.type;
                return new_operand;
            }
        }
        // 标识符未定义
        return Operand();
    }
}
// 这个函数的作用是根据一个标识符 id 获取它在符号表中对应的符号表项。
frontend::STE frontend::SymbolTable::get_ste(string id) const
{
    for (auto it = scope_stack.rbegin(); it != scope_stack.rend(); it++)
    {
        auto iter = it->table.find(id);
        if (iter != it->table.end())
        {
            return iter->second;
        }
    }
    return STE();
}
// 这个类是语义分析器的主体部分，它有一个私有变量 symbol_table，表示语义分析过程中的符号表，以及一个私有变量 tmp_cnt，表示生成临时变量时使用的计数器。
frontend::Analyzer::Analyzer() : tmp_cnt(0), symbol_table()
{
}
// 它接受一个根节点 root，返回一个 IR 程序。这个函数会递归地遍历整棵语法树，并调用一些辅助函数来实现不同类型的语义分析。
ir::Program frontend::Analyzer::get_ir_program(CompUnit *root)
{
    ir::Program program;
    // 遍历节点
    traverse(root, program);
    return program;
}
void frontend::Analyzer::traverse(AstNode *root, ir::Program &program)
{
    switch (root->type)
    {
        // CompUnit -> (Decl | FuncDef) [CompUnit]
        // Decl -> ConstDecl | VarDecl
        // ConstDecl -> 'const' BType ConstDef { ',' ConstDef } ';'
        // VarDecl -> BType VarDef { ',' VarDef } ';'
        // FuncDef -> FuncType Ident '(' [FuncFParams] ')' Block
        // 如果CompUnit第一个孩子是Decl，则是定义常量或者变量
        // 如果CompUnit第一个孩子是FuncDef，则是定义函数
    case NodeType::COMPUNIT:
    {
        // Traverse each declaration or definition in the program
        for (AstNode *child : root->children)
        {
            traverse(child, program);
        }
        break;
    }
    case NodeType::DECL:
    {
        // Traverse each declaration or definition in the program
        for (AstNode *child : root->children)
        {
            traverse(child, program);
        }
        break;
    }
    // FuncDef -> FuncType Ident '(' [FuncFParams] ')' Block
    case NodeType::FUNCDEF:
    {
        // Check the function definition for semantic errors
        GET_CHILD_PTR(node_functype, Term, 0);
        GET_CHILD_PTR(node_ident, Term, 1);
        if (node_functype->token.type == TokenType::INTTK && node_ident->token.value == "main")
        {
            ir::Function mainFunction("main", ir::Type::Int);
            program.addFunction(mainFunction);
        }
        // Traverse the body of the function
        traverse(root->children[2], program);
        break;
    }
    case NodeType::BLOCK:
    {
        // Enter a new scope for the block
        Block *block = dynamic_cast<Block *>(root);
        symbol_table.add_scope(block);
        // Traverse each statement in the block
        for (AstNode *child : root->children)
        {
            traverse(child, program);
        }
        // Exit the scope for the block
        symbol_table.exit_scope();
        break;
    }

    // Stmt -> LVal '=' Exp ';' | Block | 'if' '(' Cond ')' Stmt [ 'else' Stmt ] | 'while' '(' Cond ')' Stmt | 'break' ';' | 'continue' ';' | 'return' [Exp] ';' | [Exp] ';'
    // Exp -> AddExp
    // AddExp -> MulExp { ('+' | '-') MulExp }
    // MulExp -> UnaryExp { ('*' | '/' | '%') UnaryExp }
    // UnaryExp -> PrimaryExp | Ident '(' [FuncRParams] ')' | UnaryOp UnaryExp
    // PrimaryExp -> '(' Exp ')' | LVal | Number
    case NodeType::STMT:
    {
        GET_CHILD_PTR(node_0, Term, 0); // return
        GET_CHILD_PTR(node_1, Term, 1); // exp
        traverse(node_1, program);
    }
    case NodeType::PRIMARYEXP:
    {
        GET_CHILD_PTR(node, Term, 0); // number
        traverse(node, program);
    }
    case NodeType::NUMBER:
    {
        GET_CHILD_PTR(node, Term, 0);
        if (node->token.type == TokenType::INTLTR)
        {
            string value = node->token.value;
            ir::Instruction *returnInst1;
            returnInst1->op1 = ir::Operand(value, ir::Type::IntLiteral);
            returnInst1->op2 = ir::Operand();
            returnInst1->des = ir::Operand();
            returnInst1->op = ir::Operator::_return;
            program.functions.back().addInst(returnInst1);
        }
    }
    // Handle other root types as needed
    default:
        // Traverse each child of the current root
        for (AstNode *child : root->children)
        {
            traverse(child, program);
        }
        break;
    }
}
// FuncDef -> FuncType Ident '(' [FuncFParams] ')' Block
// FuncType -> 'void' | 'int' | 'float'
// void frontend::Analyzer::analysisFuncDef(FuncDef *root, ir::Program &program)
// {
//     // 获取函数返回类型
//     GET_CHILD_PTR(functype, FuncType, 0);
//     Type funcReturnType = getType(functype->type);

//     // 获取函数名
//     Ident *funcName = dynamic_cast<Ident *>(node->children[1]);
//     assert(funcName);
//     std::string functionName = funcName->name;

//     // 获取函数参数列表
//     FuncFParams *funcParams = nullptr;
//     if (node->children.size() > 3)
//     {
//         funcParams = dynamic_cast<FuncFParams *>(node->children[3]);
//     }

//     // 创建函数对象
//     Function *function = new Function(functionName, funcReturnType);

//     // 添加函数参数
//     if (funcParams)
//     {
//         analyzeFuncFParams(funcParams, function);
//     }

//     // 获取函数体
//     Block *functionBlock = dynamic_cast<Block *>(node->children.back());
//     assert(functionBlock);

//     // 进入函数作用域
//     symbol_table.add_scope(functionBlock);

//     // 分析函数体
//     analyzeBlock(functionBlock, program, function);

//     // 退出函数作用域
//     symbol_table.exit_scope();

//     // 将函数添加到程序中
//     program.addFunction(function);
// }
void frontend::Analyzer::analysisCompUnit(CompUnit *root, ir::Program &program) {}
void frontend::Analyzer::analysisDecl(Decl *root, ir::Program &program) {}
void frontend::Analyzer::analysisConstDecl(ConstDecl *root, ir::Program &program) {}
void frontend::Analyzer::analysisBType(BType *root, ir::Program &program) {}
void frontend::Analyzer::analysisConstDef(ConstDef *root, ir::Program &program) {}
void frontend::Analyzer::analysisConstInitVal(ConstInitVal *root, ir::Program &program) {}
void frontend::Analyzer::analysisVarDecl(VarDecl *root, ir::Program &program) {}
void frontend::Analyzer::analysisVarDef(VarDef *root, ir::Program &program) {}
void frontend::Analyzer::analysisInitVal(InitVal *root, ir::Program &program) {}
void frontend::Analyzer::analysisFuncDef(FuncDef *root, ir::Program &program) {}
void frontend::Analyzer::analysisFuncType(FuncType *root, ir::Program &program) {}
void frontend::Analyzer::analysisFuncFParam(FuncFParam *root, ir::Program &program) {}
void frontend::Analyzer::analysisFuncFParams(FuncFParams *root, ir::Program &program) {}
void frontend::Analyzer::analysisBlock(Block *root, ir::Program &program) {}
void frontend::Analyzer::analysisBlockItem(BlockItem *root, ir::Program &program) {}
void frontend::Analyzer::analysisStmt(Stmt *root, ir::Program &program) {}
void frontend::Analyzer::analysisExp(Exp *root, ir::Program &program) {}
void frontend::Analyzer::analysisCond(Cond *root, ir::Program &program) {}
void frontend::Analyzer::analysisLVal(LVal *root, ir::Program &program) {}
void frontend::Analyzer::analysisNumber(Number *root, ir::Program &program) {}
void frontend::Analyzer::analysisPrimaryExp(PrimaryExp *root, ir::Program &program) {}
void frontend::Analyzer::analysisUnaryExp(UnaryExp *root, ir::Program &program) {}
void frontend::Analyzer::analysisUnaryOp(UnaryOp *root, ir::Program &program) {}
void frontend::Analyzer::analysisFuncRParams(FuncRParams *root, ir::Program &program) {}
void frontend::Analyzer::analysisMulExp(MulExp *root, ir::Program &program) {}
void frontend::Analyzer::analysisAddExp(AddExp *root, ir::Program &program) {}
void frontend::Analyzer::analysisRelExp(RelExp *root, ir::Program &program) {}
void frontend::Analyzer::analysisEqExp(EqExp *root, ir::Program &program) {}
void frontend::Analyzer::analysisLAndExp(LAndExp *root, ir::Program &program) {}
void frontend::Analyzer::analysisLOrExp(LOrExp *root, ir::Program &program) {}
void frontend::Analyzer::analysisConstExp(ConstExp *root, ir::Program &program) {}
