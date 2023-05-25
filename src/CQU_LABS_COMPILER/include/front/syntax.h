/**
 * @file syntax.h
 * @author Yuntao Dai (d1581209858@live.com)
 * @brief 
 * in the second part, we already has a token stream, now we should analysis it and result in a syntax tree, 
 * which we also called it AST(abstract syntax tree)
 * @version 0.1
 * @date 2022-12-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SYNTAX_H
#define SYNTAX_H

#include"front/abstract_syntax_tree.h"
#include"front/token.h"

#include<vector>

namespace frontend {

// definition of Parser
// a parser should take a token stream as input, then parsing it, output a AST
struct Parser {
    uint32_t index; // current token index
    const std::vector<Token>& token_stream;

    /**
     * @brief constructor
     * @param tokens: the input token_stream
     */
    Parser(const std::vector<Token>& tokens);

    /**
     * @brief destructor
     */
    ~Parser();
    
    /**
     * @brief creat the abstract syntax tree
     * @return the root of abstract syntax tree
     */
    CompUnit* get_abstract_syntax_tree();
    
    /**
     * @brief for debug, should be called in the beginning of recursive descent functions 
     * @param node: current parsing node 
     */
    void log(AstNode* node);

    CompUnit* procCompUnit(AstNode* p);
    Decl* procDecl(AstNode* p);
    ConstDecl* procConstDecl(AstNode* p);
    BType* procBType(AstNode* p);
    ConstDef* procConstDef(AstNode* p);
    ConstInitVal* procConstInitVal(AstNode* p);
    VarDecl* procVarDecl(AstNode* p);
    VarDef* procVarDef(AstNode* p);
    InitVal* procInitVal(AstNode* p);
    FuncDef* procFuncDef(AstNode* p);
    FuncType* procFuncType(AstNode* p);
    FuncFParam* procFuncFParam(AstNode* p);
    FuncFParams* procFuncFParams(AstNode* p);
    Block* procBlock(AstNode* p);
    BlockItem* procBlockItem(AstNode* p);
    Stmt* procStmt(AstNode* p);
    Exp* procExp(AstNode* p);
    Cond* procCond(AstNode* p);
    LVal* procLVal(AstNode* p);
    Number* procNumber(AstNode* p);
    PrimaryExp* procPrimaryExp(AstNode* p);
    UnaryExp* procUnaryExp(AstNode* p);
    UnaryOp* procUnaryOp(AstNode* p);
    FuncRParams* procFuncRParams(AstNode* p);
    MulExp* procMulExp(AstNode* p);
    AddExp* procAddExp(AstNode* p);
    RelExp* procRelExp(AstNode* p);
    EqExp* procEqExp(AstNode* p);
    LAndExp* procLAndExp(AstNode* p);
    LOrExp* procLOrExp(AstNode* p);
    ConstExp* procConstExp(AstNode* p);
};

} // namespace frontend

#endif