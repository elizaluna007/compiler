#include "backend/rv_inst_impl.h"
#include <iostream>
#include <assert.h>

std::string rv::rv_inst::draw() const
{
    switch (op)
    {
    case rvOPCODE::ADD:
    case rvOPCODE::SUB:
    case rvOPCODE::XOR:
    case rvOPCODE::OR:
    case rvOPCODE::AND:
    case rvOPCODE::SLL:
    case rvOPCODE::SRL:
    case rvOPCODE::SRA:
    case rvOPCODE::SLT:
    case rvOPCODE::SLTU:
    case rvOPCODE::MUL:
    case rvOPCODE::DIV:
    case rvOPCODE::REM:
    {
        return "\t" + toString(op) + "\t" + toString(rd) + "," + toString(rs1) + "," + toString(rs2) + "\n";
        break;
    }

    case rv::rvOPCODE::FADD:
    case rv::rvOPCODE::FSUB:
    case rv::rvOPCODE::FMUL:
    case rv::rvOPCODE::FDIV:
    {
        return "\t" + toString(op) + "\t" + toString(frd) + "," + toString(frs1) + "," + toString(frs2) + "\n";
        break;
    }

    case rv::rvOPCODE::FEQ:
    case rv::rvOPCODE::FLT:
    case rv::rvOPCODE::FLE:
    {
        return "\t" + toString(op) + "\t" + toString(rd) + "," + toString(frs1) + "," + toString(frs2) + "\n";
        break;
    }

    case rvOPCODE::ADDI:
    case rvOPCODE::XORI:
    case rvOPCODE::ORI:
    case rvOPCODE::ANDI:
    case rvOPCODE::SLLI:
    case rvOPCODE::SRLI:
    case rvOPCODE::SRAI:
    case rvOPCODE::SLTI:
    case rvOPCODE::SLTIU:
    case rvOPCODE::JAL:
    {
        return "\t" + toString(op) + "\t" + toString(rd) + "," + toString(rs1) + "," + std::to_string(int(imm)) + "\n";
        break;
    }

    case rvOPCODE::LW:
    case rvOPCODE::JALR:
    {
        if (label.empty())
            return "\t" + toString(op) + "\t" + toString(rd) + "," + std::to_string(int(imm)) + "(" + toString(rs1) + ")" + "\n";
        else if (rs1 == rv::rvREG::X0)
            return "\t" + toString(op) + "\t" + toString(rd) + "," + label + "\n"; // 全局变量加载
        else
            return "\t" + toString(op) + "\t" + toString(rd) + "," + label + "," + toString(rs1) + "\n"; // 全局变量加载
        break;
    }

    case rvOPCODE::SW:
    {

        return "\t" + toString(op) + "\t" + toString(rd) + "," + std::to_string(int(imm)) + "(" + toString(rs1) + ")" + "\n";
        break;
    }

    case rv::rvOPCODE::FLW:
    {
        return "\t" + toString(op) + "\t" + toString(frd) + "," + std::to_string(int(imm)) + "(" + toString(rs1) + ")" + "\n";
        break;
    }

    case rv::rvOPCODE::FSW:
    {
        return "\t" + toString(op) + "\t" + toString(frd) + "," + std::to_string(int(imm)) + "(" + toString(rs1) + ")" + "\n";
        break;
    }

    case rvOPCODE::BEQ:
    case rvOPCODE::BNE:
    case rvOPCODE::BLT:
    case rvOPCODE::BGE:
    case rvOPCODE::BLTU:
    case rvOPCODE::BGEU:
    {
        return "\t" + toString(op) + "\t" + toString(rs1) + "," + toString(rs2) + "," + label + "\n";
        break;
    }

    case rvOPCODE::LA:
    {

        return "\t" + toString(op) + "\t" + toString(rd) + "," + label + "\n";
        break;
    }

    case rvOPCODE::LI:
    {
        return "\t" + toString(op) + "\t" + toString(rd) + "," + std::to_string(int(imm)) + "\n";
        break;
    }

    case rvOPCODE::MOV:
    {
        return "\t" + toString(op) + "\t" + toString(rd) + "," + toString(rs1) + "\n";
        break;
    }

    case rvOPCODE::J:
    {
        return "\t" + toString(op) + "\t" + label + "\n";
        break;
    }

    case rvOPCODE::JR:
    {
        return "\t" + toString(op) + "\t" + toString(rs1) + "\n";
        break;
    }

    case rv::rvOPCODE::CVT_F2I:
    {
        return "\t" + toString(op) + "\t" + toString(rd) + "," + toString(frs1) + "\n";
        break;
    }

    case rv::rvOPCODE::CVT_I2F:
    {
        return "\t" + toString(op) + "\t" + toString(frd) + "," + toString(rs1) + "\n";
        break;
    }
    case rv::rvOPCODE::FLOOR:
    {
        return "\t" + toString(op) + "\t" + toString(frd) + "," + toString(frs1) + "\n";
        break;
    }

    case rv::rvOPCODE::SEQZ:
    case rv::rvOPCODE::SNEZ:
    {
        return "\t" + toString(op) + "\t" + toString(rd) + "," + toString(rs1) + "\n";
        break;
    }

    case rv::rvOPCODE::CALL:
    {
        return "\t" + toString(op) + "\t" + label + "\n";
        break;
    }

    case rv::rvOPCODE::NOP:
    {
        return "\tnop\n";
        break;
    }

    case rv::rvOPCODE::LABEL:
    {
        return label + ":\n";
        break;
    }

    default:
        assert(0);
    }
}
rv::rv_inst::rv_inst(rvOPCODE op, rvREG rs1) : op(op), rs1(rs1){};
rv::rv_inst::rv_inst(rvOPCODE op, std::string label) : op(op), label(label){};
rv::rv_inst::rv_inst(rvOPCODE op, rvREG rd, rvREG rs1) : op(op), rd(rd), rs1(rs1){};
rv::rv_inst::rv_inst(rvOPCODE op, rvREG rd, uint32_t imm) : op(op), rd(rd), imm(imm){};
rv::rv_inst::rv_inst(rvOPCODE op, rvREG rd, std::string label) : op(op), rd(rd), label(label), frd(rv::rvFREG::F0){};
rv::rv_inst::rv_inst(rvOPCODE op, rvREG rd, rvREG rs1, uint32_t imm) : op(op), rd(rd), rs1(rs1), imm(imm){};
rv::rv_inst::rv_inst(rvOPCODE op, rvREG rd, std::string label, rvREG rs1) : op(op), rd(rd), label(label), rs1(rs1){};
rv::rv_inst::rv_inst(rvOPCODE op, rvFREG frd, std::string label, rvREG rs1) : op(op), frd(frd), label(label), rs1(rs1){};
rv::rv_inst::rv_inst(rvOPCODE op, rvREG rd, rvREG rs1, rvREG rs2) : op(op), rd(rd), rs1(rs1), rs2(rs2){};

rv::rv_inst::rv_inst(rvOPCODE op, rvFREG frd, rvFREG frs1) : op(op), frs1(frs1){};
rv::rv_inst::rv_inst(rvOPCODE op, rvFREG frd, uint32_t imm) : op(op), frd(frd), imm(imm){};
rv::rv_inst::rv_inst(rvOPCODE op, rvFREG frd, rvFREG frs1, rvFREG frs2) : op(op), frd(frd), frs1(frs1), frs2(frs2){};
rv::rv_inst::rv_inst(rvOPCODE op, rvREG rd, rvFREG frs1, rvFREG frs2) : op(op), rd(rd), frs1(frs1), frs2(frs2){};
rv::rv_inst::rv_inst(rvOPCODE op, rvFREG frd, rvFREG frs1, uint32_t imm) : op(op), frd(frd), frs1(frs1), imm(imm){};
rv::rv_inst::rv_inst(rvOPCODE op, rvFREG frd, rvREG rs1, uint32_t imm) : op(op), frd(frd), rs1(rs1), imm(imm){};
rv::rv_inst::rv_inst(rvOPCODE op, rvREG rd, rvFREG frs1, uint32_t imm) : op(op), rd(rd), frs1(frs1), imm(imm){};
rv::rv_inst::rv_inst(rvOPCODE op, rvREG rs1, uint32_t imm, rvREG rs2) : op(op), rs1(rs1), rs2(rs2), imm(imm){};
rv::rv_inst::rv_inst(rvOPCODE op, rvFREG frd, std::string label) : op(op), frd(frd), label(label){};
rv::rv_inst::rv_inst(rvOPCODE op, rvREG rs1, rvREG rs2, std::string label) : op(op), rs1(rs1), rs2(rs2), label(label){};
rv::rv_inst::rv_inst(rvOPCODE op, rvREG rs1, uint32_t imm, rvFREG frs2) : op(op), rs1(rs1), frs2(frs2), imm(imm){};

// rv_inst(rvOPCODE op, rvREG rd, rvREG rs1, rvREG rs2, uint32_t imm, rvFREG frd, rvFREG frs1, rvFREG frs2, std::string label) : op(op), rs1(rs1), rs2(rs2), imm(imm), frd(frd), frs1(frs1), frs2(frs2), label(label){};