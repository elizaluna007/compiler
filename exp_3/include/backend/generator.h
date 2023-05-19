#ifndef GENERARATOR_H
#define GENERARATOR_H

#include "ir/ir.h"
#include "backend/rv_def.h"
#include "backend/rv_inst_impl.h"

#include <map>
#include <string>
#include <vector>
#include <fstream>

namespace backend
{

    // it is a map bewteen variable and its mem addr, the mem addr of a local variable can be identified by ($sp + off)
    struct stackVarMap
    {
        std::map<ir::Operand, int> _table;

        /**
         * @brief find the addr of a ir::Operand
         * @return the offset
         */
        int find_operand(ir::Operand);

        /**
         * @brief add a ir::Operand into current map, alloc space for this variable in memory
         * @param[in] size: the space needed(in byte)
         * @return the offset
         */
        int add_operand(ir::Operand, uint32_t size = 4);
    };

    struct Generator
    {
        const ir::Program &program; // the program to gen
        std::ofstream &fout;        // output file

        Generator(ir::Program &, std::ofstream &);

        // reg allocate api
        rv::rvREG getRd(ir::Operand);
        rv::rvFREG fgetRd(ir::Operand);
        rv::rvREG getRs1(ir::Operand);
        rv::rvREG getRs2(ir::Operand);
        rv::rvFREG fgetRs1(ir::Operand);
        rv::rvFREG fgetRs2(ir::Operand);

        // generate wrapper function
        void gen();
        void gen_func(const ir::Function &);
        void gen_instr(const ir::Instruction &);

        void gen_return(const ir::Instruction &);
        void gen_goto(const ir::Instruction &);
        void gencall(const ir::Instruction &);
        void genalloc(const ir::Instruction &);
        void genstore(const ir::Instruction &);
        void genload(const ir::Instruction &);
        void gengetptr(const ir::Instruction &);
        void gendef(const ir::Instruction &);
        void genfdef(const ir::Instruction &);
        void genmov(const ir::Instruction &);
        void genfmov(const ir::Instruction &);
        void gencvt_i2f(const ir::Instruction &);
        void gencvt_f2i(const ir::Instruction &);
        void genadd(const ir::Instruction &);
        void genaddi(const ir::Instruction &);
        void genfadd(const ir::Instruction &);
        void gensub(const ir::Instruction &);
        void gensubi(const ir::Instruction &);
        void genfsub(const ir::Instruction &);
        void genmul(const ir::Instruction &);
        void genfmul(const ir::Instruction &);
        void gendiv(const ir::Instruction &);
        void genfdiv(const ir::Instruction &);
        void genmod(const ir::Instruction &);
        void genlss(const ir::Instruction &);
        void genflss(const ir::Instruction &);
        void genleq(const ir::Instruction &);
        void genfleq(const ir::Instruction &);
        void gengtr(const ir::Instruction &);
        void genfgtr(const ir::Instruction &);
        void gengeq(const ir::Instruction &);
        void genfgeq(const ir::Instruction &);
        void geneq(const ir::Instruction &);
        void genfeq(const ir::Instruction &);
        void genneq(const ir::Instruction &);
        void genfneq(const ir::Instruction &);
        void gen_not(const ir::Instruction &);
        void gen_and(const ir::Instruction &);
        void gen_or(const ir::Instruction &);
        void gen__unuse__(const ir::Instruction &);
    };

} // namespace backend

#endif