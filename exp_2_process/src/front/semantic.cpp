#include "front/semantic.h"

#include <cassert>
#define DEBUG_SEMANTIC
#define DEBUG_RESULT
using ir::Function;
using ir::Instruction;
using ir::Operand;
using ir::Operator;

using namespace std;
#include <iostream>

#define TODO assert(0 && "TODO");

#define GET_CHILD_PTR(node, type, index)                     \
    auto node = dynamic_cast<type *>(root->children[index]); \
    assert(node);
#define ANALYSIS(node, type, index)                          \
    auto node = dynamic_cast<type *>(root->children[index]); \
    assert(node);                                            \
    analysis##type(node, program);
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
// 进入新作用域时, 向符号表中添加 ScopeInfo, 相当于压栈
// struct ScopeInfo
// {
//     int cnt;
//     string name;
//     map_str_ste table;
// };
// cnt 是作用域在函数中的唯一编号, 代表是函数中出现的第几个作用域
// name 可以用来分辨作用域的类别, 'b' 代表是一个单独嵌套的作用域, 'i' 'e' 'w' 分别代表由 if else while 产生的新作用域（你也可以取你喜欢的名字，只是这样会表意比较清晰）
// table 是一张存放符号的表, {string: STE}, string 是操作数的原始名称, 表项 Variable Table Entry(STE), 实际上就是一个 IR 的操作数，即 STE -> Operand, 在 STE 中存放的应该是变量重命名后的名称
// map_str_ste = map<string, STE>;
// struct STE
// {
//     ir::Operand operand;
//     vector<int> dimension;
// };
void frontend::SymbolTable::add_scope(Block *node)
{
#ifdef DEBUG_SEMANTIC
    cout << "add_scope" << endl;
#endif

    ScopeInfo scope_info;                                                  // 生成一个新的作用域
    scope_info.cnt = scope_stack.empty() ? 0 : scope_stack.back().cnt + 1; // 得到新的作用域的cnt
    scope_info.name = "block_" + node->v + std::to_string(scope_info.cnt); // 得到新的作用域的name为"block_类型_编号"
    // 在翻译成 IR 的过程中我们需要解决不通过作用域中同名变量的问题, 我们的解决方案是重命名, 为变量名加上与作用域相关的后缀使得重命名之后的变量名字在一个 IR Function 中是独一无二的
    if (scope_stack.empty())
    {
#ifdef DEBUG_SEMANTIC
        cout << "scope_stack is empty" << endl;
#endif
    }
    else
    {
        for (auto &&item : scope_stack.back().table) // 将之前作用域的变量名重新命名，以便于在不同的作用域中识别同名的变量。
        {
            string new_name = get_scoped_name(item.first);
            STE new_ste = item.second;
            scope_info.table.insert(std::make_pair(new_name, new_ste));
        }
    }
    scope_stack.push_back(scope_info); // 将新的作用域压入作用域栈
}
// 这个函数的作用是退出当前作用域，在符号表中删除当前作用域对应的内容。
void frontend::SymbolTable::exit_scope()
{
    scope_stack.pop_back();
}
// 这个函数的作用是根据一个标识符 id 获取它在符号表中的作用域限定名。例如，如果 id 是 "x"，而在当前作用域中已经有了一个同名变量，则返回 "scope_x"。
// 输入一个变量名, 返回其在当前作用域下重命名后的名字 (相当于加后缀)
// 在翻译成 IR 的过程中我们需要解决不通过作用域中同名变量的问题, 我们的解决方案是重命名, 为变量名加上与作用域相关的后缀使得重命名之后的变量名字在一个 IR Function 中是独一无二的
string frontend::SymbolTable::get_scoped_name(string id) const
{
    const auto &current_scope = scope_stack.back(); // 当前作用域
    if (current_scope.table.find(id) != current_scope.table.end())
    {
        return "scope_" + std::to_string(current_scope.cnt) + "_" + id;
    }
    else
    {
        return id + "_scope_" + std::to_string(current_scope.cnt); // 第一次出现时
    }
}
// 这个函数的作用是根据一个标识符 id 获取它对应的操作数。如果这个标识符是一个变量，则返回一个寄存器或栈上的位置，如果是一个常量，则返回它的值。
// 在当前作用域查找这个标识符是否已经定义，如果已经定义，则返回它的操作数。
// 如果当前作用域没有定义这个标识符，则递归地在外层作用域中查找，直到找到或者到全局作用域为止。
// 如果全局作用域也没有定义这个标识符，则说明这是一个未声明的标识符，需要报错并返回一个错误的操作数。
// 输入一个变量名, 在符号表中寻找最近的同名变量, 返回对应的 Operand(注意，此 Operand 的 name 是重命名后的)
Operand frontend::SymbolTable::get_operand(string id) const
{
    const auto &current_scope = scope_stack.back(); // 当前作用域
    auto it = current_scope.table.find(id);         // 当前作用域查找id

    // // 找到标识符在当前作用域中定义
    // if (it != current_scope.table.end())
    // {
    //     return it->second.operand;
    // }
    // // 标识符在当前作用域中未定义，需要在外层作用域中查找
    // else
    // {
    //     // rbegin()是容器的成员函数，返回一个反向迭代器，指向容器中的最后一个元素。
    //     // rend()是容器的成员函数，返回一个反向迭代器，指向容器中的第一个元素之前的位置。
    //     // 这段代码的作用是从倒数第二个作用域开始向前遍历作用域栈中的元素，以查找符号表中的标识符。它排除了最后一个作用域，即当前作用域。
    //     for (auto it = scope_stack.rbegin() + 1; it != scope_stack.rend(); ++it)
    //     {
    //         auto it2 = it->table.find(id);
    //         // 找到标识符在该作用域中定义
    //         if (it2 != it->table.end())
    //         { // 找到了定义，生成新的操作数并返回
    //             Operand new_operand;
    //             new_operand.type = it2->second.operand.type;
    //             return new_operand;
    //         }
    //     }
    //     // 标识符未定义
    //     return Operand();
    // }

    // rbegin()是容器的成员函数，返回一个反向迭代器，指向容器中的最后一个元素。
    // rend()是容器的成员函数，返回一个反向迭代器，指向容器中的第一个元素之前的位置。
    // 这段代码的作用是从最后一个作用域开始向前遍历作用域栈中的元素，以查找符号表中的标识符。它排除了最后一个作用域，即当前作用域。
    for (auto it = scope_stack.rbegin(); it != scope_stack.rend(); ++it)
    {
        auto iter = it->table.find(id);
        // 找到标识符在该作用域中定义
        if (iter != it->table.end())
        { // 找到了定义，生成新的操作数并返回
            return iter->second.operand;
        }
    }
    // 标识符未定义
    return Operand();
}
// 这个函数的作用是根据一个标识符 id 获取它在符号表中对应的符号表项。
// 输入一个变量名, 在符号表中寻找最近的同名变量, 返回 STE
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
    // 标识符STE
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

    // 添加全局函数
    Function globalFunc("global", Type::null);
    program.addFunction(globalFunc);

    // 遍历节点
    analysisCompUnit(root, program);

    return program;
}
// CompUnit -> (Decl | FuncDef) [CompUnit]
void frontend::Analyzer::analysisCompUnit(CompUnit *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin compunit" << endl;
#endif
    // 根据观察，CompUnit的第一个孩子节点是Decl只能是全局赋值语句，第一个孩子节点是FuncDef只能是函数定义
    if (root->children[0]->type == NodeType::DECL)
    {
        // Decl -> ConstDecl | VarDecl
        // ConstDecl -> 'const' BType ConstDef { ',' ConstDef } ';'
        // VarDecl -> BType VarDef { ',' VarDef } ';'
        ANALYSIS(decl, Decl, 0);
        int len = root->children.size();
        int index = 1;
        if (index < len)
        {
            ANALYSIS(compunit, CompUnit, 1);
        }
        else
        {
            COPY_EXP_NODE(root, decl);
        }
    }
    else
    {
        // FuncDef -> FuncType Ident '(' [FuncFParams] ')' Block
        Function funcFunc;
        program.addFunction(funcFunc);

        ANALYSIS(funcdef, FuncDef, 0);

        program.functions.back().name = funcdef->v;

        program.functions.back().returnType = funcdef->t;

        int len = root->children.size();
        int index = 1;
        if (index < len)
        {
            ANALYSIS(compunit, CompUnit, 1);
        }
        else
        {
            COPY_EXP_NODE(root, funcdef);
        }
    }
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// Decl -> ConstDecl | VarDecl
void frontend::Analyzer::analysisDecl(Decl *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin decl" << endl;
#endif
    if (root->children[0]->type == NodeType::CONSTDECL)
    {
        ANALYSIS(constdecl, ConstDecl, 0)
    }
    else
    {
        ANALYSIS(vardecl, VarDecl, 0)
    }
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// ConstDecl -> 'const' BType ConstDef { ',' ConstDef } ';'
void frontend::Analyzer::analysisConstDecl(ConstDecl *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin constdecl" << endl;
#endif
    ANALYSIS(btype, BType, 1);
    ANALYSIS(constdef, ConstDef, 2);
    int len = root->children.size();
    int index = 3;

    while (index < len && root->children[index]->token.type == TokenType::COMMA)
    {
        index++;
        ANALYSIS(constdef, ConstDef, index);
        index++;
    }
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// BType -> 'int' | 'float'
void frontend::Analyzer::analysisBType(BType *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin btype" << endl;
#endif
    if (root->children[0]->token.type == TokenType::INTTK)
    {
        root->t = Type::Int;
    }
    else
    {
        root->t = Type::Float;
    }
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// ConstDef -> Ident { '[' ConstExp ']' } '=' ConstInitVal
void frontend::Analyzer::analysisConstDef(ConstDef *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin constdef" << endl;
#endif
    string id = symbol_table.get_scoped_name(root->children[0]->token.value);
    int len = root->children.size();
    int index = 1;
    while (index < len && root->children[index]->token.type == TokenType::LBRACK)
    {
        index++;
        ANALYSIS(constexp, ConstExp, index);
        index = index + 2;
    }
    index++;
    ANALYSIS(constinitval, ConstInitVal, index);
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// ConstInitVal -> ConstExp | '{' [ ConstInitVal { ',' ConstInitVal } ] '}'
void frontend::Analyzer::analysisConstInitVal(ConstInitVal *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin constinitval" << endl;
#endif
    int len = root->children.size();
    if (root->children[0]->type == NodeType::CONSTEXP)
    {
        ANALYSIS(constexp, ConstExp, 0);
    }
    else
    {
        if (root->children[1]->type == NodeType::CONSTINITVAL)
        {
            ANALYSIS(constinitval, ConstInitVal, 1);
            int index = 2;
            while (index < len && root->children[index]->token.type == TokenType::COMMA)
            {
                index++;
                ANALYSIS(constinitval, ConstInitVal, index);
                index++;
            }
        }
    }
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// VarDecl -> BType VarDef { ',' VarDef } ';'
void frontend::Analyzer::analysisVarDecl(VarDecl *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin vardecl" << endl;
#endif
    int len = root->children.size();
    ANALYSIS(btype, BType, 0);
    ANALYSIS(vardef, VarDef, 1);
    int index = 2;
    while (index < len && root->children[index]->token.type == TokenType::COMMA)
    {
        index++;
        ANALYSIS(vardef, VarDef, index);
        index++;
    }
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// VarDef -> Ident { '[' ConstExp ']' } [ '=' InitVal ]
void frontend::Analyzer::analysisVarDef(VarDef *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin vardef" << endl;
#endif
    int len = root->children.size();
    int index = 1;

    while (index < len && root->children[index]->token.type == TokenType::LBRACK)
    {
        index++;
        ANALYSIS(constexp, ConstExp, index);
        index = index + 2;
    }
    if (index < len && root->children[index]->token.type == TokenType::ASSIGN)
    {
        index++;
        ANALYSIS(initval, InitVal, index);
    }
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// InitVal -> Exp | '{' [ InitVal { ',' InitVal } ] '}'
void frontend::Analyzer::analysisInitVal(InitVal *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin initval" << endl;
#endif
    int len = root->children.size();
    if (root->children[0]->type == NodeType::EXP)
    {
        ANALYSIS(exp, Exp, 0);
    }
    else
    {
        if (root->children[1]->type == NodeType::INITVAL)
        {
            int index = 2;
            while (index < len && root->children[index]->token.type == TokenType::COMMA)
            {
                index++;
                ANALYSIS(initval, InitVal, index);
                index++;
            }
        }
    }
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// FuncDef -> FuncType Ident '(' [FuncFParams] ')' Block
void frontend::Analyzer::analysisFuncDef(FuncDef *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin funcdef" << endl;
#endif
    ANALYSIS(functype, FuncType, 0);
    GET_CHILD_PTR(ident, Term, 1);

    root->t = functype->t;
    root->v = ident->token.value;
    root->is_computable = false;

    if (root->children[3]->type == NodeType::FUNCFPARAMS)
    {
        ANALYSIS(funcfparams, FuncFParams, 3);
        ANALYSIS(block, Block, 5);
    }
    else
    {
        ANALYSIS(block, Block, 4);
    }
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// FuncType -> 'void' | 'int' | 'float'
void frontend::Analyzer::analysisFuncType(FuncType *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin functype" << endl;
#endif
    if (root->token.type == TokenType::VOIDTK)
    {
        root->t = Type::null;
    }
    else if (root->token.type == TokenType::INTTK)
    {
        root->t = Type::Int;
    }
    else
    {
        root->t = Type::Float;
    }
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// FuncFParam -> BType Ident ['[' ']' { '[' Exp ']' }]
void frontend::Analyzer::analysisFuncFParam(FuncFParam *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin funcfparam" << endl;
#endif
    ANALYSIS(btype, BType, 0);
    int len = root->children.size();
    int index = 4;
    while (index < len && root->children[index]->token.type == TokenType::LBRACK)
    {
        index++;
        ANALYSIS(exp, Exp, index);
        index = index + 2;
    }
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// FuncFParams -> FuncFParam { ',' FuncFParam }
void frontend::Analyzer::analysisFuncFParams(FuncFParams *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin funcfparams" << endl;
#endif
    ANALYSIS(funcfparam, FuncFParam, 0);
    int len = root->children.size();
    int index = 1;
    while (index < len && root->children[index]->token.type == TokenType::COMMA)
    {
        index++;
        ANALYSIS(initval, InitVal, index);
        index++;
    }
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// Block -> '{' { BlockItem } '}'
// BlockItem -> Decl | Stmt
void frontend::Analyzer::analysisBlock(Block *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin block" << endl;
#endif
    root->v = "block";
    // 在 Sysy 中, 作用域是由 Block 决定的
    // 进入新作用域时, 向符号表中添加 ScopeInfo, 相当于压栈
    symbol_table.add_scope(root);
    int len = root->children.size();
    int index = 1;
    while (index < len && root->children[index]->type == NodeType::BLOCKITEM)
    {
        ANALYSIS(blockitem, BlockItem, index);
        index++;
    }
    // 函数定义结束时，函数内部的作用域会退出。在函数定义结束后，函数内部的变量将不再可见。
    symbol_table.exit_scope();
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// BlockItem -> Decl | Stmt
void frontend::Analyzer::analysisBlockItem(BlockItem *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin blockitem" << endl;
#endif
    if (root->children[0]->type == NodeType::DECL)
    {
        ANALYSIS(decl, Decl, 0);
    }
    else
    {
        ANALYSIS(stmt, Stmt, 0);
    }
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// Stmt -> LVal '=' Exp ';'                        |
//         Block                                   |
//         'if' '(' Cond ')' Stmt [ 'else' Stmt ]  |
//         'while' '(' Cond ')' Stmt               |
//         'break' ';'                             |
//         'continue' ';'                          |
//         'return' [Exp] ';'                      |
//         [Exp] ';'
void frontend::Analyzer::analysisStmt(Stmt *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin stmt" << endl;
#endif
    if (root->children[0]->type == NodeType::LVAL)
    {
        ANALYSIS(lval, LVal, 0);
        ANALYSIS(exp, Exp, 2);
    }
    else if (root->children[0]->type == NodeType::BLOCK)
    {
        ANALYSIS(block, Block, 0);
        COPY_EXP_NODE(block, root);
    }
    else if (root->children[0]->type == NodeType::EXP)
    {
        ANALYSIS(exp, Exp, 0);
        COPY_EXP_NODE(exp, root);
    }
    else
    {
        GET_CHILD_PTR(ident, Term, 0);
        if (ident->token.type == TokenType::IFTK)
        {
            ANALYSIS(cond, Cond, 2);
            ANALYSIS(stmt, Stmt, 4);
            int len = root->children.size();
            int index = 5;
            if (index < len)
            {
                ANALYSIS(stmt_right, Stmt, 6);
            }
        }
        else if (ident->token.type == TokenType::WHILETK)
        {
            ANALYSIS(cond, Cond, 2);
            ANALYSIS(stmt, Stmt, 4);
        }
        else if (ident->token.type == TokenType::BREAKTK)
        {
        }
        else if (ident->token.type == TokenType::CONTINUETK)
        {
        }
        else if (ident->token.type == TokenType::RETURNTK)
        {
            cout << "add inst: returnInst begin" << endl;
            int len = root->children.size();
            int index = 1;
            if (index < len)
            {
                cout << "return sth" << endl;
                ANALYSIS(exp, Exp, 1);
                COPY_EXP_NODE(exp, root);
                if (exp->is_computable)
                {
                    Operand op1(exp->v, exp->t);
                    Instruction *returnInst = new Instruction(op1,
                                                              ir::Operand(),
                                                              ir::Operand(),
                                                              ir::Operator::_return);
                    program.functions.back().addInst(returnInst);
                    cout << "add inst: returnInst" << endl;
                }
            }
            else
            {
                Instruction *returnInst = new Instruction(ir::Operand(),
                                                          ir::Operand(),
                                                          ir::Operand(),
                                                          ir::Operator::_return);
                program.functions.back().addInst(returnInst);
                cout << "add inst: returnInst 0" << endl;
            }
        }
        else
        {
        }
    }
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// Exp -> AddExp
void frontend::Analyzer::analysisExp(Exp *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin exp" << endl;
#endif
    ANALYSIS(addexp, AddExp, 0);
    COPY_EXP_NODE(addexp, root);
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// Cond -> LOrExp
void frontend::Analyzer::analysisCond(Cond *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin cond" << endl;
#endif
    ANALYSIS(lorexp, LOrExp, 0);
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// LVal -> Ident {'[' Exp ']'}
void frontend::Analyzer::analysisLVal(LVal *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin lval" << endl;
#endif
    int len = root->children.size();
    int index = 1;

    while (index < len && root->children[index]->token.type == TokenType::LBRACK)
    {
        index++;
        ANALYSIS(exp, Exp, index);
        index = index + 2;
    }
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// Number -> IntConst | floatConst
void frontend::Analyzer::analysisNumber(Number *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin number" << endl;
#endif
    GET_CHILD_PTR(i_or_f, Term, 0);
    if (i_or_f->token.type == TokenType::INTLTR)
    {
        root->t = Type::IntLiteral;
        root->v = i_or_f->token.value;
        root->is_computable = true;
    }
    else
    {
        root->t = Type::FloatLiteral;
        root->v = i_or_f->token.value;
        root->is_computable = true;
    }
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// PrimaryExp -> '(' Exp ')' | LVal | Number
void frontend::Analyzer::analysisPrimaryExp(PrimaryExp *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin primaryexp" << endl;
#endif
    if (root->children[0]->type == NodeType::LVAL)
    {
        ANALYSIS(lval, LVal, 0);
    }
    else if (root->children[0]->type == NodeType::NUMBER)
    {
        ANALYSIS(number, Number, 0);
        COPY_EXP_NODE(number, root);
    }
    else
    {
        ANALYSIS(exp, Exp, 1);
    }
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// UnaryExp -> PrimaryExp | Ident '(' [FuncRParams] ')' | UnaryOp UnaryExp
void frontend::Analyzer::analysisUnaryExp(UnaryExp *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin unaryexp" << endl;
#endif
    if (root->children[0]->type == NodeType::PRIMARYEXP)
    {
        ANALYSIS(primaryexp, PrimaryExp, 0);
        COPY_EXP_NODE(primaryexp, root);
    }

    else if (root->children[0]->type == NodeType::UNARYOP)
    {
        ANALYSIS(unaryop, UnaryOp, 0);
        ANALYSIS(unaryexp, UnaryExp, 1);
    }
    else
    {
        int len = root->children.size();
        int index = 2;
        if (index < len)
        {
            ANALYSIS(funcrparams, FuncRParams, 2);
        }
    }
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// UnaryOp -> '+' | '-' | '!'
void frontend::Analyzer::analysisUnaryOp(UnaryOp *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin unaryop" << endl;
#endif
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// FuncRParams -> Exp { ',' Exp }
void frontend::Analyzer::analysisFuncRParams(FuncRParams *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin funcrparams" << endl;
#endif
    ANALYSIS(exp, Exp, 0);
    int len = root->children.size();
    int index = 1;
    while (index < len)
    {
        index++;
        ANALYSIS(exp, Exp, index);
        index++;
    }
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// MulExp -> UnaryExp { ('\*' | '/' | '%') UnaryExp }
void frontend::Analyzer::analysisMulExp(MulExp *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin mulexp" << endl;
#endif
    ANALYSIS(unaryexp, UnaryExp, 0);
    COPY_EXP_NODE(unaryexp, root);
    int len = root->children.size();
    int index = 1;
    while (index < len)
    {
        index++;
        ANALYSIS(unaryexp, UnaryExp, index);
        index++;
    }
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// AddExp -> MulExp { ('+' | '-') MulExp }
void frontend::Analyzer::analysisAddExp(AddExp *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin addexp" << endl;
#endif
    ANALYSIS(mulexp, MulExp, 0);
    COPY_EXP_NODE(mulexp, root);
    int len = root->children.size();
    int index = 1;
    while (index < len)
    {
        index++;
        ANALYSIS(mulexp, MulExp, index);
        index++;
    }
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// RelExp -> AddExp { ('<' | '>' | '<=' | '>=') AddExp }
void frontend::Analyzer::analysisRelExp(RelExp *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin relexp" << endl;
#endif
    ANALYSIS(addexp, AddExp, 0);
    int len = root->children.size();
    int index = 1;
    while (index < len)
    {
        index++;
        ANALYSIS(addexp_right, AddExp, index);
        index++;
    }
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// EqExp -> RelExp { ('==' | '!=') RelExp }
void frontend::Analyzer::analysisEqExp(EqExp *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin eqexp" << endl;
#endif
    ANALYSIS(relexp, RelExp, 0);
    int len = root->children.size();
    int index = 1;
    while (index < len)
    {
        index++;
        ANALYSIS(relexp_right, RelExp, index);
        index++;
    }
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// LAndExp -> EqExp [ '&&' LAndExp ]
void frontend::Analyzer::analysisLAndExp(LAndExp *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin landexp" << endl;
#endif
    ANALYSIS(eqexp, EqExp, 0);
    if (root->children.size() == 3)
    {
        ANALYSIS(landexp, LAndExp, 2);
    }
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// LOrExp -> LAndExp [ '||' LOrExp ]
void frontend::Analyzer::analysisLOrExp(LOrExp *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin lorexp" << endl;
#endif
    string name = "lorexp";
    name = symbol_table.get_scoped_name(name);
    Operand des(name, Type::Int);
    ANALYSIS(landexp, LAndExp, 0);
    Operand op1 = symbol_table.get_operand(landexp->v);
    if (root->children.size() == 3)
    {
        ANALYSIS(lorexp, LOrExp, 2);
        Operand op2 = symbol_table.get_operand(lorexp->v);
        Instruction instruction(op1, op2, des, Operator::eq);
    }
    else
    {
        COPY_EXP_NODE(root->children[0], root);
    }
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
// ConstExp -> AddExp
void frontend::Analyzer::analysisConstExp(ConstExp *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin constexp" << endl;
#endif
    ANALYSIS(addexp, AddExp, 0);
    COPY_EXP_NODE(root->children[0], root);
#ifdef DEBUG_RESULT
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << endl;
#endif
}
