#include "front/syntax.h"

#include <iostream>
#include <cassert>

using frontend::Parser;

#define DEBUG_PARSER
#define TODO assert(0 && "todo")
#define CUR_TOKEN_IS(tk_type) (token_stream[index].type == TokenType::tk_type)
#define PARSE_TOKEN(tk_type) root->children.push_back(parseTerm(root, TokenType::tk_type))
#define PARSE(name, type)       \
    auto name = new type(root); \
    assert(parse##type(name));  \
    root->children.push_back(name);

Parser::Parser(const std::vector<frontend::Token> &tokens) : index(0), token_stream(tokens)
{
}

Parser::~Parser() {}
frontend::Term *Parser::parseTerm(AstNode *parent, TokenType expected)
{
    frontend::Term *term = new frontend::Term(token_stream[index]); // 产生一个根节点
    term->parent = parent;
    index++;
    return term;
}
frontend::CompUnit *Parser::get_abstract_syntax_tree()
{
    frontend::CompUnit *compunit = new frontend::CompUnit(); // 产生一个根节点
    if (parseCompUnit(compunit))
        return compunit;
    return compunit;
}
// CompUnit -> (Decl | FuncDef) [CompUnit]
// FirstVT(CompUnit) = { 'const', 'int', 'float' }
// FirstVT(Decl) = { 'const', 'int', 'float' }
// FirstVT(FuncDef) = { 'void', 'int', 'float' }
// Decl -> ConstDecl | VarDecl
// ConstDecl -> 'const' BType ConstDef { ',' ConstDef } ';'
// VarDecl -> BType VarDef { ',' VarDef } ';'
// FirstVT(BType) = { 'int', 'float' }
// FirstVT(VarDef) = { Ident }->假如是Decl，第二个是ident，第三个可能是','，可能是';'必然不可能是FirstVT(CompUnit)
// FuncDef -> FuncType Ident '(' [FuncFParams] ')' Block
// FuncType -> 'void' | 'int' | 'float'->假如是FuncDef，第二个也是ident，第三个是'('
bool frontend::Parser::parseCompUnit(frontend::CompUnit *root)
{
    log(root);
    bool b1 = true;
    if (CUR_TOKEN_IS(CONSTTK))
    {
        PARSE(decl, Decl);
    }
    else if (CUR_TOKEN_IS(VOIDTK))
    {
        PARSE(funcdef, FuncDef);
        if (index < token_stream.size())
        {
            PARSE(compunit, CompUnit);
        }
    }
    else if (CUR_TOKEN_IS(INTTK) || CUR_TOKEN_IS(FLOATTK))
    {
        int index_beifen = index;
        PARSE_TOKEN(INTTK);
        PARSE_TOKEN(IDENFR);
        if (CUR_TOKEN_IS(LPARENT))
        {
            index = index_beifen;
            root->children.pop_back();
            root->children.pop_back();
            PARSE(funcdef, FuncDef);
        }
        else
        {
            index = index_beifen;
            root->children.pop_back();
            root->children.pop_back();
            PARSE(decl, Decl);
        }
    }
    else
    {
        b1 = false;
    }
    if (CUR_TOKEN_IS(CONSTTK) || CUR_TOKEN_IS(VOIDTK) || CUR_TOKEN_IS(INTTK) || CUR_TOKEN_IS(FLOATTK))
    {
        PARSE(compunit, CompUnit);
    }

    return b1;
};
// Decl -> ConstDecl | VarDecl
// first(ConstDecl) = { 'const' }
// first(VarDecl) = { 'void', 'int', 'float' }
bool frontend::Parser::parseDecl(frontend::Decl *root)
{
    log(root);

    bool b1 = true;
    if (CUR_TOKEN_IS(CONSTTK))
    {
        PARSE(constdecl, ConstDecl);
    }
    else if (CUR_TOKEN_IS(VOIDTK) || CUR_TOKEN_IS(INTTK) || CUR_TOKEN_IS(FLOATTK))
    {
        PARSE(vardecl, VarDecl);
    }
    else
        b1 = false;

    return b1;
};
// ConstDecl -> 'const' BType ConstDef { ',' ConstDef } ';'
bool frontend::Parser::parseConstDecl(frontend::ConstDecl *root)
{
    log(root);
    bool b1 = true;

    PARSE_TOKEN(CONSTTK);

    PARSE(btype, BType);

    PARSE(constdef, ConstDef);

    while (CUR_TOKEN_IS(COMMA))
    {
        PARSE_TOKEN(COMMA);

        PARSE(constdef_right, ConstDef);
    }

    PARSE_TOKEN(SEMICN);

    return b1;
};
// BType -> 'int' | 'float'
bool frontend::Parser::parseBType(frontend::BType *root)
{
    log(root);

    bool b1 = true;
    if (CUR_TOKEN_IS(INTTK))
    {
        PARSE_TOKEN(INTTK);
    }
    else if (CUR_TOKEN_IS(FLOATTK))
    {
        PARSE_TOKEN(FLOATTK);
    }
    else
    {
        b1 = false;
    }

    return b1;
};
// ConstDef -> Ident { '[' ConstExp ']' } '=' ConstInitVal
// FirstVT(ConstExp) = { Ident, IntConst, floatConst, '(', '+', '-', '!' }
bool frontend::Parser::parseConstDef(frontend::ConstDef *root)
{
    log(root);

    PARSE_TOKEN(IDENFR);

    bool b1 = true;
    while (CUR_TOKEN_IS(LBRACK))
    {
        PARSE_TOKEN(LBRACK);

        PARSE(constexp, ConstExp);
        PARSE_TOKEN(RBRACE);
    }
    PARSE_TOKEN(ASSIGN);

    PARSE(constinitval, ConstInitVal);

    return b1;
};

// ConstInitVal -> ConstExp | '{' [ ConstInitVal { ',' ConstInitVal } ] '}'
// first(ConstExp) = { '(', Number, Ident }
// first(ConstInitVal) = { '{', Number }
bool frontend::Parser::parseConstInitVal(frontend::ConstInitVal *root)
{
    log(root);

    bool b1 = true;
    if (CUR_TOKEN_IS(LBRACE))
    {
        PARSE_TOKEN(LBRACE);

        if (CUR_TOKEN_IS(LPARENT) || CUR_TOKEN_IS(INTLTR) || CUR_TOKEN_IS(FLOATLTR) || CUR_TOKEN_IS(IDENFR))
        {
            PARSE(constinitval, ConstInitVal);

            while (CUR_TOKEN_IS(COMMA))
            {
                PARSE_TOKEN(COMMA);

                PARSE(constinitval_right, ConstInitVal);
            }
            PARSE_TOKEN(RBRACE);
        }
    }
    else
    {
        PARSE(constexp, ConstExp);
    }

    return b1;
};
// VarDecl -> BType VarDef { ',' VarDef } ';'
bool frontend::Parser::parseVarDecl(frontend::VarDecl *root)
{
    log(root);
    bool b1 = true;
    PARSE(btype, BType);

    PARSE(vardef, VarDef);

    while (CUR_TOKEN_IS(COMMA))
    {
        PARSE_TOKEN(COMMA);

        PARSE(vardef_right, VarDef);
    }
    PARSE_TOKEN(SEMICN);

    return b1;
};
// VarDef -> Ident { '[' ConstExp ']' } [ '=' InitVal ]
bool frontend::Parser::parseVarDef(frontend::VarDef *root)
{
    log(root);

    PARSE_TOKEN(IDENFR);

    bool b1 = true;
    while (CUR_TOKEN_IS(LBRACK))
    {
        PARSE_TOKEN(LBRACK);

        PARSE(constexp, ConstExp);

        PARSE_TOKEN(RBRACK);
    }
    if (CUR_TOKEN_IS(ASSIGN))
    {
        PARSE_TOKEN(ASSIGN);

        PARSE(initval, InitVal);
    }

    return b1;
};
// InitVal -> Exp | '{' [ InitVal { ',' InitVal } ] '}'
// first(Exp) = { '(', Number, Ident }
bool frontend::Parser::parseInitVal(frontend::InitVal *root)
{
    log(root);

    bool b1 = true;
    if (CUR_TOKEN_IS(LBRACE))
    {
        PARSE_TOKEN(LBRACE);

        if (CUR_TOKEN_IS(RBRACE))
        {
            PARSE_TOKEN(RBRACE);
        }
        else
        {
            PARSE(initval, InitVal);

            while (CUR_TOKEN_IS(COMMA))
            {
                PARSE_TOKEN(COMMA);

                PARSE(initval_right, InitVal);
            }
            PARSE_TOKEN(RBRACE);
        }
    }
    else
    {
        PARSE(exp, Exp);
    }

    return b1;
};
// FuncDef -> FuncType Ident '(' [FuncFParams] ')' Block
// first(FuncFParams) = { 'void', 'int', 'float' }
bool frontend::Parser::parseFuncDef(frontend::FuncDef *root)
{
    log(root);
    bool b1 = true;

    PARSE(functype, FuncType);

    PARSE_TOKEN(IDENFR);

    PARSE_TOKEN(LPARENT);

    if (CUR_TOKEN_IS(INTTK) || CUR_TOKEN_IS(FLOATTK))
    {
        PARSE(funcfparams, FuncFParams);
    }

    PARSE_TOKEN(RPARENT);

    PARSE(block, Block);

    return b1;
};
// FuncType -> 'void' | 'int' | 'float'
bool frontend::Parser::parseFuncType(frontend::FuncType *root)
{
    log(root);

    bool b1 = true;
    if (CUR_TOKEN_IS(VOIDTK))
    {
        PARSE_TOKEN(VOIDTK);
        b1 = true;
    }
    else if (CUR_TOKEN_IS(INTTK))
    {
        PARSE_TOKEN(INTTK);
        b1 = true;
    }
    else if (CUR_TOKEN_IS(FLOATTK))
    {
        PARSE_TOKEN(FLOATTK);
        b1 = true;
    }
    else
    {
        b1 = false;
    }

    return b1;
};
// FuncFParam -> BType Ident ['[' ']' { '[' Exp ']' }]
bool frontend::Parser::parseFuncFParam(frontend::FuncFParam *root)
{
    log(root);

    PARSE(btype, BType);
    bool b1 = true;
    PARSE_TOKEN(IDENFR);

    if (CUR_TOKEN_IS(LBRACK))
    {
        PARSE_TOKEN(LBRACK);

        PARSE_TOKEN(RBRACK);

        while (CUR_TOKEN_IS(LBRACK))
        {
            PARSE_TOKEN(LBRACK);

            PARSE(exp, Exp);

            PARSE_TOKEN(RBRACK);
        }
    }

    return b1;
};
// FuncFParams -> FuncFParam { ',' FuncFParam }
bool frontend::Parser::parseFuncFParams(frontend::FuncFParams *root)
{
    log(root);
    bool b1 = true;

    PARSE(funcfparam, FuncFParam);

    while (CUR_TOKEN_IS(COMMA))
    {
        PARSE_TOKEN(COMMA);

        PARSE(funcfparam, FuncFParam);
    }

    return b1;
};
// Block -> '{' { BlockItem } '}'
// first(BlockItem)={'const', 'void', 'int', 'float','{', 'if', 'while', 'break', 'continue', 'return', ';', Ident}
// BlockItem -> Decl | Stmt
// first(Decl) = { 'const', 'void', 'int', 'float' }
// first(Stmt) = { '{', 'if', 'while', 'break', 'continue', 'return', ';', Ident }
bool frontend::Parser::parseBlock(frontend::Block *root)
{
    log(root);

    PARSE_TOKEN(LBRACE);

    bool b1 = true;
    while (CUR_TOKEN_IS(CONSTTK) || CUR_TOKEN_IS(VOIDTK) || CUR_TOKEN_IS(INTTK) || CUR_TOKEN_IS(FLOATTK) || CUR_TOKEN_IS(LBRACE) || CUR_TOKEN_IS(IFTK) || CUR_TOKEN_IS(WHILETK) || CUR_TOKEN_IS(BREAKTK) || CUR_TOKEN_IS(CONTINUETK) || CUR_TOKEN_IS(RETURNTK) || CUR_TOKEN_IS(SEMICN) || CUR_TOKEN_IS(IDENFR))
    {
        PARSE(blockitem, BlockItem);
    }

    PARSE_TOKEN(RBRACE);

    return b1;
};
// BlockItem -> Decl | Stmt
// first(Decl) = { 'const', 'void', 'int', 'float' }
// first(Stmt) = { '{', 'if', 'while', 'break', 'continue', 'return', ';', Ident }
bool frontend::Parser::parseBlockItem(frontend::BlockItem *root)
{
    log(root);

    bool b1 = true;
    if (CUR_TOKEN_IS(CONSTTK) || CUR_TOKEN_IS(VOIDTK) || CUR_TOKEN_IS(INTTK) || CUR_TOKEN_IS(FLOATTK))
    {
        PARSE(decl, Decl);
    }
    else if (CUR_TOKEN_IS(LBRACE) || CUR_TOKEN_IS(IFTK) || CUR_TOKEN_IS(WHILETK) || CUR_TOKEN_IS(BREAKTK) || CUR_TOKEN_IS(CONTINUETK) || CUR_TOKEN_IS(RETURNTK) || CUR_TOKEN_IS(SEMICN) || CUR_TOKEN_IS(IDENFR))
    {
        PARSE(stmt, Stmt);
    }
    else
    {
        b1 = false;
    }

    return b1;
};
// Stmt -> LVal '=' Exp ';' | Block | 'if' '(' Cond ')' Stmt [ 'else' Stmt ] | 'while' '(' Cond ')' Stmt | 'break' ';' | 'continue' ';' | 'return' [Exp] ';' | [Exp] ';'
// first(LVal) = { Ident }
// first(Block) = { '{' }
// first('if') = { 'if' }
// first('while') = { 'while' }
// first('break') = { 'break' }
// first('continue') = { 'continue' }
// first('return') = { 'return' }
// first(Exp) = { '+' '-' '!' '(' '++' '--' Ident IntConst FloatConst }
// LVal -> Ident {'[' Exp ']'}
bool frontend::Parser::parseStmt(frontend::Stmt *root)
{
    log(root);

    bool b1 = true;
    // 因为Exp最终可以化为LVal，所以先转换为Exp是肯定对的，这里要先假设为Exp，然后根据后一个是;还是'='
    if (CUR_TOKEN_IS(IDENFR))
    {

        int index_beifen = index;
        PARSE(exp, Exp);

        if (CUR_TOKEN_IS(SEMICN)) // 正确
        {
            PARSE_TOKEN(SEMICN);
        }
        else if (CUR_TOKEN_IS(ASSIGN))
        {

            index = index_beifen;
            root->children.pop_back();
            PARSE(lval, LVal);

            PARSE_TOKEN(ASSIGN);

            PARSE(exp, Exp);

            PARSE_TOKEN(SEMICN);
        }
    }
    else if (CUR_TOKEN_IS(LBRACE))
    {
        PARSE(block, Block);
    }
    else if (CUR_TOKEN_IS(IFTK))
    {
        PARSE_TOKEN(IFTK);
        PARSE_TOKEN(LPARENT);

        PARSE(cond, Cond);
        PARSE_TOKEN(RPARENT);

        PARSE(stmt, Stmt);

        if (CUR_TOKEN_IS(ELSETK))
        {
            PARSE_TOKEN(ELSETK);

            PARSE(stmt_right, Stmt);
        }
    }
    else if (CUR_TOKEN_IS(WHILETK))
    {
        PARSE_TOKEN(WHILETK);
        PARSE_TOKEN(LPARENT);

        PARSE(cond, Cond);
        PARSE_TOKEN(RPARENT);

        PARSE(stmt, Stmt);
    }
    else if (CUR_TOKEN_IS(BREAKTK))
    {
        PARSE_TOKEN(BREAKTK);

        PARSE_TOKEN(SEMICN);
    }
    else if (CUR_TOKEN_IS(CONTINUETK))
    {
        PARSE_TOKEN(CONTINUETK);

        PARSE_TOKEN(SEMICN);
    }
    else if (CUR_TOKEN_IS(RETURNTK))
    {
        PARSE_TOKEN(RETURNTK);

        if (CUR_TOKEN_IS(SEMICN))
        {
            PARSE_TOKEN(SEMICN);
        }
        else
        {
            PARSE(exp, Exp);

            PARSE_TOKEN(SEMICN);
        }
    }
    else if (CUR_TOKEN_IS(PLUS) || CUR_TOKEN_IS(MINU) || CUR_TOKEN_IS(NOT) || CUR_TOKEN_IS(LPARENT) || CUR_TOKEN_IS(IDENFR) || CUR_TOKEN_IS(INTLTR) || CUR_TOKEN_IS(FLOATLTR))
    {
        std::cout << "i am here now" << std::endl;
        PARSE(exp, Exp);

        PARSE_TOKEN(SEMICN);
    }
    else if (CUR_TOKEN_IS(SEMICN))
    {
        PARSE_TOKEN(SEMICN);
    }
    else
    {
        b1 = false;
    }

    return b1;
};
// Exp -> AddExp
bool frontend::Parser::parseExp(frontend::Exp *root)
{
    log(root);
    bool b1 = true;
    PARSE(addexp, AddExp);

    return b1;
};
// Cond -> LOrExp
bool frontend::Parser::parseCond(frontend::Cond *root)
{
    log(root);
    bool b1 = true;
    PARSE(lorexp, LOrExp);

    return b1;
};
// LVal -> Ident {'[' Exp ']'}
bool frontend::Parser::parseLVal(frontend::LVal *root)
{
    log(root);

    PARSE_TOKEN(IDENFR);

    bool b1 = true;
    while (CUR_TOKEN_IS(LBRACK))
    {
        PARSE_TOKEN(LBRACK);

        PARSE(exp, Exp);

        PARSE_TOKEN(RBRACK);
    }

    return b1;
};
// Number -> IntConst | floatConst
bool frontend::Parser::parseNumber(frontend::Number *root)
{
    log(root);

    bool b1 = true;

    if (CUR_TOKEN_IS(INTLTR))
    {
        PARSE_TOKEN(INTLTR);
    }
    else if (CUR_TOKEN_IS(FLOATLTR))
    {
        PARSE_TOKEN(FLOATLTR);
    }
    else
    {
        b1 = false;
    }

    return b1;
};
// PrimaryExp -> '(' Exp ')' | LVal | Number
// first(LVal) = { Ident }
bool frontend::Parser::parsePrimaryExp(frontend::PrimaryExp *root)
{
    log(root);

    bool b1 = true;
    if (CUR_TOKEN_IS(LPARENT))
    {
        PARSE_TOKEN(LPARENT);

        PARSE(exp, Exp);

        PARSE_TOKEN(RPARENT);
    }
    else if (CUR_TOKEN_IS(IDENFR))
    {
        PARSE(lval, LVal);
    }
    else if (CUR_TOKEN_IS(INTLTR) || CUR_TOKEN_IS(FLOATLTR))
    {
        PARSE(number, Number);
    }
    else
    {
        b1 = false;
    }

    return b1;
};
// UnaryExp -> PrimaryExp | Ident '(' [FuncRParams] ')' | UnaryOp UnaryExp
// first(PrimaryExp) = { '(', Number, Ident }
// first(UnaryOp) = { '+', '-', '!' }
//FirstVT(FuncRParams) = { '(', Ident, IntConst, floatConst, '+', '-', '!' }
bool frontend::Parser::parseUnaryExp(frontend::UnaryExp *root)
{
    log(root);

    bool b1 = true;
    if (CUR_TOKEN_IS(PLUS) || CUR_TOKEN_IS(MINU) || CUR_TOKEN_IS(NOT))
    {
        PARSE(unaryop, UnaryOp);

        PARSE(unaryexp, UnaryExp);
    }
    else if (CUR_TOKEN_IS(LPARENT) || CUR_TOKEN_IS(INTLTR) || CUR_TOKEN_IS(FLOATLTR))
    {
        PARSE(primaryexp, PrimaryExp);
    }
    else if (CUR_TOKEN_IS(IDENFR))
    {
        int index_beifen = index;
        PARSE_TOKEN(IDENFR);
        if (CUR_TOKEN_IS(LPARENT))
        {
            PARSE_TOKEN(IDENFR);

            if (CUR_TOKEN_IS(LPARENT) || CUR_TOKEN_IS(INTLTR) || CUR_TOKEN_IS(FLOATLTR) || CUR_TOKEN_IS(IDENFR)|| CUR_TOKEN_IS(PLUS)|| CUR_TOKEN_IS(MINU)|| CUR_TOKEN_IS(NOT))
            {
                PARSE(funcrparams, FuncRParams);
            }
            PARSE_TOKEN(RPARENT);
        }
        else
        {
            index = index_beifen;
            root->children.pop_back();
            PARSE(primaryexp, PrimaryExp);
        }
    }
    else
    {
        b1 = false;
    }

    return b1;
};
// UnaryOp -> '+' | '-' | '!'
bool frontend::Parser::parseUnaryOp(frontend::UnaryOp *root)
{
    log(root);

    bool b1 = true;

    if (CUR_TOKEN_IS(PLUS))
    {
        PARSE_TOKEN(PLUS);
    }
    else if (CUR_TOKEN_IS(MINU))
    {
        PARSE_TOKEN(MINU);
    }
    else if (CUR_TOKEN_IS(NOT))
    {
        PARSE_TOKEN(NOT);
    }
    else
    {
        b1 = false;
    }

    return b1;
};
// FuncRParams -> Exp { ',' Exp }
bool frontend::Parser::parseFuncRParams(frontend::FuncRParams *root)
{
    log(root);

    PARSE(exp, Exp);
    bool b1 = true;
    while (CUR_TOKEN_IS(COMMA))
    {
        PARSE_TOKEN(COMMA);

        PARSE(exp_right, Exp);
    }

    return b1;
};
// MulExp -> UnaryExp { ('*' | '/' | '%') UnaryExp }
bool frontend::Parser::parseMulExp(frontend::MulExp *root)
{
    log(root);

    PARSE(unaryexp, UnaryExp);
    bool b1 = true;
    while (CUR_TOKEN_IS(MULT) || CUR_TOKEN_IS(DIV) || CUR_TOKEN_IS(MOD))
    {
        if (CUR_TOKEN_IS(MULT))
        {
            PARSE_TOKEN(MULT);
        }
        else if (CUR_TOKEN_IS(DIV))
        {
            PARSE_TOKEN(DIV);
        }
        else
        {
            PARSE_TOKEN(MOD);
        }
        PARSE(unaryexp_right, UnaryExp);
    }

    return b1;
};
// AddExp -> MulExp { ('+' | '-') MulExp }
bool frontend::Parser::parseAddExp(frontend::AddExp *root)
{
    log(root);

    PARSE(mulexp, MulExp);
    bool b1 = true;
    while (CUR_TOKEN_IS(PLUS) || CUR_TOKEN_IS(MINU))
    {
        if (CUR_TOKEN_IS(PLUS))
        {
            PARSE_TOKEN(PLUS);
        }
        else
        {
            PARSE_TOKEN(MINU);
        }
        PARSE(mulexp_right, MulExp);
    }

    return b1;
};
// RelExp -> AddExp { ('<' | '>' | '<=' | '>=') AddExp }
bool frontend::Parser::parseRelExp(frontend::RelExp *root)
{
    log(root);

    PARSE(addexp, AddExp);
    bool b1 = true;
    while (CUR_TOKEN_IS(LSS) || CUR_TOKEN_IS(GTR) || CUR_TOKEN_IS(LEQ) || CUR_TOKEN_IS(GEQ))
    {
        if (CUR_TOKEN_IS(LSS))
        {
            PARSE_TOKEN(LSS);
        }

        else if (CUR_TOKEN_IS(GTR))
        {
            PARSE_TOKEN(GTR);
        }
        else if (CUR_TOKEN_IS(LEQ))
        {
            PARSE_TOKEN(LEQ);
        }
        else
        {
            PARSE_TOKEN(GEQ);
        }
        PARSE(addexp_right, AddExp);
    }

    return b1;
};
// EqExp -> RelExp { ('==' | '!=') RelExp }
bool frontend::Parser::parseEqExp(frontend::EqExp *root)
{
    log(root);

    PARSE(relexp, RelExp);
    bool b1 = true;
    while (CUR_TOKEN_IS(EQL) || CUR_TOKEN_IS(NEQ))
    {
        if (CUR_TOKEN_IS(EQL))
        {
            PARSE_TOKEN(EQL);
        }
        else
        {
            PARSE_TOKEN(NEQ);
        }
        PARSE(relexp_right, RelExp);
    }

    return b1;
};
// LAndExp -> EqExp [ '&&' LAndExp ]
bool frontend::Parser::parseLAndExp(frontend::LAndExp *root)
{
    log(root);

    PARSE(eqexp, EqExp);
    bool b1 = true;
    if (CUR_TOKEN_IS(AND))
    {
        PARSE_TOKEN(AND);

        PARSE(landexp, LAndExp);
    }

    return b1;
};
// LOrExp -> LAndExp [ '||' LOrExp ]
bool frontend::Parser::parseLOrExp(frontend::LOrExp *root)
{
    log(root);

    PARSE(landexp, LAndExp);
    bool b1 = true;
    if (CUR_TOKEN_IS(OR))
    {
        PARSE_TOKEN(OR);

        PARSE(lorexp, LOrExp);
    }

    return b1;
};

// ConstExp -> AddExp
bool frontend::Parser::parseConstExp(frontend::ConstExp *root)
{
    log(root);
    bool b1 = true;
    PARSE(addexp, AddExp);

    return b1;
};
void frontend::Parser::log(AstNode *node)
{
#ifdef DEBUG_PARSER
    std::cout << "in parse" << toString(node->type) << ", cur_token_type::" << toString(token_stream[index].type) << ", token_val::" << token_stream[index].value << '\n';
#endif
}
