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

uint32_t delt = 0;
int inst_num = 0;
backend::Generator::Generator(ir::Program &p, std::ofstream &f) : program(p), fout(f) {}

// 这个函数用于查找给定操作数（Operand）的地址偏移。它通过访问_table成员变量，并根据给定的操作数执行必要的操作来找到操作数的地址，并返回偏移量。
int backend::stackVarMap::find_operand(ir::Operand op)
{
    return _table[op];
}
// 这个函数用于将操作数添加到当前的映射表中，并为该变量在内存中分配空间。它通过更新_table成员变量，并根据给定的操作数和大小（以字节为单位）分配内存空间，并返回偏移量。
int backend::stackVarMap::add_operand(ir::Operand op, uint32_t size)
{
    _table[op] = delt;
    delt += size;
    return _table[op];
}
// 这个函数用于获取给定操作数（Operand）的寄存器目标（rvREG）。根据给定的操作数，它返回适当的rvREG值，表示操作数的寄存器目标。
rv::rvREG backend::Generator::getRd(ir::Operand)
{
    return rv::rvREG::X28;
}
// 这个函数用于获取给定操作数的整数类型源寄存器（rvREG）。根据给定的操作数，它返回适当的整数寄存器对象，表示操作数的源寄存器。
rv::rvREG backend::Generator::getRs1(ir::Operand)
{
    return rv::rvREG::X29;
}
// 这个函数用于获取给定操作数的整数类型源寄存器（rvREG）。根据给定的操作数，它返回适当的整数寄存器对象，表示操作数的源寄存器。
rv::rvREG backend::Generator::getRs2(ir::Operand)
{
    return rv::rvREG::X30;
}
// 这个函数用于获取给定操作数（Operand）的浮点寄存器目标（rvFREG）。根据给定的操作数，它返回适当的rvFREG值，表示操作数的浮点寄存器目标。
rv::rvFREG backend::Generator::fgetRd(ir::Operand)
{
    return rv::rvFREG::F28;
}

// 这个函数用于获取给定操作数的浮点寄存器目标（rv::rvFREG）。根据给定的操作数，它返回适当的浮点寄存器目标，表示操作数应存储在哪个浮点寄存器中。
rv::rvFREG backend::Generator::fgetRs1(ir::Operand)
{
    return rv::rvFREG::F29;
}
// 这个函数用于获取给定操作数的第二个浮点寄存器目标（rv::rvFREG）。根据给定的操作数，它返回适当的浮点寄存器目标，表示操作数应存储在哪个浮点寄存器中。
rv::rvFREG backend::Generator::fgetRs2(ir::Operand)
{
    return rv::rvFREG::F30;
}

void backend::Generator::gen()
{

    fout << "\t.text\n";

    // 遍历所有全局变量
    for (auto globalval : program.globalVal)
    {
        if (globalval.maxlen > 0)
            fout << "\t.comm\t" + globalval.val.name + "," + std::to_string(globalval.maxlen * 4) + ",4\n";
        else
            fout << "\t.comm\t" + globalval.val.name + ",4,4\n";
    }

    // 遍历所有函数
    for (auto &function : program.functions)
    {
        gen_func(function);
    }
}
void backend::Generator::gen_func(const ir::Function &function)
{
    fout << "\t.global\t" << function.name << "\n"
         << "\t.type\t" << function.name << ", @function\n"
         << function.name << ":\n";
    delt = 0;
    int old_pc = inst_num;
    if (function.name != "global" || function.InstVec.size() != 1)
    {
        Inst.push_back(rv::rv_inst(rv::rvOPCODE::ADDI, rv::rvREG::X2, rv::rvREG::X2, 0)); // sp=sp+0-->待修改
        inst_num++;
        stackvarmap.add_operand(Operand("ra", Type::Int));
        // sw op rd imm(rs1)
        Inst.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X1, rv::rvREG::X2, stackvarmap.find_operand(Operand("ra", Type::Int)))); // sw ra,0(sp)
        inst_num++;
        // 遍历所有指令
        for (auto &instrPtr : function.InstVec)
        {
            ir::Instruction &instruction = *instrPtr;
            gen_instr(instruction);
        }

        Inst[old_pc].imm = -delt;

        // 找到return指令的前一条指令，修改其立即数
        for (int i = 0; i < function.InstVec.size(); i++)
        {
            if (function.InstVec[i]->op == ir::Operator::_return)
            {
                int rb = Inst.size() - 1;
                Inst[rb - 1].imm = delt;
            }
        }
    }
    if (function.name == "global" && function.InstVec.size() == 1)
    {
        // global的return null-->如果该函数是global函数，最后肯定要加个jr ra
        Inst.push_back(rv::rv_inst(rv::rvOPCODE::JR, rv::rvREG::X1)); // jr ra
        inst_num++;
    }

    int new_pc = inst_num;
    for (int i = old_pc; i < new_pc; i++)
    {
        cout << "TEST: " << toString(Inst[i].op) << "\n"
             << Inst[i].draw() << endl;
        fout << Inst[i].draw();
    }
}
void backend::Generator::gen_instr(const ir::Instruction &inst)
{
    cout << "---gen_instr OP DES OP1 OP2---" << endl;
    cout << "gen_instr " << toString(inst.op) << " " << toString(inst.des.type) << " " << inst.des.name << " "
         << toString(inst.op1.type) << " " << inst.op1.name << " " << toString(inst.op2.type) << " " << inst.op2.name << endl;
    switch (inst.op)
    {
    case Operator::_return:
    {
        cout << "*return" << endl;
        switch (inst.op1.type)
        {
        case Type::IntLiteral:
            // op rs1 imm rs2
            // lw op rd imm(rs1)
            Inst.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X10, rv::rvREG::X2, stackvarmap.add_operand(inst.op1))); // lw a0,4(sp)
            inst_num++;
            // li op rd imm
            Inst.push_back(rv::rv_inst(rv::rvOPCODE::LI, rv::rvREG::X10, std::stoi(inst.op1.name))); // li a0,3
            inst_num++;
            // sw op rd imm(rs1)
            Inst.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X10, rv::rvREG::X2, stackvarmap.find_operand(inst.op1))); // sw a0,4(sp)
            inst_num++;
            // lw op rd imm(rs1)
            Inst.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X1, rv::rvREG::X2, stackvarmap.find_operand(Operand("ra", Type::Int)))); // lw ra,4(sp)
            inst_num++;
            break;
        case Type::FloatLiteral:
            break;
        case Type::Int:
            if (stackvarmap._table.find(inst.op1) != stackvarmap._table.end())
            {
                Inst.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X10, rv::rvREG::X2, stackvarmap.find_operand(inst.op1)));
                inst_num++;
            }
            else
            {
                Inst.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, inst.op1.name));
                inst_num++;
                Inst.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X10, rv::rvREG::X10, 0));
                inst_num++;
            }
            break;
        case Type::Float:
            break;
        case Type::null: // 返回null则不操作
            break;
        default:
            assert(0 && "invalid return value type");
            break;
        }

        Inst.push_back(rv::rv_inst(rv::rvOPCODE::ADDI, rv::rvREG::X2, rv::rvREG::X2, 0)); // addi sp,sp,0-->待修改
        inst_num++;
        Inst.push_back(rv::rv_inst(rv::rvOPCODE::JR, rv::rvREG::X1)); // jr ra
        inst_num++;
    }
    break;
    case Operator::call:
    {
        cout << "*call" << endl;
        auto callinst = static_cast<const ir::CallInst &>(inst);
        auto fn = callinst.op1.name;
        // op label
        Inst.push_back(rv::rv_inst(rv::rvOPCODE::CALL, fn)); // call function
        inst_num++;
    }
    }
    cout << "---gen_instr end---" << endl;
}
