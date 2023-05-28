#include "backend/rv_def.h"
#include <iostream>
#include <assert.h>

std::string rv::toString(rv::rvOPCODE r){
    switch (r)
    {
        case rvOPCODE::ADD: {
            return "add";
            break;
        }
        case rvOPCODE::SUB: {
            return "sub";
            break;
        }
        case rvOPCODE::XOR: {
            return "xor";
            break;
        }
        case rvOPCODE::OR: {
            return "or";
            break;
        }
        case rvOPCODE::AND: {
            return "and";
            break;
        }
        case rvOPCODE::SLL: {
            return "sll";
            break;
        }
        case rvOPCODE::SRL: {
            return "srl";
            break;
        }
        case rvOPCODE::SRA: {
            return "sra";
            break;
        }
        case rvOPCODE::SLT: {
            return "slt";
            break;
        }
        case rvOPCODE::SLTU: {
            return "sltu";
            break;
        }
        case rvOPCODE::ADDI: {
            return "addi";
            break;
        }
        case rvOPCODE::XORI: {
            return "xori";
            break;
        }
        case rvOPCODE::ORI: {
            return "ori";
            break;
        }
        case rvOPCODE::ANDI: {
            return "andi";
            break;
        }
        case rvOPCODE::SLLI: {
            return "slli";
            break;
        }
        case rvOPCODE::SRLI: {
            return "srli";
            break;
        }
        case rvOPCODE::SRAI: {
            return "srai";
            break;
        }
        case rvOPCODE::SLTI: {
            return "slti";
            break;
        }
        case rvOPCODE::SLTIU: {
            return "sltiu";
            break;
        }
        case rvOPCODE::LW: {
            return "lw";
            break;
        }
        case rvOPCODE::SW: {
            return "sw";
            break;
        }
        case rvOPCODE::BEQ: {
            return "beq";
            break;
        }
        case rvOPCODE::BNE: {
            return "bne";
            break;
        }
        case rvOPCODE::BLT: {
            return "blt";
            break;
        }
        case rvOPCODE::BGE: {
            return "bge";
            break;
        }
        case rvOPCODE::BLTU: {
            return "bltu";
            break;
        }
        case rvOPCODE::BGEU: {
            return "bgeu";
            break;
        }
        case rvOPCODE::JAL: {
            return "jal";
            break;
        }
        case rvOPCODE::JALR: {
            return "jalr";
            break;
        }
        case rvOPCODE::MUL: {
            return "mul";
            break;
        }
        case rvOPCODE::DIV: {
            return "div";
            break;
        }
        case rvOPCODE::REM: {
            return "rem";
            break;
        }
        case rvOPCODE::FLW: {
            return "flw";
            break;
        }
        case rvOPCODE::FSW: {
            return "fsw";
            break;
        }
        case rvOPCODE::FADD: {
            return "fadd.s";
            break;
        }
        case rvOPCODE::FSUB: {
            return "fsub.s";
            break;
        }
        case rvOPCODE::FMUL: {
            return "fmul.s";
            break;
        }
        case rvOPCODE::FDIV: {
            return "fdiv.s";
            break;
        }
        case rvOPCODE::CVT_I2F: {
            return "fcvt.s.w";
            break;
        }
        case rvOPCODE::CVT_F2I: {
            return "fcvt.w.s";
            break;
        }
        case rvOPCODE::FLOOR: {
            return "floor.w.s";
            break;
        }
        case rvOPCODE::FEQ: {
            return "feq.s";
            break;
        }
        case rvOPCODE::FLT: {
            return "flt.s";
            break;
        }
        case rvOPCODE::FLE: {
            return "fle.s";
            break;
        }
        case rvOPCODE::LA: {
            return "la";
            break;
        }
        case rvOPCODE::LI: {
            return "li";
            break;
        }
        case rvOPCODE::MOV: {
            return "mv";
            break;
        }
        case rvOPCODE::J: {
            return "j";
            break;
        }
        case rvOPCODE::JR: {
            return "jr";
            break;
        }
        case rvOPCODE::SEQZ: {
            return "seqz";
            break;
        }
        case rvOPCODE::SNEZ: {
            return "snez";
            break;
        }
        case rvOPCODE::CALL: {
            return "call";
            break;
        }
        case rvOPCODE::NOP: {
            return "nop";
            break;
        }
        default: assert(0);
    }
}

std::string rv::toString(rv::rvREG r){
    switch (r)
    {
        case rvREG::X0:{
            return "zero";
            break;
        }
        case rvREG::X1:{
            return "ra";
            break;
        }
        case rvREG::X2:{
            return "sp";
            break;
        }
        case rvREG::X3:{
            return "gp";
            break;
        }
        case rvREG::X4:{
            return "tp";
            break;
        }
        case rvREG::X5:{
            return "t0";
            break;
        }
        case rvREG::X6:{
            return "t1";
            break;
        }
        case rvREG::X7:{
            return "t2";
            break;
        }
        case rvREG::X8:{
            return "s0";
            break;
        }
        case rvREG::X9:{
            return "s1";
            break;
        }
        case rvREG::X10:{
            return "a0";
            break;
        }
        case rvREG::X11:{
            return "a1";
            break;
        }
        case rvREG::X12:{
            return "a2";
            break;
        }
        case rvREG::X13:{
            return "a3";
            break;
        }
        case rvREG::X14:{
            return "a4";
            break;
        }
        case rvREG::X15:{
            return "a5";
            break;
        }
        case rvREG::X16:{
            return "a6";
            break;
        }
        case rvREG::X17:{
            return "a7";
            break;
        }
        case rvREG::X18:{
            return "s2";
            break;
        }
        case rvREG::X19:{
            return "s3";
            break;
        }
        case rvREG::X20:{
            return "s4";
            break;
        }
        case rvREG::X21:{
            return "s5";
            break;
        }
        case rvREG::X22:{
            return "s6";
            break;
        }
        case rvREG::X23:{
            return "s7";
            break;
        }
        case rvREG::X24:{
            return "s8";
            break;
        }
        case rvREG::X25:{
            return "s9";
            break;
        }
        case rvREG::X26:{
            return "s10";
            break;
        }
        case rvREG::X27:{
            return "s11";
            break;
        }
        case rvREG::X28:{
            return "t3";
            break;
        }
        case rvREG::X29:{
            return "t4";
            break;
        }
        case rvREG::X30:{
            return "t5";
            break;
        }
        case rvREG::X31:{
            return "t6";
            break;
        }
        default: assert(0);
    }
}


std::string rv::toString(rv::rvFREG r){
    switch (r)
    {
        case rvFREG::F0:{
            return "ft0";
            break;
        }
        case rvFREG::F1:{
            return "ft1";
            break;
        }
        case rvFREG::F2:{
            return "ft2";
            break;
        }
        case rvFREG::F3:{
            return "ft3";
            break;
        }
        case rvFREG::F4:{
            return "ft4";
            break;
        }
        case rvFREG::F5:{
            return "ft5";
            break;
        }
        case rvFREG::F6:{
            return "ft6";
            break;
        }
        case rvFREG::F7:{
            return "ft7";
            break;
        }
        case rvFREG::F8:{
            return "fs0";
            break;
        }
        case rvFREG::F9:{
            return "fs1";
            break;
        }
        case rvFREG::F10:{
            return "fa0";
            break;
        }
        case rvFREG::F11:{
            return "fa1";
            break;
        }
        case rvFREG::F12:{
            return "fa2";
            break;
        }
        case rvFREG::F13:{
            return "fa3";
            break;
        }
        case rvFREG::F14:{
            return "fa4";
            break;
        }
        case rvFREG::F15:{
            return "fa5";
            break;
        }
        case rvFREG::F16:{
            return "fa6";
            break;
        }
        case rvFREG::F17:{
            return "fa7";
            break;
        }
        case rvFREG::F18:{
            return "fs2";
            break;
        }
        case rvFREG::F19:{
            return "fs3";
            break;
        }
        case rvFREG::F20:{
            return "fs4";
            break;
        }
        case rvFREG::F21:{
            return "fs5";
            break;
        }
        case rvFREG::F22:{
            return "fs6";
            break;
        }
        case rvFREG::F23:{
            return "fs7";
            break;
        }
        case rvFREG::F24:{
            return "fs8";
            break;
        }
        case rvFREG::F25:{
            return "fs9";
            break;
        }
        case rvFREG::F26:{
            return "fs10";
            break;
        }
        case rvFREG::F27:{
            return "fs11";
            break;
        }
        case rvFREG::F28:{
            return "ft3";
            break;
        }
        case rvFREG::F29:{
            return "ft4";
            break;
        }
        case rvFREG::F30:{
            return "ft5";
            break;
        }
        case rvFREG::F31:{
            return "ft6";
            break;
        }
        default: assert(0);
    }
}