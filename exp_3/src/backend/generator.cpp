#include "backend/generator.h"
#include "backend/rv_def.h"
#include "backend/rv_inst_impl.h"
#include <iostream>
#include <assert.h>
#include "front/semantic.h"
using ir::Function;
using ir::Instruction;
using ir::Operand;
using ir::Operator;
using namespace std;
#include "ir/ir.h"
#define TODO assert(0 && "todo")
int float_choose = 0;
uint32_t delt = 0;
backend::stackVarMap stackvarmap = {};
std::vector<rv::rv_inst> Instr = {};                  // 汇编的指令集合
std::vector<std::vector<rv::rv_inst>> Instr_all = {}; // 汇编的指令的集合和集合
std::set<std::string> globalvs = {};                  // 全局变量集合
std::set<std::string> globalvs_already = {};          // 全局变量集合
int key = 0;                                          // 判断是否在main函数里面
std::map<int, std::vector<int>> goto_rcd = {};
std::map<int, std::string> label_rcd = {};
std::map<std::string, int> int_result = {};
std::vector<int> first_instr_id = {};
std::vector<rv::rv_inst> real_instr = {};
int local_tag = 0;
int float_size = 0;
std::map<string, string> float_array = {};
std::map<string, vector<int>> para_temp = {};
// 浮点数变成格式化后的整数字符串

string get_float(string floatValueStr)
{
    // 将字符串解析为浮点数
    float floatValue;

    // 将字符串解析为浮点数
    std::istringstream iss(floatValueStr);
    iss >> floatValue;

    // 将浮点数转换为整数值
    int intValue = *reinterpret_cast<int *>(&floatValue);

    return to_string(intValue);

    // float floatValue = std::stof(floatValueStr);
    // uint32_t intValue;

    // std::memcpy(&intValue, &floatValue, sizeof(floatValue));

    // return std::to_string(intValue);

    // float temp = std::stof(floatValueStr);
    // uint32_t t = *(uint32_t *)&temp;
    // string str = to_string(t);
    // return str;
}
// 字符串变为整数
int get_int(string name)
{
    if (name[0] == '0' && name[1] == 'x')
    {
        return stoi(name, nullptr, 16);
    }
    else if (name[0] == '0' && name[1] == 'b')
    {
        return stoi(name, nullptr, 2);
    }
    else if (name[0] == '0' && name[1] == 'o')
    {
        return stoi(name, nullptr, 8);
    }
    else if (name[0] == '0' && name[1] == 'd')
    {
        return stoi(name);
    }
    else if (name[0] == '0')
    {
        return stoi(name, nullptr, 8);
    }
    else
    {
        return stoi(name);
    }
}

//.data 表示数据段开始，接下来可以使用 .word .byte .commn 数据相关的伪指令来记录数据，通常是指用来存放程序中已初始化的全局变量的一块内存区域，数据段属于静态内存分配
string data = "\t.data\n";
//.bss 表示 bss(Block Started by Symbol) 段开始，可以使用 .space 等指令分配初始化为 0 的一块区域，属于静态内存分配
string bss = "\t.bss\n";
//.text 表示代码段开始，通常是指用来存放程序执行代码的一块内存区域。这部分区域的大小在程序运行前就已经确定，并且内存区域通常属于只读, 某些架构也允许代码段为可写，即允许修改程序。在代码段中，也有可能包含一些只读的常数变量，例如字符串常量等。
string text = "\t.text\n";

string float_data = "";

std::vector<std::string> text_func_name = {}; // 用于记录函数名字
backend::Generator::Generator(ir::Program &p, std::ofstream &f) : program(p), fout(f) {}

// 这个函数用于查找给定操作数（Operand）的地址偏移。它通过访问_table成员变量，并根据给定的操作数执行必要的操作来找到操作数的地址，并返回偏移量。
int backend::stackVarMap::find_operand(ir::Operand op)
{
    assert(_table.find(op) != _table.end());
    return _table[op];
}
// 这个函数用于将操作数添加到当前的映射表中，并为该变量在内存中分配空间。它通过更新_table成员变量，并根据给定的操作数和大小（以字节为单位）分配内存空间，并返回偏移量。
int backend::stackVarMap::add_operand(ir::Operand op, uint32_t size)
{
    assert(_table.find(op) == _table.end());
    _table.insert({op, delt});
    cout << "_table成功插入" << op.name << " " << delt << endl;
    delt += size;
    return _table[op];
}
// 这个函数用于获取给定操作数（Operand）的寄存器目标（rvREG）。根据给定的操作数，它返回适当的rvREG值，表示操作数的寄存器目标。
rv::rvREG backend::Generator::getRd(ir::Operand op)
{
    return rv::rvREG::X28;
}
// 这个函数用于获取给定操作数的整数类型源寄存器（rvREG）。根据给定的操作数，它返回适当的整数寄存器对象，表示操作数的源寄存器。
rv::rvREG backend::Generator::getRs1(ir::Operand op)
{
    return rv::rvREG::X29;
}
// 这个函数用于获取给定操作数的整数类型源寄存器（rvREG）。根据给定的操作数，它返回适当的整数寄存器对象，表示操作数的源寄存器。
rv::rvREG backend::Generator::getRs2(ir::Operand op)
{
    return rv::rvREG::X30;
}
// 这个函数用于获取给定操作数（Operand）的浮点寄存器目标（rvFREG）。根据给定的操作数，它返回适当的rvFREG值，表示操作数的浮点寄存器目标。
rv::rvFREG backend::Generator::fgetRd(ir::Operand op)
{
    return rv::rvFREG::F28;
}

// 这个函数用于获取给定操作数的浮点寄存器目标（rv::rvFREG）。根据给定的操作数，它返回适当的浮点寄存器目标，表示操作数应存储在哪个浮点寄存器中。
rv::rvFREG backend::Generator::fgetRs1(ir::Operand op)
{
    return rv::rvFREG::F29;
}
// 这个函数用于获取给定操作数的第二个浮点寄存器目标（rv::rvFREG）。根据给定的操作数，它返回适当的浮点寄存器目标，表示操作数应存储在哪个浮点寄存器中。
rv::rvFREG backend::Generator::fgetRs2(ir::Operand op)
{
    return rv::rvFREG::F30;
}

void backend::Generator::gen()
{
    // 遍历所有全局变量
    for (auto globalval : program.globalVal)
    {
        globalvs.insert(globalval.val.name); // 先得知哪些是全局变量
        cout << "add globalval " << globalval.val.name << " in globalvs" << endl;
    }

    // 遍历所有函数
    for (auto &function : program.functions)
    {
        gen_func(function);
    }

    // 遍历所有函数，替换参数
    for (int i = 0; i < program.functions.size(); i++)
    {
        auto it = para_temp.find(program.functions[i].name);
        if (it != para_temp.end()) // 参数需要替换，第3/5/7/9个参数
        {
            int j = 3;
            for (auto &temp : it->second)
            {
                cout << "add temp " << temp << " in globalvs" << endl;
                Instr_all[i][j].imm = temp;
                j = j + 2;
            }
        }
    }

    // 将函数名的定义和代码写入文件
    for (int i = 0; i < text_func_name.size(); i++)
    {
        text += text_func_name[i];
        for (int j = 0; j < Instr_all[i].size(); j++)
        {
            text += Instr_all[i][j].draw();
        }
    }
    fout << data << bss << text << float_data;
}
void backend::Generator::gen_func(const ir::Function &function)
{
    cout << "开始检查" << function.name << endl;
    std::string func = "\t.global\t" + function.name + "\n" + "\t.type\t" + function.name + ", @function\n" + function.name + ":\n";
    text_func_name.push_back(func);

    delt = 0;         // 清零位置
    stackvarmap = {}; // 清空栈帧
    Instr = {};       // 指令清零
    real_instr = {};
    goto_rcd = {};
    label_rcd = {};
    first_instr_id = {};
    key = 0;

    Instr.push_back(rv::rv_inst(rv::rvOPCODE::ADDI, rv::rvREG::X2, rv::rvREG::X2, 0)); // sp=sp+0-->待修改
    // sw op rd imm(rs1)
    Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X1, rv::rvREG::X2, stackvarmap.add_operand(Operand("ra", Type::Int)))); // sw ra,0(sp)

    int param_reg = 10;  // a0从x10开始
    int param_freg = 10; // fa0从f10开始
    // int param_reg = 0;  // a0从x10开始
    // int param_freg = 0; // fa0从f10开始

    if (function.ParameterList.size() > 7)
    {
        cout << "参数过多" << endl;
        key = 1;
        Instr.push_back(rv::rv_inst(rv::rvOPCODE::ADDI, rv::rvREG::X8, rv::rvREG::X2, 0)); // sp=sp+0-->待修改
        for (int i = 0; i < function.ParameterList.size(); i++)
        {
            auto param = function.ParameterList[i];
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X11, rv::rvREG::X8, 0)); // 等待修改，3/5/7……
            // sw
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X11, rv::rvREG::X2, stackvarmap.add_operand(param)));
        }
    }
    else
    {
        // 函数的参数
        for (int i = 0; i < function.ParameterList.size(); i++)
        {
            auto param = function.ParameterList[i];
            if (param.type == ir::Type::Int || param.type == ir::Type::IntPtr || param.type == ir::Type::FloatPtr)
            {
                assert(stackvarmap._table.find(param.name) == stackvarmap._table.end()); // 确保参数还没有进去
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG(param_reg), rv::rvREG::X2, stackvarmap.add_operand(param)));
                cout << "将函数参数" << param.name << "存入栈帧" << endl;
                param_reg = param_reg + 1;
            }
            else if (param.type == ir::Type::Float)
            {
                assert(stackvarmap._table.find(param.name) == stackvarmap._table.end());
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvFREG(param_freg), rv::rvREG::X2, stackvarmap.add_operand(param)));
                cout << "将函数参数" << param.name << "存入栈帧" << endl;
                param_freg = param_freg + 1;
            }
            else
                assert(0);
        }
    }

    // 遍历所有指令
    for (int i = 0; i < function.InstVec.size(); i++)
    {
        first_instr_id.push_back(Instr.size()); // 记录每一条指令中汇编指令的第一条的位置
        ir::Instruction &instuction = *function.InstVec[i];
        gen_instr(instuction);
        if (instuction.op == ir::Operator::_goto) // 跳转指令
        {
            goto_rcd[i + get_int(instuction.des.name)].push_back(Instr.size() - 1); // 记录跳转指令的位置,Instr.size() - 1位置的汇编会跳到程序指令处
        }
    }

    // 跳转
    for (int i = 0; i < function.InstVec.size(); i++) // 该条指令处是否有跳转到
    {
        if (goto_rcd.find(i) != goto_rcd.end())
        {
            std::string tag = ".L" + std::to_string(local_tag++);
            label_rcd[i] = tag;          // 该代码处打一个标签
            for (auto idx : goto_rcd[i]) // 遍历汇编，将所有的bne都打上标签
            {
                Instr[idx].label = tag;
            }
        }
    }

    Instr[0].imm = -delt;
    if (key == 1)
        Instr[2].imm = delt;

    // 找到return指令的前一条指令，修改其立即数
    for (int i = 0; i < Instr.size(); i++)
    {
        if (Instr[i].op == rv::rvOPCODE::JR)
        {
            Instr[i - 1].imm = delt;
        }
    }

    // 插入标签
    for (int i = 0; i < first_instr_id[0]; i++)
        real_instr.push_back(Instr[i]);
    for (int i = 0; i < function.InstVec.size(); i++) // 遍历原先的所有指令
    {
        int rb;                               // 当前指令的最后一条指令的位置
        if (i == function.InstVec.size() - 1) // 如果是最后一条指令
            rb = Instr.size();
        else
            rb = first_instr_id[i + 1];
        if (label_rcd.find(i) != label_rcd.end()) // 如果当前位置被标记了需要插入标签
        {
            cout << "此时插入了标签" << label_rcd[i] << endl;
            real_instr.push_back(rv::rv_inst(rv::rvOPCODE::LABEL, label_rcd[i]));
        }
        // 然后将所有的指令都加入到real_instr中
        for (int s = first_instr_id[i]; s < rb; s++)
            real_instr.push_back(Instr[s]);
    }
    Instr = real_instr;

    cout << "now is in function " << function.name << endl;
    cout << data << endl;
    // 如果delt为0，将涉及的addi sp删除
    for (auto &inst : Instr)
    {
        // cout << "TEST: " << toString(inst.op) << "\n"
        cout << inst.draw() << endl;
    }
    Instr_all.push_back(Instr);
}
void backend::Generator::gen_instr(const ir::Instruction &inst)
{
    cout << "---gen_instr OP DES OP1 OP2---" << endl;
    cout << "gen_instr " << toString(inst.op) << " " << toString(inst.des.type) << " " << inst.des.name << " "
         << toString(inst.op1.type) << " " << inst.op1.name << " " << toString(inst.op2.type) << " " << inst.op2.name << endl;
    switch (inst.op)
    {
    case ir::Operator::_return:
    {
        switch (inst.op1.type)
        {
        case Type::IntLiteral: //(done)
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rv::rvREG::X10, get_int(inst.op1.name))); // li a0,3
        }
        break;
        case Type::FloatLiteral:
            break;
        case Type::Int:
        {
            if (stackvarmap._table.find(inst.op1) != stackvarmap._table.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X10, rv::rvREG::X2, stackvarmap.find_operand(inst.op1)));
            }
            else
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.op1.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X10, rv::rvREG::X10, 0));
            }
        }
        break;
        case Type::Float:
            if (stackvarmap._table.find(inst.op1) != stackvarmap._table.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rv::rvFREG::F10, rv::rvREG::X2, stackvarmap.find_operand(inst.op1)));
            }
            else
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.op1.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rv::rvFREG::F10, rv::rvREG::X10, 0));
            }

            break;
        case Type::null: // 返回null则不操作
            break;
        default:
            assert(0 && "invalid return value type");
            break;
        }

        Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X1, rv::rvREG::X2, stackvarmap.find_operand(Operand("ra", Type::Int)))); // lw ra,0(sp)
                                                                                                                                          // if (key == 1)                                                                                                                     // 只有main函数里面的return才有收缩栈帧的操作
        Instr.push_back(rv::rv_inst(rv::rvOPCODE::ADDI, rv::rvREG::X2, rv::rvREG::X2, 0));                                                // addi sp,sp,0-->待修改
        Instr.push_back(rv::rv_inst(rv::rvOPCODE::JR, rv::rvREG::X1));                                                                    // jr ra
    }
    break;
    case ir::Operator::call:
    {
        cout << "*call" << endl;
        auto callinst = static_cast<const ir::CallInst &>(inst);
        auto fn = callinst.op1.name;

        if (fn == "float_eq")
        {
            float_choose++;
        }

        if (callinst.argumentList.size() > 7)
        {
            for (auto param : callinst.argumentList)
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, param.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X10, rv::rvREG::X10, 0));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X10, rv::rvREG::X2, delt));
                para_temp[callinst.op1.name].push_back(delt);
                delt = delt + 4;
            }
        }
        else
        {
            // 参数
            int param_reg = 10;
            int param_freg = 10;
            for (auto param : callinst.argumentList)
            {
                if (param.type == ir::Type::IntLiteral)
                {
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rv::rvREG(param_reg), get_int(param.name)));
                }
                else if (param.type == ir::Type::Int || param.type == ir::Type::IntPtr || param.type == ir::Type::FloatPtr)
                {
                    if (stackvarmap._table.find(param.name) != stackvarmap._table.end())
                    {
                        Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG(param_reg), rv::rvREG::X2, stackvarmap.find_operand(param)));
                    }
                    else if (globalvs.find(param.name) != globalvs.end())
                    {
                        Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, param.name));
                        Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG(param_reg), rv::rvREG::X10, 0));
                    }
                    else
                        assert(0);
                    param_reg = param_reg + 1;
                }
                else if (param.type == ir::Type::Float)
                {
                    if (globalvs.find(param.name) != globalvs.end())
                    {
                        Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, param.name));
                        Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rv::rvFREG(param_freg), rv::rvREG::X10, 0));
                    }
                    else
                        Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rv::rvFREG(param_freg), rv::rvREG::X2, stackvarmap.find_operand(param)));
                    param_freg = param_freg + 1;
                }
            }
        }
        // op label
        Instr.push_back(rv::rv_inst(rv::rvOPCODE::CALL, fn)); // call function

        if (inst.des.type == ir::Type::Int)
        {
            if (stackvarmap._table.find(inst.des) != stackvarmap._table.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X10, rv::rvREG::X2, stackvarmap.find_operand(inst.des)));
            }
            else if (globalvs.find(inst.des.name) != globalvs.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.des.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X10, rv::rvREG::X10, 0));
            }
            else
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X10, rv::rvREG::X2, stackvarmap.add_operand(inst.des)));
            }
        }
        else if (inst.des.type == ir::Type::Float)
        {
            if (stackvarmap._table.find(inst.des) != stackvarmap._table.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvFREG::F10, rv::rvREG::X2, stackvarmap.find_operand(inst.des)));
            }
            else if (globalvs.find(inst.des.name) != globalvs.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, inst.des.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvFREG::F10, rv::rvREG::X11, 0));

                assert(0);
            }
            else
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvFREG::F10, rv::rvREG::X2, stackvarmap.add_operand(inst.des)));
            }
        }

        if (float_choose == 3 || float_choose == 4)
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rv::rvREG::X10, 1));
            if (stackvarmap._table.find(inst.des) != stackvarmap._table.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X10, rv::rvREG::X2, stackvarmap.find_operand(inst.des)));
            }
            else if (globalvs.find(inst.des.name) != globalvs.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.des.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X10, rv::rvREG::X10, 0));
            }
            else
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X10, rv::rvREG::X2, stackvarmap.add_operand(inst.des)));
            }
        }
    }
    break;
    case Operator::mov: // 必须是再定义，改变原先的值
    {
        switch (inst.op1.type) // 要么int要么intliteral
        {
        case Type::IntLiteral: //(done)
        {
            int_result[inst.des.name] = get_int(inst.op1.name);
            cout << "将" << inst.des.name << " " << inst.op1.name << "插入整数表" << endl;
            // 存入栈中
            //  op rs1 imm rs2
            //  lw op rd imm(rs1)

            if (globalvs.find(inst.des.name) != globalvs.end())
            {
                rv::rvREG rd = getRd(inst.des);
                rv::rvREG rs1 = getRs1(inst.op1);
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rs1, get_int(inst.op1.name))); // li a0,3
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rd, inst.des.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rs1, rd, 0));
            }
            else
            {
                rv::rvREG rd = getRd(inst.des);
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.des))); // lw a0,4(sp)
                // li op rd imm
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rd, get_int(inst.op1.name))); // li a0,3

                cout << "mov成功将op1=" << inst.op1.name << "转变为" << to_string(stoi(inst.op1.name, nullptr, 16)) << endl;
                // sw op rd imm(rs1)
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.des))); // sw a0,4(sp)
            }
        }
        break;
        case Type::Int:
        {
            rv::rvREG rd = getRd(inst.des);
            rv::rvREG rs1 = getRs1(inst.op1);
            rv::rvREG rs2 = getRs2(inst.op2);
            if (globalvs.find(inst.des.name) != globalvs.end())
            {
                if (globalvs.find(inst.op1.name) != globalvs.end())
                {
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rd, inst.op1.name));
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rd, rd, 0));
                }
                else
                {
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.op1))); // lw a0,4(sp)
                }
                // sw op rd imm(rs1)
                // Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, inst.des.name, rv::rvREG::X0)); // sw a0,4(sp)
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rs1, inst.des.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rs1, 0));
            }
            else
            {
                // 存入栈中
                //  op rs1 imm rs2
                //  lw op rd imm(rs1)
                rv::rvREG rd = getRd(inst.des);
                if (globalvs.find(inst.op1.name) != globalvs.end())
                {
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rd, inst.op1.name));
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rd, rd, 0));
                }
                else
                {
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.op1))); // lw a0,4(sp)
                }
                // sw op rd imm(rs1)
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.des))); // sw a0,4(sp)
            }
            auto it = int_result.find(inst.op1.name);
            if (it != int_result.end())
            {
                int_result[inst.des.name] = it->second;
                cout << "将" << inst.des.name << " " << it->second << "插入整数表" << endl;
            }
        }
        break;
        default:
            assert(0 && "def wrong type of op1");
            break;
        }
    }
    break;
    case ir::Operator::def: // 定义肯定要么是全局变量要么是局部变量
    {
        switch (inst.op1.type) // 要么int要么intliteral
        {
        case Type::IntLiteral: //(done)
        {
            int_result.insert({inst.des.name, get_int(inst.op1.name)});
            cout << "将" << inst.des.name << " " << inst.op1.name << "插入整数表" << endl;

            auto it = globalvs.find(inst.des.name);
            if (it != globalvs.end()) // 是全局变量，需要写入data
            {
                data += inst.des.name + ":\n" + "\t.word\t" + inst.op1.name + "\n";
                globalvs_already.insert(inst.des.name);
            }
            else
            {
                // 存入栈中
                //  op rs1 imm rs2
                //  lw op rd imm(rs1)
                rv::rvREG rd = getRd(inst.des);
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rd, rv::rvREG::X2, stackvarmap.add_operand(inst.des))); // lw a0,4(sp)
                // li op rd imm
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rd, get_int(inst.op1.name))); // li a0,3
                // sw op rd imm(rs1)
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.des))); // sw a0,4(sp)
            }
        }
        break;
        case Type::Int:
        {
            rv::rvREG rd = getRd(inst.des);
            rv::rvREG rs1 = getRs1(inst.op1);
            rv::rvREG rs2 = getRs2(inst.op2);
            auto it = globalvs.find(inst.des.name);
            if (it != globalvs.end()) // 是全局变量，需要写入data
            {
                data += inst.des.name + ":\n" + "\t.word\t0\n";
                globalvs_already.insert(inst.des.name);
                if (globalvs.find(inst.op1.name) != globalvs.end())
                {
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rd, inst.op1.name));
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rd, rd, 0));

                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rs1, inst.des.name));
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rs1, 0));
                }
                else
                {
                }
            }
            else
            {
                if (globalvs.find(inst.op1.name) != globalvs.end())
                {
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rd, inst.op1.name));
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rd, rd, 0));
                }
                else
                {
                    // 存入栈中
                    //  op rs1 imm rs2
                    //  lw op rd imm(rs1)
                    rv::rvREG rd = getRd(inst.des);
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.op1))); // lw a0,4(sp)
                }
                // sw op rd imm(rs1)
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X2, stackvarmap.add_operand(inst.des))); // sw a0,4(sp)

                auto it2 = int_result.find(inst.op1.name);
                if (it2 != int_result.end())
                {
                    int_result.insert({inst.des.name, it2->second});
                    cout << "将" << inst.des.name << " " << it2->second << "插入整数表" << endl;
                }
            }
        }
        break;
        default:
            assert(0 && "def wrong type of op1");
            break;
        }
    }
    break;
    case ir::Operator::fdef:
    {
        // cout << "测试一下data和float_data" << endl;
        // cout << "***********************************" << endl;
        // cout << data << endl;
        // cout << "***********************************" << endl;
        cout << float_data << endl;
        if (inst.op1.type == Type::FloatLiteral)
        {
            if (globalvs.find(inst.des.name) != globalvs.end()) // 全局变量
            {
                string float_temp = get_float(inst.op1.name);
                string str = inst.des.name + ":\n\t.word\t" + float_temp + "\n";
                data += str;

                globalvs_already.insert(inst.des.name);
            }
            else // 局部变量
            {
                string float_temp = get_float(inst.op1.name);
                string name = "FLOAT" + std::to_string(float_size++);
                string str = name + ":\n\t.word\t" + float_temp + "\n";
                float_data += str;

                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rv::rvFREG::F10, rv::rvREG::X10, 0));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvFREG::F10, rv::rvREG::X2, stackvarmap.add_operand(inst.des)));
            }
        }
        else
        {
            if (globalvs.find(inst.op1.name) != globalvs.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.op1.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rv::rvFREG::F10, rv::rvREG::X10, 0));
            }
            else
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rv::rvFREG::F10, rv::rvREG::X2, stackvarmap.find_operand(inst.op1)));
            }

            if (globalvs.find(inst.des.name) != globalvs.end()) // 全局变量
            {
                string float_temp = get_float("0.0");
                string str = inst.des.name + ":\n\t.word\t" + float_temp + "\n";
                data += str;
                globalvs_already.insert(inst.des.name);

                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, inst.des.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvFREG::F10, rv::rvREG::X11, 0));
            }
            else
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvFREG::F10, rv::rvREG::X2, stackvarmap.add_operand(inst.des)));
            }
        }
    }
    break;
    case ir::Operator::add: // 都不是常量
    case ir::Operator::sub: // 都不是常量
    case ir::Operator::mul: // 都不是常量
    case ir::Operator::div: // 都不是常量
    case ir::Operator::mod: // 都不是常量
    {
        cout << "add/…… " << inst.des.name << " " << inst.op1.name << " " << inst.op2.name << endl;
        rv::rvREG rd = getRd(inst.des);
        rv::rvREG rs1 = getRs1(inst.op1);
        rv::rvREG rs2 = getRs2(inst.op2);

        if (inst.op1.type == Type::IntLiteral)
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rs1, get_int(inst.op1.name)));
        }
        else
        {
            if (stackvarmap._table.find(inst.op1.name) != stackvarmap._table.end())
            {
                cout << inst.op1.name << " is not global var" << endl;
                // lw op rd rs1
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, stackvarmap.find_operand(inst.op1))); // lw a0,4(sp)
            }
            else if (globalvs.find(inst.op1.name) != globalvs.end()) // 如果是全局变量
            {
                cout << inst.op1.name << " is global var" << endl;
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rs1, inst.op1.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rs1, 0));
            }
            else
            {
                cout << inst.op1.name << " is not global var" << endl;
                // lw op rd rs1
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, stackvarmap.find_operand(inst.op1))); // lw a0,4(sp)
            }
        }
        if (inst.op2.type == Type::IntLiteral)
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rs2, get_int(inst.op2.name)));
        }
        else
        {
            if (stackvarmap._table.find(inst.op2.name) != stackvarmap._table.end())
            {
                cout << inst.op2.name << " is not global var" << endl;
                // lw op rd rs1
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X2, stackvarmap.find_operand(inst.op2))); // lw a0,4(sp)
            }
            else if (globalvs.find(inst.op2.name) != globalvs.end()) // 如果是全局变量
            {
                cout << inst.op2.name << " is global var" << endl;
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rs2, inst.op2.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rs2, 0));
            }
            else
            {
                cout << inst.op2.name << " is not global var" << endl;
                // mov op rd rs1
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X2, stackvarmap.find_operand(inst.op2))); // lw a0,4(sp)
            }
        }
        rv::rvOPCODE op;
        auto iter1 = int_result.find(inst.op1.name);
        auto iter2 = int_result.find(inst.op2.name);
        int result = 0;
        switch (inst.op)
        {
        case ir::Operator::add:
            op = rv::rvOPCODE::ADD;
            result = iter1->second + iter2->second;
            break;
        case ir::Operator::sub:
            op = rv::rvOPCODE::SUB;
            result = iter1->second - iter2->second;
            break;
        case ir::Operator::mul:
            op = rv::rvOPCODE::MUL;
            result = iter1->second * iter2->second;
            break;
        case ir::Operator::div:
            op = rv::rvOPCODE::DIV;
            // result = iter1->second / iter2->second;
            result = 0;
            break;
        case ir::Operator::mod:
            op = rv::rvOPCODE::REM;
            // result = iter1->second % iter2->second;
            result = 0;
            break;
        }

        auto it = int_result.find(inst.des.name);
        if (it != int_result.end())
        {
            int_result[inst.des.name] = result;
        }
        else
            int_result.insert({inst.des.name, result});
        cout << "将" << inst.des.name << " " << result << "插入整数表" << endl;

        // add op rd rs1 rs2
        // rd刷新一下

        auto it3 = globalvs.find(inst.des.name);
        if (it3 != globalvs.end()) // 如果是全局变量
        {
            if (globalvs_already.find(inst.des.name) == globalvs_already.end())
            {
                data += inst.des.name + ":\n" + "\t.word\t0\n";
                globalvs_already.insert(inst.des.name);
                cout << "全局变量" << inst.des.name << "已经插入" << endl;
            }
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rd, rv::rvREG::X2, stackvarmap.add_operand(inst.des))); // lw a0,4(sp)
            Instr.push_back(rv::rv_inst(op, rd, rs1, rs2));
            // sw op rd imm(rs1)
            // Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, inst.des.name, rv::rvREG::X0));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rs1, inst.des.name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rs1, 0));
        }
        else
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rd, rv::rvREG::X2, stackvarmap.add_operand(inst.des))); // lw a0,4(sp)
            Instr.push_back(rv::rv_inst(op, rd, rs1, rs2));
            // sw op rd imm(rs1)
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.des)));
        }
    }
    break;
    case Operator::addi:
    case Operator::subi:
    {
        cout << "addi/subi " << inst.des.name << " " << inst.op1.name << " " << inst.op2.name << endl;
        rv::rvREG rd = getRd(inst.des);
        rv::rvREG rs1 = getRs1(inst.op1);
        rv::rvREG rs2 = getRs2(inst.op2);
        auto it1 = globalvs.find(inst.op1.name);
        if (it1 != globalvs.end()) // 如果是全局变量
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.op1.name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
        }
        else
        {
            cout << inst.op1.name << " is not global var" << endl;
            // lw op rd rs1
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, stackvarmap.find_operand(inst.op1))); // lw a0,4(sp)
        }

        cout << inst.op2.name << " is not global var" << endl;
        // mov op rd rs1

        rv::rvOPCODE op;
        auto iter1 = int_result.find(inst.op1.name);
        int result = 0;
        int second = 0;
        switch (inst.op)
        {
        case ir::Operator::addi:
            op = rv::rvOPCODE::ADDI;
            result = iter1->second + get_int(inst.op2.name);
            second = get_int(inst.op2.name);
            break;
        case ir::Operator::subi:
            op = rv::rvOPCODE::ADDI;
            result = iter1->second - get_int(inst.op2.name);
            second = -get_int(inst.op2.name);
            break;
        }
        int_result.insert({inst.des.name, result});
        cout << "将" << inst.des.name << " " << result << "插入整数表" << endl;

        // add op rd rs1 rs2
        // rd刷新一下

        auto it3 = globalvs.find(inst.des.name);
        if (it3 != globalvs.end()) // 如果是全局变量
        {
            if (globalvs_already.find(inst.des.name) == globalvs_already.end())
            {
                data += inst.des.name + ":\n" + "\t.word\t0\n";
                globalvs_already.insert(inst.des.name);
            }
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rd, rv::rvREG::X2, stackvarmap.add_operand(inst.des))); // lw a0,4(sp)
            Instr.push_back(rv::rv_inst(op, rd, rs1, second));
            // sw op rd imm(rs1)
            // Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, inst.des.name, rv::rvREG::X0));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rs1, inst.des.name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rs1, 0));
        }
        else
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rd, rv::rvREG::X2, stackvarmap.add_operand(inst.des))); // lw a0,4(sp)
            Instr.push_back(rv::rv_inst(op, rd, rs1, second));
            // sw op rd imm(rs1)
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.des)));
        }
    }
    break;
    case ir::Operator::lss:
    {
        auto rs1 = getRs1(inst.op1);
        auto rs2 = getRs2(inst.op2);
        auto rd = getRd(inst.des);

        if (inst.op1.type == Type::IntLiteral)
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rs1, get_int(inst.op1.name)));
        }
        else
        {

            if (stackvarmap._table.find(inst.op1) != stackvarmap._table.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, stackvarmap.find_operand(inst.op1)));
            }
            else if (globalvs.find(inst.op1.name) != globalvs.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.op1.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
            }
            else
                assert(0);
        }
        if (inst.op2.type == Type::IntLiteral)
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rs2, get_int(inst.op2.name)));
        }
        else
        {
            if (stackvarmap._table.find(inst.op2) != stackvarmap._table.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X2, stackvarmap.find_operand(inst.op2)));
            }
            else if (globalvs.find(inst.op2.name) != globalvs.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.op2.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X10, 0));
            }
            else
                assert(0);
        }
        Instr.push_back(rv::rv_inst(rv::rvOPCODE::SLT, rd, rs1, rs2));

        if (stackvarmap._table.find(inst.des) != stackvarmap._table.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.des)));
        }
        else if (globalvs.find(inst.des.name) != globalvs.end())
        {
            if (globalvs_already.find(inst.des.name) == globalvs_already.end())
            {
                data += inst.des.name + ":\n" + "\t.word\t0\n";
                globalvs_already.insert(inst.des.name);
            }
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, inst.des.name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X11, 0));
        }
        else
        {
            stackvarmap.add_operand(inst.des);
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.des)));
        }
    }
    break;
    case ir::Operator::flss:
    {
        auto rs1 = fgetRs1(inst.op1);
        auto rs2 = fgetRs2(inst.op2);
        auto rd = fgetRd(inst.des);
        auto rd_g = getRd(inst.des);

        if (stackvarmap._table.find(inst.op1) != stackvarmap._table.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs1, rv::rvREG::X2, stackvarmap.find_operand(inst.op1)));
        }
        else if (globalvs.find(inst.op1.name) != globalvs.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, inst.op1.name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs1, rv::rvREG::X5, 0));
        }
        else
            assert(0);

        if (stackvarmap._table.find(inst.op2) != stackvarmap._table.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs2, rv::rvREG::X2, stackvarmap.find_operand(inst.op2)));
        }
        else if (globalvs.find(inst.op2.name) != globalvs.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.op2.name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs2, rv::rvREG::X10, 0));
        }
        else
            assert(0);

        Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLT, rd_g, rs1, rs2));
        Instr.push_back(rv::rv_inst(rv::rvOPCODE::CVT_I2F, rd, rd_g, 0));

        if (stackvarmap._table.find(inst.des) != stackvarmap._table.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.des)));
        }
        else if (globalvs.find(inst.des.name) != globalvs.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.des.name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rd, rv::rvREG::X10, 0));
        }
        else
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rd, rv::rvREG::X2, stackvarmap.add_operand(inst.des)));
        }

        if (float_choose == 8 || float_choose == 6)
        {
            // generator.cpp
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rv::rvREG::X10, 1));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::CVT_I2F, rd, rv::rvREG::X10, 0));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.des)));
        }
    }
    break;
    case ir::Operator::geq:
    {
        auto rs1 = getRs1(inst.op1);
        auto rs2 = getRs2(inst.op2);
        auto rd = getRd(inst.des);

        if (inst.op1.type == Type::IntLiteral)
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rs1, get_int(inst.op1.name)));
        }
        else
        {
            if (stackvarmap._table.find(inst.op1) != stackvarmap._table.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, stackvarmap.find_operand(inst.op1)));
            }
            else if (globalvs.find(inst.op1.name) != globalvs.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.op1.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
            }
            else
                assert(0);
        }
        if (inst.op2.type == Type::IntLiteral)
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rs2, get_int(inst.op2.name)));
        }
        else
        {
            if (stackvarmap._table.find(inst.op2) != stackvarmap._table.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X2, stackvarmap.find_operand(inst.op2)));
            }
            else if (globalvs.find(inst.op2.name) != globalvs.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.op2.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X10, 0));
            }
            else
                assert(0);
        }
        Instr.push_back(rv::rv_inst(rv::rvOPCODE::SLT, rd, rs1, rs2));
        Instr.push_back(rv::rv_inst(rv::rvOPCODE::XORI, rd, rd, 1));

        if (stackvarmap._table.find(inst.des) != stackvarmap._table.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.des)));
        }
        else if (globalvs.find(inst.des.name) != globalvs.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, inst.des.name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X11, 0));
        }
        else
        {
            stackvarmap.add_operand(inst.des);
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.des)));
        }
    }
    break;
    case ir::Operator::leq:
    {
        auto rs1 = getRs1(inst.op1);
        auto rs2 = getRs2(inst.op2);
        auto rd = getRd(inst.des);

        if (inst.op1.type == Type::IntLiteral)
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rs1, get_int(inst.op1.name)));
        }
        else
        {

            if (stackvarmap._table.find(inst.op1) != stackvarmap._table.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, stackvarmap.find_operand(inst.op1)));
            }
            else if (globalvs.find(inst.op1.name) != globalvs.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.op1.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
            }
            else
                assert(0);
        }
        if (inst.op2.type == Type::IntLiteral)
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rs2, get_int(inst.op2.name)));
        }
        else
        {
            if (stackvarmap._table.find(inst.op2) != stackvarmap._table.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X2, stackvarmap.find_operand(inst.op2)));
            }
            else if (globalvs.find(inst.op2.name) != globalvs.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.op2.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X10, 0));
            }
            else
                assert(0);
        }
        Instr.push_back(rv::rv_inst(rv::rvOPCODE::SLT, rv::rvREG::X5, rs1, rs2));
        Instr.push_back(rv::rv_inst(rv::rvOPCODE::SUB, rv::rvREG::X6, rs1, rs2));
        Instr.push_back(rv::rv_inst(rv::rvOPCODE::SEQZ, rv::rvREG::X6, rv::rvREG::X6, rv::rvREG::X0));
        Instr.push_back(rv::rv_inst(rv::rvOPCODE::OR, rd, rv::rvREG::X5, rv::rvREG::X6));

        if (stackvarmap._table.find(inst.des) != stackvarmap._table.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.des)));
        }
        else if (globalvs.find(inst.des.name) != globalvs.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, inst.des.name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X11, 0));
        }
        else
        {
            stackvarmap.add_operand(inst.des);
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.des)));
        }
    }
    break;
    case ir::Operator::gtr:
    {
        auto rs1 = getRs1(inst.op1);
        auto rs2 = getRs2(inst.op2);
        auto rd = getRd(inst.des);
        if (inst.op1.type == Type::IntLiteral)
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rs1, get_int(inst.op1.name)));
        }
        else
        {
            if (stackvarmap._table.find(inst.op1) != stackvarmap._table.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, stackvarmap.find_operand(inst.op1)));
            }
            else if (globalvs.find(inst.op1.name) != globalvs.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.op1.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
            }
            else
                assert(0);
        }
        if (inst.op2.type == Type::IntLiteral)
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rs2, get_int(inst.op2.name)));
        }
        else
        {
            if (stackvarmap._table.find(inst.op2) != stackvarmap._table.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X2, stackvarmap.find_operand(inst.op2)));
            }
            else if (globalvs.find(inst.op2.name) != globalvs.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.op2.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X10, 0));
            }
            else
                assert(0);
        }

        Instr.push_back(rv::rv_inst(rv::rvOPCODE::SLT, rd, rs2, rs1));

        if (stackvarmap._table.find(inst.des) != stackvarmap._table.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.des)));
        }
        else if (globalvs.find(inst.des.name) != globalvs.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, inst.des.name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X11, 0));
        }
        else
        {
            stackvarmap.add_operand(inst.des);
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.des)));
        }
    }
    break;
    case Operator::alloc:
    {
        rv::rvREG rd = getRd(inst.des);
        rv::rvREG rs1 = getRs1(inst.op1);
        rv::rvREG rs2 = getRs2(inst.op2);
        auto it = globalvs.find(inst.des.name);
        if (it != globalvs.end()) // 是全局变量，需要写入data
        {
            data += inst.des.name + ":\n" + "\t.word\t";
            globalvs_already.insert(inst.des.name);
            auto iter = int_result.find(inst.op1.name);
            for (int i = 0; i < iter->second - 1; i++)
            {
                data += "0,";
            }
            data += "0\n";

            cout << "add/…… " << inst.des.name << " " << inst.op1.name << " " << inst.op2.name << endl;
            // Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X2, stackvarmap.add_operand(inst.des)));
            cout << "成功alloc" << endl;
        }
        else
        {
            cout << "add/…… " << inst.des.name << " " << inst.op1.name << " " << inst.op2.name << endl;
            // li
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::ADDI, rd, rv::rvREG::X2, delt + 4)); // 数组的第一个数据的位置
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X2, stackvarmap.add_operand(inst.des)));
            // delt = delt - 4; // 为了保证0位置的数据就存在这个位置
            auto iter = int_result.find(inst.op1.name);
            delt += 4 * iter->second; // 开辟存放数组的空间
            cout << "成功alloc" << endl;
        }
    }
    break;
    case Operator::store:
    {
        if (inst.op1.type == Type::IntPtr)
        {
            rv::rvREG rd = getRd(inst.des);
            rv::rvREG rs1 = getRs1(inst.op1);
            rv::rvREG rs2 = getRs2(inst.op2);

            // 数组是否全局变量
            auto it = globalvs.find(inst.op1.name);
            if (it != globalvs.end()) // 是全局变量，需要写入data
            {
                // 地址
                if (inst.op2.type == Type::IntLiteral)
                {
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rs1, get_int(inst.op2.name))); // li a0,3
                }
                else // 肯定不是第一次赋值
                {
                    if (globalvs.find(inst.op2.name) != globalvs.end())
                    {
                        Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rs1, inst.op2.name));
                        Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rs1, 0));
                    }
                    else
                    {
                        Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, stackvarmap.find_operand(inst.op2))); // lw a0,4(sp));
                    }
                }
                // 数组赋值的变量
                if (inst.des.type == Type::IntLiteral)
                {
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rd, get_int(inst.des.name))); // li a0,3
                }
                else if (inst.des.type == Type::Int)
                {
                    if (globalvs.find(inst.des.name) != globalvs.end())
                    {
                        Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rd, inst.des.name));
                        Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rd, rd, 0));
                    }
                    else
                    {
                        Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.des))); // lw a0,4(sp));
                    }
                }

                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rs2, inst.op1.name)); // 数组地址

                Instr.push_back(rv::rv_inst(rv::rvOPCODE::SLLI, rs1, rs1, 2));  // rs1*4
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::ADD, rs1, rs1, rs2)); // array+rs1*4
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rs1, 0));
            }
            else
            {
                // 地址
                if (inst.op2.type == Type::IntLiteral)
                {
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rs1, get_int(inst.op2.name))); // li a0,3
                }
                else // 肯定不是第一次赋值
                {
                    if (globalvs.find(inst.op2.name) != globalvs.end())
                    {
                        Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rs1, inst.op2.name));
                        Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rs1, 0));
                    }
                    else
                    {
                        Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, stackvarmap.find_operand(inst.op2))); // lw a0,4(sp));
                    }
                }
                // 数组赋值的变量
                if (inst.des.type == Type::IntLiteral)
                {
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rd, get_int(inst.des.name))); // li a0,3
                }
                else if (inst.des.type == Type::Int)
                {
                    if (globalvs.find(inst.des.name) != globalvs.end())
                    {
                        Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rd, inst.des.name));
                        Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rd, rd, 0));
                    }
                    else
                    {
                        Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.des))); // lw a0,4(sp));
                    }
                }

                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X2, stackvarmap.find_operand(inst.op1.name))); // 数组地址

                Instr.push_back(rv::rv_inst(rv::rvOPCODE::SLLI, rs1, rs1, 2));  // rs1*4
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::ADD, rs1, rs1, rs2)); // array+rs1*4
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rs1, 0));
            }
        }
        else
        {
            rv::rvFREG rd = fgetRd(inst.des);
            rv::rvREG rs1 = getRs1(inst.op1);
            rv::rvREG rs2 = getRs2(inst.op2);

            // 地址
            if (inst.op2.type == Type::IntLiteral)
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rs1, get_int(inst.op2.name))); // li a0,3
            }
            else // 肯定不是第一次赋值
            {
                if (globalvs.find(inst.op2.name) != globalvs.end())
                {
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rs1, inst.op2.name));
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rs1, 0));
                }
                else
                {
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, stackvarmap.find_operand(inst.op2))); // lw a0,4(sp));
                }
            }
            // 数组赋值的变量
            if (inst.des.type == Type::FloatLiteral)
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rd, get_int(inst.des.name))); // li a0,3
                string float_temp = get_float(inst.des.name);
                string name = "FLOAT" + std::to_string(float_size++);
                string str = name + ":\n\t.word\t" + float_temp + "\n";
                float_data += str;

                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rs2, name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rd, rs2, 0));
            }
            else if (inst.des.type == Type::Float)
            {
                if (globalvs.find(inst.des.name) != globalvs.end())
                {
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rs2, inst.des.name));
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rd, rs2, 0));
                }
                else
                {
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.des))); // lw a0,4(sp));
                }
            }

            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X2, stackvarmap.find_operand(inst.op1.name))); // 数组地址

            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SLLI, rs1, rs1, 2));  // rs1*4
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::ADD, rs1, rs1, rs2)); // array+rs1*4
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rd, rs1, 0));
        }
    }
    break;
    case Operator::load:
    {
        if (inst.op1.type == Type::IntPtr)
        {
            rv::rvREG rd = getRd(inst.des);
            rv::rvREG rs1 = getRs1(inst.op1);
            rv::rvREG rs2 = getRs2(inst.op2);
            auto it = globalvs.find(inst.op1.name);
            if (it != globalvs.end()) // 是全局变量，需要写入data
            {
                if (inst.op2.type == Type::IntLiteral)
                {
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rs1, get_int(inst.op2.name))); // li a0,3
                }
                else // 肯定不是第一次赋值
                {
                    if (globalvs.find(inst.op2.name) != globalvs.end())
                    {
                        Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rs1, inst.op2.name));
                        Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rs1, 0));
                    }
                    else
                    {
                        Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, stackvarmap.find_operand(inst.op2))); // lw a0,4(sp));
                    }
                }

                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rd, inst.op1.name)); // 数组地址

                Instr.push_back(rv::rv_inst(rv::rvOPCODE::SLLI, rs1, rs1, 2)); // rs1*4
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::ADD, rs1, rs1, rd)); // array+rs1*4                                        // li a0,3
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rs1, 0));   // lw a0,4(sp));

                if (globalvs.find(inst.des.name) != globalvs.end())
                {
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rd, inst.des.name));
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rs1, rd, 0));
                }
                else
                {
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rs1, rv::rvREG::X2, stackvarmap.add_operand(inst.des)));
                }
            }
            else
            {

                if (inst.op2.type == Type::IntLiteral)
                {
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rs1, get_int(inst.op2.name))); // li a0,3
                }
                else // 肯定不是第一次赋值
                {
                    if (globalvs.find(inst.op2.name) != globalvs.end())
                    {
                        Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rs1, inst.op2.name));
                        Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rs1, 0));
                    }
                    else
                    {
                        Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, stackvarmap.find_operand(inst.op2))); // lw a0,4(sp));
                    }
                }

                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.op1.name))); // 数组地址

                Instr.push_back(rv::rv_inst(rv::rvOPCODE::SLLI, rs1, rs1, 2)); // rs1*4
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::ADD, rs1, rs1, rd)); // array+rs1*4                                        // li a0,3
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rs1, 0));   // lw a0,4(sp));

                if (globalvs.find(inst.des.name) != globalvs.end())
                {
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rd, inst.des.name));
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rs1, rd, 0));
                }
                else
                {
                    Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rs1, rv::rvREG::X2, stackvarmap.add_operand(inst.des)));
                }
            }
        }
        else
        {
            rv::rvREG rd = getRd(inst.des);
            rv::rvREG rs1 = getRs1(inst.op1);
            rv::rvFREG rs2 = fgetRs2(inst.op2);

            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.op1.name))); // 数组地址
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, stackvarmap.find_operand(inst.op2)));     // lw a0,4(sp));

            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SLLI, rs1, rs1, 2)); // rs1*4
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::ADD, rs1, rs1, rd)); // array+rs1*4                                        // li a0,3
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs2, rs1, 0));  // lw a0,4(sp));

            Instr.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rs2, rv::rvREG::X2, stackvarmap.add_operand(inst.des)));
        }
    }
    break;
    case ir::Operator::eq:
    {
        auto rs1 = getRs1(inst.op1);
        auto rs2 = getRs2(inst.op2);
        auto rd = getRd(inst.des);

        if (inst.op1.type == Type::IntLiteral)
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rs1, get_int(inst.op1.name)));
        }
        else
        {
            if (stackvarmap._table.find(inst.op1) != stackvarmap._table.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, stackvarmap.find_operand(inst.op1)));
            }
            else if (globalvs.find(inst.op1.name) != globalvs.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.op1.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
            }
            else
                assert(0);
        }
        if (inst.op2.type == Type::IntLiteral)
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rs2, get_int(inst.op2.name)));
        }
        else
        {
            if (stackvarmap._table.find(inst.op2) != stackvarmap._table.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X2, stackvarmap.find_operand(inst.op2)));
            }
            else if (globalvs.find(inst.op2.name) != globalvs.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.op2.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X10, 0));
            }
            else
                assert(0);
        }
        Instr.push_back(rv::rv_inst(rv::rvOPCODE::SUB, rd, rs1, rs2));
        Instr.push_back(rv::rv_inst(rv::rvOPCODE::SEQZ, rd, rd, rv::rvREG::X0));

        if (stackvarmap._table.find(inst.des) != stackvarmap._table.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.des)));
        }
        else if (globalvs.find(inst.des.name) != globalvs.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, inst.des.name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X11, 0));
        }
        else
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X2, stackvarmap.add_operand(inst.des)));
        }
    }
    break;
    case ir::Operator::neq:
    {
        cout << "开始neq" << endl;

        cout << "是整数" << endl;
        auto rs1 = getRs1(inst.op1);
        auto rs2 = getRs2(inst.op2);
        auto rd = getRd(inst.des);

        if (stackvarmap._table.find(inst.op1) != stackvarmap._table.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, stackvarmap.find_operand(inst.op1)));
        }
        else if (globalvs.find(inst.op1.name) != globalvs.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.op1.name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
        }
        else
            assert(0);

        if (stackvarmap._table.find(inst.op2) != stackvarmap._table.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X2, stackvarmap.find_operand(inst.op2)));
        }
        else if (globalvs.find(inst.op2.name) != globalvs.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.op2.name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X10, 0));
        }
        else
            assert(0);

        Instr.push_back(rv::rv_inst(rv::rvOPCODE::SUB, rd, rs1, rs2));
        Instr.push_back(rv::rv_inst(rv::rvOPCODE::SNEZ, rd, rd, rv::rvREG::X0));

        if (stackvarmap._table.find(inst.des) != stackvarmap._table.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.des)));
        }
        else if (globalvs.find(inst.des.name) != globalvs.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, inst.des.name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X11, 0));
        }
        else
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X2, stackvarmap.add_operand(inst.des)));
        }
    }
    break;
    case ir::Operator::fneq:
    {
        // 太麻烦了，直接特殊法

        // if (stof(inst.op1.name) != stof(inst.op2.name))
        // {
        //     Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rv::rvREG::X10, 1));
        //     Instr.push_back(rv::rv_inst(rv::rvOPCODE::CVT_I2F, rv::rvFREG::F10, rv::rvREG::X10, 0));
        //     Instr.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvFREG::F10, rv::rvREG::X2, stackvarmap.add_operand(inst.des)));
        // }
        // else
        // {
        //     Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rv::rvREG::X10, 0));
        //     Instr.push_back(rv::rv_inst(rv::rvOPCODE::CVT_I2F, rv::rvFREG::F10, rv::rvREG::X10, 0));
        //     Instr.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvFREG::F10, rv::rvREG::X2, stackvarmap.add_operand(inst.des)));
        // }

        cout << "是浮点数" << endl;
        cout << "neq 浮点数" << endl;
        auto rs1 = fgetRs1(inst.op1);
        auto rs2 = fgetRs2(inst.op2);
        auto rd = fgetRd(inst.des);
        auto rd_g = getRd(inst.des);

        float temp = std::atof(inst.op1.name.c_str());
        uint32_t float_temp = *(uint32_t *)&temp;
        string name = "FLOAT" + std::to_string(float_size++);
        string str = name + ":\n\t.word\t" + std::to_string(float_temp) + "\n";
        float_data += str;

        Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, name));
        Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs1, rv::rvREG::X10, 0));

        temp = std::atof(inst.op2.name.c_str());
        float_temp = *(uint32_t *)&temp;
        name = "FLOAT" + std::to_string(float_size++);
        str = name + ":\n\t.word\t" + std::to_string(float_temp) + "\n";
        float_data += str;

        Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, name));
        Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs2, rv::rvREG::X10, 0));

        cout << "float data is now " << float_data << endl;

        Instr.push_back(rv::rv_inst(rv::rvOPCODE::FSUB, rd, rs1, rs2));
        Instr.push_back(rv::rv_inst(rv::rvOPCODE::CVT_F2I, rd_g, rd, 0));
        Instr.push_back(rv::rv_inst(rv::rvOPCODE::SNEZ, rd_g, rd_g, rv::rvREG::X0));
        Instr.push_back(rv::rv_inst(rv::rvOPCODE::CVT_I2F, rd, rd_g, 0));

        Instr.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rd, rv::rvREG::X2, stackvarmap.add_operand(inst.des)));
        cout << "将" << inst.des.name << "加入堆栈" << endl;
    }
    break;
    case ir::Operator::_not:
    {
        auto rs1 = getRs1(inst.op1);

        if (inst.op1.type == Type::IntLiteral)
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rs1, get_int(inst.op1.name)));
        }
        else
        {

            if (stackvarmap._table.find(inst.op1) != stackvarmap._table.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, stackvarmap.find_operand(inst.op1)));
            }
            else if (globalvs.find(inst.op1.name) != globalvs.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.op1.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
            }
            else
                assert(0);
        }
        Instr.push_back(rv::rv_inst(rv::rvOPCODE::SEQZ, rs1, rs1, rv::rvREG::X0));

        if (stackvarmap._table.find(inst.des) != stackvarmap._table.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rs1, rv::rvREG::X2, stackvarmap.find_operand(inst.des)));
        }
        else if (globalvs.find(inst.des.name) != globalvs.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, inst.des.name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rs1, rv::rvREG::X11, 0));
        }
        else
        {
            stackvarmap.add_operand(inst.des);
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rs1, rv::rvREG::X2, stackvarmap.find_operand(inst.des)));
        }
    }
    break;
    case ir::Operator::_or:
    case ir::Operator::_and:
    {
        rv::rvOPCODE op;
        if (inst.op == ir::Operator::_or)
            op = rv::rvOPCODE::OR;
        else
            op = rv::rvOPCODE::AND;
        auto rs1 = getRs1(inst.op1);
        auto rs2 = getRs2(inst.op2);
        auto rd = getRd(inst.des);
        if (inst.op1.type == Type::IntLiteral)
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rs1, get_int(inst.op1.name)));
        }
        else
        {

            if (stackvarmap._table.find(inst.op1) != stackvarmap._table.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, stackvarmap.find_operand(inst.op1)));
            }
            else if (globalvs.find(inst.op1.name) != globalvs.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.op1.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
            }
            else
                assert(0);
        }
        Instr.push_back(rv::rv_inst(rv::rvOPCODE::SNEZ, rs1, rs1, rv::rvREG::X0));

        if (inst.op2.type == Type::IntLiteral)
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rs2, get_int(inst.op2.name)));
        }
        else
        {

            if (stackvarmap._table.find(inst.op2) != stackvarmap._table.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X2, stackvarmap.find_operand(inst.op2)));
            }
            else if (globalvs.find(inst.op2.name) != globalvs.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.op2.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X10, 0));
            }
            else
                assert(0);
        }
        Instr.push_back(rv::rv_inst(rv::rvOPCODE::SNEZ, rs2, rs2, rv::rvREG::X0));

        Instr.push_back(rv::rv_inst(op, rd, rs1, rs2));

        if (stackvarmap._table.find(inst.des) != stackvarmap._table.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.des)));
        }
        else if (globalvs.find(inst.des.name) != globalvs.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, inst.des.name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X11, 0));
        }
        else
        {

            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rv::rvREG::X2, stackvarmap.add_operand(inst.des)));
        }
    }
    break;
    case ir::Operator::_goto:
    {
        if (stackvarmap._table.find(inst.op1) != stackvarmap._table.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X10, rv::rvREG::X2, stackvarmap.find_operand(inst.op1)));
        }
        else if (globalvs.find(inst.op1.name) != globalvs.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.op1.name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X10, rv::rvREG::X10, 0));
        }
        else
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rv::rvREG::X10, 1)); // 无条件一定跳转
        }

        Instr.push_back(rv::rv_inst(rv::rvOPCODE::BNE, rv::rvREG::X10, rv::rvREG::X0, ""));

        assert(inst.des.type == ir::Type::IntLiteral);
        // goto_rcd[ir_pc + get_int(inst.des.name)].push_back(Instr.size() - 1);
    }
    break;
    case ir::Operator::cvt_i2f:
    {
        auto rs1 = getRs1(inst.op1);

        if (inst.op1.type == Type::IntLiteral)
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LI, rs1, get_int(inst.op1.name)));
        }
        else
        {
            if (stackvarmap._table.find(inst.op1) != stackvarmap._table.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, stackvarmap.find_operand(inst.op1)));
            }
            else if (globalvs.find(inst.op1.name) != globalvs.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.op1.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
            }
            else
                assert(0);
        }

        Instr.push_back(rv::rv_inst(rv::rvOPCODE::CVT_I2F, rv::rvFREG::F10, rs1, 0));

        if (stackvarmap._table.find(inst.des) != stackvarmap._table.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X2, stackvarmap.find_operand(inst.des)));
        }
        else if (globalvs.find(inst.des.name) != globalvs.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, inst.des.name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvFREG::F10, rv::rvREG::X5, 0));
        }
        else
        {
            stackvarmap.add_operand(inst.des);
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvFREG::F10, rv::rvREG::X2, stackvarmap.find_operand(inst.des)));
        }
    }
    break;
    case ir::Operator::cvt_f2i:
    {
        auto rs1 = fgetRs1(inst.op1);

        if (inst.op1.type == Type::FloatLiteral)
        {
            string float_temp = get_float(inst.op1.name);
            string name = "FLOAT" + std::to_string(float_size++);
            string str = name + ":\n\t.word\t" + float_temp + "\n";
            float_data += str;

            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs1, rv::rvREG::X10, 0));
        }
        else
        {
            if (stackvarmap._table.find(inst.op1) != stackvarmap._table.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs1, rv::rvREG::X2, stackvarmap.find_operand(inst.op1)));
            }
            else if (globalvs.find(inst.op1.name) != globalvs.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.op1.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs1, rv::rvREG::X10, 0));
            }
            else
                assert(0);
        }

        // Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLOOR, rs1, rs1));
        Instr.push_back(rv::rv_inst(rv::rvOPCODE::CVT_F2I, rv::rvREG::X10, rs1, 0));

        if (stackvarmap._table.find(inst.des) != stackvarmap._table.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X10, rv::rvREG::X2, stackvarmap.find_operand(inst.des)));

            string float_temp = get_float("0.5");
            string name = "FLOAT" + std::to_string(float_size++);
            string str = name + ":\n\t.word\t" + float_temp + "\n";
            float_data += str;

            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rv::rvFREG::F10, rv::rvREG::X11, 0));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::FSUB, rv::rvFREG::F10, rs1, rv::rvFREG::F10));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::CVT_F2I, rv::rvREG::X12, rv::rvFREG::F10, 0));

            // beq
            string label = ".L" + std::to_string(local_tag++);
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::BEQ, rv::rvREG::X12, rv::rvREG::X10, label));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X12, rv::rvREG::X2, stackvarmap.find_operand(inst.des)));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LABEL, label));
        }
        else if (globalvs.find(inst.des.name) != globalvs.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, inst.des.name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X10, rv::rvREG::X5, 0));

            string float_temp = get_float("0.5");
            string name = "FLOAT" + std::to_string(float_size++);
            string str = name + ":\n\t.word\t" + float_temp + "\n";
            float_data += str;

            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rv::rvFREG::F10, rv::rvREG::X11, 0));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::FSUB, rv::rvFREG::F10, rs1, rv::rvFREG::F10));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::CVT_F2I, rv::rvREG::X12, rv::rvFREG::F10, 0));

            // beq
            string label = ".L" + std::to_string(local_tag++);
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::BEQ, rv::rvREG::X12, rv::rvREG::X10, label));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, inst.des.name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X12, rv::rvREG::X5, 0));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LABEL, label));
        }
        else
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X10, rv::rvREG::X2, stackvarmap.add_operand(inst.des)));

            string float_temp = get_float("0.5");
            string name = "FLOAT" + std::to_string(float_size++);
            string str = name + ":\n\t.word\t" + float_temp + "\n";
            float_data += str;

            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rv::rvFREG::F10, rv::rvREG::X11, 0));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::FSUB, rv::rvFREG::F10, rs1, rv::rvFREG::F10));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::CVT_F2I, rv::rvREG::X12, rv::rvFREG::F10, 0));

            // beq
            string label = ".L" + std::to_string(local_tag++);
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::BEQ, rv::rvREG::X12, rv::rvREG::X10, label));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X12, rv::rvREG::X2, stackvarmap.find_operand(inst.des)));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LABEL, label));
        }
    }
    break;
    case ir::Operator::fsub:
    case ir::Operator::fadd:
    case ir::Operator::fmul:
    case ir::Operator::fdiv:
    {
        auto rs1 = fgetRs1(inst.op1);
        auto rs2 = fgetRs2(inst.op2);
        auto rd = fgetRd(inst.des);

        if (inst.op1.type == Type::FloatLiteral)
        {
            string float_temp = get_float(inst.op1.name);
            string name = "FLOAT" + std::to_string(float_size++);
            string str = name + ":\n\t.word\t" + float_temp + "\n";
            float_data += str;

            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs1, rv::rvREG::X10, 0));
        }
        else
        {
            if (stackvarmap._table.find(inst.op1) != stackvarmap._table.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs1, rv::rvREG::X2, stackvarmap.find_operand(inst.op1)));
            }
            else if (globalvs.find(inst.op1.name) != globalvs.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.op1.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs1, rv::rvREG::X10, 0));
            }
            else
                assert(0);
        }

        if (inst.op2.type == Type::FloatLiteral)
        {
            string float_temp = get_float(inst.op2.name);
            string name = "FLOAT" + std::to_string(float_size++);
            string str = name + ":\n\t.word\t" + float_temp + "\n";
            float_data += str;

            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs2, rv::rvREG::X10, 0));
        }
        else
        {
            if (stackvarmap._table.find(inst.op2) != stackvarmap._table.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs2, rv::rvREG::X2, stackvarmap.find_operand(inst.op2)));
            }
            else if (globalvs.find(inst.op2.name) != globalvs.end())
            {
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.op2.name));
                Instr.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs2, rv::rvREG::X10, 0));
            }
            else
                assert(0);
        }
        rv::rvOPCODE op;
        switch (inst.op)
        {
        case ir::Operator::fsub:
            op = rv::rvOPCODE::FSUB;
            break;
        case ir::Operator::fadd:
            op = rv::rvOPCODE::FADD;
            break;
        case ir::Operator::fmul:
            op = rv::rvOPCODE::FMUL;
            break;
        case ir::Operator::fdiv:
            op = rv::rvOPCODE::FDIV;
            break;
        }
        Instr.push_back(rv::rv_inst(op, rd, rs1, rs2));

        if (stackvarmap._table.find(inst.des) != stackvarmap._table.end())
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rd, rv::rvREG::X2, stackvarmap.find_operand(inst.des)));
        }
        else if (globalvs.find(inst.des.name) != globalvs.end())
        {
            auto it = globalvs_already.find(inst.des.name);
            if (it == globalvs_already.end())
            {
                cout << "还未插入";
                string float_temp = get_float("0.0");
                string str = inst.des.name + ":\n\t.word\t" + float_temp + "\n";
                data += str;
                globalvs_already.insert(inst.des.name);
            }

            Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.des.name));
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rd, rv::rvREG::X10, 0));
        }
        else
        {
            Instr.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rd, rv::rvREG::X2, stackvarmap.add_operand(inst.des)));
        }
    }
    break;
    }
    cout << "---gen_instr end---" << endl;
}
