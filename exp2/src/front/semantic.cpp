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

    // �����һ��ά�ȿ�ʼ����������ֵ
    for (int i = numDimensions - 1; i >= 0; --i)
    {
        int currentIndex = indices[i];
        index += currentIndex * multiplier;
        multiplier *= dimension[i];
    }

    return index;
}
// ��������������ʶ�м��ֵ
int counter = 0;
// pcλ��
int pc = 0;
// ����������е�ָ��
vector<Instruction *> Inst = {};
// �����ݴ�function
Function function_temp = Function();
ir::CallInst *callInst_temp;
// ���������Ҫ�жϵ������и���
vector<int> break_pc = {};
int origin;
int destination;

map<string, int> result;

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

// �����������һ��ָ���ַ����� IR ������Ӧ�� map ��ָ�롣��� map �洢��һЩ���ú��������� getint��putint �ȵȡ�
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
// �������������������ű������һ���µ������򣬲��� node ��ʾ����������Ӧ���﷨���ڵ㡣
// ������������ʱ, ����ű������ ScopeInfo, �൱��ѹջ
// struct ScopeInfo
// {
//     int cnt;
//     string name;
//     map_str_ste table;
// };
// cnt ���������ں����е�Ψһ���, �����Ǻ����г��ֵĵڼ���������
// name ���������ֱ�����������, 'b' ������һ������Ƕ�׵�������, 'i' 'e' 'w' �ֱ������ if else while ����������������Ҳ����ȡ��ϲ�������֣�ֻ�����������Ƚ�������
// table ��һ�Ŵ�ŷ��ŵı�, {string: STE}, string �ǲ�������ԭʼ����, ���� Variable Table Entry(STE), ʵ���Ͼ���һ�� IR �Ĳ��������� STE -> Operand, �� STE �д�ŵ�Ӧ���Ǳ����������������
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

    ScopeInfo scope_info;                                                  // ����һ���µ�������
    scope_info.cnt = scope_stack.empty() ? 0 : scope_stack.back().cnt + 1; // �õ��µ��������cnt
    scope_info.name = "block_" + node->v + std::to_string(scope_info.cnt); // �õ��µ��������nameΪ"block_����_���"
    // �ڷ���� IR �Ĺ�����������Ҫ�����ͨ����������ͬ������������, ���ǵĽ��������������, Ϊ��������������������صĺ�׺ʹ��������֮��ı���������һ�� IR Function ���Ƕ�һ�޶���
    if (scope_stack.empty())
    {
#ifdef DEBUG_SEMANTIC
        cout << "scope_stack is empty" << endl;
#endif
    }
    else
    {
        for (auto &&item : scope_stack.back().table) // ��֮ǰ������ı����������������Ա����ڲ�ͬ����������ʶ��ͬ���ı�����
        {
            string new_name = get_scoped_name(item.first);
            STE new_ste = item.second;
            scope_info.table.insert(std::make_pair(new_name, new_ste));
        }
    }
    scope_stack.push_back(scope_info); // ���µ�������ѹ��������ջ
}
// ����������������˳���ǰ�������ڷ��ű���ɾ����ǰ�������Ӧ�����ݡ�
void frontend::SymbolTable::exit_scope()
{
    scope_stack.pop_back();
}
// ��������������Ǹ���һ����ʶ�� id ��ȡ���ڷ��ű��е��������޶��������磬��� id �� "x"�����ڵ�ǰ���������Ѿ�����һ��ͬ���������򷵻� "scope_x"��
// ����һ��������, �������ڵ�ǰ��������������������� (�൱�ڼӺ�׺)
// �ڷ���� IR �Ĺ�����������Ҫ�����ͨ����������ͬ������������, ���ǵĽ��������������, Ϊ��������������������صĺ�׺ʹ��������֮��ı���������һ�� IR Function ���Ƕ�һ�޶���
string frontend::SymbolTable::get_scoped_name(string id) const
{
    if (scope_stack.empty())
    {
        cout << "get scoped name end    " << id << endl;
        return id;
    }
    const auto &current_scope = scope_stack.back(); // ��ǰ������
    if (current_scope.table.find(id) != current_scope.table.end())
    {
        return "scope_" + std::to_string(current_scope.cnt) + "_" + id;
    }
    else
    {
        return id + "_scope_" + std::to_string(current_scope.cnt); // ��һ�γ���ʱ
    }
}
// ��������������Ǹ���һ����ʶ�� id ��ȡ����Ӧ�Ĳ���������������ʶ����һ���������򷵻�һ���Ĵ�����ջ�ϵ�λ�ã������һ���������򷵻�����ֵ��
// �ڵ�ǰ��������������ʶ���Ƿ��Ѿ����壬����Ѿ����壬�򷵻����Ĳ�������
// �����ǰ������û�ж��������ʶ������ݹ��������������в��ң�ֱ���ҵ����ߵ�ȫ��������Ϊֹ��
// ���ȫ��������Ҳû�ж��������ʶ������˵������һ��δ�����ı�ʶ������Ҫ��������һ������Ĳ�������
// ����һ��������, �ڷ��ű���Ѱ�������ͬ������, ���ض�Ӧ�� Operand(ע�⣬�� Operand �� name �����������)
Operand frontend::SymbolTable::get_operand(string id) const
{
    // todo
    if (id == "getint" || id == "getch" || id == "getarray" || id == "getfaray")
    {
        return Operand(id, Type::Int);
    }
    const auto &current_scope = scope_stack.back(); // ��ǰ������
    auto it = current_scope.table.find(id);         // ��ǰ���������id

    // // �ҵ���ʶ���ڵ�ǰ�������ж���
    // if (it != current_scope.table.end())
    // {
    //     return it->second.operand;
    // }
    // // ��ʶ���ڵ�ǰ��������δ���壬��Ҫ������������в���
    // else
    // {
    //     // rbegin()�������ĳ�Ա����������һ�������������ָ�������е����һ��Ԫ�ء�
    //     // rend()�������ĳ�Ա����������һ�������������ָ�������еĵ�һ��Ԫ��֮ǰ��λ�á�
    //     // ��δ���������Ǵӵ����ڶ���������ʼ��ǰ����������ջ�е�Ԫ�أ��Բ��ҷ��ű��еı�ʶ�������ų������һ�������򣬼���ǰ������
    //     for (auto it = scope_stack.rbegin() + 1; it != scope_stack.rend(); ++it)
    //     {
    //         auto it2 = it->table.find(id);
    //         // �ҵ���ʶ���ڸ��������ж���
    //         if (it2 != it->table.end())
    //         { // �ҵ��˶��壬�����µĲ�����������
    //             Operand new_operand;
    //             new_operand.type = it2->second.operand.type;
    //             return new_operand;
    //         }
    //     }
    //     // ��ʶ��δ����
    //     return Operand();
    // }

    // rbegin()�������ĳ�Ա����������һ�������������ָ�������е����һ��Ԫ�ء�
    // rend()�������ĳ�Ա����������һ�������������ָ�������еĵ�һ��Ԫ��֮ǰ��λ�á�
    // ��δ���������Ǵ����һ��������ʼ��ǰ����������ջ�е�Ԫ�أ��Բ��ҷ��ű��еı�ʶ�������ų������һ�������򣬼���ǰ������
    for (auto it = scope_stack.rbegin(); it != scope_stack.rend(); ++it)
    {
        auto iter = it->table.find(id);
        // �ҵ���ʶ���ڸ��������ж���
        if (iter != it->table.end())
        { // �ҵ��˶��壬�����µĲ�����������
            return iter->second.operand;
        }
    }
    // ��ʶ��δ����
    return Operand(id);
}
// ��������������Ǹ���һ����ʶ�� id ��ȡ���ڷ��ű��ж�Ӧ�ķ��ű��
// ����һ��������, �ڷ��ű���Ѱ�������ͬ������, ���� STE
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
    // ��ʶ��STE
    return STE();
}
// ���������������������岿�֣�����һ��˽�б��� symbol_table����ʾ������������еķ��ű��Լ�һ��˽�б��� tmp_cnt����ʾ������ʱ����ʱʹ�õļ�������
frontend::Analyzer::Analyzer() : tmp_cnt(0), symbol_table()
{
}
// ������һ�����ڵ� root������һ�� IR �������������ݹ�ر��������﷨����������һЩ����������ʵ�ֲ�ͬ���͵����������
ir::Program frontend::Analyzer::get_ir_program(CompUnit *root)
{
    ir::Program program;

    // ���ȫ�ֺ���
    // Function globalFunc("global", Type::null);
    // program.addFunction(globalFunc);
    // cout << "add func "
    //      << "global"
    //      << " " << toString(Type::null) << "  in program" << endl;
    function_temp = Function("global", Type::null);

    // ���ȫ��������
    ScopeInfo scope_info;       // ����һ���µ�������
    scope_info.cnt = 0;         // �õ��µ��������cnt
    scope_info.name = "global"; // �õ��µ��������name
    symbol_table.scope_stack.push_back(scope_info);
    cout << "add scope_info " << symbol_table.scope_stack.back().name << " in symbol table" << endl;

    // �����ڵ�
    analysisCompUnit(root, program);

    // ���ȫ�ֱ���
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
    // ���ݹ۲죬CompUnit�ĵ�һ�����ӽڵ���Declֻ����ȫ�ָ�ֵ��䣬��һ�����ӽڵ���FuncDefֻ���Ǻ�������
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
        // ���µĺ�������֮ǰ
        if (function_temp.name == "global")
        {
            Instruction *globalreturn = new Instruction(ir::Operand(),
                                                        ir::Operand(),
                                                        ir::Operand(), ir::Operator::_return);
            Inst.push_back(globalreturn);
            pc++;

            cout << "add globalreturn" << endl;

            program.addFunction(function_temp);
            function_temp = Function();
            cout << "add func "
                 << "global"
                 << " " << toString(Type::null) << "  in program" << endl;

            for (int q = 0; q < pc; q++)
            {
                program.functions.back().addInst(Inst[q]);

                cout << "pc is " << q << " , add Instruction " << toString(Inst[q]->op) << " in program " << function_temp.name << endl;
                cout << toString(Inst[q]->op) << " " << toString(Inst[q]->des.type) << " " << Inst[q]->des.name << " " << toString(Inst[q]->op1.type) << " " << Inst[q]->op1.name << " " << toString(Inst[q]->op2.type) << " " << Inst[q]->op2.name << endl;
            }

            cout << "add return" << endl;
        }
        // FuncDef -> FuncType Ident '(' [FuncFParams] ')' Block
        function_temp = Function(); // ����
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

        // STE ste;
        // ste.operand = Operand(funcdef->v, funcdef->t);
        // symbol_table.scope_stack.back().table.insert({funcdef->v, ste});

        cout << "pc_old is " << pc_old << " pc_new is " << pc_new << endl;
        for (int q = pc_old; q < pc_new; q++)
        {
            program.functions.back().addInst(Inst[q]);

            cout << "pc is " << q << " " << toString(Inst[q]->op) << " " << toString(Inst[q]->des.type) << " " << Inst[q]->des.name << " " << toString(Inst[q]->op1.type) << " " << Inst[q]->op1.name << " " << toString(Inst[q]->op2.type) << " " << Inst[q]->op2.name << " in program " << function_temp.name << endl;
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
    // des��type�ȶ����
    Operand des("0", btype->t); // Ŀ��δ֪,������֪
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
    cout << pc << "  " << Inst.back()->des.name << " changed" << endl;
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
    GET_CHILD_PTR(l_or_a, Term, index);
    // �����飬��Ҫ�ı�des��type
    if (index < len - 2 && l_or_a->token.type == TokenType::LBRACK)
    {
        cout << "is array def to alloc" << endl;
        // ���￼�ǵ���ֵ��ʱ�����������ȴ��ڵ�ֵ���ʶ�ԭ��ָ��ݣ���������
        Instruction *old_inst = Inst.back();
        Inst.pop_back();
        pc--;
        cout << "pop an inst" << endl;

        cout << "to change the type" << endl;
        Type t = old_inst->des.type;
        if (t == Type::Int)
        {
            old_inst->op1.type = Type::Int;
            old_inst->des.type = Type::IntPtr;
        }

        else
        {
            old_inst->op1.type = Type::Float;
            old_inst->des.type = Type::FloatPtr;
        }

        old_inst->op = ir::Operator::alloc;

        cout << "add alloc" << endl;

        vector<int> dim;
        while (index < len - 2 && l_or_a->token.type == TokenType::LBRACK)
        {
            cout << "into one time" << endl;
            // op1��name��type
            index++;
            ANALYSIS(constexp, ConstExp, index);
            if (!constexp->is_computable)
            {
                map<std::string, int>::iterator it = result.find(constexp->v);
                if (it != result.end())
                {
                    dim.push_back(it->second);
                    cout << "array ������һ���ṹ����" << endl;
                }
            }
            else
            {
                dim.push_back(std::stoi(constexp->v));
            }
            index = index + 2;
            if (index < len)
            {
                GET_CHILD_PTR(l_or_a, Term, index);
                if (l_or_a->token.type == TokenType::ASSIGN)
                {
                    break;
                }
            }
        }

        int all = 1;
        for (int i = 0; i < dim.size(); i++)
        {
            all *= dim[i];
        }
        old_inst->op1.name = to_string(all);
        old_inst->op1.type = Type::IntLiteral;
        Inst.push_back(old_inst);
        pc++;

        cout << all << "           " << toString(Inst.back()->op) << endl;

        Operand op = Inst.back()->des;
        STE ste;
        ste.operand = op;
        ste.dimension = dim;

        symbol_table.scope_stack.back().table[op.name] = ste;

        cout << "add  " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;

        // �����Ҹ�ֵ
        // ����ָ�ָ�������д�������һ��������Ϊ���������ڶ���������ΪҪ�������������±꣬Ŀ�Ĳ�����Ϊ���������
        if (index < len)
        {
            index++;
            ANALYSIS(constinitval, ConstInitVal, index);
            index++;
        }
    }
    // �������飬�Ǿ�һ���Ǹ�ֵ
    else
    {
        // ���￼�ǵ���ֵ��ʱ�����������ȴ��ڵ�ֵ���ʶ�ԭ��ָ��ݣ���������
        Instruction *old_inst = Inst.back();
        Inst.pop_back();
        pc--;
        cout << "pop an inst" << endl;

        index++;
        ANALYSIS(constinitval, ConstInitVal, index);
        old_inst->op1.name = constinitval->v;
        old_inst->op1.type = constinitval->t;
        cout << "constinitval  " << toString(constinitval->t) << "  " << constinitval->v << endl;

        Inst.push_back(old_inst);
        pc++;

        cout << "the inst is           " << toString(Inst.back()->op) << endl;

        Operand op = Inst.back()->des;
        STE ste;
        ste.operand = op;
        symbol_table.scope_stack.back().table[op.name] = ste;
        cout << "add  " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;

        string name = old_inst->op1.name;
        cout << "op1 is " << name << endl;
        map<std::string, int>::iterator it = result.find(name);
        if (it != result.end())
        {
            result.insert({old_inst->des.name, it->second});
            cout << "result�н� " << old_inst->des.name << " �� " << it->second << " ��" << endl;
        }

        if (constinitval->is_computable)
        {
            result.insert({Inst.back()->des.name, stoi(constinitval->v)});
            cout << "result�н� " << Inst.back()->des.name << " �� " << stoi(constinitval->v) << " ��" << endl;
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
            // ����ָ�ָ�������д�������һ��������Ϊ���������ڶ���������ΪҪ�������������±꣬Ŀ�Ĳ�����Ϊ�������
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

                cout << "add store" << endl;

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
    // des��type�ȶ����
    Operand des("0", btype->t); // Ŀ��δ֪,������֪
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
    // des��name�ȶ����
    GET_CHILD_PTR(ident, Term, 0);
    cout << pc << "  " << Inst.back()->des.name << "changed" << endl;
    Inst.back()->des.name = ident->token.value;

    int key = 0; // �����жϵ�ǰ�Ƿ���������ֵ
    if (Inst.back()->des.type == Type::Int)
    {
        key = 1;
    }
    int len = root->children.size();
    int index = 1;
    if (index < len)
    {
        GET_CHILD_PTR(l_or_a, Term, index);
        // �����飬��Ҫ�ı�des��type
        if (index < len && l_or_a->token.type == TokenType::LBRACK)
        {
            // ���￼�ǵ���ֵ��ʱ�����������ȴ��ڵ�ֵ���ʶ�ԭ��ָ��ݣ���������
            Instruction *old_inst = Inst.back();
            Inst.pop_back();
            pc--;
            cout << "pop an inst" << endl;

            Type t = old_inst->des.type;
            if (t == Type::Int)
            {
                old_inst->op1.type = Type::Int;
                old_inst->des.type = Type::IntPtr;
            }

            else
            {
                old_inst->op1.type = Type::Float;
                old_inst->des.type = Type::FloatPtr;
            }

            old_inst->op = ir::Operator::alloc;

            cout << "add alloc" << endl;

            vector<int> dim;
            while (index < len && l_or_a->token.type == TokenType::LBRACK)
            {
                // op1��name��type
                index++;
                ANALYSIS(constexp, ConstExp, index);
                if (!constexp->is_computable)
                {
                    map<std::string, int>::iterator it = result.find(constexp->v);
                    if (it != result.end())
                    {
                        dim.push_back(it->second);
                        cout << "array ������һ���ṹ����" << endl;
                        cout << "dim add " << it->second << endl;
                    }
                }
                else
                {
                    dim.push_back(std::stoi(constexp->v));
                    cout << "dim add " << constexp->v << endl;
                }
                index = index + 2;
                if (index < len)
                {
                    GET_CHILD_PTR(l_or_a, Term, index);
                    if (l_or_a->token.type == TokenType::ASSIGN)
                    {
                        break;
                    }
                }
            }
            int all = 1;
            for (int i = 0; i < dim.size(); i++)
            {
                all *= dim[i];
            }
            old_inst->op1.name = to_string(all);
            old_inst->op1.type = Type::IntLiteral;
            Inst.push_back(old_inst);
            pc++;

            cout << "add alloc " << all << endl;

            cout << all << "           " << toString(Inst.back()->op) << endl;

            Operand op = Inst.back()->des;
            STE ste;
            ste.operand = op;
            ste.dimension = dim;

            symbol_table.scope_stack.back().table[op.name] = ste;
            cout << "add  " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;

            // �����Ҹ�ֵ
            // ����ָ�ָ�������д�������һ��������Ϊ���������ڶ���������ΪҪ�������������±꣬Ŀ�Ĳ�����Ϊ���������
            if (index < len)
            {
                index++;
                ANALYSIS(initval, InitVal, index);
                index++;
            }
        }
        // �������飬�Ǿ�һ���Ǹ�ֵ
        else
        {
            // ���￼�ǵ���ֵ��ʱ�����������ȴ��ڵ�ֵ���ʶ�ԭ��ָ��ݣ���������
            Instruction *old_inst = Inst.back();
            Inst.pop_back();
            pc--;
            cout << "pop an inst" << endl;

            index++;
            ANALYSIS(initval, InitVal, index);

            old_inst->op1.name = initval->v;
            old_inst->op1.type = initval->t;
            cout << "initval  " << toString(initval->t) << "  " << initval->v << endl;

            Inst.push_back(old_inst);
            pc++;

            cout << "add alloc" << endl;

            Operand op = Inst.back()->des;
            STE ste;
            ste.operand = op;
            symbol_table.scope_stack.back().table.insert({op.name, ste});
            cout << "add  " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;

            // �����������ֵ��ֱ����ӵ�result
            if (key)
            {
                if (initval->is_computable)
                {
                    result.insert({op.name, stoi(initval->v)});
                    cout << "result�н� " << op.name << " �� " << stoi(initval->v) << " ��" << endl;
                }
            }
        }
    }
    // ����һ��Ident�����κθ�ֵ
    else
    {
        STE ste;
        Operand op = Inst.back()->des;
        ste.operand = op;
        auto it = symbol_table.scope_stack.back().table.find(op.name);
        if (it != symbol_table.scope_stack.back().table.end())
        {
            symbol_table.scope_stack.back().table[op.name] = ste;
            cout << "///////add xiugai  " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
        }
        else
        {
            symbol_table.scope_stack.back().table.insert({op.name, ste});
            cout << "//////add  insert  " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
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
            // ����ָ�ָ�������д�������һ��������Ϊ���������ڶ���������ΪҪ�������������±꣬Ŀ�Ĳ�����Ϊ�������
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

                cout << "add store" << endl;

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

        cout << "add call global" << endl;
    }

    root->t = functype->t;
    root->v = ident->token.value;
    root->is_computable = false;

    if (root->children[3]->type == NodeType::FUNCFPARAMS)
    {
        // �������ڲ���
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

    STE ste;
    Operand op(ident->token.value, btype->t);
    ste.operand = op;
    auto it = symbol_table.scope_stack.back().table.find(op.name);
    if (it != symbol_table.scope_stack.back().table.end())
    {
        symbol_table.scope_stack.back().table[op.name] = ste;
        cout << "///////add xiugai  " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
    }
    else
    {
        symbol_table.scope_stack.back().table.insert({op.name, ste});
        cout << "//////add  insert  " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
    }

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
    cout << "add funcfparam " << toString(op1.type) << " " << op1.name << " in " << endl;

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
    // �� Sysy ��, ���������� Block ������
    // ������������ʱ, ����ű������ ScopeInfo, �൱��ѹջ
    symbol_table.add_scope(root);
    int len = root->children.size();
    int index = 1;
    while (index < len && root->children[index]->type == NodeType::BLOCKITEM)
    {
        ANALYSIS(blockitem, BlockItem, index);
        index++;
    }
    // �����������ʱ�������ڲ�����������˳����ں�����������󣬺����ڲ��ı��������ٿɼ���
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
        // ��һ��������Ϊ��ֵ�������ڶ�����������ʹ�ã����Ϊ����ֵ������
        Operand op1(exp->v, exp->t);
        Operand des(lval->v, lval->t);
        ir::Instruction *movInst = new Instruction(op1,
                                                   ir::Operand(),
                                                   des, ir::Operator::mov);
        Inst.push_back(movInst);
        pc++;

        cout << "add mov" << endl;

        if (exp->t == Type::Int)
        {
            map<std::string, int>::iterator it = result.find(exp->v);
            if (it != result.end())
            {
                result.insert({lval->v, it->second});
                cout << "result�н� " << lval->v << " �� " << it->second << " ��" << endl;
            }
        }
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
            // ��һ��goto,ָ��������ִ��
            Instruction *gotoInst1 = new Instruction(op1,
                                                     ir::Operand(),
                                                     ir::Operand("2", ir::Type::IntLiteral), ir::Operator::_goto);
            Inst.push_back(gotoInst1);
            pc++;

            cout << "add goto" << endl;

            int pc_to_change1 = pc; // ��Ҫ�޸ĵ�ָ���λ�ã�ָ����һ��else if ��俪ʼǰ

            // �ڶ���goto,ָ����һ���ж����,��Ҫ����
            Instruction *gotoInst2 = new Instruction(ir::Operand(),
                                                     ir::Operand(),
                                                     ir::Operand("1", ir::Type::IntLiteral), ir::Operator::_goto);
            Inst.push_back(gotoInst2);
            pc++;

            cout << "add goto" << endl;
            int pc_1 = pc;
            ANALYSIS(stmt, Stmt, 4);
            int pc_to_change2 = pc;
            // ������goto,ָ���յ�,��Ҫ����
            Instruction *gotoInst = new Instruction(ir::Operand(),
                                                    ir::Operand(),
                                                    ir::Operand("1", Type::IntLiteral),
                                                    ir::Operator::_goto);
            Inst.push_back(gotoInst);
            pc++;

            cout << "add goto" << endl;

            int pc_2 = pc;

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
            // ��һ��goto,ָ��������ִ��
            Instruction *gotoInst1 = new Instruction(op1,
                                                     ir::Operand(),
                                                     ir::Operand("2", ir::Type::IntLiteral), ir::Operator::_goto);
            Inst.push_back(gotoInst1);
            pc++;

            cout << "add goto" << endl;

            int pc_to_change1 = pc;

            // �ڶ���goto,ָ���յ�
            Instruction *gotoInst2 = new Instruction(ir::Operand(),
                                                     ir::Operand(),
                                                     ir::Operand("1", ir::Type::IntLiteral), ir::Operator::_goto);
            Inst.push_back(gotoInst2);
            pc++;

            cout << "add goto" << endl;

            ANALYSIS(stmt, Stmt, 4);

            string pc_again = to_string(while_begin - pc);
            // ������goto,ָ�����
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

    // else
    // {
    //     root->t = Type::null;
    // }

    if (index < len)
    {
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
        // ȡ��ָ�����loadָ��������ȡ������һ��������Ϊ���������ڶ���������ΪҪȡ�����������±꣬Ŀ�Ĳ�����Ϊȡ����ű�����
        Operand op1 = symbol_table.get_operand(ident->v);
        Operand op2("0", Type::IntLiteral);
        string id = "t" + to_string(counter++);
        root->v = id;
        Operand des(id, t);
        vector<int> dimension = ste.dimension;

        vector<int> dim;
        GET_CHILD_PTR(lbrack, Term, index);
        string arr_index_name;
        int num = 0;
        while (index < len && lbrack->token.type == TokenType::LBRACK)
        {
            num++;
            index++;
            ANALYSIS(exp, Exp, index);
            if (exp->is_computable)
            {
                dim.push_back(stoi(exp->v));
                cout << "array find is " << exp->v << endl;
            }
            else
            {
                arr_index_name = exp->v;
                map<std::string, int>::iterator it1 = result.find(exp->v);
                dim.push_back(it1->second);
                cout << "array find is " << it1->second << endl;
            }
            index = index + 2;
        }

        if (num == 1 && arr_index_name != "")
        {
            op2.name = arr_index_name;
            op2.type = Type::Int;
            Instruction *loadInst = new Instruction(op1,
                                                    op2, des, ir::Operator::load);
            Inst.push_back(loadInst);
            pc++;

            cout << "add load" << endl;
        }
        else
        {
            int all = calculateIndex(dimension, dim); // �õ�λ��
            op2.name = to_string(all);
            // ��һ��������Ϊ��ֵ�������ڶ�����������ʹ�ã����Ϊ����ֵ������
            Instruction *loadInst = new Instruction(op1,
                                                    op2, des, ir::Operator::load);
            Inst.push_back(loadInst);
            pc++;

            cout << "add load" << endl;
        }

        op = des;
        ste;
        ste.operand = op;
        symbol_table.scope_stack.back().table.insert({op.name, ste});
        cout << "add  " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;

        root->t = t;
        root->v = id;
    }
    else
    {
        Operand op = symbol_table.get_operand(ident->v);
        root->v = ident->v;
        root->t = op.type;
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
            // defһ��0
            Operand op1("0", Type::IntLiteral);
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

            // ����
            //  defһ��0
            op1 = des;
            Operand op2(unaryexp->v, unaryexp->t);
            id = "t" + to_string(counter++);
            des = Operand(id, Type::Int);
            if (unaryexp->is_computable)
            {

                Instruction *subInst = new Instruction(op1, op2, des, ir::Operator::subi);
                Inst.push_back(subInst);
                cout << "add sub" << endl;
            }
            else
            {
                Instruction *subInst = new Instruction(op1, op2, des, ir::Operator::sub);
                Inst.push_back(subInst);
                cout << "add sub" << endl;
            }

            pc++;

            ste.operand = des;
            symbol_table.scope_stack.back().table.insert({des.name, ste});
            cout << "add  " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;

            root->v = id;

            if (unaryexp->is_computable)
            {
                result.insert({id, -stoi(unaryexp->v)});
                cout << "result�н� " << id << " �� " << -stoi(unaryexp->v) << " ��" << endl;
            }
        }
        else
        {
            // ����ȡ������ ! ����һ��������Ϊȡ�Ǳ������ڶ�����������ʹ�ã����Ϊȡ�ǽ��������
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
            vector<Operand> paraList = {};
            callInst_temp = new ir::CallInst(Operand(), paraList, Operand());
            ANALYSIS(funcrparam, FuncRParams, 2);
            // һ��������Ϊ��ֵ�������ڶ�����������ʹ�ã����Ϊ����ֵ������
            Operand op1 = symbol_table.get_operand(ident->v);
            string id = "t" + to_string(counter++);
            Operand des(id, op1.type);
            root->v = id;

            vector<Operand> paraVec1 = callInst_temp->argumentList;
            ir::CallInst *callInst = new ir::CallInst(op1, paraVec1, des);
            cout << "call func param is����" << paraVec1.size() << endl;
            for (int i = 0; i < paraVec1.size(); i++)
            {
                cout << toString(paraVec1[i].type) << " " << paraVec1[i].name << endl;
            }
            Inst.push_back(callInst);
            pc++;

            cout << "add call" << endl;

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

            cout << "add call" << endl;

            STE ste;
            Operand op = des;
            ste.operand = op;
            symbol_table.scope_stack.back().table.insert({op.name, ste});
            cout << "add  " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
        }
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

    cout << "add FuncRParam " << toString(exp->t) << " " << exp->v << " in FuncRParams" << endl;
    paraVec1.push_back(op);

    COPY_EXP_NODE(exp, root);
    int len = root->children.size();
    int index = 1;
    while (index < len)
    {
        cout << "index is " << index << " : to analysis funcrpapam" << endl;
        index++;
        ANALYSIS(exp_right, Exp, index);
        Operand op(exp_right->v, exp_right->t);
        cout << "add FuncRParam " << toString(exp_right->t) << " " << exp_right->v << " in FuncRParams" << endl;
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

        if (unaryexp->is_computable) // �˷��ǳ�����Ҫ�ȶ���
        {
            Operand op1(unaryexp->v, unaryexp->t);
            string id = "t" + to_string(counter++);

            result.insert({id, stoi(unaryexp->v)});
            cout << "result�н� " << id << " �� " << stoi(unaryexp->v) << " ��" << endl;

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

        if (unaryexp_right->is_computable) // �˷��ǳ�����Ҫ�ȶ���
        {
            Operand op1(unaryexp_right->v, unaryexp_right->t);
            string id = "t" + to_string(counter++);

            result.insert({id, stoi(unaryexp_right->v)});
            cout << "result�н� " << id << " �� " << stoi(unaryexp_right->v) << " ��" << endl;

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
        Operand op1(unaryexp->v, unaryexp->t);
        Operand op2(unaryexp_right->v, unaryexp_right->t);
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

            string name1 = op1.name;
            string name2 = op2.name;
            string name3 = des.name;

            map<std::string, int>::iterator it1 = result.find(name1);
            map<std::string, int>::iterator it2 = result.find(name2);
            if (it1 != result.end() && it2 != result.end())
            {
                cout << name1 << "      " << name2 << endl;
                result.insert({name3, it1->second * it2->second});
                cout << "result�н� " << name3 << " �� " << it1->second * it2->second << " ��" << endl;
            }
        }
        else if (term->token.type == TokenType::DIV)
        {
            Instruction *divInst = new Instruction(op1,
                                                   op2,
                                                   des, ir::Operator::div);
            Inst.push_back(divInst);
            pc++;

            cout << "add div" << endl;

            string name1 = op1.name;
            string name2 = op2.name;
            string name3 = des.name;
            map<std::string, int>::iterator it1 = result.find(name1);
            map<std::string, int>::iterator it2 = result.find(name2);
            if (it1 != result.end() && it2 != result.end())
            {
                cout << name1 << "      " << name2 << endl;
                result.insert({name3, it1->second / it2->second});
                cout << "result�н� " << name3 << " �� " << it1->second / it2->second << " ��" << endl;
            }
        }
        else
        {
            Instruction *modInst = new Instruction(op1,
                                                   op2,
                                                   des, ir::Operator::mod);
            Inst.push_back(modInst);
            pc++;

            cout << "add mod" << endl;

            string name1 = op1.name;
            string name2 = op2.name;
            string name3 = des.name;
            map<std::string, int>::iterator it1 = result.find(name1);
            map<std::string, int>::iterator it2 = result.find(name2);
            if (it1 != result.end() && it2 != result.end())
            {
                cout << name1 << "      " << name2 << endl;
                result.insert({name3, it1->second % it2->second});
                cout << "result�н� " << name3 << " �� " << it1->second % it2->second << " ��" << endl;
            }
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

        // �������ǳ���
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
        // ���������ǳ���
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
            Operand des(id, Type::Int);
            if (term->token.type == TokenType::PLUS)
            {
                Instruction *addInst = new Instruction(op1, op2, des, ir::Operator::add);
                Inst.push_back(addInst);
                pc++;

                cout << "add add" << endl;

                string name1 = op1.name;
                string name2 = op2.name;
                string name3 = des.name;
                map<std::string, int>::iterator it1 = result.find(name1);
                map<std::string, int>::iterator it2 = result.find(name2);
                if (it1 != result.end() && it2 != result.end())
                {
                    cout << name1 << "      " << name2 << endl;
                    result.insert({name3, it1->second + it2->second});
                    cout << "result�н� " << name3 << " �� " << it1->second + it2->second << " ��" << endl;
                }
            }
            else
            {
                Instruction *subInst = new Instruction(op1, op2, des, ir::Operator::sub);
                Inst.push_back(subInst);
                pc++;

                cout << "add sub" << endl;

                string name1 = op1.name;
                string name2 = op2.name;
                string name3 = des.name;
                map<std::string, int>::iterator it1 = result.find(name1);
                map<std::string, int>::iterator it2 = result.find(name2);
                if (it1 != result.end() && it2 != result.end())
                {
                    cout << name1 << "      " << name2 << endl;
                    result.insert({name3, it1->second - it2->second});
                    cout << it1->second << "    " << it2->second << endl;
                    cout << "result�н� " << name3 << " �� " << it1->second - it2->second << " ��" << endl;
                }
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
                    Instruction *addiInst = new Instruction(op1,
                                                            op2,
                                                            des, ir::Operator::addi);
                    Inst.push_back(addiInst);
                    pc++;

                    cout << "add addi" << endl;
                    cout << pc - 1 << "************************************************************des name is " << des.name << endl;

                    Operand op = des;
                    STE ste;
                    ste.operand = op;
                    symbol_table.scope_stack.back().table.insert({op.name, ste});
                    cout << "add  " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;

                    map<std::string, int>::iterator it = result.find(mulexp->v);
                    if (it != result.end())
                    {
                        result.insert({id, it->second + stoi(mulexp_right->v)});
                        cout << "result�н� " << id << " �� " << it->second + stoi(mulexp_right->v) << " ��" << endl;
                    }
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

        STE ste;
        ste.operand = des;
        symbol_table.scope_stack.back().table.insert({des.name, ste});
        cout << "add  " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
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
            Operand op1(relexp->v, relexp->t);
            Operand op2(relexp_right->v, relexp_right->t);
            Operand des(id, Type::Int);
            Instruction *eqInst = new Instruction(op1, op2, des, ir::Operator::neq);
            Inst.push_back(eqInst);
            pc++;

            cout << "add eq" << endl;
            relexp_right->v = id;

            STE ste;
            ste.operand = des;
            symbol_table.scope_stack.back().table.insert({des.name, ste});
            cout << "add  " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
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
        map<string, int>::iterator it = result.find(eqexp->v);
        if (it != result.end() && it->second)
        {
        }
        else
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
        if (landexp->is_computable) // �˷��ǳ�����Ҫ�ȶ���
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
        if (lorexp->is_computable) // �˷��ǳ�����Ҫ�ȶ���
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
