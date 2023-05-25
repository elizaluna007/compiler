#include"front/syntax.h"

#include<iostream>
#include<cassert>

using frontend::Parser;

// #define DEBUG_PARSER
#define TODO assert(0 && "todo")
#define CUR_TOKEN_IS(tk_type) (token_stream[index].type == TokenType::tk_type)
#define PARSE_TOKEN(tk_type) root->children.push_back(parseTerm(root, TokenType::tk_type))
#define PARSE(name, type) auto name = new type(root); assert(parse##type(name)); root->children.push_back(name); 


Parser::Parser(const std::vector<frontend::Token>& tokens): index(0), token_stream(tokens) {}

Parser::~Parser() {}

frontend::CompUnit* Parser::get_abstract_syntax_tree(){
    return procCompUnit(nullptr);
}

frontend::CompUnit* frontend::Parser::procCompUnit(frontend::AstNode* p){
    auto node = new CompUnit(p);
    if (token_stream[index].type == TokenType::CONSTTK){
        auto child = procDecl(node);
        node->children.push_back(child);
    }
    else if(token_stream[index].type == TokenType::VOIDTK){
        auto child = procFuncDef(node);
        node->children.push_back(child);
    }
    else if(index + 2 < token_stream.size() && token_stream[index+1].type == TokenType::IDENFR && 
        token_stream[index+2].type == TokenType::LPARENT){
        auto child = procFuncDef(node);
        node->children.push_back(child);
    }
    else if(index + 2 < token_stream.size() && token_stream[index+1].type == TokenType::IDENFR && 
        (token_stream[index+2].type == TokenType::LBRACK || token_stream[index+2].type == TokenType::ASSIGN ||
        token_stream[index+2].type == TokenType::COMMA || token_stream[index+2].type == TokenType::SEMICN)){
        auto child = procDecl(node);
        node->children.push_back(child);
    }
    else assert(0);

    if (index < token_stream.size()) {
        // auto child = procCompUnit(node);
        node->children.push_back(procCompUnit(node));
    }

    return node;
}

frontend::Decl* frontend::Parser::procDecl(frontend::AstNode* p){

    auto node = new Decl(p);
    if(token_stream[index].type == TokenType::CONSTTK){
        auto child = procConstDecl(node);
        node->children.push_back(child);
    }
    else if(token_stream[index].type == TokenType::INTTK || token_stream[index].type == TokenType::FLOATTK){
        auto child = procVarDecl(node);
        node->children.push_back(child);
    }
    else assert(0);

    return node;
}

frontend::ConstDecl* frontend::Parser::procConstDecl(frontend::AstNode* p){

    auto node = new ConstDecl(p);

    if(token_stream[index].type != TokenType::CONSTTK)assert(0);
    else {
        node->children.push_back(new Term(token_stream[index],node));
        index++;
    }

    // auto child = procBType(node);
    node->children.push_back(procBType(node));

    // auto child = procConstDef(node);
    node->children.push_back(procConstDef(node));

    while (token_stream[index].type == TokenType::COMMA)
    {
        node->children.push_back(new Term(token_stream[index],node));
        index++;
        // auto child = procConstDef(node);
        node->children.push_back(procConstDef(node));
    }

    if(token_stream[index].type != TokenType::SEMICN) assert(0);
    else {
        node->children.push_back(new Term(token_stream[index],node));
        index++;
        return node;
    } 
    
}

frontend::BType* frontend::Parser::procBType(frontend::AstNode* p){

    auto node = new BType(p);

    if(token_stream[index].type == TokenType::INTTK || token_stream[index].type == TokenType::FLOATTK){
        node->children.push_back(new Term(token_stream[index],node));
        index++;
    }
    else assert(0);

    return node;
}

frontend::ConstDef* frontend::Parser::procConstDef(frontend::AstNode* p){

    auto node = new ConstDef(p);

    if(token_stream[index].type == TokenType::IDENFR){
        node->children.push_back(new Term(token_stream[index],node));
        index++;
    }
    else assert(0);

    while (token_stream[index].type == TokenType::LBRACK)
    {
        node->children.push_back(new Term(token_stream[index],node));
        index++;

        // auto child = procConstExp(node);
        node->children.push_back(procConstExp(node));

        if(token_stream[index].type == TokenType::RBRACK){
            node->children.push_back(new Term(token_stream[index],node));
            index++;
        }
        else assert(0);
    }

    if(token_stream[index].type == TokenType::ASSIGN){
        node->children.push_back(new Term(token_stream[index],node));
        index++;
    }
    else assert(0);

    // auto child = procConstInitVal(node);
    node->children.push_back(procConstInitVal(node));

    return node;   
}



frontend::ConstInitVal* frontend::Parser::procConstInitVal(frontend::AstNode* p){

    auto node = new ConstInitVal(p);

    if(token_stream[index].type == TokenType::LPARENT || token_stream[index].type == TokenType::IDENFR ||
    token_stream[index].type == TokenType::INTLTR || token_stream[index].type == TokenType::FLOATLTR ||
    token_stream[index].type == TokenType::PLUS || token_stream[index].type == TokenType::MINU ||
    token_stream[index].type == TokenType::NOT){
        // auto child = procConstExp(node);
        node->children.push_back(procConstExp(node));
    }
    else if(token_stream[index].type == TokenType::LBRACE){
        node->children.push_back(new Term(token_stream[index],node));
        index++;

        if(token_stream[index].type == TokenType::LPARENT || token_stream[index].type == TokenType::IDENFR ||
        token_stream[index].type == TokenType::INTLTR || token_stream[index].type == TokenType::FLOATLTR ||
        token_stream[index].type == TokenType::PLUS || token_stream[index].type == TokenType::MINU ||
        token_stream[index].type == TokenType::NOT || token_stream[index].type == TokenType::LBRACE){
            // auto child = procConstInitVal(node);
            node->children.push_back(procConstInitVal(node));

            while(token_stream[index].type == TokenType::COMMA){
                node->children.push_back(new Term(token_stream[index],node));
                index++;

                // auto child = procConstInitVal(node);
                node->children.push_back(procConstInitVal(node));
            }
        }

        if(token_stream[index].type == TokenType::RBRACE){
            node->children.push_back(new Term(token_stream[index],node));
            index++;
        }
        else assert(0);
    }

    return node;  
}


frontend::VarDecl* frontend::Parser::procVarDecl(frontend::AstNode* p){

    auto node = new VarDecl(p);

    // auto child = procBType(node);
    node->children.push_back(procBType(node));

    // auto child = procVarDef(node);
    node->children.push_back(procVarDef(node));

    while (token_stream[index].type == TokenType::COMMA)
    {
        node->children.push_back(new Term(token_stream[index],node));
        index++;

        // auto child = procVarDef(node);
        node->children.push_back(procVarDef(node));
    }

    if(token_stream[index].type == TokenType::SEMICN){
        node->children.push_back(new Term(token_stream[index],node));
        index++;
    }
    else assert(0);
    
    return node;  
}


frontend::VarDef* frontend::Parser::procVarDef(frontend::AstNode* p){

    auto node = new VarDef(p);

    if(token_stream[index].type == TokenType::IDENFR){
        node->children.push_back(new Term(token_stream[index],node));
        index++;
    }
    else assert(0);

    while (token_stream[index].type == TokenType::LBRACK)
    {
        node->children.push_back(new Term(token_stream[index],node));
        index++;

        // auto child = procConstExp(node);
        node->children.push_back(procConstExp(node));

        if(token_stream[index].type == TokenType::RBRACK){
            node->children.push_back(new Term(token_stream[index],node));
            index++;
        }
        else assert(0);
    }
    
    if(token_stream[index].type == TokenType::ASSIGN){
        node->children.push_back(new Term(token_stream[index],node));
        index++;

        // auto child = procInitVal(node);
        node->children.push_back(procInitVal(node));
    }
  
    return node;  
}


frontend::InitVal* frontend::Parser::procInitVal(frontend::AstNode* p){

    auto node = new InitVal(p);

    if(token_stream[index].type == TokenType::LBRACE){
        node->children.push_back(new Term(token_stream[index],node));
        index++;
        
        if(token_stream[index].type == TokenType::LPARENT || token_stream[index].type == TokenType::IDENFR ||
        token_stream[index].type == TokenType::INTLTR || token_stream[index].type == TokenType::FLOATLTR ||
        token_stream[index].type == TokenType::PLUS || token_stream[index].type == TokenType::MINU ||
        token_stream[index].type == TokenType::NOT || token_stream[index].type == TokenType::LBRACE){
            // auto child = procInitVal(node);
            node->children.push_back(procInitVal(node));

            while (token_stream[index].type == TokenType::COMMA)
            {
                node->children.push_back(new Term(token_stream[index],node));
                index++;

                // auto child = procInitVal(node);
                node->children.push_back(procInitVal(node));
            }
            
        }

        if(token_stream[index].type == TokenType::RBRACE){
            node->children.push_back(new Term(token_stream[index],node));
            index++;
        }
        else assert(0);
    }
    else if(token_stream[index].type == TokenType::LPARENT || token_stream[index].type == TokenType::IDENFR ||
    token_stream[index].type == TokenType::INTLTR || token_stream[index].type == TokenType::FLOATLTR ||
    token_stream[index].type == TokenType::PLUS || token_stream[index].type == TokenType::MINU ||
    token_stream[index].type == TokenType::NOT){
        // auto child = procExp(node);
        node->children.push_back(procExp(node));
    }
    else assert(0);

    return node;  
}


frontend::FuncDef* frontend::Parser::procFuncDef(frontend::AstNode* p){

    auto node = new FuncDef(p);

    // auto child = procFuncType(node);
    node->children.push_back(procFuncType(node));

    if(token_stream[index].type == TokenType::IDENFR){
        node->children.push_back(new Term(token_stream[index],node));
        index++;
    }
    else assert(0);

    if(token_stream[index].type == TokenType::LPARENT){
        node->children.push_back(new Term(token_stream[index],node));
        index++;
    }
    else assert(0);

    if(token_stream[index].type == TokenType::INTTK || token_stream[index].type == TokenType::FLOATTK){
        // auto child = procFuncFParams(node);
        node->children.push_back(procFuncFParams(node));
    }

    if(token_stream[index].type == TokenType::RPARENT){
        node->children.push_back(new Term(token_stream[index],node));
        index++;
    }
    else assert(0);

    // auto child = procBlock(node);
    node->children.push_back(procBlock(node));

    return node;  
}

frontend::FuncType* frontend::Parser::procFuncType(frontend::AstNode* p){

    auto node = new FuncType(p);

    if(token_stream[index].type == TokenType::VOIDTK || token_stream[index].type == TokenType::INTTK ||
    token_stream[index].type == TokenType::FLOATTK){
        node->children.push_back(new Term(token_stream[index],node));
        index++;
    }

    return node;  
}


frontend::FuncFParam* frontend::Parser::procFuncFParam(frontend::AstNode* p){

    auto node = new FuncFParam(p);

    // auto child = procBType(node);
    node->children.push_back(procBType(node));

    if(token_stream[index].type == TokenType::IDENFR){
        node->children.push_back(new Term(token_stream[index],node));
        index++;
    }
    else assert(0);

    if(token_stream[index].type == TokenType::LBRACK){
        node->children.push_back(new Term(token_stream[index],node));
        index++;

        if(token_stream[index].type == TokenType::RBRACK){
            node->children.push_back(new Term(token_stream[index],node));
            index++;
        }
        else assert(0);

        while (token_stream[index].type == TokenType::LBRACK)
        {
            node->children.push_back(new Term(token_stream[index],node));
            index++;

            // auto child = procExp(node);
            node->children.push_back(procExp(node));

            if(token_stream[index].type == TokenType::RBRACK){
                node->children.push_back(new Term(token_stream[index],node));
                index++;
            }
            else assert(0);
        }
        
    }
    
    return node;  
}


frontend::FuncFParams* frontend::Parser::procFuncFParams(frontend::AstNode* p){

    auto node = new FuncFParams(p);

    // auto child = procFuncFParam(node);
    node->children.push_back(procFuncFParam(node));

    while (token_stream[index].type == TokenType::COMMA)
    {
        node->children.push_back(new Term(token_stream[index],node));
        index++;

        // auto child = procFuncFParam(node);
        node->children.push_back(procFuncFParam(node));
    }
    
    return node;  
}


frontend::Block* frontend::Parser::procBlock(frontend::AstNode* p){

    auto node = new Block(p);

    if(token_stream[index].type == TokenType::LBRACE){
        node->children.push_back(new Term(token_stream[index],node));
        index++;
    }
    else assert(0);

    while (token_stream[index].type == TokenType::CONSTTK || token_stream[index].type == TokenType::INTTK ||
    token_stream[index].type == TokenType::FLOATTK || token_stream[index].type == TokenType::IDENFR || token_stream[index].type == TokenType::LBRACE ||
    token_stream[index].type == TokenType::IFTK || token_stream[index].type == TokenType::WHILETK ||
    token_stream[index].type == TokenType::CONTINUETK || token_stream[index].type == TokenType::RETURNTK ||
    token_stream[index].type == TokenType::LPARENT || token_stream[index].type == TokenType::INTLTR ||
    token_stream[index].type == TokenType::FLOATLTR || token_stream[index].type == TokenType::PLUS ||
    token_stream[index].type == TokenType::MINU || token_stream[index].type == TokenType::NOT || token_stream[index].type == TokenType::SEMICN || 
    token_stream[index].type == TokenType::BREAKTK)
    {
        // auto child = procBlockItem(node);
        node->children.push_back(procBlockItem(node));
    }

    if(token_stream[index].type == TokenType::RBRACE){
        node->children.push_back(new Term(token_stream[index],node));
        index++;
    }
    else assert(0);
    

    return node;  
}

frontend::BlockItem* frontend::Parser::procBlockItem(frontend::AstNode* p){

    auto node = new BlockItem(p);

    if(token_stream[index].type == TokenType::CONSTTK || token_stream[index].type == TokenType::INTTK ||
    token_stream[index].type == TokenType::FLOATTK){
        // auto child = procDecl(node);
        node->children.push_back(procDecl(node));
    }
    else if(token_stream[index].type == TokenType::IDENFR || token_stream[index].type == TokenType::LBRACE ||
    token_stream[index].type == TokenType::IFTK || token_stream[index].type == TokenType::WHILETK ||
    token_stream[index].type == TokenType::CONTINUETK || token_stream[index].type == TokenType::RETURNTK ||
    token_stream[index].type == TokenType::LPARENT || token_stream[index].type == TokenType::INTLTR ||
    token_stream[index].type == TokenType::FLOATLTR || token_stream[index].type == TokenType::PLUS ||
    token_stream[index].type == TokenType::MINU || token_stream[index].type == TokenType::NOT || token_stream[index].type == TokenType::SEMICN ||
    token_stream[index].type == TokenType::BREAKTK){
        // auto child = procStmt(node);
        node->children.push_back(procStmt(node));
    }
    else assert(0);

    return node;  
}


frontend::Stmt* frontend::Parser::procStmt(frontend::AstNode* p){

    auto node = new Stmt(p);

    if(token_stream[index].type == TokenType::LBRACE){
        // auto child = procBlock(node);
        node->children.push_back(procBlock(node));
    }
    else if(token_stream[index].type == TokenType::IFTK){
        node->children.push_back(new Term(token_stream[index],node));
        index++;

        if(token_stream[index].type == TokenType::LPARENT){
            node->children.push_back(new Term(token_stream[index],node));
            index++;
        }
        else assert(0);

        // auto child = procCond(node);
        node->children.push_back(procCond(node));

        if(token_stream[index].type == TokenType::RPARENT){
            node->children.push_back(new Term(token_stream[index],node));
            index++;
        }
        else assert(0);

        // auto child = procStmt(node);
        node->children.push_back(procStmt(node));

        if(token_stream[index].type == TokenType::ELSETK){
            node->children.push_back(new Term(token_stream[index],node));
            index++;

            // auto child = procStmt(node);
            node->children.push_back(procStmt(node));
        }

    }
    else if(token_stream[index].type == TokenType::WHILETK){
        node->children.push_back(new Term(token_stream[index],node));
        index++;

        if(token_stream[index].type == TokenType::LPARENT){
            node->children.push_back(new Term(token_stream[index],node));
            index++;
        }
        else assert(0);

        // auto child = procCond(node);
        node->children.push_back(procCond(node));

        if(token_stream[index].type == TokenType::RPARENT){
            node->children.push_back(new Term(token_stream[index],node));
            index++;
        }
        else assert(0);

        // auto child = procStmt(node);
        node->children.push_back(procStmt(node));

    }
    else if(token_stream[index].type == TokenType::BREAKTK){
        node->children.push_back(new Term(token_stream[index],node));
        index++;

        if(token_stream[index].type == TokenType::SEMICN){
            node->children.push_back(new Term(token_stream[index],node));
            index++;
        }
        else assert(0);
    }
    else if(token_stream[index].type == TokenType::CONTINUETK){
        node->children.push_back(new Term(token_stream[index],node));
        index++;

        if(token_stream[index].type == TokenType::SEMICN){
            node->children.push_back(new Term(token_stream[index],node));
            index++;
        }
        else assert(0);
    }
    else if(token_stream[index].type == TokenType::RETURNTK){
        node->children.push_back(new Term(token_stream[index],node));
        index++;

        if(token_stream[index].type == TokenType::LPARENT || token_stream[index].type == TokenType::IDENFR ||
        token_stream[index].type == TokenType::INTLTR || token_stream[index].type == TokenType::FLOATLTR ||
        token_stream[index].type == TokenType::PLUS || token_stream[index].type == TokenType::MINU ||
        token_stream[index].type == TokenType::NOT){
            // auto child = procExp(node);
            node->children.push_back(procExp(node));
        }

        if(token_stream[index].type == TokenType::SEMICN){
            node->children.push_back(new Term(token_stream[index],node));
            index++;
        }
        else assert(0);
    }
    else if(token_stream[index].type == TokenType::LPARENT ||
    token_stream[index].type == TokenType::INTLTR || token_stream[index].type == TokenType::FLOATLTR ||
    token_stream[index].type == TokenType::PLUS || token_stream[index].type == TokenType::MINU ||
    token_stream[index].type == TokenType::NOT){
        // auto child = procExp(node);
        node->children.push_back(procExp(node));   
    }
    else if(token_stream[index].type == TokenType::SEMICN){
        node->children.push_back(new Term(token_stream[index],node));
        index++;
    }
    else if(token_stream[index].type == TokenType::IDENFR){
        int di = 0;
        bool containEq = false;
        while(index + di < token_stream.size()){
            if(token_stream[index + di].type == TokenType::SEMICN)break;
            else if(token_stream[index + di].type == TokenType::ASSIGN) containEq = true;
            di++;
        }

        if(containEq){
            // auto child = procLVal(node);
            node->children.push_back(procLVal(node));

            if(token_stream[index].type == TokenType::ASSIGN){
                node->children.push_back(new Term(token_stream[index],node));
                index++;
            }
            else assert(0);

            // auto child = procExp(node);
            node->children.push_back(procExp(node));

            if(token_stream[index].type == TokenType::SEMICN){
                node->children.push_back(new Term(token_stream[index],node));
                index++;
            }
            else assert(0);
        }
        else{
            // auto child = procExp(node);
            node->children.push_back(procExp(node));

            if(token_stream[index].type == TokenType::SEMICN){
                node->children.push_back(new Term(token_stream[index],node));
                index++;
            }
            else assert(0);
        }
    }

    else assert(0);

    return node;
}


frontend::Exp* frontend::Parser::procExp(frontend::AstNode* p){

    auto node = new Exp(p);

    auto child = procAddExp(node);
    node->children.push_back(child);

    return node;
}


frontend::Cond* frontend::Parser::procCond(frontend::AstNode* p){

    auto node = new Cond(p);

    auto child = procLOrExp(node);
    node->children.push_back(child);

    return node;
}


frontend::LVal* frontend::Parser::procLVal(frontend::AstNode* p){

    auto node = new LVal(p);

    if(token_stream[index].type == TokenType::IDENFR){
        node->children.push_back(new Term(token_stream[index],node));
        index++;
    }
    else assert(0);

    while (token_stream[index].type == TokenType::LBRACK)
    {
        node->children.push_back(new Term(token_stream[index],node));
        index++;

        // auto child = procExp(node);
        node->children.push_back(procExp(node));

        if(token_stream[index].type == TokenType::RBRACK){
            node->children.push_back(new Term(token_stream[index],node));
            index++;
        }
        else assert(0);
    }
    

    return node;
}


frontend::Number* frontend::Parser::procNumber(frontend::AstNode* p){

    auto node = new Number(p);

    if(token_stream[index].type == TokenType::INTLTR || token_stream[index].type == TokenType::FLOATLTR){
        node->children.push_back(new Term(token_stream[index],node));
        index++;
    }
    else assert(0);

    return node;
}


frontend::PrimaryExp* frontend::Parser::procPrimaryExp(frontend::AstNode* p){

    auto node = new PrimaryExp(p);

    if(token_stream[index].type == TokenType::LPARENT){
        node->children.push_back(new Term(token_stream[index],node));
        index++;

        auto child = procExp(node);
        node->children.push_back(child);

        if(token_stream[index].type == TokenType::RPARENT){
            node->children.push_back(new Term(token_stream[index],node));
            index++;
        }
        else assert(0);
    }
    else if(token_stream[index].type == TokenType::IDENFR){
        auto child = procLVal(node);
        node->children.push_back(child);
    }
    else if(token_stream[index].type == TokenType::INTLTR || token_stream[index].type == TokenType::FLOATLTR){
        auto child = procNumber(node);
        node->children.push_back(child);
    }
    else assert(0);

    return node;
}

frontend::UnaryExp* frontend::Parser::procUnaryExp(frontend::AstNode* p){

    auto node = new UnaryExp(p);

    if(token_stream[index].type == TokenType::LPARENT || token_stream[index].type == TokenType::INTLTR ||
    token_stream[index].type == TokenType::FLOATLTR){
        // auto child = procPrimaryExp(node);
        node->children.push_back(procPrimaryExp(node));
    }
    else if(token_stream[index].type == TokenType::PLUS || token_stream[index].type == TokenType::MINU ||
    token_stream[index].type == TokenType::NOT){
        // auto child = procUnaryOp(node);
        node->children.push_back(procUnaryOp(node));

        // auto child = procUnaryExp(node);
        node->children.push_back(procUnaryExp(node));
    }
    else if(token_stream[index].type == TokenType::IDENFR){
        if(index + 1 < token_stream.size() && token_stream[index+1].type == TokenType::LPARENT){
            node->children.push_back(new Term(token_stream[index],node));
            index++;

            node->children.push_back(new Term(token_stream[index],node));
            index++;

            if(token_stream[index].type == TokenType::LPARENT || token_stream[index].type == TokenType::IDENFR ||
            token_stream[index].type == TokenType::INTLTR || token_stream[index].type == TokenType::FLOATLTR ||
            token_stream[index].type == TokenType::PLUS || token_stream[index].type == TokenType::MINU ||
            token_stream[index].type == TokenType::NOT){
                // auto child = procFuncRParams(node);
                node->children.push_back(procFuncRParams(node));
            }
            
            if(token_stream[index].type == TokenType::RPARENT){
                node->children.push_back(new Term(token_stream[index],node));
                index++;
            }
            else assert(0);

        }
        else{
            // auto child = procPrimaryExp(node);
            node->children.push_back(procPrimaryExp(node));
        }
    }
    else assert(0);

    return node;
}

frontend::UnaryOp* frontend::Parser::procUnaryOp(frontend::AstNode* p){

    auto node = new UnaryOp(p);

    if(token_stream[index].type == TokenType::PLUS || token_stream[index].type == TokenType::MINU||
    token_stream[index].type == TokenType::NOT){
        node->children.push_back(new Term(token_stream[index],node));
        index++;
    }
    else assert(0);

    return node;
}

frontend::FuncRParams* frontend::Parser::procFuncRParams(frontend::AstNode* p){

    auto node = new FuncRParams(p);

    // auto child = procExp(node);
    node->children.push_back(procExp(node));

    while (token_stream[index].type == TokenType::COMMA)
    {
        node->children.push_back(new Term(token_stream[index],node));
        index++;

        // auto child = procExp(node);
        node->children.push_back(procExp(node));
    }

    return node;
}

frontend::MulExp* frontend::Parser::procMulExp(frontend::AstNode* p){

    auto node = new MulExp(p);

    // auto child = procUnaryExp(node);
    node->children.push_back(procUnaryExp(node));

    while (token_stream[index].type == TokenType::MULT || token_stream[index].type == TokenType::DIV ||
    token_stream[index].type == TokenType::MOD)
    {
        node->children.push_back(new Term(token_stream[index],node));
        index++;

        // auto child = procUnaryExp(node);
        node->children.push_back(procUnaryExp(node));
    }

    return node;
}

frontend::AddExp* frontend::Parser::procAddExp(frontend::AstNode* p){

    auto node = new AddExp(p);

    // auto child = procMulExp(node);
    node->children.push_back(procMulExp(node));

    while (token_stream[index].type == TokenType::PLUS || token_stream[index].type == TokenType::MINU)
    {
        node->children.push_back(new Term(token_stream[index],node));
        index++;

        // auto child = procMulExp(node);
        node->children.push_back(procMulExp(node));
    }

    return node;
}

frontend::RelExp* frontend::Parser::procRelExp(frontend::AstNode* p){

    auto node = new RelExp(p);

    // auto child = procAddExp(node);
    node->children.push_back(procAddExp(node));

    while(token_stream[index].type == TokenType::LSS || token_stream[index].type == TokenType::GTR ||
    token_stream[index].type == TokenType::LEQ || token_stream[index].type == TokenType::GEQ){
        node->children.push_back(new Term(token_stream[index],node));
        index++;

        // auto child = procAddExp(node);
        node->children.push_back(procAddExp(node));
    }

    return node;  
}

frontend::EqExp* frontend::Parser::procEqExp(frontend::AstNode* p){

    auto node = new EqExp(p);

    // auto child = procRelExp(node);
    node->children.push_back(procRelExp(node));

    while(token_stream[index].type == TokenType::EQL || token_stream[index].type == TokenType::NEQ){
        node->children.push_back(new Term(token_stream[index],node));
        index++;

        // auto child = procRelExp(node);
        node->children.push_back(procRelExp(node));
    }

    return node;  
}


frontend::LAndExp* frontend::Parser::procLAndExp(frontend::AstNode* p){

    auto node = new LAndExp(p);

    // auto child = procEqExp(node);
    node->children.push_back(procEqExp(node));

    if(token_stream[index].type == TokenType::AND){
        node->children.push_back(new Term(token_stream[index],node));
        index++;

        // auto child = procLAndExp(node);
        node->children.push_back(procLAndExp(node));
    }

    return node;  
}

frontend::LOrExp* frontend::Parser::procLOrExp(frontend::AstNode* p){

    auto node = new LOrExp(p);

    // auto child = procLAndExp(node);
    node->children.push_back(procLAndExp(node));

    if(token_stream[index].type == TokenType::OR){
        node->children.push_back(new Term(token_stream[index],node));
        index++;

        // auto child = procLOrExp(node);
        node->children.push_back(procLOrExp(node));
    }

    return node;  
}

frontend::ConstExp* frontend::Parser::procConstExp(frontend::AstNode* p){

    auto node = new ConstExp(p);

    // auto child = procAddExp(node);
    node->children.push_back(procAddExp(node));

    return node;  
}



void Parser::log(AstNode* node){
#ifdef DEBUG_PARSER
        std::cout << "in parse" << toString(node->type) << ", cur_token_type::" << toString(token_stream[index].type) << ", token_val::" << token_stream[index].value << '\n';
#endif
}
