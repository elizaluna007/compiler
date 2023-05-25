#ifndef GENERARATOR_H
#define GENERARATOR_H

#include "ir/ir.h"
#include "backend/rv_def.h"
#include "backend/rv_inst_impl.h"

#include<map>
#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include<set>

#define DPRINT(content) std::cout<<content<<std::endl;
#define UINT32(content) uint32_t(std::stoi(content))

namespace backend {


struct operand_less
{
    bool operator()(ir::Operand a, ir::Operand b){
        return a.name < b.name;
    }
};

// it is a map bewteen variable and its mem addr, the mem addr of a local variable can be identified by ($sp + off)
struct stackVarMap {
    std::map<ir::Operand, int, operand_less> _table;
    uint32_t delt = 0;

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


struct Generator {
    const ir::Program& program;         // the program to gen
    std::ofstream& fout;                 // output file
    std::vector<uint32_t> float_literal_list;
    std::set<std::string> globalvs;
    int local_tag = 0;
    
    Generator(ir::Program&, std::ofstream&);

    // reg allocate api
    rv::rvREG getRd(ir::Operand);
    rv::rvFREG fgetRd(ir::Operand);
    rv::rvREG getRs1(ir::Operand);
    rv::rvREG getRs2(ir::Operand);
    rv::rvFREG fgetRs1(ir::Operand);
    rv::rvFREG fgetRs2(ir::Operand);

    // generate wrapper function
    void gen();
    void gen_func(const ir::Function&);
    void gen_instr(const ir::Instruction&, stackVarMap&, std::vector<rv::rv_inst>&, int ir_pc, std::map<int,std::vector<int>>&);
};



} // namespace backend


#endif