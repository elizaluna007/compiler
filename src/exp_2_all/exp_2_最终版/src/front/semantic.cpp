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
frontend::STE ste_temp;
// ���������Ҫ�жϵ������и���
vector<int> break_pc = {};

map<string, int> result;
map<string, int> result_arr;
vector<Operand> back;
int arr_len = 0;
int cnt = 0;
// ���������Լ���ά��
map<string, vector<string>> arr_dim;

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

    ScopeInfo scope_info;                                        // ����һ���µ�������
    scope_info.cnt = cnt++;                                      // �õ��µ��������cnt
    scope_info.name = "block_" + std::to_string(scope_info.cnt); // �õ��µ��������nameΪ"block_����_���"
                                                                 // �ڷ���� IR �Ĺ�����������Ҫ�����ͨ����������ͬ������������, ���ǵĽ��������������, Ϊ��������������������صĺ�׺ʹ��������֮��ı���������һ�� IR Function ���Ƕ�һ�޶���
    scope_stack.push_back(scope_info);                           // ���µ�������ѹ��������ջ
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
    cout << "��ǰ��������" << scope_stack.back().name << endl;
    cout << "�����ʱ������Ƕ��֮�����������Ƿ��Ѵ����������ı���" << endl;
    for (int i = scope_stack.size() - 1; i >= 0; i--)
    {
        cout << "��������" << scope_stack[i].name << "�в���" << id << endl;
        auto iter = scope_stack[i].table.find(id);
        if (iter != scope_stack[i].table.end())
        {
            cout << "��������" << scope_stack[i].name << "���ҵ���" << id << endl;
            return id + "_" + to_string(scope_stack.back().cnt);
        }
    }
    // �����ڵ�ǰ��������û�б����壺�����ǰ�������ڲ�������ñ�������ͬ�Ķ��壬����Ҫ����������������ζ�Ÿñ��������ⲿ�������ж���Ļ��߻�δ���壬���������������
    // �����ڵ�ǰ���������ж�����壺�����ǰ�������ڴ��ڶ����ñ�������ͬ�Ķ��壬�������������������ô��Ҫ��������������Ϊ�ڷ���� IR �Ĺ����У���������һ���������ڱ�����Ψһ�ģ����������������ͻ��
    // ������Ƕ�׵��������б����壺���������Ƕ�׵��������б����壬���������������Ҳ������ñ�������ͬ�Ķ��壬��ô��Ҫ��������������Ϊ���ڲ��������У���Ҫ�����������������ͬ���ı�������ȷ���������õ���ȷ�ԡ�
    cout << "����ʱ����Ҫ���������ʷ���ԭֵ" << id << endl;
    return id;
}
string frontend::SymbolTable::get_scoped_name_use(string id) const
{
    cout << "ʹ�õ�ʱ�������ǰ����Ƿ����ԭֵ�Լ���������ֵ" << endl;
    for (int i = scope_stack.size() - 1; i >= 0; i--)
    {
        cout << "��������" << scope_stack[i].name << "�в���" << id << endl;
        auto iter = scope_stack[i].table.find(id);
        if (iter != scope_stack[i].table.end())
        {
            cout << "��������" << scope_stack[i].name << "���ҵ���" << id << endl;
            return id;
        }
        iter = scope_stack[i].table.find(id + "_" + to_string(scope_stack[i].cnt));
        if (iter != scope_stack[i].table.end())
        {
            cout << "��������" << scope_stack[i].name << "���ҵ���" << id + "_" + to_string(scope_stack[i].cnt) << endl;
            return id + "_" + to_string(scope_stack[i].cnt);
        }
    }
}
// ��������������Ǹ���һ����ʶ�� id ��ȡ����Ӧ�Ĳ���������������ʶ����һ���������򷵻�һ���Ĵ�����ջ�ϵ�λ�ã������һ���������򷵻�����ֵ��
// �ڵ�ǰ��������������ʶ���Ƿ��Ѿ����壬����Ѿ����壬�򷵻����Ĳ�������
// �����ǰ������û�ж��������ʶ������ݹ��������������в��ң�ֱ���ҵ����ߵ�ȫ��������Ϊֹ��
// ���ȫ��������Ҳû�ж��������ʶ������˵������һ��δ�����ı�ʶ������Ҫ��������һ������Ĳ�������
// ����һ��������, �ڷ��ű���Ѱ�������ͬ������, ���ض�Ӧ�� Operand(ע�⣬�� Operand �� name �����������)
Operand frontend::SymbolTable::get_operand(string id) const
{
    auto iter = get_lib_funcs()->find(id);
    if (iter != get_lib_funcs()->end())
    {
        return Operand(id, iter->second->returnType);
    }
    const auto &current_scope = scope_stack.back(); // ��ǰ������
    auto it = current_scope.table.find(id);         // ��ǰ���������id

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
    function_temp = Function("global", Type::null);

    // ���ȫ��������
    ScopeInfo scope_info;       // ����һ���µ�������
    scope_info.cnt = 0;         // �õ��µ��������cnt
    scope_info.name = "global"; // �õ��µ��������name
    symbol_table.scope_stack.push_back(scope_info);
    cout << "add scope_info " << symbol_table.scope_stack.back().name << " in symbol table" << endl;

    // �����ڵ�
    analysisCompUnit(root, program);

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
            // ���ȫ�ֱ���
            for (auto &iter : symbol_table.scope_stack[0].table)
            {
                auto item = result_arr.find(iter.first);
                if (item != result_arr.end())
                {
                    ir::GlobalVal g(iter.second.operand, item->second);
                    program.globalVal.push_back(g);
                }
                else
                    program.globalVal.push_back(iter.second.operand);
            }
            Instruction *globalreturn = new Instruction(ir::Operand(),
                                                        ir::Operand(),
                                                        ir::Operand(), ir::Operator::_return);
            Inst.push_back(globalreturn);
            pc++;

            program.addFunction(function_temp);
            function_temp = Function();
            cout << "add function global" << toString(Type::null) << "  in program" << endl;

            for (int q = 0; q < pc; q++)
            {
                program.functions.back().addInst(Inst[q]);

                cout << "pc = " << q << ":  " << toString(Inst[q]->op) << " " << toString(Inst[q]->des.type) << " " << Inst[q]->des.name << " " << toString(Inst[q]->op1.type) << " " << Inst[q]->op1.name << " " << toString(Inst[q]->op2.type) << " " << Inst[q]->op2.name << endl;
            }
        }

        cout << "********************************begin a function********************************" << endl;
        ANALYSIS(funcdef, FuncDef, 0);
        cout << "**********************************end a function********************************" << endl;

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
    Operator op;
    if (btype->t == Type::Int)
    {
        op1.name = "0";
        op1.type = Type::IntLiteral;
        des.type = Type::Int;
        op = Operator::def;
    }
    else
    {
        op1.name = "0";
        op1.type = Type::FloatLiteral;
        des.type = Type::Float;
        op = Operator::fdef;
    }
    Instruction *assignInst = new Instruction(op1,
                                              Operand(),
                                              des,
                                              op);
    Inst.push_back(assignInst);
    pc++;

    cout << "add def/fdef" << endl;

    ANALYSIS(constdef, ConstDef, 2);

    int len = root->children.size();
    int index = 3;
    GET_CHILD_PTR(c_or_s, Term, index);
    while (index < len && c_or_s->token.type == TokenType::COMMA)
    {
        Instruction *assignInst = new Instruction(op1,
                                                  Operand(),
                                                  des,
                                                  op);
        Inst.push_back(assignInst);
        pc++;

        cout << "add def/fdef" << endl;

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
    int len = root->children.size();
    int index = 0;
    GET_CHILD_PTR(ident, Term, index);
    // todo
    // ident->v = ident->token.value;
    ident->v = symbol_table.get_scoped_name(ident->token.value);
    Inst.back()->des.name = ident->v;
    index = 1;
    GET_CHILD_PTR(l_or_a, Term, index);
    // �����飬��Ҫ�ı�des��type
    if (index < len - 2 && l_or_a->token.type == TokenType::LBRACK)
    {
        // ���￼�ǵ���ֵ��ʱ�����������ȴ��ڵ�ֵ���ʶ�ԭ��ָ��ݣ���������
        Instruction *old_inst = Inst.back();
        Inst.pop_back();
        pc--;
        cout << "pop an inst" << endl;

        cout << "to change the type" << endl;
        Type t = old_inst->des.type;
        Type t_init;
        if (t == Type::Int)
        {
            old_inst->op1.type = Type::Int;
            old_inst->des.type = Type::IntPtr;
            t_init = Type::IntLiteral;
        }

        else
        {
            old_inst->op1.type = Type::Float;
            old_inst->des.type = Type::FloatPtr;
            t_init = Type::FloatLiteral;
        }

        old_inst->op = ir::Operator::alloc;

        cout << "add alloc" << endl;
        string id = "t" + to_string(counter++);
        Operand mul_temp(id, Type::Int);
        Instruction *inst = new Instruction(Operand("1", Type::IntLiteral), Operand(), mul_temp, Operator::def);
        Inst.push_back(inst);
        pc++;

        vector<int> dim;
        while (index < len - 2 && l_or_a->token.type == TokenType::LBRACK)
        {
            // op1��name��type
            index++;
            ANALYSIS(constexp, ConstExp, index);
            if (!constexp->is_computable)
            {
                id = "t" + to_string(counter++);
                inst = new Instruction(mul_temp, Operand(constexp->v, Type::Int), Operand(id, Type::Int), Operator::mul);
                Inst.push_back(inst);
                pc++;

                mul_temp = Operand(id, Type::Int);

                map<std::string, int>::iterator it = result.find(constexp->v);
                if (it != result.end())
                {
                    dim.push_back(it->second);
                    cout << "array ������һ���ṹ����" << endl;
                }
            }
            else
            {
                id = "t" + to_string(counter++);
                Operand mul_temp_2(id, Type::Int);
                inst = new Instruction(Operand(constexp->v, Type::IntLiteral), Operand(), mul_temp_2, Operator::def);
                Inst.push_back(inst);
                pc++;

                id = "t" + to_string(counter++);
                Instruction *inst = new Instruction(mul_temp, mul_temp_2, Operand(id, Type::Int), Operator::mul);
                Inst.push_back(inst);
                pc++;

                mul_temp = Operand(id, Type::Int);

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
        arr_len = all;
        old_inst->op1.name = id;
        old_inst->op1.type = Type::Int;
        Inst.push_back(old_inst);
        pc++;

        cout << all << "           " << toString(Inst.back()->op) << endl;
        cout << "�õ�����" << Inst.back()->des.name << "�Ĵ�С��" << to_string(all) << endl;

        Operand op = Inst.back()->des;
        STE ste;
        ste.operand = op;
        ste.dimension = dim;

        symbol_table.scope_stack.back().table.insert({op.name, ste});

        cout << "add  " << toString(op.type) << " " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
        result_arr.insert({op.name, arr_len});
        cout << "��ʼ�����ʼ�����õ�������Ĵ�С��" << arr_len << endl;
        for (int i = 0; i < arr_len; i++)
        {
            string id = "t" + to_string(counter++);
            Instruction *inst = new Instruction(op,
                                                Operand(to_string(i), Type::IntLiteral),
                                                Operand("0", t_init),
                                                ir::Operator::store);
            Inst.push_back(inst);
            pc++;

            cout << "add store" << endl;
        }
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
        if ((constinitval->t == Type::Int || constinitval->t == Type::IntLiteral) && old_inst->des.type == Type::Float)
        {
            string id = "t" + to_string(counter++);
            Instruction *inst = new Instruction(Operand(constinitval->v, constinitval->t),
                                                Operand(),
                                                Operand(id, Type::Float),
                                                Operator::cvt_i2f);
            Inst.push_back(inst);
            pc++;

            cout << "add cvt_i2f inst" << endl;
            constinitval->t = Type::Float;
            constinitval->v = id;
            constinitval->is_computable = false;
        }
        else if ((constinitval->t == Type::Float || constinitval->t == Type::FloatLiteral) && old_inst->des.type == Type::Int)
        {
            string id = "t" + to_string(counter++);
            Instruction *inst = new Instruction(Operand(constinitval->v, constinitval->t),
                                                Operand(),
                                                Operand(id, Type::Int),
                                                Operator::cvt_f2i);
            Inst.push_back(inst);
            pc++;

            cout << "add cvt_f2i inst" << endl;
            constinitval->t = Type::Int;
            constinitval->v = id;
            constinitval->is_computable = false;
        }
        old_inst->op1.name = constinitval->v;
        old_inst->op1.type = constinitval->t;

        Inst.push_back(old_inst);
        pc++;

        cout << "the inst is           " << toString(Inst.back()->op) << endl;

        Operand op = Inst.back()->des;
        STE ste;
        ste.operand = op;
        symbol_table.scope_stack.back().table[op.name] = ste;
        cout << "add  " << toString(op.type) << " " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;

        string name = old_inst->op1.name;
        cout << "op1 is " << name << endl;
        if (old_inst->op1.type == Type::Int || old_inst->op1.type == Type::IntLiteral)
        {
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
        Operand des = Inst.back()->op1; // allocָ���des�����ƺ�����
        Type t;
        if (des.type == Type::IntPtr)
        {
            t = Type::Int;
        }
        else
        {
            t = Type::Float;
        }
        if (root->children[1]->type == NodeType::CONSTINITVAL)
        {
            // ����ָ�ָ�������д�������һ��������Ϊ���������ڶ���������ΪҪ�������������±꣬Ŀ�Ĳ�����Ϊ�������
            int index = 1;
            int arr_index = 0;

            while (index < len)
            {
                ANALYSIS(constinitval, ConstInitVal, index);
                index = index + 2;

                if ((constinitval->t == Type::Int || constinitval->t == Type::IntLiteral) && t == Type::Float)
                {
                    string id = "t" + to_string(counter++);
                    Instruction *inst = new Instruction(Operand(constinitval->v, constinitval->t), Operand(), Operand(id, Type::Float), Operator::cvt_i2f);
                    Inst.push_back(inst);
                    pc++;

                    cout << "add i2f" << endl;
                    constinitval->v = id;
                    constinitval->t = Type::Float;
                    constinitval->is_computable = false;
                }
                if ((constinitval->t == Type::Float || constinitval->t == Type::FloatLiteral) && t == Type::Int)
                {
                    string id = "t" + to_string(counter++);
                    Instruction *inst = new Instruction(Operand(constinitval->v, constinitval->t), Operand(), Operand(id, Type::Float), Operator::cvt_f2i);
                    Inst.push_back(inst);
                    pc++;

                    cout << "add f2i" << endl;
                    constinitval->v = id;
                    constinitval->t = Type::Float;
                    constinitval->is_computable = false;
                }
                Instruction *storeInst = new Instruction(des,
                                                         Operand(to_string(arr_index), Type::IntLiteral),
                                                         Operand(constinitval->v, constinitval->t),
                                                         ir::Operator::store);
                Inst.push_back(storeInst);
                pc++;

                cout << "add store" << endl;

                arr_index++;
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
    Operator op;
    if (btype->t == Type::Int)
    {
        op1.name = "0";
        op1.type = Type::IntLiteral;
        des.type = Type::Int;
        op = Operator::def;
    }
    else
    {
        op1.name = "0";
        op1.type = Type::FloatLiteral;
        des.type = Type::Float;
        op = Operator::fdef;
    }
    Instruction *assignInst = new Instruction(op1,
                                              ir::Operand(),
                                              des,
                                              op);
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
                                                      op);
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
    // todo
    // ident->v = ident->token.value;
    ident->v = symbol_table.get_scoped_name(ident->token.value);
    Inst.back()->des.name = ident->v;
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
            Type t_init;
            if (t == Type::Int)
            {
                old_inst->op1.type = Type::Int;
                old_inst->des.type = Type::IntPtr;
                t_init = Type::IntLiteral;
            }

            else
            {
                old_inst->op1.type = Type::Float;
                old_inst->des.type = Type::FloatPtr;
                t_init = Type::FloatLiteral;
            }

            old_inst->op = ir::Operator::alloc;

            cout << "add alloc" << endl;

            string id = "t" + to_string(counter++);
            Operand mul_temp(id, Type::Int);
            Instruction *inst = new Instruction(Operand("1", Type::IntLiteral), Operand(), mul_temp, Operator::def);
            Inst.push_back(inst);
            pc++;

            string arr_name = old_inst->des.name;
            vector<string> dim_index = {};
            vector<int> dim;
            while (index < len && l_or_a->token.type == TokenType::LBRACK)
            {
                // op1��name��type
                index++;
                ANALYSIS(constexp, ConstExp, index);
                if (!constexp->is_computable) // δ֪����ֱ�����
                {
                    id = "t" + to_string(counter++);
                    inst = new Instruction(mul_temp, Operand(constexp->v, Type::Int), Operand(id, Type::Int), Operator::mul);
                    Inst.push_back(inst);
                    pc++;

                    mul_temp = Operand(id, Type::Int);

                    map<std::string, int>::iterator it = result.find(constexp->v);
                    if (it != result.end())
                    {
                        dim.push_back(it->second);
                        cout << "array ������һ���ṹ����" << endl;
                        cout << "dim add " << it->second << endl;
                    }
                    dim_index.push_back(constexp->v);
                }
                else
                {
                    id = "t" + to_string(counter++);
                    Operand mul_temp_2(id, Type::Int);
                    inst = new Instruction(Operand(constexp->v, Type::IntLiteral), Operand(), mul_temp_2, Operator::def);
                    Inst.push_back(inst);
                    pc++;

                    dim_index.push_back(id);
                    STE ste;
                    ste.operand = mul_temp_2;
                    symbol_table.scope_stack.back().table.insert({id, ste});

                    id = "t" + to_string(counter++);
                    Instruction *inst = new Instruction(mul_temp, mul_temp_2, Operand(id, Type::Int), Operator::mul);
                    Inst.push_back(inst);
                    pc++;

                    mul_temp = Operand(id, Type::Int);

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
            // ��������������ά�Ȱ�
            arr_dim[arr_name] = dim_index;

            int all = 1;
            for (int i = 0; i < dim.size(); i++)
            {
                all *= dim[i];
            }
            arr_len = all;
            old_inst->op1.name = id;
            old_inst->op1.type = Type::Int;
            Inst.push_back(old_inst);
            pc++;

            cout << "add alloc " << all << endl;

            cout << all << "           " << toString(Inst.back()->op) << endl;

            Operand op = Inst.back()->des;
            STE ste;
            ste.operand = op;
            ste.dimension = dim;

            // symbol_table.scope_stack.back().table[op.name] = ste;
            symbol_table.scope_stack.back().table.insert({op.name, ste});
            cout << "add  " << toString(op.type) << " " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
            result_arr.insert({op.name, arr_len});
            cout << "��ʼ�����ʼ�����õ�������Ĵ�С��" << arr_len << endl;
            for (int i = 0; i < arr_len; i++)
            {
                string id = "t" + to_string(counter++);
                Instruction *inst = new Instruction(op,
                                                    Operand(to_string(i), Type::IntLiteral),
                                                    Operand("0", t_init),
                                                    ir::Operator::store);
                Inst.push_back(inst);
                pc++;

                cout << "add store" << endl;
            }

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
            if ((initval->t == Type::Int || initval->t == Type::IntLiteral) && old_inst->des.type == Type::Float)
            {
                string id = "t" + to_string(counter++);
                Instruction *inst = new Instruction(Operand(initval->v, initval->t),
                                                    Operand(),
                                                    Operand(id, Type::Float),
                                                    Operator::cvt_i2f);
                Inst.push_back(inst);
                pc++;

                cout << "add cvt_i2f inst" << endl;
                initval->t = Type::Float;
                initval->v = id;
                initval->is_computable = false;
            }
            else if ((initval->t == Type::Float || initval->t == Type::FloatLiteral) && old_inst->des.type == Type::Int)
            {
                string id = "t" + to_string(counter++);
                Instruction *inst = new Instruction(Operand(initval->v, initval->t),
                                                    Operand(),
                                                    Operand(id, Type::Int),
                                                    Operator::cvt_f2i);
                Inst.push_back(inst);
                pc++;

                cout << "add cvt_f2i inst" << endl;
                initval->t = Type::Int;
                initval->v = id;
                initval->is_computable = false;
            }

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
            cout << "add  " << toString(op.type) << " " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;

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
            cout << "update  " << toString(op.type) << " " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
        }
        else
        {
            symbol_table.scope_stack.back().table.insert({op.name, ste});
            cout << "insert  " << toString(op.type) << " " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
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
        Operand des = Inst.back()->op1; // ��һ���϶��ǳ�ʼ���ģ����Եõ�op1
        Type t;
        Type t_init;
        if (des.type == Type::IntPtr)
        {
            t = Type::Int;
            t_init = Type::IntLiteral;
        }
        else
        {
            t = Type::Float;
            t_init = Type::FloatLiteral;
        }

        if (root->children[1]->type == NodeType::INITVAL) // �϶������鸳ֵ
        {
            //  ����ָ�ָ�������д�������һ��������Ϊ���������ڶ���������ΪҪ�������������±꣬Ŀ�Ĳ�����Ϊ�������
            int index = 1;
            int arr_index = 0;
            while (index < len)
            {
                ANALYSIS(initval, InitVal, index);
                index = index + 2;
                if ((initval->t == Type::Int || initval->t == Type::IntLiteral) && t == Type::Float)
                {
                    string id = "t" + to_string(counter++);
                    Instruction *inst = new Instruction(Operand(initval->v, initval->t), Operand(), Operand(id, Type::Float), Operator::cvt_i2f);
                    Inst.push_back(inst);
                    pc++;

                    cout << "add i2f" << endl;
                    initval->v = id;
                    initval->t = Type::Float;
                    initval->is_computable = false;
                }
                if ((initval->t == Type::Float || initval->t == Type::FloatLiteral) && t == Type::Int)
                {
                    string id = "t" + to_string(counter++);
                    Instruction *inst = new Instruction(Operand(initval->v, initval->t), Operand(), Operand(id, Type::Float), Operator::cvt_f2i);
                    Inst.push_back(inst);
                    pc++;

                    cout << "add f2i" << endl;
                    initval->v = id;
                    initval->t = Type::Float;
                    initval->is_computable = false;
                }
                Instruction *storeInst = new Instruction(des,
                                                         Operand(to_string(arr_index), Type::IntLiteral),
                                                         Operand(initval->v, initval->t),
                                                         ir::Operator::store);
                Inst.push_back(storeInst);
                pc++;

                cout << "add store" << endl;

                arr_index++;
            }
            STE ste = symbol_table.get_ste(des.name);
            vector<int> dim = ste.dimension;
            cout << "�������С���" << endl;
            for (int i = 0; i < dim.size(); i++)
            {
                cout << i << " is " << dim[i] << endl;
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
// FuncDef -> FuncType Ident '(' [FuncFParams] ')' BlockcallInst
void frontend::Analyzer::analysisFuncDef(FuncDef *root, ir::Program &program)
{
#ifdef DEBUG_SEMANTIC
    cout << "begin funcdef" << endl;
#endif
    int pc_old = pc;
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

    STE ste;
    Operand op(root->v, root->t);
    ste.operand = op;
    cout << "add  function " << toString(op.type) << " " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
    symbol_table.scope_stack.back().table.insert({op.name, ste});
    cout << "add  function " << toString(op.type) << " " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;

    int block_begin;
    if (root->children[3]->type == NodeType::FUNCFPARAMS)
    {
        block_begin = 5;
        // �������ڲ���
        ANALYSIS(funcfparams, FuncFParams, 3);
    }
    else
    {
        block_begin = 4;
    }

    function_temp.name = root->v;
    function_temp.returnType = root->t;
    program.addFunction(function_temp);
    cout << "add function " << toString(function_temp.returnType) << "  " << function_temp.name << " in program" << endl;

    ANALYSIS(block, Block, block_begin);

    if (function_temp.returnType == Type::null)
    {
        Instruction *funcreturn = new Instruction(ir::Operand(),
                                                  ir::Operand(),
                                                  ir::Operand(), ir::Operator::_return);
        Inst.push_back(funcreturn);
        pc++;

        cout << "add funcreturn" << endl;
    }

    int pc_new = pc;
    cout << "pc_old is " << pc_old << " pc_new is " << pc_new << endl;

    for (int q = pc_old; q < pc_new; q++)
    {
        program.functions.back().addInst(Inst[q]);

        cout << "pc is " << q << " " << toString(Inst[q]->op) << " " << toString(Inst[q]->des.type) << " " << Inst[q]->des.name << " " << toString(Inst[q]->op1.type) << " " << Inst[q]->op1.name << " " << toString(Inst[q]->op2.type) << " " << Inst[q]->op2.name << " in program " << function_temp.name << endl;
    }
    function_temp = Function();

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
    // todo
    root->v = ident->token.value;
    // root->v = symbol_table.get_scoped_name_use(ident->token.value);
    root->is_computable = false;
    int len = root->children.size();
    int index = 4;
    if (index <= len)
    {
        if (btype->t == Type::Int)
        {
            root->t = Type::IntPtr;
        }
        else
        {
            root->t = Type::FloatPtr;
        }
        if (index < len)
        {
            GET_CHILD_PTR(term, Term, index);
            while (index < len && term->token.type == TokenType::LBRACK)
            {
                index++;
                ANALYSIS(exp, Exp, index);
                index = index + 2;
            }
        }
    }

    STE ste;
    Operand op(ident->token.value, root->t);
    ste.operand = op;
    auto it = symbol_table.scope_stack.back().table.find(op.name);
    if (it != symbol_table.scope_stack.back().table.end())
    {
        symbol_table.scope_stack.back().table[op.name] = ste;
        cout << "update  " << toString(op.type) << " " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
    }
    else
    {
        symbol_table.scope_stack.back().table.insert({op.name, ste});
        cout << "insert " << toString(op.type) << " " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
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
        if (lval->arr_name != "") // lval�����飬��Ҫstore
        {
            Operand op1 = symbol_table.get_operand(lval->arr_name); // �����ַ
            Operand op2 = symbol_table.get_operand(lval->v);        // �±�
            Operand des(exp->v, exp->t);                            // ����
            // ����ָ�ָ�������д�������һ��������Ϊ���������ڶ���������ΪҪ�������������±꣬Ŀ�Ĳ�����Ϊ���������
            ir::Instruction *storeInst = new Instruction(op1,
                                                         op2,
                                                         des, ir::Operator::store);
            Inst.push_back(storeInst);
            pc++;

            cout << "add store" << endl;
        }
        else
        {
            Operator mov_or_fmov;
            if (exp->t == Type::Int || exp->t == Type::IntLiteral)
            {
                mov_or_fmov = Operator::mov;
            }
            else
            {
                mov_or_fmov = Operator::fmov;
            }
            // ��һ��������Ϊ��ֵ�������ڶ�����������ʹ�ã����Ϊ����ֵ������
            Operand op1(exp->v, exp->t);
            Operand des(lval->v, lval->t);
            ir::Instruction *movInst = new Instruction(op1,
                                                       ir::Operand(),
                                                       des,
                                                       mov_or_fmov);
            Inst.push_back(movInst);
            pc++;

            cout << "add mov/fmov" << endl;

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

                if ((exp->t == Type::Int || exp->t == Type::IntLiteral) && program.functions.back().returnType == Type::Float)
                {
                    string id = "t" + to_string(counter++);
                    Instruction *i2fInst = new Instruction(ir::Operand(exp->v, exp->t),
                                                           ir::Operand(),
                                                           ir::Operand(id, Type::Float),
                                                           ir::Operator::cvt_i2f);
                    Inst.push_back(i2fInst);
                    pc++;

                    cout << "add i2f" << endl;

                    exp->t = Type::Float;
                    exp->v = id;
                    exp->is_computable = false;
                }
                else if ((exp->t == Type::Float || exp->t == Type::FloatLiteral) && program.functions.back().returnType == Type::Int)
                {
                    string id = "t" + to_string(counter++);
                    Instruction *f2iInst = new Instruction(ir::Operand(exp->v, exp->t),
                                                           ir::Operand(),
                                                           ir::Operand(id, Type::Int),
                                                           ir::Operator::cvt_f2i);
                    Inst.push_back(f2iInst);
                    pc++;

                    cout << "add i2f" << endl;
                    exp->t = Type::Int;
                    exp->v = id;
                    exp->is_computable = false;
                }
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
    // todo
    //  ident->v = ident->token.value;
    ident->v = symbol_table.get_scoped_name_use(ident->token.value);
    root->v = ident->v;
    int len = root->children.size();
    int index = 1;

    // �������һ����
    if (index < len)
    {
        root->arr_name = ident->v; // ��һ�����飬���ϴ���������
        Operand op = symbol_table.get_operand(ident->v);
        cout << "�ҵ�������" << op.name << "��returntTybe�� " << toString(op.type) << endl;
        STE ste = symbol_table.get_ste(ident->v);
        Type t = op.type;
        if (t == Type::Int || t == Type::Float)
        {
            root->t = t;
        }
        else if (t == Type::IntPtr)
        {
            t = Type::Int;
            root->t = Type::Int;
        }
        else if (t == Type::FloatPtr)
        {
            cout << "�ɹ���float��ֵ��t" << endl;
            t == Type::Float;
            root->t = Type::Float;
        }

        vector<int> dimension = ste.dimension;
        Operand op2("0", Type::IntLiteral);
        vector<int> dim;
        GET_CHILD_PTR(lbrack, Term, index);
        string arr_index_name;
        int num = 0;
        vector<string> arr_index_name_list = {}; // ʵ�ʵ�λ��
        while (index < len && lbrack->token.type == TokenType::LBRACK)
        {
            num++;
            index++;
            ANALYSIS(exp, Exp, index);
            if (exp->is_computable)
            {
                dim.push_back(stoi(exp->v));
                cout << "array find is " << exp->v << endl;

                string id = "t" + to_string(counter++);
                Instruction *inst = new Instruction(Operand(exp->v, Type::IntLiteral), Operand(), Operand(id, Type::Int), Operator::def);
                Inst.push_back(inst);
                pc++;
                arr_index_name_list.push_back(id);
            }
            else
            {
                arr_index_name = exp->v;
                map<std::string, int>::iterator it1 = result.find(exp->v);
                dim.push_back(it1->second);
                cout << "array find is " << it1->second << endl;
                arr_index_name_list.push_back(exp->v);
            }
            index = index + 2;
        }

        auto it = arr_dim.find(ident->v);
        vector<string> arr_dim_temp;
        if (it != arr_dim.end())
        {
            arr_dim_temp = it->second;
        }
        else
        {
            arr_dim_temp = vector<string>();
        }
        if (arr_index_name_list.size() == 1)
        {
            Operand op1(arr_index_name_list[0], Type::Int);

            root->arr_name = ident->v;
            root->v = arr_index_name_list[0];
            root->is_computable = false;

            STE ste;
            ste.operand = op1;
            symbol_table.scope_stack.back().table.insert({arr_index_name_list[0], ste});
        }
        else if (arr_index_name_list.size() == 2)
        {
            string id1 = "t" + to_string(counter++);
            string id2 = "t" + to_string(counter++);
            Operand op1(arr_dim_temp[1], Type::Int);
            Operand op2(arr_index_name_list[0], Type::Int);
            Operand op3(arr_index_name_list[1], Type::Int);
            Instruction *inst1 = new Instruction(op1, op2, Operand(id1, Type::Int), Operator::mul);
            Inst.push_back(inst1);
            pc++;
            Instruction *inst2 = new Instruction(Operand(id1, Type::Int), op3, Operand(id2, Type::Int), Operator::add);
            Inst.push_back(inst2);
            pc++;

            STE ste;
            ste.operand = Operand(id2, Type::Int);
            symbol_table.scope_stack.back().table.insert({id2, ste});

            root->arr_name = ident->v;
            root->v = id2;
            root->is_computable = false;

            // int all = calculateIndex(dimension, dim); // �õ�λ��
            // op2.name = to_string(all);
            // Operand op1(to_string(all), Type::IntLiteral);
            // string id = "t" + to_string(counter++);
            // Operand des_temp(id, Type::Int);
            // Instruction *defInst = new Instruction(op1, Operand(), des_temp, ir::Operator::def);
            // Inst.push_back(defInst);
            // pc++;
            // cout << "add def" << endl;

            // Operand des = Operand(id, t);

            // STE ste;
            // ste.operand = des;
            // symbol_table.scope_stack.back().table.insert({des.name, ste});
            // cout << "add  " << toString(des.type) << " " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;

            // root->v = id;              // �������ݵ�λ��
            // root->t = t;               // �������ݵ�����
            // root->arr_name = ident->v; // ������һ�����飬���ϴ���������
            // root->arr_index = all;     // �������ݵ�λ��
        }
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
        if (lval->arr_name != "") // ����һ�����飬��������Ҫload����
        {
            Operand op1 = symbol_table.get_operand(lval->arr_name); // ������Ϣ
            Operand op2 = symbol_table.get_operand(lval->v);        // λ��
            string id = "t" + to_string(counter++);
            Operand des(id, lval->t); // ���

            // ��һ��������Ϊ��ֵ�������ڶ�����������ʹ�ã����Ϊ����ֵ������
            Instruction *loadInst = new Instruction(op1,
                                                    op2, des, ir::Operator::load);
            Inst.push_back(loadInst);
            pc++;

            cout << "add load" << endl;
            root->v = id;
            root->t = lval->t;
        }
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
            Type t;
            Type t_des;
            Operator def_or_fdef;
            Operator sub;
            if (unaryexp->t == Type::Int || unaryexp->t == Type::IntLiteral)
            {
                t = Type::IntLiteral;
                t_des = Type::Int;
                def_or_fdef = ir::Operator::def;
                if (unaryexp->is_computable)
                {
                    sub = ir::Operator::subi;
                }
                else
                {
                    sub = ir::Operator::sub;
                }
            }
            else
            {
                t = Type::FloatLiteral;
                t_des = Type::Float;
                def_or_fdef = ir::Operator::fdef;
                sub = ir::Operator::fsub;
                if (unaryexp->is_computable)
                {
                    unaryexp->t = Type::FloatLiteral;
                }
            }
            // a=-a->0-a
            // defһ��0
            Operand op1("0", t);
            string id = "t" + to_string(counter++);
            Operand des(id, t_des);
            Instruction *defInst = new Instruction(op1, Operand(), des, def_or_fdef);
            Inst.push_back(defInst);
            pc++;

            cout << "add def/fdef" << endl;

            STE ste;
            ste.operand = des;
            symbol_table.scope_stack.back().table.insert({des.name, ste});
            cout << "add  " << toString(des.type) << " " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;

            // ����
            //  defһ��0
            op1 = des;
            Operand op2(unaryexp->v, unaryexp->t);
            id = "t" + to_string(counter++);
            des = Operand(id, t_des);

            Instruction *subInst = new Instruction(op1, op2, des, sub);
            Inst.push_back(subInst);
            pc++;
            cout << "add sub" << endl;

            ste.operand = des;
            symbol_table.scope_stack.back().table.insert({des.name, ste});
            cout << "add  " << toString(des.type) << " " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;

            if (unaryexp->is_computable)
            {
                result.insert({id, -stoi(unaryexp->v)});
                cout << "result�н� " << id << " �� " << -stoi(unaryexp->v) << " ��" << endl;
            }

            root->v = id;
            root->t = t_des;
            root->is_computable = false;
        }
        else
        {
            Operand op1(unaryexp->v, unaryexp->t);
            if (unaryexp->t != Type::Int && unaryexp->t != Type::IntLiteral)
            {
                string id = "t" + to_string(counter++);
                Instruction *inst = new Instruction(op1, Operand(), Operand(id, Type::Int), Operator::cvt_f2i);
                Inst.push_back(inst);
                pc++;

                cout << "add f2i" << endl;
                unaryexp->t = Type::Int;
                unaryexp->v = id;
                unaryexp->is_computable = false;
                op1 = Operand(unaryexp->v, unaryexp->t);
            }
            // ����ȡ������ ! ����һ��������Ϊȡ�Ǳ������ڶ�����������ʹ�ã����Ϊȡ�ǽ��������
            string id = "t" + to_string(counter++);
            Operand des(id, Type::Int);
            Instruction *notInst = new Instruction(op1, Operand(), des, ir::Operator::_not);
            Inst.push_back(notInst);
            pc++;
            cout << "add not" << endl;

            STE ste;
            ste.operand = des;
            symbol_table.scope_stack.back().table.insert({des.name, ste});
            cout << "add  " << toString(des.type) << " " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;

            root->v = id;
        }
    }
    // Ident '(' [FuncRParams] ')'
    else
    {
        GET_CHILD_PTR(ident, Term, 0);
        ident->v = ident->token.value;
        COPY_EXP_NODE(ident, root);
        vector<Operand> paraVec_true = {}; // ����װԭ��Ӧ�ô��ڵĲ���
        cout << "����Ѱ�ҵĺ�����������" << ident->v << endl;
        auto iter = get_lib_funcs()->find(ident->v);
        if (iter == get_lib_funcs()->end())
        {
            for (auto i : program.functions)
            {
                if (i.name == ident->v)
                {
                    paraVec_true = i.ParameterList;
                }
            }
            cout << "not find lib func" << endl;
        }
        else
        {
            paraVec_true = iter->second->ParameterList;
            cout << "find lib func" << endl;
        }
        Operand op1 = symbol_table.get_operand(ident->v);
        int len = root->children.size();
        int index = 2;
        if (index < len - 1) // �в���
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
            cout << "call func param is����" << paraVec1.size() << endl;
            for (int i = 0; i < paraVec1.size(); i++)
            {

                if ((paraVec1[i].type == Type::Int || paraVec1[i].type == Type::IntLiteral) && paraVec_true[i].type == Type::Float)
                {
                    string id = "t" + to_string(counter++);
                    back.push_back(paraVec1[i]);
                    Instruction *inst = new Instruction(paraVec1[i], Operand(), Operand(id, Type::Float), Operator::cvt_i2f);
                    Inst.push_back(inst);
                    pc++;

                    cout << "add i2f" << endl;

                    paraVec1[i] = Operand(id, Type::Float);
                    cout << "����һ��i2f����ת��" << endl;
                }
                else if ((paraVec1[i].type == Type::Float || paraVec1[i].type == Type::FloatLiteral) && paraVec_true[i].type == Type::Int)
                {
                    string id = "t" + to_string(counter++);
                    Instruction *inst = new Instruction(paraVec1[i], Operand(), Operand(id, Type::Int), Operator::cvt_f2i);
                    Inst.push_back(inst);
                    pc++;

                    cout << "add f2i" << endl;

                    paraVec1[i] = Operand(id, Type::Int);
                    cout << "����һ��f2i����ת��" << endl;
                }
                cout << toString(paraVec1[i].type) << " " << paraVec1[i].name << endl;
            }
            ir::CallInst *callInst = new ir::CallInst(op1, paraVec1, des);
            Inst.push_back(callInst);
            pc++;

            cout << "add call" << endl;

            STE ste;
            Operand op = des;
            ste.operand = op;
            symbol_table.scope_stack.back().table.insert({op.name, ste});
            cout << "add  " << toString(op.type) << " " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
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
            cout << "add  " << toString(op.type) << " " << op.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
        }
        root->is_computable = false;
        root->t = op1.type;
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
    vector<Operand> paraVec1 = {}; // ����װ�õ��Ĳ���
    int len = root->children.size();
    int index = 0;
    int funcrpapam_index = 0;
    while (index < len)
    {
        cout << "index is " << index << " : to analysis funcrpapam" << endl;
        ANALYSIS(exp, Exp, index);
        index = index + 2;

        Operand op(exp->v, exp->t);
        cout << "add FuncRParam " << toString(exp->t) << " " << exp->v << " in FuncRParams" << endl;
        paraVec1.push_back(op);
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

        Operator def_or_fdef;
        Operator mul_or_fmul_or_div_or_fdiv_or_mod;
        Type t;
        Type t_temp;
        Operand op1(unaryexp->v, unaryexp->t);
        Operand op2(unaryexp_right->v, unaryexp_right->t);
        if (unaryexp->t == Type::Float || unaryexp_right->t == Type::Float || unaryexp->t == Type::FloatLiteral || unaryexp_right->t == Type::FloatLiteral)
        {
            t = Type::Float;
            t_temp = Type::FloatLiteral;
            def_or_fdef = Operator::fdef;
            if (term->token.type == TokenType::MULT)
                mul_or_fmul_or_div_or_fdiv_or_mod = Operator::fmul;
            else if (term->token.type == TokenType::DIV)
                mul_or_fmul_or_div_or_fdiv_or_mod = Operator::fdiv;
            if (unaryexp->t == Type::Int || unaryexp->t == Type::IntLiteral)
            {
                string id = "t" + to_string(counter++);
                Instruction *inst = new Instruction(op1,
                                                    Operand(),
                                                    Operand(id, Type::Float),
                                                    Operator::cvt_i2f);
                Inst.push_back(inst);
                pc++;

                cout << "add cvt_i2f inst" << endl;
                unaryexp->v = id;
                unaryexp->t = Type::Float;
                unaryexp->is_computable = false;
                op1 = Operand(unaryexp->v, unaryexp->t);
            }
            if (unaryexp_right->t == Type::Int || unaryexp_right->t == Type::IntLiteral)
            {
                string id = "t" + to_string(counter++);
                Instruction *inst = new Instruction(op2,
                                                    Operand(),
                                                    Operand(id, Type::Float),
                                                    Operator::cvt_i2f);
                Inst.push_back(inst);
                pc++;

                cout << "add cvt_i2f inst" << endl;
                unaryexp_right->v = id;
                unaryexp_right->t = Type::Float;
                unaryexp_right->is_computable = false;
                op1 = Operand(unaryexp_right->v, unaryexp_right->t);
            }
        }
        else
        {
            t = Type::Int;
            t_temp = Type::IntLiteral;
            def_or_fdef = Operator::def;
            if (term->token.type == TokenType::MULT)
                mul_or_fmul_or_div_or_fdiv_or_mod = Operator::mul;
            else if (term->token.type == TokenType::DIV)
                mul_or_fmul_or_div_or_fdiv_or_mod = Operator::div;
            else
                mul_or_fmul_or_div_or_fdiv_or_mod = Operator::mod;
        }

        cout << "inst op is " << toString(mul_or_fmul_or_div_or_fdiv_or_mod) << endl;

        if (unaryexp->is_computable) // �˷��ǳ�����Ҫ�ȶ���
        {
            Operand op1(unaryexp->v, t_temp);
            string id = "t" + to_string(counter++);

            if (t == Type::Int)
            {
                result.insert({id, stoi(unaryexp->v)});
                cout << "result�н� " << id << " �� " << stoi(unaryexp->v) << " ��" << endl;
            }

            Operand des(id, t);
            Instruction *defInst = new Instruction(op1, Operand(), des, def_or_fdef);
            Inst.push_back(defInst);
            pc++;

            if (t == Type::Int)
                cout << "add def" << endl;
            else
                cout << "add fdef" << endl;

            STE ste;
            ste.operand = des;
            symbol_table.scope_stack.back().table.insert({des.name, ste});
            cout << "add  " << toString(des.type) << " " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;

            unaryexp->v = id;
            unaryexp->t = t;
        }

        if (unaryexp_right->is_computable) // �˷��ǳ�����Ҫ�ȶ���
        {
            Operand op1(unaryexp_right->v, t_temp);
            string id = "t" + to_string(counter++);
            if (t == Type::Int)
            {
                result.insert({id, stoi(unaryexp_right->v)});
                cout << "result�н� " << id << " �� " << stoi(unaryexp_right->v) << " ��" << endl;
            }

            Operand des(id, t);
            Instruction *defInst = new Instruction(op1, Operand(), des, def_or_fdef);
            Inst.push_back(defInst);
            pc++;

            if (t == Type::Int)
                cout << "add def" << endl;
            else
                cout << "add fdef" << endl;

            STE ste;
            ste.operand = des;
            symbol_table.scope_stack.back().table.insert({des.name, ste});
            cout << "add  " << toString(des.type) << " " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;

            unaryexp_right->v = id;
            unaryexp_right->t = t;
        }

        op1 = Operand(unaryexp->v, unaryexp->t);
        op2 = Operand(unaryexp_right->v, unaryexp_right->t);
        string id = "t" + to_string(counter++);
        Operand des(id, t);

        Instruction *inst = new Instruction(op1,
                                            op2,
                                            des, mul_or_fmul_or_div_or_fdiv_or_mod);
        Inst.push_back(inst);
        pc++;

        cout << "add */��/mod inst" << endl;

        if (t == Type::Int)
        {
            string name1 = op1.name;
            string name2 = op2.name;
            string name3 = des.name;
            map<std::string, int>::iterator it1 = result.find(name1);
            map<std::string, int>::iterator it2 = result.find(name2);
            if (it1 != result.end() && it2 != result.end())
            {
                cout << name1 << "      " << name2 << endl;
                if (mul_or_fmul_or_div_or_fdiv_or_mod == Operator::mul)
                {
                    result.insert({name3, it1->second * it2->second});
                    cout << "result�н� " << name3 << " �� " << it1->second * it2->second << " ��" << endl;
                }
                else if (mul_or_fmul_or_div_or_fdiv_or_mod == Operator::div)
                {
                    result.insert({name3, it1->second / it2->second});
                    cout << "result�н� " << name3 << " �� " << it1->second / it2->second << " ��" << endl;
                }
                else if (mul_or_fmul_or_div_or_fdiv_or_mod == Operator::mod)
                {
                    result.insert({name3, it1->second % it2->second});
                    cout << "result�н� " << name3 << " �� " << it1->second % it2->second << " ��" << endl;
                }
            }
        }

        root->t = t;
        root->v = id;
        root->is_computable = false;

        unaryexp->v = id;
        unaryexp->t = t;
        unaryexp->is_computable = false;
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
    COPY_EXP_NODE(mulexp, root);
    int len = root->children.size();
    int index = 1;
    while (index < len)
    {
        GET_CHILD_PTR(term, Term, index);
        index++;
        ANALYSIS(mulexp_right, MulExp, index);
        index++;

        Type t;
        Operator add_or_sub;
        Operand op1(mulexp->v, mulexp->t);
        Operand op2(mulexp_right->v, mulexp_right->t);
        if (mulexp->t == Type::Float || mulexp_right->t == Type::Float || mulexp->t == Type::FloatLiteral || mulexp_right->t == Type::FloatLiteral)
        {
            if (mulexp->is_computable && mulexp_right->is_computable)
                t = Type::FloatLiteral;
            else
            {
                t = Type::Float;
                if (term->token.type == TokenType::PLUS)
                    add_or_sub = Operator::fadd;
                else
                    add_or_sub = Operator::fsub;

                if (mulexp->t == Type::IntLiteral)
                {
                    mulexp->t = Type::FloatLiteral;
                }
                if (mulexp_right->t == Type::IntLiteral)
                {
                    mulexp_right->t = Type::FloatLiteral;
                }
            }

            if (mulexp->t == Type::Int || mulexp->t == Type::IntLiteral)
            {
                string id = "t" + to_string(counter++);
                Instruction *inst = new Instruction(op1,
                                                    Operand(),
                                                    Operand(id, Type::Float),
                                                    Operator::cvt_i2f);
                Inst.push_back(inst);
                pc++;

                cout << "add cvt_i2f inst" << endl;
                mulexp->v = id;
                mulexp->t = Type::Float;
                mulexp->is_computable = false;
                op1 = Operand(mulexp->v, mulexp->t);
            }
            if (mulexp_right->t == Type::Int || mulexp_right->t == Type::IntLiteral)
            {
                string id = "t" + to_string(counter++);
                Instruction *inst = new Instruction(op2,
                                                    Operand(),
                                                    Operand(id, Type::Float),
                                                    Operator::cvt_i2f);
                Inst.push_back(inst);
                pc++;

                cout << "add cvt_i2f inst" << endl;
                mulexp_right->v = id;
                mulexp_right->t = Type::Float;
                mulexp_right->is_computable = false;
                op2 = Operand(mulexp_right->v, mulexp_right->t);
            }
        }
        else
        {
            if (mulexp->is_computable && mulexp_right->is_computable)
                t = Type::IntLiteral;
            else
            {
                t = Type::Int;
                if (!mulexp->is_computable && !mulexp_right->is_computable)
                {
                    if (term->token.type == TokenType::PLUS)
                        add_or_sub = Operator::add;
                    else
                        add_or_sub = Operator::sub;
                }
                else if (!mulexp->is_computable)
                {
                    if (term->token.type == TokenType::PLUS)
                        add_or_sub = Operator::addi;
                    else
                        add_or_sub = Operator::subi;
                }
                else
                {
                    if (term->token.type == TokenType::PLUS)
                    {
                        Operand temp = op1;
                        op1 = op2;
                        op2 = temp;
                        add_or_sub = Operator::addi;
                    }

                    else
                    {
                        add_or_sub = Operator::sub;
                        string id = "t" + to_string(counter++);
                        Operand des_temp(id, Type::Int);
                        Instruction *defInst = new Instruction(op1,
                                                               Operand(),
                                                               des_temp, ir::Operator::def);
                        Inst.push_back(defInst);
                        pc++;

                        cout << "add def" << endl;

                        mulexp->t = Type::Int;
                        mulexp->v = id;
                        mulexp->is_computable = false;
                    }
                }
            }
        }

        // �������ǳ���
        if (mulexp->is_computable && mulexp_right->is_computable)
        {
            if (term->token.type == TokenType::PLUS)
            {
                if (t == Type::IntLiteral)
                {
                    root->v = to_string(std::stoi(mulexp->v) + std::stoi(mulexp_right->v));
                    root->t = t;
                }
                else
                {
                    root->v = to_string(std::stof(mulexp->v) + std::stof(mulexp_right->v));
                    root->t = t;
                }
            }
            else
            {
                if (t == Type::IntLiteral)
                {
                    root->v = to_string(std::stoi(mulexp->v) - std::stoi(mulexp_right->v));
                    root->t = t;
                }
                else
                {
                    root->v = to_string(std::stof(mulexp->v) - std::stof(mulexp_right->v));
                    root->t = t;
                }
            }
            root->is_computable = true;
            mulexp->v = root->v;
            mulexp->t = root->t;
            mulexp->is_computable = true;
        }
        else
        {
            string id = "t" + to_string(counter++);
            Operand des(id, t);
            Instruction *inst = new Instruction(op1, op2, des, add_or_sub);
            Inst.push_back(inst);
            pc++;

            cout << "add +/- inst" << endl;

            if (t == Type::Int)
            {
                string name1 = op1.name;
                string name2 = op2.name;
                string name3 = des.name;
                map<std::string, int>::iterator it1 = result.find(name1);
                map<std::string, int>::iterator it2 = result.find(name2);
                if (it1 != result.end() && it2 != result.end())
                {
                    if (add_or_sub == Operator::add || add_or_sub == Operator::addi || add_or_sub == Operator::fadd)
                    {
                        cout << name1 << "      " << name2 << endl;
                        result.insert({name3, it1->second + it2->second});
                        cout << "result�н� " << name3 << " �� " << it1->second + it2->second << " ��" << endl;
                    }
                    else
                    {
                        cout << name1 << "      " << name2 << endl;
                        result.insert({name3, it1->second - it2->second});
                        cout << "result�н� " << name3 << " �� " << it1->second - it2->second << " ��" << endl;
                    }
                }

                STE ste;
                ste.operand = des;
                symbol_table.scope_stack.back().table.insert({des.name, ste});
                cout << "add  " << toString(des.type) << " " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
            }

            root->v = id;
            root->t = t;
            root->is_computable = false;
            mulexp->v = id;
            mulexp->t = t;
            mulexp->is_computable = false;
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
        Operator op;
        Type t;

        if ((addexp->t == Type::Int || addexp->t == Type::IntLiteral) && (addexp_right->t == Type::Int || addexp_right->t == Type::IntLiteral))
        {
            t = Type::Int;
            if (term->token.type == TokenType::LSS)
                op = Operator::lss;
            else if (term->token.type == TokenType::GTR)
                op = Operator::gtr;
            else if (term->token.type == TokenType::LEQ)
                op = Operator::leq;
            else
                op = Operator::geq;
        }
        else
        {
            t = Type::Float;
            if (term->token.type == TokenType::LSS)
                op = Operator::flss;
            else if (term->token.type == TokenType::GTR)
                op = Operator::fgtr;
            else if (term->token.type == TokenType::LEQ)
                op = Operator::fleq;
            else
                op = Operator::fgeq;

            if (addexp->t == Type::Int || addexp->t == Type::IntLiteral)
            {
                string id = "t" + to_string(counter++);
                Instruction *inst = new Instruction(Operand(addexp->v, addexp->t),
                                                    Operand(),
                                                    Operand(id, Type::Float), ir::Operator::cvt_i2f);
                Inst.push_back(inst);
                pc++;

                cout << "add cvt_i2f" << endl;

                addexp->v = id;
                addexp->t = Type::Float;
                addexp->is_computable = false;
            }
            if (addexp_right->t == Type::Int || addexp_right->t == Type::IntLiteral)
            {
                string id = "t" + to_string(counter++);
                Instruction *inst = new Instruction(Operand(addexp_right->v, addexp_right->t),
                                                    Operand(),
                                                    Operand(id, Type::Float), ir::Operator::cvt_i2f);
                Inst.push_back(inst);
                pc++;

                cout << "add cvt_i2f" << endl;

                addexp_right->v = id;
                addexp_right->t = Type::Float;
                addexp_right->is_computable = false;
            }
        }
        Operand op1(addexp->v, addexp->t);
        Operand op2(addexp_right->v, addexp_right->t);
        string id = "t" + to_string(counter++);
        Operand des(id, t);
        Instruction *inst = new Instruction(op1, op2, des, op);
        Inst.push_back(inst);
        pc++;

        cout << "add </>/<=/>=" << endl;

        root->v = id;
        root->t = t;
        root->is_computable = false;

        STE ste;
        ste.operand = des;
        symbol_table.scope_stack.back().table.insert({des.name, ste});
        cout << "add  " << toString(des.type) << " " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
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
            cout << "add  " << toString(des.type) << " " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
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
            cout << "add  " << toString(des.type) << " " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
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
            cout << "add  " << toString(des.type) << " " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
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
            cout << "add  " << toString(des.type) << " " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
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
        // �ȶ�ǰһ����һ��and
        Operand op1(eqexp->v, eqexp->t);
        if (eqexp->t != Type::Int && eqexp->t != Type::IntLiteral)
        {
            // �ֽ����븡����0��һ����ֵ�ж�
            string id_1 = "t" + to_string(counter++);
            Instruction *inst = new Instruction(op1, Operand("0", Type::FloatLiteral), Operand(id_1, Type::Float), Operator::fneq);
            Inst.push_back(inst);
            pc++;

            cout << "add neq" << endl;

            // Ȼ��ת��������
            string id_2 = "t" + to_string(counter++);
            Instruction *inst_2 = new Instruction(Operand(id_1, Type::Float), Operand(), Operand(id_2, Type::Int), Operator::cvt_f2i);
            Inst.push_back(inst_2);
            pc++;

            cout << "add f2i" << endl;
            eqexp->t = Type::Int;
            eqexp->v = id_2;
            eqexp->is_computable = false;
            op1 = Operand(eqexp->v, eqexp->t);
        }
        Operand op_temp("1", Type::IntLiteral);
        string id = "t" + to_string(counter++);
        Operand des(id, Type::Int);
        Instruction *andInst = new Instruction(op1, op_temp, des, ir::Operator::_and);
        Inst.push_back(andInst);
        pc++;

        cout << "&&֮ǰ���ж�һ��ǰһ��" << endl;
        STE ste;
        ste.operand = des;
        symbol_table.scope_stack.back().table.insert({des.name, ste});
        cout << "add  " << toString(des.type) << " " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
        root->v = id;

        // ������Լ���ִ�У���������
        // ��һ��������Ϊ��ת��������Ϊ���α�����type = Type::null�ı�������Ϊ���α���ʱ��ʾ������ת��ֵ������0������ת��������Ϊ��������ת���ڶ�����������ʹ�ã�Ŀ�Ĳ�����ӦΪ���Σ���ֵΪ��ת���Ŀǰpc��ƫ������
        Instruction *gotoInst = new Instruction(des, Operand(), ir::Operand("2", Type::IntLiteral), ir::Operator::_goto);
        Inst.push_back(gotoInst);
        pc++;
        cout << "add goto" << endl;
        cout << "&&֮ǰһ���Ľ���������ж��Ƿ���ת" << endl;

        int pc_to_change = pc;
        Instruction *gotoInst_2 = new Instruction(Operand(), Operand(), ir::Operand("2", Type::IntLiteral), ir::Operator::_goto);
        Inst.push_back(gotoInst_2);
        pc++;
        cout << "add goto" << endl;
        cout << "&&֮ǰһ���Ľ���������ж��Ƿ���ת" << endl;

        // goto
        ANALYSIS(landexp, LAndExp, 2);
        Operand op2(landexp->v, landexp->t);
        if (landexp->t != Type::Int && landexp->t != Type::IntLiteral)
        {
            // �ֽ����븡����0��һ����ֵ�ж�
            string id_1 = "t" + to_string(counter++);
            Instruction *inst = new Instruction(op2, Operand("0", Type::FloatLiteral), Operand(id_1, Type::Float), Operator::fneq);
            Inst.push_back(inst);
            pc++;

            cout << "add neq" << endl;

            // Ȼ��ת��������
            string id_2 = "t" + to_string(counter++);
            Instruction *inst_2 = new Instruction(Operand(id_1, Type::Float), Operand(), Operand(id_2, Type::Int), Operator::cvt_f2i);
            Inst.push_back(inst_2);
            pc++;

            cout << "add f2i" << endl;

            landexp->t = Type::Int;
            landexp->v = id_2;
            landexp->is_computable = false;
            op2 = Operand(landexp->v, landexp->t);
        }

        Instruction *andInst_2 = new Instruction(op1, op2, des, ir::Operator::_and);
        Inst.push_back(andInst_2);
        pc++;

        cout << "add and" << endl;

        int pc_des = pc;
        Inst[pc_to_change]->des.name = to_string(pc_des - pc_to_change);
        cout << "in and: where is pc: " << pc_to_change << " change inst goto's des's name = " << pc_des - pc_to_change << endl;
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
    COPY_EXP_NODE(landexp, root);
    if (root->children.size() == 3)
    {
        Operand op1(landexp->v, landexp->t);
        if (landexp->t != Type::Int && landexp->t != Type::IntLiteral)
        {
            // �ֽ����븡����0��һ����ֵ�ж�
            string id_1 = "t" + to_string(counter++);
            Instruction *inst = new Instruction(op1, Operand("0", Type::FloatLiteral), Operand(id_1, Type::Float), Operator::fneq);
            Inst.push_back(inst);
            pc++;

            cout << "add neq" << endl;

            // Ȼ��ת��������
            string id_2 = "t" + to_string(counter++);
            Instruction *inst_2 = new Instruction(Operand(id_1, Type::Float), Operand(), Operand(id_2, Type::Int), Operator::cvt_f2i);
            Inst.push_back(inst_2);
            pc++;

            cout << "add f2i" << endl;

            landexp->t = Type::Int;
            landexp->v = id_2;
            landexp->is_computable = false;
            op1 = Operand(landexp->v, landexp->t);
        }

        // �ȶ�ǰһ����һ��or�������˵��op1�϶����ԣ�ֱ������
        Operand op_temp("0", Type::IntLiteral);
        string id = "t" + to_string(counter++);
        Operand des(id, Type::Int);
        Instruction *orInst = new Instruction(op1, op_temp, des, ir::Operator::_or);
        Inst.push_back(orInst);
        pc++;

        cout << "&&֮ǰ���ж�һ��ǰһ��" << endl;
        STE ste;
        ste.operand = des;
        symbol_table.scope_stack.back().table.insert({des.name, ste});
        cout << "add  " << toString(des.type) << " " << des.name << "  in table  " << symbol_table.scope_stack.back().name << endl;
        root->v = id;

        // �������ֱ��������һ������&&��ͬ��������һ����ת������
        // ��һ��������Ϊ��ת��������Ϊ���α�����type = Type::null�ı�������Ϊ���α���ʱ��ʾ������ת��ֵ������0������ת��������Ϊ��������ת���ڶ�����������ʹ�ã�Ŀ�Ĳ�����ӦΪ���Σ���ֵΪ��ת���Ŀǰpc��ƫ������
        int pc_to_change = pc;
        Instruction *gotoInst = new Instruction(des, Operand(), ir::Operand("1", Type::IntLiteral), ir::Operator::_goto);
        Inst.push_back(gotoInst);
        pc++;

        cout << "add goto" << endl;
        cout << "&&֮ǰһ���Ľ���������ж��Ƿ���ת" << endl;

        ANALYSIS(lorexp, LOrExp, 2);
        Operand op2(lorexp->v, lorexp->t);
        if (lorexp->t != Type::Int && lorexp->t != Type::IntLiteral)
        {
            // �ֽ����븡����0��һ����ֵ�ж�
            string id_1 = "t" + to_string(counter++);
            Instruction *inst = new Instruction(op2, Operand("0", Type::FloatLiteral), Operand(id_1, Type::Float), Operator::fneq);
            Inst.push_back(inst);
            pc++;

            cout << "add neq" << endl;

            // Ȼ��ת��������
            string id_2 = "t" + to_string(counter++);
            Instruction *inst_2 = new Instruction(Operand(id_1, Type::Float), Operand(), Operand(id_2, Type::Int), Operator::cvt_f2i);
            Inst.push_back(inst_2);
            pc++;

            cout << "add f2i" << endl;

            lorexp->t = Type::Int;
            lorexp->v = id_2;
            lorexp->is_computable = false;
            op2 = Operand(lorexp->v, lorexp->t);
        }
        Instruction *orInst_2 = new Instruction(op1, op2, des, Operator::_or);
        Inst.push_back(orInst_2);
        pc++;

        int pc_des = pc;
        Inst[pc_to_change]->des.name = to_string(pc_des - pc_to_change);
        cout << "in or: where is pc: " << pc_to_change << " change inst goto's des's name = " << pc_des - pc_to_change << endl;

        root->v = des.name;
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
