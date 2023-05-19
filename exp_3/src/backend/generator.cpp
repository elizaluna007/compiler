#include "backend/generator.h"

#include <assert.h>

#define TODO assert(0 && "todo")

backend::Generator::Generator(ir::Program &p, std::ofstream &f) : program(p), fout(f) {}

void backend::Generator::gen()
{
    // 遍历所有函数
    for (auto &function : program.functions)
    {
        gen_func(function);
    }
}
void backend::Generator::gen_func(const ir::Function &function)
{
    // 遍历所有指令
    for (auto &instrPtr : function.InstVec)
    {
        ir::Instruction &instruction = *instrPtr;
        gen_instr(instruction);
    }
}
void backend::Generator::gen_instr(const ir::Instruction &instruction)
{
    switch (instruction.op)
    {
    case ir::Operator::_return:
        gen_return(instruction);
        break;
    case ir::Operator::_goto:
        gen_goto(instruction);
        break;
    case ir::Operator::call:
        gencall(instruction);
        break;
    case ir::Operator::alloc:
        genalloc(instruction);
        break;
    case ir::Operator::store:
        genstore(instruction);
        break;
    case ir::Operator::load:
        genload(instruction);
        break;
    case ir::Operator::getptr:
        gengetptr(instruction);
        break;
    case ir::Operator::def:
        gendef(instruction);
        break;
    case ir::Operator::fdef:
        genfdef(instruction);
        break;
    case ir::Operator::mov:
        genmov(instruction);
        break;
    case ir::Operator::fmov:
        genfmov(instruction);
        break;
    case ir::Operator::cvt_i2f:
        gencvt_i2f(instruction);
        break;
    case ir::Operator::cvt_f2i:
        gencvt_f2i(instruction);
        break;
    case ir::Operator::add:
        genadd(instruction);
        break;
    case ir::Operator::addi:
        genaddi(instruction);
        break;
    case ir::Operator::fadd:
        genfadd(instruction);
        break;
    case ir::Operator::sub:
        gensub(instruction);
        break;
    case ir::Operator::subi:
        gensubi(instruction);
        break;
    case ir::Operator::fsub:
        genfsub(instruction);
        break;
    case ir::Operator::mul:
        genmul(instruction);
        break;
    case ir::Operator::fmul:
        genfmul(instruction);
        break;
    case ir::Operator::div:
        gendiv(instruction);
        break;
    case ir::Operator::fdiv:
        genfdiv(instruction);
        break;
    case ir::Operator::mod:
        genmod(instruction);
        break;
    case ir::Operator::lss:
        genlss(instruction);
        break;
    case ir::Operator::flss:
        genflss(instruction);
        break;
    case ir::Operator::leq:
        genleq(instruction);
        break;
    case ir::Operator::fleq:
        genfleq(instruction);
        break;
    case ir::Operator::gtr:
        gengtr(instruction);
        break;
    case ir::Operator::fgtr:
        genfgtr(instruction);
        break;
    case ir::Operator::geq:
        gengeq(instruction);
        break;
    case ir::Operator::fgeq:
        genfgeq(instruction);
        break;
    case ir::Operator::eq:
        geneq(instruction);
        break;
    case ir::Operator::feq:
        genfeq(instruction);
        break;
    case ir::Operator::neq:
        genneq(instruction);
        break;
    case ir::Operator::fneq:
        genfneq(instruction);
        break;
    case ir::Operator::_not:
        gen_not(instruction);
        break;
    case ir::Operator::_and:
        gen_and(instruction);
        break;
    case ir::Operator::_or:
        gen_or(instruction);
        break;
    case ir::Operator::__unuse__:
        gen__unuse__(instruction);
        break;

    default:
        break;
    }
}
void backend::Generator::gen_return(const ir::Instruction &instruction)
{
}
void backend::Generator::gen_goto(const ir::Instruction &instruction)
{
}
void backend::Generator::gencall(const ir::Instruction &instruction)
{
}
void backend::Generator::genalloc(const ir::Instruction &instruction)
{
}
void backend::Generator::genstore(const ir::Instruction &instruction)
{
}
void backend::Generator::genload(const ir::Instruction &instruction)
{
}
void backend::Generator::gengetptr(const ir::Instruction &instruction)
{
}
void backend::Generator::gendef(const ir::Instruction &instruction)
{
}
void backend::Generator::genfdef(const ir::Instruction &instruction)
{
}
void backend::Generator::genmov(const ir::Instruction &instruction)
{
}
void backend::Generator::genfmov(const ir::Instruction &instruction)
{
}
void backend::Generator::gencvt_i2f(const ir::Instruction &instruction)
{
}
void backend::Generator::gencvt_f2i(const ir::Instruction &instruction)
{
}
void backend::Generator::genadd(const ir::Instruction &instruction)
{
}
void backend::Generator::genaddi(const ir::Instruction &instruction)
{
}
void backend::Generator::genfadd(const ir::Instruction &instruction)
{
}
void backend::Generator::gensub(const ir::Instruction &instruction)
{
}
void backend::Generator::gensubi(const ir::Instruction &instruction)
{
}
void backend::Generator::genfsub(const ir::Instruction &instruction)
{
}
void backend::Generator::genmul(const ir::Instruction &instruction)
{
}
void backend::Generator::genfmul(const ir::Instruction &instruction)
{
}
void backend::Generator::gendiv(const ir::Instruction &instruction)
{
}
void backend::Generator::genfdiv(const ir::Instruction &instruction)
{
}
void backend::Generator::genmod(const ir::Instruction &instruction)
{
}
void backend::Generator::genlss(const ir::Instruction &instruction)
{
}
void backend::Generator::genflss(const ir::Instruction &instruction)
{
}
void backend::Generator::genleq(const ir::Instruction &instruction)
{
}
void backend::Generator::genfleq(const ir::Instruction &instruction)
{
}
void backend::Generator::gengtr(const ir::Instruction &instruction)
{
}
void backend::Generator::genfgtr(const ir::Instruction &instruction)
{
}
void backend::Generator::gengeq(const ir::Instruction &instruction)
{
}
void backend::Generator::genfgeq(const ir::Instruction &instruction)
{
}
void backend::Generator::geneq(const ir::Instruction &instruction)
{
}
void backend::Generator::genfeq(const ir::Instruction &instruction)
{
}
void backend::Generator::genneq(const ir::Instruction &instruction)
{
}
void backend::Generator::genfneq(const ir::Instruction &instruction)
{
}
void backend::Generator::gen_not(const ir::Instruction &instruction)
{
}
void backend::Generator::gen_and(const ir::Instruction &instruction)
{
}
void backend::Generator::gen_or(const ir::Instruction &instruction)
{
}
void backend::Generator::gen__unuse__(const ir::Instruction &instruction)
{
}
