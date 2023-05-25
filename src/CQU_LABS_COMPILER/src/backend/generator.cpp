#include"backend/generator.h"

#include<assert.h>
#include<vector>

#define TODO assert(0 && "todo")


backend::Generator::Generator(ir::Program& p, std::ofstream& f): program(p), fout(f) {}

std::string get_name(std::string block_name){
    int idx = block_name.find(":");
    return block_name.substr(0,idx);
}

int backend::stackVarMap::find_operand(ir::Operand operand){
    assert(_table.find(operand) != _table.end());
    return _table[operand];
}

int backend::stackVarMap::add_operand(ir::Operand operand, uint32_t size){
    assert(_table.find(operand) == _table.end());
    _table[operand] = delt;
    delt += size;
    return _table[operand];
}

rv::rvREG backend::Generator::getRd(ir::Operand operand){
    return rv::rvREG::X28;
}

rv::rvREG backend::Generator::getRs1(ir::Operand operand){
    return rv::rvREG::X29;
}

rv::rvREG backend::Generator::getRs2(ir::Operand operand){
    return rv::rvREG::X30;
}

rv::rvFREG backend::Generator::fgetRd(ir::Operand operand){
    return rv::rvFREG::F28;
}

rv::rvFREG backend::Generator::fgetRs1(ir::Operand operand){
    return rv::rvFREG::F29;
}

rv::rvFREG backend::Generator::fgetRs2(ir::Operand operand){
    return rv::rvFREG::F30;
}

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


std::string rv::rv_inst::draw() const{
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
        case rvOPCODE::REM:{
            return "\t" + toString(op) + "\t" + toString(rd) + "," + toString(rs1) + "," + toString(rs2) + "\n";
            break;
        }

        case rv::rvOPCODE::FADD:
        case rv::rvOPCODE::FSUB:
        case rv::rvOPCODE::FMUL:
        case rv::rvOPCODE::FDIV:{
            return "\t" + toString(op) + "\t" + toString(frd) + "," + toString(frs1) + "," + toString(frs2) + "\n";
            break;
        }

        case rv::rvOPCODE::FEQ:
        case rv::rvOPCODE::FLT:
        case rv::rvOPCODE::FLE:{
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
        case rvOPCODE::JAL:{
            return "\t" + toString(op) + "\t" + toString(rd) + "," + toString(rs1) + "," + std::to_string(int(imm)) + "\n";
            break;
        }

        case rvOPCODE::LW:
        case rvOPCODE::JALR:{
            return "\t" + toString(op) + "\t" + toString(rd) + "," + std::to_string(int(imm)) + "(" + toString(rs1) + ")" + "\n";
            break;
        }

        case rvOPCODE::SW:{
            return "\t" + toString(op) + "\t" + toString(rs2) + "," + std::to_string(int(imm)) + "(" + toString(rs1) + ")" + "\n";
            break;
        }

        case rv::rvOPCODE::FLW:{
            return "\t" + toString(op) + "\t" + toString(frd) + "," + std::to_string(int(imm)) + "(" + toString(rs1) + ")" + "\n";
            break;
        }

        case rv::rvOPCODE::FSW:{
            return "\t" + toString(op) + "\t" + toString(frs2) + "," + std::to_string(int(imm)) + "(" + toString(rs1) + ")" + "\n";
            break;
        }

        case rvOPCODE::BEQ:
        case rvOPCODE::BNE:
        case rvOPCODE::BLT:
        case rvOPCODE::BGE:
        case rvOPCODE::BLTU:
        case rvOPCODE::BGEU:{
            return "\t" + toString(op) + "\t" + toString(rs1) + "," + toString(rs2) + "," + label + "\n";
            break;        
        }

        case rvOPCODE::LA:{
            return "\t" + toString(op) + "\t" + toString(rd) + "," + label + "\n";
            break;
        }

        case rvOPCODE::LI:{
            return "\t" + toString(op) + "\t" + toString(rd) + "," + std::to_string(int(imm)) + "\n";
            break;
        }

        case rvOPCODE::MOV:{
            return "\t" + toString(op) + "\t" + toString(rd) + "," + toString(rs1) + "\n";
            break;
        }

        case rvOPCODE::J:{
            return "\t" + toString(op) + "\t" + label + "\n";
            break;
        }

        case rvOPCODE::JR:{
            return "\t" + toString(op) + "\t" + toString(rs1) + "\n";
            break;
        }

        case rv::rvOPCODE::CVT_F2I:{
            return "\t" + toString(op) + "\t" + toString(rd) + "," + toString(frs1) + "\n";
            break;
        }

        case rv::rvOPCODE::CVT_I2F:{
            return "\t" + toString(op) + "\t" + toString(frd) + "," + toString(rs1) + "\n";
            break;
        }

        case rv::rvOPCODE::SEQZ:
        case rv::rvOPCODE::SNEZ:{
            return "\t" + toString(op) + "\t" + toString(rd) + "," + toString(rs1) + "\n";
            break;
        }

        case rv::rvOPCODE::CALL:{
            return "\t" + toString(op) + "\t" + label + "\n";
            break;
        }

        case rv::rvOPCODE::NOP:{
            return "\tnop\n";
            break;
        }

        case rv::rvOPCODE::LABEL:{
            return label + ":\n";
            break;
        }

        default: assert(0);
    }
}


rv::rv_inst::rv_inst(rvOPCODE op, rvREG rd, rvREG rs1, rvREG rs2):op(op), rd(rd), rs1(rs1), rs2(rs2) {};
rv::rv_inst::rv_inst(rvOPCODE op, rvFREG frd, rvFREG frs1, rvFREG frs2):op(op), frd(frd), frs1(frs1), frs2(frs2) {};
rv::rv_inst::rv_inst(rvOPCODE op, rvREG rd, rvFREG frs1, rvFREG frs2):op(op), rd(rd), frs1(frs1), frs2(frs2) {};
rv::rv_inst::rv_inst(rvOPCODE op, rvREG rd, rvREG rs1, uint32_t imm):op(op), rd(rd), rs1(rs1), imm(imm) {};
rv::rv_inst::rv_inst(rvOPCODE op, rvFREG frd, rvREG rs1, uint32_t imm):op(op), frd(frd), rs1(rs1), imm(imm) {};
rv::rv_inst::rv_inst(rvOPCODE op, rvREG rd, rvFREG frs1, uint32_t imm):op(op), rd(rd), frs1(frs1), imm(imm) {};
rv::rv_inst::rv_inst(rvOPCODE op, rvREG rs1, uint32_t imm, rvREG rs2):op(op), rs1(rs1), rs2(rs2), imm(imm) {};
rv::rv_inst::rv_inst(rvOPCODE op, rvREG rs1, rvREG rs2, std::string label):op(op), rs1(rs1), rs2(rs2), label(label) {};
rv::rv_inst::rv_inst(rvOPCODE op, rvREG rs1, uint32_t imm, rvFREG frs2):op(op), rs1(rs1), frs2(frs2), imm(imm) {};
rv::rv_inst::rv_inst(rvOPCODE op, rvREG rd, uint32_t imm):op(op), rd(rd), imm(imm){};
rv::rv_inst::rv_inst(rvOPCODE op, rvREG rd, std::string label):op(op), rd(rd), label(label) {};
rv::rv_inst::rv_inst(rvOPCODE op, rvREG rs1):op(op), rs1(rs1) {};
rv::rv_inst::rv_inst(rvOPCODE op, std::string label):op(op), label(label) {};

void backend::Generator::gen_instr(const ir::Instruction& instr, 
    stackVarMap& func_stack, std::vector<rv::rv_inst>& insts, int ir_pc, std::map<int,std::vector<int>>& goto_rcd){

    switch (instr.op)
    {
        case ir::Operator::_return:{
            if (instr.op1.type == ir::Type::Int){
                if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X10, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
                }
                else if(globalvs.find(instr.op1.name) != globalvs.end()){
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op1.name)));
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X10, rv::rvREG::X10, 0));
                }
                else assert(0);         
            }
            else if(instr.op1.type == ir::Type::Float){
                if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rv::rvFREG::F10, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
                }
                else if(globalvs.find(instr.op1.name) != globalvs.end()){
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, get_name(instr.op1.name)));
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rv::rvFREG::F10, rv::rvREG::X5, 0));
                }
                else assert(0);
            }
            else if(instr.op1.type == ir::Type::IntLiteral){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LI, rv::rvREG::X10, std::atoi(instr.op1.name.c_str())));
                
            }
            else if(instr.op1.type == ir::Type::FloatLiteral){
                float temp = std::atof(instr.op1.name.c_str());
                float_literal_list.push_back(*(uint32_t *)&temp);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, "FLOAT" + std::to_string(float_literal_list.size()-1)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rv::rvFREG::F10, rv::rvREG::X10, 0));
            }
            else if(instr.op1.type == ir::Type::null){}
            else assert(0);
            
            insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X1, rv::rvREG::X2, 
                func_stack.find_operand(ir::Operand("return_register_saved_address", ir::Type::Int))));
            insts.push_back(rv::rv_inst(rv::rvOPCODE::ADDI, rv::rvREG::X2, rv::rvREG::X2, 0));
            insts.push_back(rv::rv_inst(rv::rvOPCODE::JR, rv::rvREG::X1));

            break;
        }

        case ir::Operator::call:{
            int param_reg = 10;
            int param_freg = 10;
            for(auto param:((ir::CallInst&) instr).argumentList){
                if(param.type == ir::Type::Int ||  param.type == ir::Type::Float){
                    if(func_stack._table.find(param.name) != func_stack._table.end()){
                        insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG(param_reg), rv::rvREG::X2, func_stack.find_operand(param)));
                    }
                    else if(globalvs.find(param.name) != globalvs.end()){
                        insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG(param_reg), get_name(param.name)));
                        insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG(param_reg), rv::rvREG(param_reg), 0));
                    }
                    else assert(0);
                    param_reg = param_reg + 1;
                }
                else if(param.type == ir::Type::IntPtr ||param.type == ir::Type::FloatPtr){
                    if(func_stack._table.find(param.name) != func_stack._table.end()){
                        insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG(param_reg), rv::rvREG::X2, func_stack.find_operand(param)));
                    }
                    else if(globalvs.find(param.name) != globalvs.end()){
                        insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG(param_reg), get_name(param.name)));
                    }
                    else assert(0);
                    param_reg = param_reg + 1;
                }
                else if(param.type == ir::Type::Float){
                    if(func_stack._table.find(param.name) != func_stack._table.end()){
                        insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rv::rvFREG(param_freg), rv::rvREG::X2, func_stack.find_operand(param)));
                    }
                    else if(globalvs.find(param.name) != globalvs.end()){
                        insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, get_name(param.name)));
                        insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rv::rvFREG(param_freg), rv::rvREG::X5, 0));
                    }
                    else assert(0);
                    param_freg = param_freg + 1;
                }
                else assert(0);
            }

            insts.push_back(rv::rv_inst(rv::rvOPCODE::CALL, instr.op1.name));

            if(instr.des.type == ir::Type::Int){
                if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rv::rvREG::X10));
                }
                else if(globalvs.find(instr.des.name) != globalvs.end()){
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, get_name(instr.des.name)));
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X11, 0, rv::rvREG::X10));
                }
                else{
                    func_stack.add_operand(instr.des);
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rv::rvREG::X10));
                }
            }
            else if(instr.des.type == ir::Type::Float){
                if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X2, func_stack.find_operand(instr.des), rv::rvFREG::F10));
                }
                else if(globalvs.find(instr.des.name) != globalvs.end()){
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, get_name(instr.des.name)));
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X11, 0, rv::rvFREG::F10));
                }
                else{
                    func_stack.add_operand(instr.des);
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X2, func_stack.find_operand(instr.des), rv::rvFREG::F10));
                }  
            }
            else if(instr.des.type == ir::Type::null);
            else assert(0);

            break;
        }

        case ir::Operator::def:{
            insts.push_back(rv::rv_inst(rv::rvOPCODE::LI, rv::rvREG::X10, UINT32(instr.op1.name) ));
            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rv::rvREG::X10));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X11, 0, rv::rvREG::X10));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rv::rvREG::X10));
            }
            break;
        }

        case ir::Operator::fdef:{
            float temp = std::atof(instr.op1.name.c_str());
            float_literal_list.push_back(*(uint32_t *)&temp);
            insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, "FLOAT" + std::to_string(float_literal_list.size()-1)));
            insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rv::rvFREG::F10, rv::rvREG::X10, 0));

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X2, func_stack.find_operand(instr.des), rv::rvFREG::F10));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X11, 0, rv::rvFREG::F10));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X2, func_stack.find_operand(instr.des), rv::rvFREG::F10));
            }
            break;
        }

        case ir::Operator::add:{
            auto rs1 = getRs1(instr.op1);
            auto rs2 = getRs2(instr.op2);
            auto rd = getRd(instr.des);

            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
            }
            else assert(0);

            if(func_stack._table.find(instr.op2) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X2, func_stack.find_operand(instr.op2)));
            }
            else if(globalvs.find(instr.op2.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op2.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X10, 0));
            }
            else assert(0);
            
            insts.push_back(rv::rv_inst(rv::rvOPCODE::ADD, rd, rs1, rs2));

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X11, 0, rd));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }  
            break;
        }

        case ir::Operator::fadd:{
            auto rs1 = fgetRs1(instr.op1);
            auto rs2 = fgetRs2(instr.op2);
            auto rd = fgetRd(instr.des);

            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs1, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs1, rv::rvREG::X5, 0));
            }
            else assert(0);

            if(func_stack._table.find(instr.op2) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs2, rv::rvREG::X2, func_stack.find_operand(instr.op2)));
            }
            else if(globalvs.find(instr.op2.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, get_name(instr.op2.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs2, rv::rvREG::X5, 0));
            }
            else assert(0);
            
            insts.push_back(rv::rv_inst(rv::rvOPCODE::FADD, rd, rs1, rs2));

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X5, 0, rd));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }  
            break;
        }

        case ir::Operator::sub:{
            auto rs1 = getRs1(instr.op1);
            auto rs2 = getRs2(instr.op2);
            auto rd = getRd(instr.des);

            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
            }
            else assert(0);

            if(func_stack._table.find(instr.op2) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X2, func_stack.find_operand(instr.op2)));
            }
            else if(globalvs.find(instr.op2.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op2.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X10, 0));
            }
            else assert(0);
            
            insts.push_back(rv::rv_inst(rv::rvOPCODE::SUB, rd, rs1, rs2));

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X11, 0, rd));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }  
            break;
        }

        case ir::Operator::fsub:{
            auto rs1 = fgetRs1(instr.op1);
            auto rs2 = fgetRs2(instr.op2);
            auto rd = fgetRd(instr.des);

            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs1, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs1, rv::rvREG::X5, 0));
            }
            else assert(0);

            if(func_stack._table.find(instr.op2) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs2, rv::rvREG::X2, func_stack.find_operand(instr.op2)));
            }
            else if(globalvs.find(instr.op2.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, get_name(instr.op2.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs2, rv::rvREG::X5, 0));
            }
            else assert(0);
            
            insts.push_back(rv::rv_inst(rv::rvOPCODE::FSUB, rd, rs1, rs2));

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X5, 0, rd));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }  
            break;
        }

        case ir::Operator::mul:{
            auto rs1 = getRs1(instr.op1);
            auto rs2 = getRs2(instr.op2);
            auto rd = getRd(instr.des);

            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
            }
            else assert(0);

            if(func_stack._table.find(instr.op2) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X2, func_stack.find_operand(instr.op2)));
            }
            else if(globalvs.find(instr.op2.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op2.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X10, 0));
            }
            else assert(0);
            
            insts.push_back(rv::rv_inst(rv::rvOPCODE::MUL, rd, rs1, rs2));

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X11, 0, rd));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }  
            break;
        }

        case ir::Operator::fmul:{
            auto rs1 = fgetRs1(instr.op1);
            auto rs2 = fgetRs2(instr.op2);
            auto rd = fgetRd(instr.des);

            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs1, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs1, rv::rvREG::X5, 0));
            }
            else assert(0);

            if(func_stack._table.find(instr.op2) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs2, rv::rvREG::X2, func_stack.find_operand(instr.op2)));
            }
            else if(globalvs.find(instr.op2.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, get_name(instr.op2.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs2, rv::rvREG::X5, 0));
            }
            else assert(0);
            
            insts.push_back(rv::rv_inst(rv::rvOPCODE::FMUL, rd, rs1, rs2));

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X5, 0, rd));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }  
            break;
        }

        case ir::Operator::div:{
            auto rs1 = getRs1(instr.op1);
            auto rs2 = getRs2(instr.op2);
            auto rd = getRd(instr.des);

            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
            }
            else assert(0);

            if(func_stack._table.find(instr.op2) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X2, func_stack.find_operand(instr.op2)));
            }
            else if(globalvs.find(instr.op2.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op2.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X10, 0));
            }
            else assert(0);
            
            insts.push_back(rv::rv_inst(rv::rvOPCODE::DIV, rd, rs1, rs2));

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X11, 0, rd));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }  
            break;
        }

        case ir::Operator::fdiv:{
            auto rs1 = fgetRs1(instr.op1);
            auto rs2 = fgetRs2(instr.op2);
            auto rd = fgetRd(instr.des);

            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs1, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs1, rv::rvREG::X5, 0));
            }
            else assert(0);

            if(func_stack._table.find(instr.op2) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs2, rv::rvREG::X2, func_stack.find_operand(instr.op2)));
            }
            else if(globalvs.find(instr.op2.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, get_name(instr.op2.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs2, rv::rvREG::X5, 0));
            }
            else assert(0);
            
            insts.push_back(rv::rv_inst(rv::rvOPCODE::FDIV, rd, rs1, rs2));

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X5, 0, rd));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }  
            break;
        }

        case ir::Operator::mod:{
            auto rs1 = getRs1(instr.op1);
            auto rs2 = getRs2(instr.op2);
            auto rd = getRd(instr.des);

            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
            }
            else assert(0);

            if(func_stack._table.find(instr.op2) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X2, func_stack.find_operand(instr.op2)));
            }
            else if(globalvs.find(instr.op2.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op2.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X10, 0));
            }
            else assert(0);
            
            insts.push_back(rv::rv_inst(rv::rvOPCODE::REM, rd, rs1, rs2));

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X11, 0, rd));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }  
            break;
        }

        case ir::Operator::eq:{
            auto rs1 = getRs1(instr.op1);
            auto rs2 = getRs2(instr.op2);
            auto rd = getRd(instr.des);

            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
            }
            else assert(0);

            if(func_stack._table.find(instr.op2) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X2, func_stack.find_operand(instr.op2)));
            }
            else if(globalvs.find(instr.op2.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op2.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X10, 0));
            }
            else assert(0);
            
            insts.push_back(rv::rv_inst(rv::rvOPCODE::SUB, rd, rs1, rs2));
            insts.push_back(rv::rv_inst(rv::rvOPCODE::SEQZ, rd, rd, rv::rvREG::X0));

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X11, 0, rd));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }  
            break;
        }

        case ir::Operator::neq:{
            auto rs1 = getRs1(instr.op1);
            auto rs2 = getRs2(instr.op2);
            auto rd = getRd(instr.des);

            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
            }
            else assert(0);

            if(func_stack._table.find(instr.op2) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X2, func_stack.find_operand(instr.op2)));
            }
            else if(globalvs.find(instr.op2.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op2.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X10, 0));
            }
            else assert(0);
            
            insts.push_back(rv::rv_inst(rv::rvOPCODE::SUB, rd, rs1, rs2));
            insts.push_back(rv::rv_inst(rv::rvOPCODE::SNEZ, rd, rd, rv::rvREG::X0));

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X11, 0, rd));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }  

            break;
        }

        case ir::Operator::fneq:{
            auto rs1 = fgetRs1(instr.op1);
            auto rs2 = fgetRs2(instr.op2);
            auto rd = getRd(instr.des);

            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs1, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs1, rv::rvREG::X5, 0));
            }
            else assert(0);

            if(func_stack._table.find(instr.op2) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs2, rv::rvREG::X2, func_stack.find_operand(instr.op2)));
            }
            else if(globalvs.find(instr.op2.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, get_name(instr.op2.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs2, rv::rvREG::X5, 0));
            }
            else assert(0);
            
            insts.push_back(rv::rv_inst(rv::rvOPCODE::FLT, rd, rs1, rs2));
            insts.push_back(rv::rv_inst(rv::rvOPCODE::FLT, rd, rs2, rs1));

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X5, 0, rd));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }  

            break;
        }

        case ir::Operator::addi:{
            auto rs1 = getRs1(instr.op1);
            assert(instr.op2.type == ir::Type::IntLiteral);
            auto rd = getRd(instr.des);

            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
            }
            else assert(0);

            insts.push_back(rv::rv_inst(rv::rvOPCODE::ADDI, rd, rs1, UINT32(instr.op2.name)));

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X11, 0, rd));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }  

            break;
        }

        case ir::Operator::subi:{
            auto rs1 = getRs1(instr.op1);
            assert(instr.op2.type == ir::Type::IntLiteral);
            auto rd = getRd(instr.des);

            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
            }
            else assert(0);

            insts.push_back(rv::rv_inst(rv::rvOPCODE::ADDI, rd, rs1, - int(UINT32(instr.op2.name))));

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X11, 0, rd));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }  

            break;
        }

        case ir::Operator::mov:{
            auto rs1 = getRs1(instr.op1);

            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
            }
            else assert(0);

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rs1));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X11, 0, rs1));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rs1));
            }  
            break;
        }

        case ir::Operator::fmov:{
            auto rs1 = fgetRs1(instr.op1);

            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs1, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs1, rv::rvREG::X5, 0));
            }
            else assert(0);

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X2, func_stack.find_operand(instr.des), rs1));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X5, 0, rs1));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X2, func_stack.find_operand(instr.des), rs1));
            }  
            break;
        }

        case ir::Operator::lss:{
            auto rs1 = getRs1(instr.op1);
            auto rs2 = getRs2(instr.op2);
            auto rd = getRd(instr.des);

            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
            }
            else assert(0);

            if(func_stack._table.find(instr.op2) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X2, func_stack.find_operand(instr.op2)));
            }
            else if(globalvs.find(instr.op2.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op2.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X10, 0));
            }
            else assert(0);
            
            insts.push_back(rv::rv_inst(rv::rvOPCODE::SLT, rd, rs1, rs2));

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X11, 0, rd));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }     
            break;
        }

        case ir::Operator::flss:{
            auto rs1 = fgetRs1(instr.op1);
            auto rs2 = fgetRs2(instr.op2);
            auto rd = getRd(instr.des);

            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs1, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs1, rv::rvREG::X5, 0));
            }
            else assert(0);

            if(func_stack._table.find(instr.op2) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs2, rv::rvREG::X2, func_stack.find_operand(instr.op2)));
            }
            else if(globalvs.find(instr.op2.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, get_name(instr.op2.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs2, rv::rvREG::X5, 0));
            }
            else assert(0);
            
            insts.push_back(rv::rv_inst(rv::rvOPCODE::FLT, rd, rs1, rs2));

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X5, 0, rd));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }     
            break;
        }

        case ir::Operator::geq:{
            auto rs1 = getRs1(instr.op1);
            auto rs2 = getRs2(instr.op2);
            auto rd = getRd(instr.des);

            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
            }
            else assert(0);

            if(func_stack._table.find(instr.op2) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X2, func_stack.find_operand(instr.op2)));
            }
            else if(globalvs.find(instr.op2.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op2.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X10, 0));
            }
            else assert(0);
            
            insts.push_back(rv::rv_inst(rv::rvOPCODE::SLT, rd, rs1, rs2));
            insts.push_back(rv::rv_inst(rv::rvOPCODE::XORI, rd, rd, 1));

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X11, 0, rd));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }     
            break;
        }

        case ir::Operator::leq:{
            auto rs1 = getRs1(instr.op1);
            auto rs2 = getRs2(instr.op2);
            auto rd = getRd(instr.des);

            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
            }
            else assert(0);

            if(func_stack._table.find(instr.op2) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X2, func_stack.find_operand(instr.op2)));
            }
            else if(globalvs.find(instr.op2.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op2.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X10, 0));
            }
            else assert(0);
            
            insts.push_back(rv::rv_inst(rv::rvOPCODE::SLT, rv::rvREG::X5, rs1, rs2));
            insts.push_back(rv::rv_inst(rv::rvOPCODE::SUB, rv::rvREG::X6, rs1, rs2));
            insts.push_back(rv::rv_inst(rv::rvOPCODE::SEQZ, rv::rvREG::X6, rv::rvREG::X6, rv::rvREG::X0));
            insts.push_back(rv::rv_inst(rv::rvOPCODE::OR, rd, rv::rvREG::X5, rv::rvREG::X6));

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X11, 0, rd));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }     
            break;
        }

        case ir::Operator::gtr:{
            auto rs1 = getRs1(instr.op1);
            auto rs2 = getRs2(instr.op2);
            auto rd = getRd(instr.des);

            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
            }
            else assert(0);

            if(func_stack._table.find(instr.op2) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X2, func_stack.find_operand(instr.op2)));
            }
            else if(globalvs.find(instr.op2.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op2.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X10, 0));
            }
            else assert(0);

            insts.push_back(rv::rv_inst(rv::rvOPCODE::SLT, rd, rs2, rs1));

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X11, 0, rd));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }     
            break;
        }

        case ir::Operator::cvt_i2f:{
            auto rs1 = getRs1(instr.op1);

            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
            }
            else assert(0);

            insts.push_back(rv::rv_inst(rv::rvOPCODE::CVT_I2F, rv::rvFREG::F10, rs1, 0));

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X2, func_stack.find_operand(instr.des), rv::rvFREG::F10));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X5, 0, rv::rvFREG::F10));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X2, func_stack.find_operand(instr.des), rv::rvFREG::F10));
            }  
            break;
        }

        case ir::Operator::cvt_f2i:{
            auto rs1 = fgetRs1(instr.op1);

            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs1, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rs1, rv::rvREG::X5, 0));
            }
            else assert(0);

            insts.push_back(rv::rv_inst(rv::rvOPCODE::CVT_F2I, rv::rvREG::X10, rs1, 0));

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rv::rvREG::X10));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X5, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X5, 0, rv::rvREG::X10));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rv::rvREG::X10));
            }  
            break;
        }

        case ir::Operator::_not:{
            auto rs1 = getRs1(instr.op1);

            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
            }
            else assert(0);

            insts.push_back(rv::rv_inst(rv::rvOPCODE::SEQZ, rs1, rs1, rv::rvREG::X0));

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rs1));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X11, 0, rs1));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rs1));
            }  
            break;
        }

        case ir::Operator::_or:{
            auto rs1 = getRs1(instr.op1);
            auto rs2 = getRs2(instr.op2);
            auto rd = getRd(instr.des);

            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
            }
            else assert(0);
            insts.push_back(rv::rv_inst(rv::rvOPCODE::SNEZ, rs1, rs1, rv::rvREG::X0));

            if(func_stack._table.find(instr.op2) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X2, func_stack.find_operand(instr.op2)));
            }
            else if(globalvs.find(instr.op2.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op2.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X10, 0));
            }
            else assert(0);
            insts.push_back(rv::rv_inst(rv::rvOPCODE::SNEZ, rs2, rs2, rv::rvREG::X0));
            
            insts.push_back(rv::rv_inst(rv::rvOPCODE::OR, rd, rs1, rs2));

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X11, 0, rd));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }  
            break;
        }

        case ir::Operator::_and:{
            auto rs1 = getRs1(instr.op1);
            auto rs2 = getRs2(instr.op2);
            auto rd = getRd(instr.des);

            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs1, rv::rvREG::X10, 0));
            }
            else assert(0);
            insts.push_back(rv::rv_inst(rv::rvOPCODE::SNEZ, rs1, rs1, rv::rvREG::X0));

            if(func_stack._table.find(instr.op2) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X2, func_stack.find_operand(instr.op2)));
            }
            else if(globalvs.find(instr.op2.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op2.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rs2, rv::rvREG::X10, 0));
            }
            else assert(0);
            insts.push_back(rv::rv_inst(rv::rvOPCODE::SNEZ, rs2, rs2, rv::rvREG::X0));
            
            insts.push_back(rv::rv_inst(rv::rvOPCODE::AND, rd, rs1, rs2));

            if(func_stack._table.find(instr.des) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }
            else if(globalvs.find(instr.des.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, get_name(instr.des.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X11, 0, rd));
            }
            else{
                func_stack.add_operand(instr.des);
                insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rd));
            }  
            break;
        }

        case ir::Operator::alloc:{
            assert(instr.op1.type == ir::Type::IntLiteral);
            func_stack.add_operand(instr.des, UINT32(instr.op1.name) * 4 + 4);
            insts.push_back(rv::rv_inst(rv::rvOPCODE::ADDI, rv::rvREG::X10, rv::rvREG::X2, func_stack.find_operand(instr.des) + 4));
            insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rv::rvREG::X10));
            break;
        }

        case ir::Operator::_goto:{
            if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X10, rv::rvREG::X2, func_stack.find_operand(instr.op1)));
            }
            else if(globalvs.find(instr.op1.name) != globalvs.end()){
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op1.name)));
                insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X10, rv::rvREG::X10, 0));
            }
            
            insts.push_back(rv::rv_inst(rv::rvOPCODE::BNE, rv::rvREG::X10,rv::rvREG::X0, ""));
            assert(instr.des.type == ir::Type::IntLiteral);
            goto_rcd[ir_pc + std::stoi(instr.des.name)].push_back(insts.size() - 1);
            break;
        }

        case ir::Operator::store:{
            if(instr.des.type == ir::Type::Int){
                if(instr.op2.type == ir::Type::IntLiteral){
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::LI, rv::rvREG::X10, UINT32(instr.op2.name) * 4 ));
                }
                else if(instr.op2.type == ir::Type::Int){
                    if(func_stack._table.find(instr.op2) != func_stack._table.end()){
                        insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X10, rv::rvREG::X2, func_stack.find_operand(instr.op2)));
                    }
                    else if(globalvs.find(instr.op2.name) != globalvs.end()){
                        insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op2.name)));
                        insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X10, rv::rvREG::X10, 0));
                    }
                    else assert(0);
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::SLLI, rv::rvREG::X10, rv::rvREG::X10, 2));
                }
                else assert(0);


                if(func_stack._table.find(instr.des) != func_stack._table.end()){
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X11, rv::rvREG::X2, func_stack.find_operand(instr.des)));
                }
                else if(globalvs.find(instr.des.name) != globalvs.end()){
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, get_name(instr.des.name)));
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X11, rv::rvREG::X11, 0));
                }
                else assert(0);

                if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X12, rv::rvREG::X2 ,func_stack.find_operand(instr.op1)));
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::ADD, rv::rvREG::X12, rv::rvREG::X12, rv::rvREG::X10));
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X12, 0, rv::rvREG::X11));  
                }
                else if(globalvs.find(instr.op1.name) != globalvs.end()){
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X12, get_name(instr.op1.name)));
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::ADD, rv::rvREG::X12, rv::rvREG::X12, rv::rvREG::X10));
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X12, 0, rv::rvREG::X11));  
                }
                else assert(0);
            }
            else if(instr.des.type == ir::Type::Float){
                if(instr.op2.type == ir::Type::IntLiteral){
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::LI, rv::rvREG::X10, UINT32(instr.op2.name) * 4 ));
                }
                else if(instr.op2.type == ir::Type::Int){
                    if(func_stack._table.find(instr.op2) != func_stack._table.end()){
                        insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X10, rv::rvREG::X2, func_stack.find_operand(instr.op2)));
                    }
                    else if(globalvs.find(instr.op2.name) != globalvs.end()){
                        insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op2.name)));
                        insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X10, rv::rvREG::X10, 0));
                    }
                    else assert(0);
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::SLLI, rv::rvREG::X10, rv::rvREG::X10, 2));
                }
                else assert(0);

                if(func_stack._table.find(instr.des) != func_stack._table.end()){
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rv::rvFREG::F10, rv::rvREG::X2, func_stack.find_operand(instr.des)));
                }
                else if(globalvs.find(instr.des.name) != globalvs.end()){
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, get_name(instr.des.name)));
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rv::rvFREG::F10, rv::rvREG::X11, 0));
                }
                else assert(0);

                if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X12, rv::rvREG::X2 ,func_stack.find_operand(instr.op1)));
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::ADD, rv::rvREG::X12, rv::rvREG::X12, rv::rvREG::X10));
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X12, 0, rv::rvFREG::F10));  
                }
                else if(globalvs.find(instr.op1.name) != globalvs.end()){
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X12, get_name(instr.op1.name)));
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::ADD, rv::rvREG::X12, rv::rvREG::X12, rv::rvREG::X10));
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X12, 0, rv::rvFREG::F10));  
                }
                else assert(0);
            }
            else assert(0);
            break;
        }

        case ir::Operator::load:{
            if(instr.des.type == ir::Type::Int){
                if(instr.op2.type == ir::Type::IntLiteral){
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::LI, rv::rvREG::X10, UINT32(instr.op2.name) * 4 ));
                }
                else if(instr.op2.type == ir::Type::Int){
                    if(func_stack._table.find(instr.op2) != func_stack._table.end()){
                        insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X10, rv::rvREG::X2, func_stack.find_operand(instr.op2)));
                    }
                    else if(globalvs.find(instr.op2.name) != globalvs.end()){
                        insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op2.name)));
                        insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X10, rv::rvREG::X10, 0));
                    }
                    else assert(0);
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::SLLI, rv::rvREG::X10, rv::rvREG::X10, 2));
                }
                else assert(0);

                if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X11, rv::rvREG::X2 ,func_stack.find_operand(instr.op1)));
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::ADD, rv::rvREG::X11, rv::rvREG::X11, rv::rvREG::X10));
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X11, rv::rvREG::X11 ,0));  
                }
                else if(globalvs.find(instr.op1.name) != globalvs.end()){
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, get_name(instr.op1.name)));
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::ADD, rv::rvREG::X11, rv::rvREG::X11, rv::rvREG::X10));
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X11, rv::rvREG::X11 ,0));             
                }
                else assert(0);

                if(func_stack._table.find(instr.des) != func_stack._table.end()){
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rv::rvREG::X11)); 
                }
                else if((globalvs.find(instr.des.name) != globalvs.end())){
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X12, get_name(instr.des.name)));
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X12, 0, rv::rvREG::X11)); 
                }
                else{
                    func_stack.add_operand(instr.des);
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(instr.des), rv::rvREG::X11)); 
                }
            }
            else if(instr.des.type == ir::Type::Float){
                if(instr.op2.type == ir::Type::IntLiteral){
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::LI, rv::rvREG::X10, UINT32(instr.op2.name) * 4 ));
                }
                else if(instr.op2.type == ir::Type::Int){
                    if(func_stack._table.find(instr.op2) != func_stack._table.end()){
                        insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X10, rv::rvREG::X2, func_stack.find_operand(instr.op2)));
                    }
                    else if(globalvs.find(instr.op2.name) != globalvs.end()){
                        insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X10, get_name(instr.op2.name)));
                        insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X10, rv::rvREG::X10, 0));
                    }
                    else assert(0);
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::SLLI, rv::rvREG::X10, rv::rvREG::X10, 2));
                }
                else assert(0);

                if(func_stack._table.find(instr.op1) != func_stack._table.end()){
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::LW, rv::rvREG::X11, rv::rvREG::X2 ,func_stack.find_operand(instr.op1)));
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::ADD, rv::rvREG::X11, rv::rvREG::X11, rv::rvREG::X10));
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rv::rvFREG::F10, rv::rvREG::X11 ,0));  
                }
                else if(globalvs.find(instr.op1.name) != globalvs.end()){
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X11, get_name(instr.op1.name)));
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::ADD, rv::rvREG::X11, rv::rvREG::X11, rv::rvREG::X10));
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::FLW, rv::rvFREG::F10, rv::rvREG::X11 ,0));             
                }
                else assert(0);

                if(func_stack._table.find(instr.des) != func_stack._table.end()){
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X2, func_stack.find_operand(instr.des), rv::rvFREG::F10)); 
                }
                else if((globalvs.find(instr.des.name) != globalvs.end())){
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::LA, rv::rvREG::X12, get_name(instr.des.name)));
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X12, 0, rv::rvFREG::F10)); 
                }
                else{
                    func_stack.add_operand(instr.des);
                    insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X2, func_stack.find_operand(instr.des), rv::rvFREG::F10)); 
                }
            }
            break;
        }
        
        case ir::Operator::__unuse__:{
            insts.push_back(rv::rv_inst(rv::rvOPCODE::NOP, rv::rvREG::X2, "")); 
            break;
        }

        default:{
            // DPRINT(ir::toString(instr.op));
            assert(0);
        } 
    }
    
}

void backend::Generator::gen_func(const ir::Function& function){
    stackVarMap func_stack;
    std::vector< rv::rv_inst> insts;
    std::vector< rv::rv_inst> rinsts;
    std::map<int, std::vector<int>> goto_rcd;
    std::map<int, std::string> label_rcd;
    std::vector<int> first_instr_id;

    insts.push_back(rv::rv_inst(rv::rvOPCODE::ADDI, rv::rvREG::X2, rv::rvREG::X2, 0));

    auto ra = ir::Operand("return_register_saved_address", ir::Type::Int);
    func_stack.add_operand(ra);
    insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, func_stack.find_operand(ra), rv::rvREG::X1));

    int param_reg = 10;
    int param_freg = 10;

    for(int i=0; i < function.ParameterList.size(); i++){
        auto param = function.ParameterList[i];
        if(param.type == ir::Type::Int || param.type == ir::Type::IntPtr || param.type == ir::Type::Int || param.type == ir::Type::FloatPtr){
            assert(func_stack._table.find(param.name) == func_stack._table.end());
            int delt = func_stack.add_operand(param);
            insts.push_back(rv::rv_inst(rv::rvOPCODE::SW, rv::rvREG::X2, delt, rv::rvREG(param_reg))); 
            param_reg = param_reg + 1;
        }
        else if(param.type == ir::Type::Float){
            assert(func_stack._table.find(param.name) == func_stack._table.end());
            int delt = func_stack.add_operand(param);
            insts.push_back(rv::rv_inst(rv::rvOPCODE::FSW, rv::rvREG::X2, delt, rv::rvFREG(param_freg))); 
            param_freg = param_freg + 1;
        }
        else assert(0);
    }

    for(int i=0; i<function.InstVec.size(); i++){
        first_instr_id.push_back(insts.size());
        gen_instr(*function.InstVec[i], func_stack, insts, i, goto_rcd);
    }

    insts[0].imm = (- func_stack.delt);
    // insts[insts.size()-2].imm =  func_stack.delt;

    for(int i = 0; i < function.InstVec.size(); i++){
        if(goto_rcd.find(i) != goto_rcd.end()) {
            std::string tag = ".L" + std::to_string(local_tag++);  
            label_rcd[i] = tag;
            for(auto idx:goto_rcd[i]){
                insts[idx].label = tag;
            }   
        }
        if(function.InstVec[i]->op == ir::Operator::_return){
            int rb;
            if(i == function.InstVec.size()-1)rb = insts.size() - 1;
            else rb = first_instr_id[i+1] - 1;
            insts[rb - 1].imm = func_stack.delt;
        }
    }
    
    for(int i = 0; i < first_instr_id[0]; i++) rinsts.push_back(insts[i]);

    for(int i = 0; i < function.InstVec.size(); i++){
        int rb;
        if(i == function.InstVec.size()-1)rb = insts.size() - 1;
        else rb = first_instr_id[i+1] - 1;
        if(label_rcd.find(i) != label_rcd.end()) {
            rinsts.push_back(rv::rv_inst(rv::rvOPCODE::LABEL, label_rcd[i]));
        }
        for(int s = first_instr_id[i]; s <= rb; s++) rinsts.push_back(insts[s]);
    }



    for (auto inst:rinsts){ fout << inst.draw();}
}

void backend::Generator::gen() {
    fout << "\t.text\n";
    for(auto gv: program.globalVal){
        if(gv.maxlen > 0) fout << "\t.comm\t" + get_name(gv.val.name) + "," + std::to_string(gv.maxlen * 4) + ",4\n";
        else fout << "\t.comm\t" + get_name(gv.val.name) + ",4,4\n";
        globalvs.insert(gv.val.name);
    }
    
    for(auto f:program.functions){
        fout << "\t.global\t" + f.name +"\n";
        fout << "\t.type\t" + f.name +", @function\n";
        fout << f.name <<":\n";
        gen_func(f);
    }

    for(int i = 0; i < float_literal_list.size(); i++){
        fout << "FLOAT" + std::to_string(i) + ":\n\t.word\t" + std::to_string(float_literal_list[i]) + "\n";
    }
}