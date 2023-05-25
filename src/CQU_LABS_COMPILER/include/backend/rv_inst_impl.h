#ifndef RV_INST_IMPL_H
#define RV_INST_IMPL_H

#include "backend/rv_def.h"

namespace rv {


struct rv_inst{
    rvREG rd, rs1, rs2;         // operands of rv inst
    rvFREG frd, frs1, frs2;
    rvOPCODE op;                // opcode of rv inst
    
    uint32_t imm;               // optional, in immediate inst
    std::string label;          // optional, in beq/jarl inst

    std::string draw() const;
    rv_inst(rvOPCODE op, rvREG rd, rvREG rs1, rvREG rs2);
    rv_inst(rvOPCODE op, rvFREG rd, rvFREG rs1, rvFREG rs2);
    rv_inst(rvOPCODE op, rvREG rd, rvFREG rs1, rvFREG rs2);
    rv_inst(rvOPCODE op, rvREG rd, rvREG rs1, uint32_t imm);
    rv_inst(rvOPCODE op, rvFREG rd, rvREG rs1, uint32_t imm);
    rv_inst(rvOPCODE op, rvREG rd, rvFREG rs1, uint32_t imm);
    rv_inst(rvOPCODE op, rvREG rs1, uint32_t imm, rvREG rs2);
    rv_inst(rvOPCODE op, rvREG rs1, rvREG rs2, std::string label);
    rv_inst(rvOPCODE op, rvREG rs1, uint32_t imm, rvFREG rs2);
    rv_inst(rvOPCODE op, rvREG rd, uint32_t imm);
    rv_inst(rvOPCODE op, rvREG rd, std::string label);
    rv_inst(rvOPCODE op, rvREG rs1);
    rv_inst(rvOPCODE op, std::string label);
};


};

#endif