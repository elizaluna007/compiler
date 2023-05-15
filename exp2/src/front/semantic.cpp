#include "front/semantic.h"

#include <cassert>
#define DEBUG_SEMANTIC 1
#define DEBUG_RESULT 1
using ir::Function;
using ir::Instruction;
using ir::Operand;
using ir::Operator;

using namespace std;
#include <iostream>

int calculateIndex(const std::vector<int> &dimension, const std::vector<int> &indices)
{
    int numDimensions = dimension.size();
    int index = 0;
    int multiplier = 1;

    // 从最后一个维度开始，计算索引值
    for (int i = numDimensions - 1; i >= 0; --i)
    {
        int currentIndex = indices[i];
        index += currentIndex * multiplier;
        multiplier *= dimension[i];
    }

    return index;
}
// 计数器，用来标识中间的值
int counter = 0;
// pc位置
int pc = 0;
// 用来存放所有的指令
vector<Instruction *> Inst;
// 用来暂存function
Function function_temp;
ir::CallInst *callInst_temp;
// 用来存放需要中断的语句进行更新
vector<int> break_pc;
int origin;
int destination;

#define TODO assert(0 && "TODO");

#define GET_CHILD_PTR(node_ptr, type, index)                      \
    type *node_ptr = dynamic_cast<type *>(root->children[index]); \
    assert(node_ptr);
#define ANALYSIS(node, type, index)                           \
    type *node = dynamic_cast<type *>(root->children[index]); \
    assert(node);                                             \
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
    if (scope_stack.empty())
    {
        cout << "get scoped name end    " << id << endl;
        return id;
    }
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
    return Operand(id);
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
    // Function globalFunc("global", Type::null);
    // program.addFunction(globalFunc);
    // cout << "add func "
    //      << "global"
    //      << " " << toString(Type::null) << "  in program" << endl;
    function_temp = Function("global", Type::null);

    // 添加全局作用域
    ScopeInfo scope_info;       // 生成一个新的作用域
    scope_info.cnt = 0;         // 得到新的作用域的cnt
    scope_info.name = "global"; // 得到新的作用域的name
    symbol_table.scope_stack.push_back(scope_info);
    cout << "add scope_info " << symbol_table.scope_stack.back().name << " in symbol table" << endl;

    // 遍历节点
    analysisCompUnit(root, program);

    // 添加全局变量
    for (auto &iter : symbol_table.scope_stack[0].table)
    {
        program.globalVal.push_back(iter.second.operand);
    }

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
        // 在新的函数定义之前
        if (function_temp.name == "global")
        {
            Instruction *globalreturn = new Instruction(ir::Operand(),
                                                        ir::Operand(),
                                                        ir::Operand(), ir::Operator::_return);
            Inst.push_back(globalreturn);
            pc++;

            program.addFunction(function_temp);
            function_temp = Function();
            cout << "add func "
                 << "global"
                 << " " << toString(Type::null) << "  in program" << endl;

            for (int q = 0; q < pc; q++)
            {
                program.functions.back().addInst(Inst[q]);

                cout << "pc is " << q << " , add Instruction " << toString(Inst[q]->op) << " in program " << function_temp.name << endl;
            }

            cout << "add return" << endl;
        }
        // FuncDef -> FuncType Ident '(' [FuncFParams] ')' Block
        function_temp = Function(); // 清零
        int pc_old = pc;
        cout << "***************************1*********************" << endl;
        for (int i = 0; i < function_temp.ParameterList.size(); i++)
        {
            cout << "param is " << toString(function_temp.ParameterList[i].type) << "  " << function_temp.ParameterList[i].name << endl;
        }
        ANALYSIS(funcdef, FuncDef, 0);
        int pc_new = pc;
        cout << "***************************2*********************" << endl;
        for (int i = 0; i < function_temp.ParameterList.size(); i++)
        {
            cout << "param is " << toString(function_temp.ParameterList[i].type) << "  " << function_temp.ParameterList[i].name << endl;
        }

        function_temp.name = funcdef->v;
        function_temp.returnType = funcdef->t;
        program.addFunction(function_temp);
        cout << "***************************3*********************" << endl;
        cout << "add func " << toString(funcdef->t) << " " << funcdef->v << "  in program" << endl;
        for (int i = 0; i < function_temp.ParameterList.size(); i++)
        {
            cout << function_temp.name << " param is " << toString(function_temp.ParameterList[i].type) << "  " << function_temp.ParameterList[i].name << endl;
        }

        for (int q = pc_old; q < pc_new; q++)
        {
            program.functions.back().addInst(Inst[q]);

            cout << "pc is " << q << " , add Instruction " << toString(Inst[q]->op) << " in program " << function_temp.name << endl;
        }
        function_temp = Function();

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
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
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
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
#endif
}
// ConstDecl -> 'const' BType ConstDef { ',' ConstDef } ';'
void frontend::Analyzer::analysisConstDecl(ConstDecl *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin constdecl" << endl;
#endif
    ANALYSIS(btype, BType, 1);
    // des的type先定义好
    Operand des("0", btype->t); // 目的未知,类型已知
    Operand op1;
    if (btype->t == Type::Int)
    {
        op1.name = "0";
        op1.type = Type::IntLiteral;
        des.type = Type::Int;
    }
    else
    {
        op1.name = "";
        op1.type = Type::FloatLiteral;
        des.type = Type::Float;
    }
    Instruction *assignInst = new Instruction(op1,
                                              ir::Operand(),
                                              des,
                                              ir::Operator::def);
    Inst.push_back(assignInst);
    pc++;

    cout << "add def" << endl;

    ANALYSIS(constdef, ConstDef, 2);

    int len = root->children.size();
    int index = 3;
    GET_CHILD_PTR(c_or_s, Term, index);
    while (index < len && c_or_s->token.type == TokenType::COMMA)
    {
        Instruction *assignInst = new Instruction(op1,
                                                  ir::Operand(),
                                                  des,
                                                  ir::Operator::def);
        Inst.push_back(assignInst);
        pc++;

        cout << "add def" << endl;

        index++;
        ANALYSIS(constdef, ConstDef, index);
        index++;
        if (index < len - 1)
        {
            cout << "index: " << index << endl;
            cout << "len: " << len << endl;
            GET_CHILD_PTR(term, Term, index);
        }
        else
        {
            break;
        }
    }
#ifdef DEBUG_RESULT
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
#endif
}
// BType -> 'int' | 'float'
void frontend::Analyzer::analysisBType(BType *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin btype" << endl;
#endif
    GET_CHILD_PTR(i_or_f, Term, 0);
    if (i_or_f->token.type == TokenType::INTTK)
    {
        root->t = Type::Int;
    }
    else
    {
        root->t = Type::Float;
    }
#ifdef DEBUG_RESULT
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
#endif
}
// ConstDef -> Ident { '[' ConstExp ']' } '=' ConstInitVal
void frontend::Analyzer::analysisConstDef(ConstDef *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin constdef" << endl;
#endif
    string id = "t" + to_string(counter);
    counter++;
    int len = root->children.size();
    int index = 0;
    GET_CHILD_PTR(ident, Term, index);
    Inst.back()->des.name = ident->token.value;
    // while (index < len && term->token.type == TokenType::LBRACK)
    // {
    //     index++;
    //     ANALYSIS(constexp, ConstExp, index);
    //     index = index + 2;
    //     GET_CHILD_PTR(term, Term, index);
    //     if (term->token.type == TokenType::ASSIGN)
    //     {
    //         break;
    //     }
    // }
    // index++;
    // ANALYSIS(constinitval, ConstInitVal, index);
    index = 1;
    GET_CHILD_PTR(term, Term, index);
    GET_CHILD_PTR(l_or_a, Term, index);
    // 是数组，需要改变des的type
    if (index < len - 2 && l_or_a->token.type == TokenType::LBRACK)
    {
        Type t = Inst.back()->des.type;
        if (t == Type::Int)
        {
            Inst.back()->op1.type = Type::Int;
            Inst.back()->des.type = Type::IntPtr;
        }

        else
        {
            Inst.back()->op1.type = Type::Float;
            Inst.back()->des.type = Type::FloatPtr;
        }

        Inst.back()->op = ir::Operator::alloc;

        cout << "add alloc" << endl;

        vector<int> dim;
        string arr_len;

        int key = 1;
        while (index < len - 2 && l_or_a->token.type == TokenType::LBRACK)
        {
            // op1的name和type
            index++;
            ANALYSIS(constexp, ConstExp, index);
            if (!constexp->is_computable)
            {
                key = 0;
                arr_len = constexp->v;
            }
            else
            {
                dim.push_back(std::stoi(constexp->v));
                index = index + 2;
                if (index < len)
                {
                    GET_CHILD_PTR(l_or_a, Term, index);
                    if (l_or_a->token.type == TokenType::ASSIGN)
                    {
                        key = 2;
                        break;
                    }
                }
            }
        }
        if (key)
        {
            int all = 1;
            for (int i = 0; i < dim.size(); i++)
            {
                all *= dim[i];
            }
            Inst.back()->op1.name = to_string(all);
            Inst.back()->op1.type = Type::IntLiteral;

            cout << all << "           " << toString(Inst.back()->op) << endl;

            Operand op = Inst.back()->des;
            STE ste;
            ste.operand = op;
            ste.dimension = dim;

            symbol_table.scope_stack.back().table[op.name] = ste;

            cout << "add  " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
        }
        else
        {
            Inst.back()->op1.name = arr_len;

            cout << arr_len << "           " << toString(Inst.back()->op) << endl;

            Operand op = Inst.back()->des;
            STE ste;
            ste.operand = op;
            ste.dimension = dim;

            symbol_table.scope_stack.back().table[op.name] = ste;

            cout << "add  " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
        }

        // 数组且赋值
        // 存数指令，指向数组中存数。第一个操作数为数组名，第二个操作数为要存数所在数组下标，目的操作数为存入的数。
        if (key == 2)
        {
            index++;
            ANALYSIS(constinitval, ConstInitVal, index);
            index++;
        }
    }
    // 不是数组，那就一定是赋值
    else
    {
        // 这里考虑到赋值的时候后面可能是先存在的值，故对原本指令备份，重新填入
        Instruction *old_inst = Inst.back();
        Inst.pop_back();
        pc--;

        index++;
        ANALYSIS(constinitval, ConstInitVal, index);
        old_inst->op1.name = constinitval->v;
        old_inst->op1.type = constinitval->t;
        cout << "constinitval  " << toString(constinitval->t) << "  " << constinitval->v << endl;

        Inst.push_back(old_inst);
        pc++;

        Operand op = Inst.back()->des;
        STE ste;
        ste.operand = op;
        symbol_table.scope_stack.back().table[op.name] = ste;
        cout << "add  " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
    }

#ifdef DEBUG_RESULT
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
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
        COPY_EXP_NODE(constexp, root);
    }
    else
    {
        Operand des = Inst.back()->des;
        if (root->children[1]->type == NodeType::CONSTINITVAL)
        {
            // ANALYSIS(constinitval, ConstInitVal, 1);
            // int index = 2;
            // while (index < len && root->children[index]->token.type == TokenType::COMMA)
            // {
            //     index++;
            //     ANALYSIS(constinitval, ConstInitVal, index);
            //     index++;
            // }
            // 存数指令，指向数组中存数。第一个操作数为数组名，第二个操作数为要存数所在数组下标，目的操作数为存入的数
            Operand op1 = des;
            int all = 1;
            STE ste = symbol_table.get_ste(op1.name);
            for (int i = 0; i < ste.dimension.size(); i++)
            {
                all *= ste.dimension[i];
            }
            int index = 0;
            for (int i = 0; i < all; i++)
            {
                Operand op2;
                op2.name = to_string(i);
                op2.type = Type::IntLiteral;
                index++;
                ANALYSIS(constinitval, ConstInitVal, index);
                index++;

                Operand des(constinitval->v, constinitval->t);

                cout << "------------------" << op1.name << "   " << toString(op1.type) << " " << op2.name << " " << toString(des.type) << "   " << des.name << endl;
                Instruction *storeInst = new Instruction(op1,
                                                         op2,
                                                         des,
                                                         ir::Operator::store);

                Inst.push_back(storeInst);
                pc++;

                if (!constinitval->is_computable)
                {
                    STE ste_add;
                    Operand op_add = des;
                    ste_add.operand = op_add;

                    cout << "op add is            " << op_add.name << endl;
                    auto it = symbol_table.scope_stack.back().table.find(op_add.name);
                    if (it != symbol_table.scope_stack.back().table.end())
                    {
                        symbol_table.scope_stack.back().table[op_add.name] = ste_add;
                    }
                    else
                    {
                        symbol_table.scope_stack.back().table.insert({op_add.name, ste_add});
                    }
                }
            }
        }
        else
        {
            root->v = "0";
            root->t = Type::null;
        }
    }
#ifdef DEBUG_RESULT
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
#endif
}
// VarDecl -> BType VarDef { ',' VarDef } ';'
void frontend::Analyzer::analysisVarDecl(VarDecl *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin vardecl" << endl;
#endif
    ANALYSIS(btype, BType, 0);
    // des的type先定义好
    Operand des("0", btype->t); // 目的未知,类型已知
    Operand op1;
    if (btype->t == Type::Int)
    {
        op1.name = "0";
        op1.type = Type::IntLiteral;
        des.type = Type::Int;
    }
    else
    {
        op1.name = "";
        op1.type = Type::FloatLiteral;
        des.type = Type::Float;
    }
    Instruction *assignInst = new Instruction(op1,
                                              ir::Operand(),
                                              des,
                                              ir::Operator::def);
    Inst.push_back(assignInst);
    pc++;

    cout << "add def" << endl;

    ANALYSIS(vardef, VarDef, 1);

    int len = root->children.size();
    int index = 2;
    if (index < len)
    {
        GET_CHILD_PTR(term, Term, index);
        while (index < len && term->token.type == TokenType::COMMA)
        {
            Instruction *assignInst = new Instruction(op1,
                                                      ir::Operand(),
                                                      des,
                                                      ir::Operator::def);
            Inst.push_back(assignInst);
            pc++;

            cout << "add def" << endl;

            index++;
            ANALYSIS(vardef, VarDef, index);
            index++;
            if (index < len - 1)
            {
                cout << "index: " << index << endl;
                cout << "len: " << len << endl;
                GET_CHILD_PTR(term, Term, index);
            }
            else
            {
                break;
            }
        }
    }

#ifdef DEBUG_RESULT
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
#endif
}
// VarDef -> Ident { '[' ConstExp ']' } [ '=' InitVal ]
void frontend::Analyzer::analysisVarDef(VarDef *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin vardef" << endl;
#endif
    // des的name先定义好
    GET_CHILD_PTR(ident, Term, 0);
    Inst.back()->des.name = ident->token.value;
    int len = root->children.size();
    int index = 1;
    if (index < len)
    {
        GET_CHILD_PTR(l_or_a, Term, index);
        // 是数组，需要改变des的type
        if (index < len && l_or_a->token.type == TokenType::LBRACK)
        {
            cout << "shuzu begin" << endl;
            Type t = Inst.back()->des.type;
            if (t == Type::Int)
            {
                Inst.back()->op1.type = Type::Int;
                Inst.back()->des.type = Type::IntPtr;
            }

            else
            {
                Inst.back()->op1.type = Type::Float;
                Inst.back()->des.type = Type::FloatPtr;
            }

            Inst.back()->op = ir::Operator::alloc;

            cout << "add alloc" << endl;

            vector<int> dim;

            int key = 1;
            while (index < len && l_or_a->token.type == TokenType::LBRACK)
            {
                // op1的name和type
                index++;
                ANALYSIS(constexp, ConstExp, index);
                if (!constexp->is_computable)
                {
                    key = 0;
                }
                dim.push_back(std::stoi(constexp->v));
                index = index + 2;
                if (index < len)
                {
                    GET_CHILD_PTR(l_or_a, Term, index);
                    if (l_or_a->token.type == TokenType::ASSIGN)
                    {
                        key = 2;
                        break;
                    }
                }
            }
            int all = 1;
            for (int i = 0; i < dim.size(); i++)
            {
                all *= dim[i];
            }
            Inst.back()->op1.name = to_string(all);
            if (key)
            {
                Inst.back()->op1.type = Type::IntLiteral;
            }
            cout << all << "           " << toString(Inst.back()->op) << endl;

            Operand op = Inst.back()->des;
            STE ste;
            ste.operand = op;
            ste.dimension = dim;

            symbol_table.scope_stack.back().table[op.name] = ste;
            cout << "add  " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;

            // 数组且赋值
            // 存数指令，指向数组中存数。第一个操作数为数组名，第二个操作数为要存数所在数组下标，目的操作数为存入的数。
            cout << "***********************************" << toString(l_or_a->token.type) << endl;
            if (key == 2)
            {
                cout << "to fuzhi" << endl;
                index++;
                ANALYSIS(initval, InitVal, index);
                index++;
            }
        }
        // 不是数组，那就一定是赋值
        else
        {
            // 这里考虑到赋值的时候后面可能是先存在的值，故对原本指令备份，重新填入
            Instruction *old_inst = Inst.back();
            Inst.pop_back();
            pc--;

            index++;
            ANALYSIS(initval, InitVal, index);

            old_inst->op1.name = initval->v;
            old_inst->op1.type = initval->t;
            cout << "initval  " << toString(initval->t) << "  " << initval->v << endl;

            Inst.push_back(old_inst);
            pc++;

            Operand op = Inst.back()->des;
            STE ste;
            ste.operand = op;
            symbol_table.scope_stack.back().table.insert({op.name, ste});
            cout << "add  " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
        }
    }
    // 单纯一个Ident，无任何赋值
    else
    {
        STE ste;
        Operand op = Inst.back()->des;
        ste.operand = op;
        symbol_table.scope_stack.back().table.insert({op.name, ste});

        cout << "add  " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
    }
#ifdef DEBUG_RESULT
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
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
        COPY_EXP_NODE(exp, root);
    }
    else
    {
        Operand des = Inst.back()->des;
        if (root->children[1]->type == NodeType::INITVAL)
        {
            // 存数指令，指向数组中存数。第一个操作数为数组名，第二个操作数为要存数所在数组下标，目的操作数为存入的数
            Operand op1 = des;
            int all = 1;
            STE ste = symbol_table.get_ste(op1.name);
            for (int i = 0; i < ste.dimension.size(); i++)
            {
                all *= ste.dimension[i];
            }
            int index = 0;
            for (int i = 0; i < all; i++)
            {
                Operand op2;
                op2.name = to_string(i);
                op2.type = Type::IntLiteral;
                cout << index << " begin initval" << endl;
                index++;
                ANALYSIS(initval, InitVal, index);
                index++;

                Operand des(initval->v, initval->t);

                cout << "yao cun ru de shu is " << initval->v << endl;

                // if (initval->t == Type::IntLiteral)
                //     des.type = Type::Int;
                // else if (initval->t == Type::FloatLiteral)
                //     des.type = Type::Float;

                cout << "------------------" << op1.name << "   " << toString(op1.type) << " " << op2.name << " " << toString(des.type) << "   " << des.name << endl;
                Instruction *storeInst = new Instruction(op1,
                                                         op2,
                                                         des,
                                                         ir::Operator::store);

                Inst.push_back(storeInst);
                pc++;

                if (!initval->is_computable)
                {
                    STE ste_add;
                    Operand op_add = des;
                    ste_add.operand = op_add;

                    cout << "op add is            " << op_add.name << endl;
                    auto it = symbol_table.scope_stack.back().table.find(op_add.name);
                    if (it != symbol_table.scope_stack.back().table.end())
                    {
                        symbol_table.scope_stack.back().table[op_add.name] = ste_add;
                        cout << "///////add xiugai  " << op_add.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
                    }
                    else
                    {
                        symbol_table.scope_stack.back().table.insert({op_add.name, ste_add});
                        cout << "//////add  insert  " << op_add.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
                    }
                }
            }
            // int index = 2;
            // while (index < len && root->children[index]->token.type == TokenType::COMMA)
            // {
            //     index++;
            //     ANALYSIS(initval, InitVal, index);
            //     index++;
            // }
        }
        else
        {
            root->v = "0";
            root->t = Type::null;
        }
    }
#ifdef DEBUG_RESULT
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
#endif
}
// FuncDef -> FuncType Ident '(' [FuncFParams] ')' BlockcallInst
void frontend::Analyzer::analysisFuncDef(FuncDef *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin funcdef" << endl;
#endif
    ANALYSIS(functype, FuncType, 0);
    GET_CHILD_PTR(ident, Term, 1);
    if (ident->token.value == "main")
    {
        ir::CallInst *callGlobal = new ir::CallInst(ir::Operand("global", ir::Type::null),
                                                    ir::Operand("t0", ir::Type::null));
        Inst.push_back(callGlobal);
        pc++;
    }

    root->t = functype->t;
    root->v = ident->token.value;
    root->is_computable = false;

    if (root->children[3]->type == NodeType::FUNCFPARAMS)
    {
        // 函数存在参数
        ANALYSIS(funcfparams, FuncFParams, 3);

        STE ste;
        Operand op(root->v, root->t);
        ste.operand = op;
        symbol_table.scope_stack[0].table.insert({op.name, ste});

        ANALYSIS(block, Block, 5);
    }
    else
    {
        STE ste;
        Operand op(root->v, root->t);
        ste.operand = op;
        symbol_table.scope_stack[0].table.insert({op.name, ste});
        ANALYSIS(block, Block, 4);
    }

#ifdef DEBUG_RESULT
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
#endif
}
// FuncType -> 'void' | 'int' | 'float'
void frontend::Analyzer::analysisFuncType(FuncType *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin functype" << endl;
#endif
    GET_CHILD_PTR(term, Term, 0);
    if (term->token.type == TokenType::VOIDTK)
    {
        root->t = Type::null;
    }
    else if (term->token.type == TokenType::INTTK)
    {
        root->t = Type::Int;
    }
    else
    {
        root->t = Type::Float;
    }
#ifdef DEBUG_RESULT
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
#endif
}
// FuncFParam -> BType Ident ['[' ']' { '[' Exp ']' }]
void frontend::Analyzer::analysisFuncFParam(FuncFParam *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin funcfparam" << endl;
#endif
    ANALYSIS(btype, BType, 0);
    GET_CHILD_PTR(ident, Term, 1);

    root->t = btype->t;
    root->v = ident->token.value;
    root->is_computable = false;
    int len = root->children.size();
    int index = 4;
    while (index < len && root->children[index]->token.type == TokenType::LBRACK)
    {
        index++;
        ANALYSIS(exp, Exp, index);
        index = index + 2;
    }
#ifdef DEBUG_RESULT
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
#endif
}
// FuncFParams -> FuncFParam { ',' FuncFParam }
void frontend::Analyzer::analysisFuncFParams(FuncFParams *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin funcfparams" << endl;
#endif
    vector<Operand> paraVec;
    ANALYSIS(funcfparam, FuncFParam, 0);
    Operand op1(funcfparam->v, funcfparam->t);
    paraVec.push_back(op1);
    cout << "add funcfparam" << toString(op1.type) << " " << op1.name << " in " << endl;

    int len = root->children.size();
    int index = 1;
    if (index < len)
    {
        GET_CHILD_PTR(term, Term, index);
        while (index < len - 1 && term->token.type == TokenType::COMMA)
        {
            index++;
            ANALYSIS(funcfparam_right, FuncFParam, index);

            Operand op1(funcfparam_right->v, funcfparam_right->t);
            paraVec.push_back(op1);

            cout << "add funcfparam " << toString(op1.type) << " " << op1.name << " in " << endl;

            index++;
        }
    }

    function_temp.ParameterList = paraVec;

#ifdef DEBUG_RESULT
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
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
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
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
        origin = pc;
        destination = pc;
        ANALYSIS(stmt, Stmt, 0);
    }
#ifdef DEBUG_RESULT
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
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
        // 第一个操作数为赋值变量，第二个操作数不使用，结果为被赋值变量。
        Operand op1(exp->v, exp->t);
        Operand des(lval->v, lval->t);
        ir::Instruction *movInst = new Instruction(op1,
                                                   ir::Operand(),
                                                   des, ir::Operator::mov);
        Inst.push_back(movInst);
        pc++;

        cout << "add mov" << endl;
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
            // cond
            //  if cond goto 2
            //  goto next else(analysis)
            //  stmt
            //  goto end
            //  cond
            //  else if cond goto 2
            //  stmt
            //  goto end
            //  else
            //  stmt
            ANALYSIS(cond, Cond, 2);
            Operand op1(cond->v, cond->t);
            // 第一个goto,指向条件中执行
            Instruction *gotoInst1 = new Instruction(op1,
                                                     ir::Operand(),
                                                     ir::Operand("2", ir::Type::IntLiteral), ir::Operator::_goto);
            Inst.push_back(gotoInst1);
            pc++;

            int pc_to_change1 = pc; // 需要修改的指令的位置，指向下一个else if 语句开始前
            cout << "add goto" << endl;
            // 第二个goto,指向下一个判断语句,需要更新
            Instruction *gotoInst2 = new Instruction(ir::Operand(),
                                                     ir::Operand(),
                                                     ir::Operand("1", ir::Type::IntLiteral), ir::Operator::_goto);
            Inst.push_back(gotoInst2);
            pc++;

            cout << "add goto" << endl;
            int pc_1 = pc;
            ANALYSIS(stmt, Stmt, 4);
            int pc_to_change2 = pc;
            // 第三个goto,指向终点,需要更新
            Instruction *gotoInst = new Instruction(ir::Operand(),
                                                    ir::Operand(),
                                                    ir::Operand("1", Type::IntLiteral),
                                                    ir::Operator::_goto);
            Inst.push_back(gotoInst);
            pc++;

            int pc_2 = pc;
            cout << "add goto" << endl;

            Inst[pc_to_change1]->des.name = to_string(pc_2 - pc_1 + 1);

            cout << "in if: 1 where is pc: " << pc_to_change1 << " change inst goto's des's name = " << to_string(pc_2 - pc_1 + 1) << endl;

            int len = root->children.size();
            int index = 5;
            if (index < len)
            {
                ANALYSIS(stmt_right, Stmt, 6);
            }
            int pc_des = pc;
            Inst[pc_to_change2]->des.name = to_string(pc_des - pc_2 + 1);

            cout << "in if: 2 where is pc: " << pc_to_change2 << " change inst goto's des's name = " << to_string(pc_des - pc_2 + 1) << endl;
        }
        else if (ident->token.type == TokenType::WHILETK)
        {
            break_pc.clear();
            int while_begin = pc;
            ANALYSIS(cond, Cond, 2);
            Operand op1(cond->v, cond->t);
            // 第一个goto,指向条件中执行
            Instruction *gotoInst1 = new Instruction(op1,
                                                     ir::Operand(),
                                                     ir::Operand("2", ir::Type::IntLiteral), ir::Operator::_goto);
            Inst.push_back(gotoInst1);
            pc++;

            int pc_to_change1 = pc;
            cout << "add goto" << endl;
            // 第二个goto,指向终点
            Instruction *gotoInst2 = new Instruction(ir::Operand(),
                                                     ir::Operand(),
                                                     ir::Operand("1", ir::Type::IntLiteral), ir::Operator::_goto);
            Inst.push_back(gotoInst2);
            pc++;

            ANALYSIS(stmt, Stmt, 4);

            string pc_again = to_string(while_begin - pc);
            // 第三个goto,指向起点
            Instruction *gotoInst = new Instruction(ir::Operand(),
                                                    ir::Operand(),
                                                    ir::Operand(pc_again, Type::IntLiteral),
                                                    ir::Operator::_goto);
            Inst.push_back(gotoInst);
            pc++;
            cout << "add goto" << endl;
            cout << "in where: 1 where is pc: return back to " << pc_again << endl;

            int pc_des = pc;
            Inst[pc_to_change1]->des.name = to_string(pc_des - pc_to_change1);

            cout << "in where: 2 where is pc: " << pc_to_change1 << " change inst goto's des's name = " << to_string(pc_des - pc_to_change1) << endl;

            for (int i = 0; i < break_pc.size(); i++)
            {
                Inst[break_pc[i]]->des.name = to_string(pc_des - break_pc[i]);
                cout << "in where: break: where is pc: " << break_pc[i] << " change inst goto's des's name = " << pc_des - break_pc[i] << endl;
            }
        }
        else if (ident->token.type == TokenType::BREAKTK)
        {
            break_pc.push_back(pc);
            cout << "break: where pc is " << pc << " find break" << endl;
            Instruction *gotoInst = new Instruction(ir::Operand("", Type::null),
                                                    ir::Operand(),
                                                    ir::Operand("1", Type::IntLiteral),
                                                    ir::Operator::_goto);
            Inst.push_back(gotoInst);
            pc++;
            cout << "add goto" << endl;
        }
        else if (ident->token.type == TokenType::CONTINUETK)
        {
        }
        else if (ident->token.type == TokenType::RETURNTK)
        {
            int pc_to_change;
            int len = root->children.size();
            int index = 1;
            if (index < len)
            {
                ANALYSIS(exp, Exp, 1);
                COPY_EXP_NODE(exp, root);

                Operand op1(exp->v, exp->t);
                Instruction *returnInst = new Instruction(op1,
                                                          ir::Operand(),
                                                          ir::Operand(),
                                                          ir::Operator::_return);
                Inst.push_back(returnInst);
                pc++;

                cout << "add return" << endl;
            }
            else
            {
                Instruction *returnInst = new Instruction(ir::Operand(),
                                                          ir::Operand(),
                                                          ir::Operand(),
                                                          ir::Operator::_return);
                Inst.push_back(returnInst);
                pc++;
                cout << "add return" << endl;
            }
        }
        else
        {
        }
    }

#ifdef DEBUG_RESULT
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
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
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
#endif
}
// Cond -> LOrExp
void frontend::Analyzer::analysisCond(Cond *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin cond" << endl;
#endif
    ANALYSIS(lorexp, LOrExp, 0);
    COPY_EXP_NODE(lorexp, root);
#ifdef DEBUG_RESULT
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
#endif
}
// LVal -> Ident {'[' Exp ']'}
void frontend::Analyzer::analysisLVal(LVal *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin lval" << endl;
#endif

    GET_CHILD_PTR(ident, Term, 0);
    ident->v = ident->token.value;
    root->v = ident->v;
    int len = root->children.size();
    int index = 1;

    Operand op = symbol_table.get_operand(ident->v);
    STE ste = symbol_table.get_ste(ident->v);
    Type t = op.type;
    if (t == Type::Int || t == Type::Float)
    {
        root->t = t;
    }
    else if (t == Type::IntPtr)
    {
        t = Type::Int;
        root->t = Type::IntPtr;
    }
    else if (t == Type::FloatLiteral)
    {
        t == Type::Float;
        root->t = Type::FloatLiteral;
    }
    // else
    // {
    //     root->t = Type::null;
    // }

    if (index < len)
    {
        // 第一个操作数为赋值变量，第二个操作数不使用，结果为被赋值变量。
        Operand op1 = symbol_table.get_operand(ident->v);
        Operand op2("0", Type::IntLiteral);
        string id = "t" + to_string(counter++);
        root->v = id;
        Operand des(id, t);
        vector<int> dimension = ste.dimension;

        vector<int> dim;
        GET_CHILD_PTR(lbrack, Term, index);
        while (index < len && lbrack->token.type == TokenType::LBRACK)
        {
            index++;
            ANALYSIS(exp, Exp, index);
            dim.push_back(stoi(exp->v));
            index = index + 2;
        }
        int all = calculateIndex(dimension, dim); // 得到位置
        op2.name = to_string(all);
        // 第一个操作数为赋值变量，第二个操作数不使用，结果为被赋值变量。
        Instruction *loadInst = new Instruction(op1,
                                                op2, des, ir::Operator::load);
        Inst.push_back(loadInst);
        pc++;

        cout << "add load" << endl;

        Operand op = des;
        STE ste;
        ste.operand = op;
        symbol_table.scope_stack.back().table.insert({op.name, ste});
        cout << "add  " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;

        root->t = t;
        root->v = id;
    }

    root->is_computable = false;

#ifdef DEBUG_RESULT
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }

    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
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
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
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
        COPY_EXP_NODE(lval, root);
    }
    else if (root->children[0]->type == NodeType::NUMBER)
    {
        ANALYSIS(number, Number, 0);
        COPY_EXP_NODE(number, root);
    }
    else
    {
        ANALYSIS(exp, Exp, 1);
        COPY_EXP_NODE(exp, root);
    }
#ifdef DEBUG_RESULT
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
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

        if (unaryop->v == "+")
        {
            COPY_EXP_NODE(unaryexp, root);
        }
        else if (unaryop->v == "-")
        {
            // a=-a->0-a
            // def一个0
            Operand op1("0", Type::IntLiteral);
            string id = "t" + to_string(counter++);
            Operand des(id, Type::Int);
            Instruction *defInst = new Instruction(op1, Operand(), des, ir::Operator::def);
            Inst.push_back(defInst);
            pc++;

            STE ste;
            ste.operand = des;
            symbol_table.scope_stack.back().table.insert({des.name, ste});
            cout << "add  " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;

            // 减法
            //  def一个0
            op1 = des;
            Operand op2(unaryexp->v, unaryexp->t);
            id = "t" + to_string(counter++);
            des = Operand(id, Type::Int);
            if (unaryexp->is_computable)
            {

                Instruction *subInst = new Instruction(op1, op2, des, ir::Operator::subi);
                Inst.push_back(subInst);
            }
            else
            {
                Instruction *subInst = new Instruction(op1, op2, des, ir::Operator::sub);
                Inst.push_back(subInst);
            }

            pc++;

            ste.operand = des;
            symbol_table.scope_stack.back().table.insert({des.name, ste});
            cout << "add  " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;

            root->v = id;
        }
        else
        {
            // 变量取非运算 ! ，第一个操作数为取非变量，第二个操作数不使用，结果为取非结果变量。
            Operand op1(unaryexp->v, unaryexp->t);
            string id = "t" + to_string(counter++);
            Operand des(id, Type::Int);
            Instruction *notInst = new Instruction(op1, Operand(), des, ir::Operator::_not);
            Inst.push_back(notInst);
            pc++;
            cout << "add not" << endl;

            STE ste;
            ste.operand = des;
            symbol_table.scope_stack.back().table.insert({des.name, ste});
            cout << "add  " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;

            root->v = id;
        }
    }
    else
    {
        GET_CHILD_PTR(ident, Term, 0);
        ident->v = ident->token.value;
        COPY_EXP_NODE(ident, root);

        int len = root->children.size();
        int index = 2;
        if (index < len - 1)
        {
            callInst_temp = new ir::CallInst(Operand(), Operand());
            ANALYSIS(funcrparam, FuncRParams, 2);
            // 一个操作数为赋值变量，第二个操作数不使用，结果为被赋值变量。
            Operand op1 = symbol_table.get_operand(ident->v);
            string id = "t" + to_string(counter++);
            Operand des(id, op1.type);
            root->v = id;

            vector<Operand> paraVec1 = callInst_temp->argumentList;
            ir::CallInst *callInst = new ir::CallInst(op1, paraVec1, des);
            Inst.push_back(callInst);
            pc++;

            STE ste;
            Operand op = des;
            ste.operand = op;
            symbol_table.scope_stack.back().table.insert({op.name, ste});
            cout << "add  " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
        }
        else
        {
            Operand op1 = symbol_table.get_operand(ident->v);
            string id = "t" + to_string(counter++);
            Operand des(id, op1.type);
            root->v = id;
            ir::CallInst *callInst = new ir::CallInst(op1,
                                                      des);
            Inst.push_back(callInst);
            pc++;

            STE ste;
            Operand op = des;
            ste.operand = op;
            symbol_table.scope_stack.back().table.insert({op.name, ste});
            cout << "add  " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
        }
    }
#ifdef DEBUG_RESULT
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
#endif
}
// UnaryOp -> '+' | '-' | '!'
void frontend::Analyzer::analysisUnaryOp(UnaryOp *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin unaryop" << endl;
#endif
    GET_CHILD_PTR(term, Term, 0);
    if (term->token.type == TokenType::PLUS)
    {
        root->v = "+";
    }
    else if (term->token.type == TokenType::MINU)
    {
        root->v = "-";
    }
    else
    {
        root->v = "!";
    }
#ifdef DEBUG_RESULT
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
#endif
}
// FuncRParams -> Exp { ',' Exp }
void frontend::Analyzer::analysisFuncRParams(FuncRParams *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin funcrparams" << endl;
#endif

    vector<Operand> paraVec1;
    ANALYSIS(exp, Exp, 0);
    Operand op(exp->v, exp->t);
    paraVec1.push_back(op);
    COPY_EXP_NODE(exp, root);
    int len = root->children.size();
    int index = 1;
    while (index < len)
    {
        index++;
        ANALYSIS(exp_right, Exp, index);
        Operand op(exp_right->v, exp->t);
        paraVec1.push_back(op);
        index++;
    }
    callInst_temp->argumentList = paraVec1;
#ifdef DEBUG_RESULT
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
#endif
}
// MulExp -> UnaryExp { ('*' | '/' | '%') UnaryExp }
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
        GET_CHILD_PTR(term, Term, index);
        index++;
        ANALYSIS(unaryexp_right, UnaryExp, index);
        index++;
        Operand op1(unaryexp->v, unaryexp->t);

        if (unaryexp->is_computable) // 乘法是常数需要先定义
        {
            Operand op1(unaryexp->v, unaryexp->t);
            string id = "t" + to_string(counter++);
            Type t;
            if (unaryexp->t == Type::IntLiteral)
                t = Type::Int;
            else
                t = Type::Float;
            Operand des(id, t);
            Instruction *defInst = new Instruction(op1, Operand(), des, ir::Operator::def);
            Inst.push_back(defInst);
            pc++;

            cout << "add def" << endl;
            STE ste;
            ste.operand = des;
            symbol_table.scope_stack.back().table.insert({des.name, ste});
            cout << "add  " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
            unaryexp->v = id;
            unaryexp->t = t;
        }

        if (unaryexp_right->is_computable) // 乘法是常数需要先定义
        {
            Operand op1(unaryexp_right->v, unaryexp_right->t);
            string id = "t" + to_string(counter++);
            Type t;
            if (unaryexp_right->t == Type::IntLiteral)
                t = Type::Int;
            else
                t = Type::Float;
            Operand des(id, t);
            Instruction *defInst = new Instruction(op1, Operand(), des, ir::Operator::def);
            Inst.push_back(defInst);
            pc++;

            cout << "add def" << endl;
            STE ste;
            ste.operand = des;
            symbol_table.scope_stack.back().table.insert({des.name, ste});
            cout << "add  " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
            unaryexp_right->v = id;
            unaryexp_right->t = t;
        }
        Operand op2(unaryexp_right->v, ir::Type::Int);
        string id = "t" + to_string(counter++);
        Operand des(id, ir::Type::Int);
        if (term->token.type == TokenType::MULT)
        {
            Instruction *mulInst = new Instruction(op1,
                                                   op2,
                                                   des, ir::Operator::mul);
            Inst.push_back(mulInst);
            pc++;

            cout << "add mul" << endl;
        }
        else if (term->token.type == TokenType::DIV)
        {
            Instruction *divInst = new Instruction(op1,
                                                   op2,
                                                   des, ir::Operator::div);
            Inst.push_back(divInst);
            pc++;

            cout << "add div" << endl;
        }
        else
        {
            Instruction *modInst = new Instruction(op1,
                                                   op2,
                                                   des, ir::Operator::mod);
            Inst.push_back(modInst);
            pc++;

            cout << "add mod" << endl;
        }
        root->t = unaryexp->t;
        root->v = id;
        root->is_computable = false;
        unaryexp->v = id;
    }
#ifdef DEBUG_RESULT
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
#endif
}
// AddExp -> MulExp { ('+' | '-') MulExp }
void frontend::Analyzer::analysisAddExp(AddExp *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin addexp" << endl;
#endif
    ANALYSIS(mulexp, MulExp, 0);
    cout << "the first mulexp type is " << toString(mulexp->t) << endl;
    COPY_EXP_NODE(mulexp, root);
    int len = root->children.size();
    int index = 1;
    while (index < len)
    {
        GET_CHILD_PTR(term, Term, index);
        index++;
        ANALYSIS(mulexp_right, MulExp, index);
        index++;

        // 两个都是常量
        if (mulexp->is_computable && mulexp_right->is_computable)
        {
            cout << "two is computable" << endl;
            root->is_computable = true;
            if (term->token.type == TokenType::PLUS)
            {
                if (mulexp->t == Type::Int && mulexp_right->t == Type::Int)
                {
                    root->v = to_string(std::stoi(mulexp->v) + std::stoi(mulexp_right->v));
                }
                else
                {
                    root->v = to_string(std::stof(mulexp->v) + std::stof(mulexp_right->v));
                }
            }
            else
            {
                if (mulexp->t == Type::Int && mulexp_right->t == Type::Int)
                    root->v = to_string(std::stoi(mulexp->v) - std::stoi(mulexp_right->v));
                else
                    root->v = to_string(std::stof(mulexp->v) - std::stof(mulexp_right->v));
            }
        }
        // 两个都不是常量
        else if (!mulexp->is_computable && !mulexp_right->is_computable)
        {
            cout << "the first mulexp type is " << toString(mulexp->t) << endl;
            cout << "the second mulexp type is " << toString(mulexp_right->t) << endl;
            cout << "two is not computable" << endl;
            Operand op1 = Operand(mulexp->v, mulexp->t);
            Operand op2 = Operand(mulexp_right->v, mulexp_right->t);
            string id = "t" + to_string(counter++);
            cout << "the first mulexp type is " << toString(mulexp->t) << endl;
            if (mulexp->t == Type::Int && mulexp_right->t == Type::Int)
                root->t = Type::Int;
            else
                root->t = Type::Float;
            Operand des(id, op1.type);
            if (term->token.type == TokenType::PLUS)
            {
                Instruction *addInst = new Instruction(op1, op2, des, ir::Operator::add);
                Inst.push_back(addInst);
                pc++;

                cout << "add add" << endl;
            }
            else
            {
                Instruction *subInst = new Instruction(op1, op2, des, ir::Operator::sub);
                Inst.push_back(subInst);
                pc++;

                cout << "add sub" << endl;
            }

            root->v = id;
            mulexp->v = id;
            Operand op = des;
            STE ste;
            ste.operand = op;
            symbol_table.scope_stack.back().table.insert({op.name, ste});
            cout << "add  " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
        }
        else if (!mulexp->is_computable && mulexp_right->is_computable)
        {
            cout << "second is computable" << endl;
            Operand op1(mulexp->v, mulexp->t);
            Operand op2(mulexp_right->v, mulexp_right->t);
            if (term->token.type == TokenType::PLUS)
            {
                if (mulexp->t == Type::Int && mulexp_right->t == Type::IntLiteral)
                {
                    string id = "t" + to_string(counter++);
                    root->v = id;
                    root->t = Type::Int;
                    Operand des(id, Type::Int);
                    Instruction *addInst = new Instruction(op1,
                                                           op2,
                                                           des, ir::Operator::addi);
                    Inst.push_back(addInst);
                    pc++;

                    cout << "add addi" << endl;

                    Operand op = des;
                    STE ste;
                    ste.operand = op;
                    symbol_table.scope_stack.back().table.insert({op.name, ste});
                    cout << "add  " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
                }
            }
            else
            {
                if (mulexp->t == Type::Int && mulexp_right->t == Type::IntLiteral)
                {
                    string id = "t" + to_string(counter++);
                    root->v = id;
                    root->t = Type::Int;
                    Operand des(id, Type::Int);
                    Instruction *subInst = new Instruction(op1,
                                                           op2,
                                                           des, ir::Operator::subi);
                    Inst.push_back(subInst);
                    pc++;

                    cout << "add subi" << endl;
                }
            }
            {
            }
        }
        else
        {
            cout << "first is computable" << endl;
            Operand op2(mulexp->v, mulexp->t);
            Operand op1(mulexp_right->v, mulexp_right->t);
            if (term->token.type == TokenType::PLUS)
            {
                if (mulexp_right->t == Type::Int && mulexp->t == Type::IntLiteral)
                {
                    string id = "t" + to_string(counter++);
                    root->v = id;
                    root->t = Type::Int;
                    Operand des(id, Type::Int);
                    Instruction *addInst = new Instruction(op1,
                                                           op2,
                                                           des, ir::Operator::addi);
                    Inst.push_back(addInst);
                    pc++;

                    cout << "add addi" << endl;

                    Operand op = des;
                    STE ste;
                    ste.operand = op;
                    symbol_table.scope_stack.back().table.insert({op.name, ste});
                    cout << "add  " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
                }
            }
            else
            {
                if (mulexp_right->t == Type::Int && mulexp->t == Type::IntLiteral)
                {
                    string id = "t" + to_string(counter++);
                    root->v = id;
                    root->t = Type::Int;
                    mulexp->v = id;
                    Operand des(id, Type::Int);
                    Instruction *subInst = new Instruction(op1,
                                                           op2,
                                                           des, ir::Operator::subi);
                    Inst.push_back(subInst);
                    pc++;

                    cout << "add subi" << endl;
                }
            }
        }
    }
#ifdef DEBUG_RESULT
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
#endif
}
// RelExp -> AddExp { ('<' | '>' | '<=' | '>=') AddExp }
void frontend::Analyzer::analysisRelExp(RelExp *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin relexp" << endl;
#endif
    ANALYSIS(addexp, AddExp, 0);
    COPY_EXP_NODE(addexp, root);
    int len = root->children.size();
    int index = 1;
    while (index < len)
    {
        GET_CHILD_PTR(term, Term, index);
        index++;
        ANALYSIS(addexp_right, AddExp, index);
        index++;
        Operand op1(addexp->v, addexp->t);
        Operand op2(addexp_right->v, addexp_right->t);
        string id = "t" + to_string(counter++);
        Operand des(id, Type::Int);
        if (term->token.type == TokenType::LSS)
        {
            Instruction *lssinst = new Instruction(op1, op2, des, ir::Operator::lss);
            Inst.push_back(lssinst);
            pc++;

            cout << "add lss" << endl;
        }
        else if (term->token.type == TokenType::GTR)
        {
            Instruction *gtrInst = new Instruction(op1, op2, des, ir::Operator::gtr);
            Inst.push_back(gtrInst);
            pc++;

            cout << "add gtr" << endl;
        }
        else if (term->token.type == TokenType::LEQ)
        {
            Instruction *leqInst = new Instruction(op1, op2, des, ir::Operator::leq);
            Inst.push_back(leqInst);
            pc++;

            cout << "add leq" << endl;
        }
        else
        {
            Instruction *geqInst = new Instruction(op1, op2, des, ir::Operator::geq);
            Inst.push_back(geqInst);
            pc++;

            cout << "add geq" << endl;
        }
        root->v = id;
        root->t = Type::Int;
        root->is_computable = false;
    }
#ifdef DEBUG_RESULT
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
#endif
}
// EqExp -> RelExp { ('==' | '!=') RelExp }
void frontend::Analyzer::analysisEqExp(EqExp *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin eqexp" << endl;
#endif
    ANALYSIS(relexp, RelExp, 0);
    COPY_EXP_NODE(relexp, root);
    int len = root->children.size();
    int index = 1;
    while (index < len)
    {
        GET_CHILD_PTR(term, Term, index);
        index++;
        ANALYSIS(relexp_right, RelExp, index);
        index++;
        if (relexp->is_computable)
        {
            Operand op1(relexp->v, Type::IntLiteral);
            string id = "t" + to_string(counter++);
            Operand des(id, Type::Int);
            Instruction *defInst = new Instruction(op1, Operand(), des, ir::Operator::def);
            Inst.push_back(defInst);
            pc++;

            cout << "add def" << endl;

            STE ste;
            ste.operand = des;
            symbol_table.scope_stack.back().table.insert({des.name, ste});
            cout << "add  " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
            relexp->v = id;
            relexp->t = Type::Int;
            relexp->is_computable = false;
        }

        if (relexp_right->is_computable)
        {
            Operand op1(relexp_right->v, Type::IntLiteral);
            string id = "t" + to_string(counter++);
            Operand des(id, Type::Int);
            Instruction *defInst = new Instruction(op1, Operand(), des, ir::Operator::def);
            Inst.push_back(defInst);
            pc++;

            cout << "add def" << endl;

            STE ste;
            ste.operand = des;
            symbol_table.scope_stack.back().table.insert({des.name, ste});
            cout << "add  " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
            relexp_right->v = id;
            relexp_right->t = Type::Int;
            relexp_right->is_computable = false;
        }
        string id = "t" + to_string(counter++);
        if (term->token.type == TokenType::EQL)
        {
            Operand op1(relexp->v, relexp->t);
            Operand op2(relexp_right->v, relexp_right->t);
            Operand des(id, Type::Int);
            Instruction *eqInst = new Instruction(op1, op2, des, ir::Operator::eq);
            Inst.push_back(eqInst);
            pc++;

            cout << "add eq" << endl;
            relexp_right->v = id;

            STE ste;
            ste.operand = des;
            symbol_table.scope_stack.back().table.insert({des.name, ste});
            cout << "add  " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
        }
        else
        {
        }
        relexp = relexp_right;
        root->v = id;
        root->is_computable = false;
        root->t = Type::Int;
    }
#ifdef DEBUG_RESULT
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
#endif
}
// LAndExp -> EqExp [ '&&' LAndExp ]
void frontend::Analyzer::analysisLAndExp(LAndExp *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin landexp" << endl;
#endif
    ANALYSIS(eqexp, EqExp, 0);
    COPY_EXP_NODE(eqexp, root);
    if (root->children.size() == 3)
    {
        ANALYSIS(landexp, LAndExp, 2);

        Operand op1(eqexp->v, eqexp->t);
        Operand op2(landexp->v, landexp->t);
        string id = "t" + to_string(counter++);
        Operand des(id, Type::Int);

        Instruction *andInst = new Instruction(op1, op2, des, ir::Operator::_and);
        Inst.push_back(andInst);
        pc++;

        cout << "add and" << endl;
        STE ste;
        ste.operand = des;
        symbol_table.scope_stack.back().table.insert({des.name, ste});
        cout << "add  " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
        root->v = id;
    }
#ifdef DEBUG_RESULT
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
#endif
}
// LOrExp -> LAndExp [ '||' LOrExp ]
void frontend::Analyzer::analysisLOrExp(LOrExp *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin lorexp" << endl;
#endif

    ANALYSIS(landexp, LAndExp, 0);
    Operand op1 = symbol_table.get_operand(landexp->v);
    if (root->children.size() == 3)
    {
        if (landexp->is_computable) // 乘法是常数需要先定义
        {
            Operand op1(landexp->v, landexp->t);
            string id = "t" + to_string(counter++);
            Operand des(id, Type::Int);
            Instruction *defInst = new Instruction(op1, Operand(), des, ir::Operator::def);
            Inst.push_back(defInst);
            pc++;

            cout << "add def" << endl;

            STE ste;
            ste.operand = des;
            symbol_table.scope_stack.back().table.insert({des.name, ste});
            cout << "add  " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
            landexp->v = id;
            landexp->t = Type::Int;
            landexp->is_computable = false;

            cout << "complete 1" << endl;
        }
        ANALYSIS(lorexp, LOrExp, 2);
        if (lorexp->is_computable) // 乘法是常数需要先定义
        {
            Operand op1(lorexp->v, lorexp->t);
            string id = "t" + to_string(counter++);
            Operand des(id, Type::Int);
            Instruction *defInst = new Instruction(op1, Operand(), des, ir::Operator::def);
            Inst.push_back(defInst);
            pc++;

            cout << "add def" << endl;
            STE ste;
            ste.operand = des;
            symbol_table.scope_stack.back().table.insert({des.name, ste});
            cout << "add  " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
            lorexp->v = id;
            lorexp->t = Type::Int;
            lorexp->is_computable = false;
            cout << "complete 2" << endl;
        }

        Operand op1 = symbol_table.get_operand(landexp->v);
        Operand op2 = symbol_table.get_operand(lorexp->v);
        string id = "t" + to_string(counter++);
        Operand des(id, Type::Int);
        Instruction *orInst = new Instruction(op1, op2, des, Operator::_or);
        Inst.push_back(orInst);
        pc++;

        cout << "add or" << endl;
        STE ste;
        ste.operand = des;
        symbol_table.scope_stack.back().table.insert({des.name, ste});

        root->v = id;
        root->t = Type::Int;
        root->is_computable = false;
    }
    else
    {
        COPY_EXP_NODE(landexp, root);
    }

#ifdef DEBUG_RESULT
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
#endif
}
// ConstExp -> AddExp
void frontend::Analyzer::analysisConstExp(ConstExp *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin constexp" << endl;
#endif
    ANALYSIS(addexp, AddExp, 0);
    COPY_EXP_NODE(addexp, root);
#ifdef DEBUG_RESULT
    string sure;
    if (root->is_computable)
    {
        sure = "true";
    }
    else
    {
        sure = "false";
    }
    cout << toString(root->type) << "    " << root->v << "    " << toString(root->t) << "    " << sure << endl;
#endif
}
