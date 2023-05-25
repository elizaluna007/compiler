/**
 * @file semantic.h
 * @author Yuntao Dai (d1581209858@live.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-06
 * 
 * a Analyzer should 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SEMANTIC_H
#define SEMANTIC_H

#define SEMANTIC_DEBUG
#define DPRINT(value) std::cout<<value<<std::endl;

#define CVT_POINT(root,type) ((type*)root)
#define COMMIT_INSTR(instr) (curr_function->addInst(instr))
#define TO_PTR_TYPE(type) (type == Type::Int ? Type::IntPtr : (type == Type::Int ? Type::FloatPtr : Type::null) )

#include"ir/ir.h"
#include"front/abstract_syntax_tree.h"

#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<stack>
using std::map;
using std::string;
using std::vector;
using std::stack;

namespace frontend
{

// definition of symbol table entry
struct STE {
    ir::Operand operand;
    vector<int> dimension;
};

struct ConstOperand
{
    void* v;
    Type t;
    std::vector<int> dimension;

    ConstOperand(void* v = NULL, Type t = Type::null, std::vector<int> dimension = std::vector<int>());
    bool isNull();
};


using map_str_ste = map<string, STE>;
// definition of scope infomation
struct ScopeInfo {
    int cnt;
    string name;
    map_str_ste table;
    map <string, ConstOperand> const_table;
};

// surpport lib functions
map<std::string,ir::Function*>* get_lib_funcs();

// definition of symbol table
struct SymbolTable{
    vector<ScopeInfo> scope_stack;
    map<std::string,ir::Function*> functions;
    
    ir::Operand zero;
    ir::Operand fzero;
    ir::Operand one;
    
    /**
     * @brief enter a new scope, record the infomation in scope stacks
     * @param node: a Block node, entering a new Block means a new name scope
     */
    // void add_scope(Block* block);
    void add_scope(std::string name);

    /**
     * @brief exit a scope, pop out infomations
     */
    void exit_scope();

    /**
     * @brief Get the scoped name, to deal the same name in different scopes, we change origin id to a new one with scope infomation,
     * for example, we have these code:
     * "     
     * int a;
     * {
     *      int a; ....
     * }
     * "
     * in this case, we have two variable both name 'a', after change they will be 'a' and 'a_block'
     * @param id: origin id 
     * @return string: new name with scope infomations
     */
    string get_scoped_name(string id) const;

    string get_var_name(string id) const;

    /**
     * @brief get the right operand with the input name
     * @param id identifier name
     * @return Operand 
     */
    ir::Operand get_operand(string id) const;

    ir::Operand get_operand_inscope(string id) const;

    /**
     * @brief get the right ste with the input name
     * @param id identifier name
     * @return STE 
     */
    STE get_ste(string id) const;

    

    ir::Operand add_ste(std::string name, vector<int> dimension, ir::Type t);
    ir::Operand add_temp(ir::Type t);
    void add_const(std::string name, vector<int> dimension, void* v, ir::Type t);
    ConstOperand get_const(std::string name);
    ConstOperand get_const_inscope(string name);
};


// singleton class
struct Analyzer {
    int tmp_cnt;
    vector<ir::Instruction*> g_init_inst;
    SymbolTable symbol_table;

    ir::Program* prog;
    ir::Function* curr_function;

    /**
     * @brief constructor
     */
    Analyzer();

    // analysis functions
    ir::Program get_ir_program(CompUnit*);

    // reject copy & assignment
    Analyzer(const Analyzer&) = delete;
    Analyzer& operator=(const Analyzer&) = delete;

    void transCompUnit(CompUnit* root, AstNode * p);
    void transDecl(Decl * root, AstNode * p);
    void transConstDecl(ConstDecl * root, AstNode * p);
    void transBType(BType * root, AstNode * p);
    void transConstDef(ConstDef * root, AstNode * p);
    void transConstInitVal(ConstInitVal * root, AstNode * p);
    void transVarDecl(VarDecl * root, AstNode * p);
    void transVarDef(VarDef * root, AstNode * p);
    void transInitVal(InitVal * root, AstNode * p);
    void transFuncDef(FuncDef * root, AstNode * p);
    void transFuncType(FuncType * root, AstNode * p);
    void transFuncFParam(FuncFParam * root, AstNode * p);
    void transFuncFParams(FuncFParams * root, AstNode * p);
    void transBlock(Block * root, AstNode * p);
    void transBlockItem(BlockItem * root, AstNode * p);
    void transStmt(Stmt * root, AstNode * p);
    void transExp(Exp * root, AstNode * p);
    void transCond(Cond * root, AstNode * p);
    void transLVal(LVal * root, AstNode* p);
    void transNumber(Number * root, AstNode* p);
    void transPrimaryExp(PrimaryExp * root, AstNode* p);
    void transUnaryExp(UnaryExp * root, AstNode * p);
    void transUnaryOp(UnaryOp * root, AstNode * p);
    void transFuncRParams(FuncRParams * root, AstNode * p);
    void transMulExp(MulExp * root, AstNode * p);
    void transAddExp(AddExp * root, AstNode * p);
    void transRelExp(RelExp * root, AstNode * p);
    void transEqExp(EqExp * root, AstNode * p);
    void transLAndExp(LAndExp * root, AstNode * p);
    void transLOrExp(LOrExp * root, AstNode * p);
    void transConstExp(ConstExp * root, AstNode * p);
    
    
    
    
    
    
    
    
    
    
};

int value2int(std::string value);
double value2float(std::string value);

} // namespace frontend

#endif