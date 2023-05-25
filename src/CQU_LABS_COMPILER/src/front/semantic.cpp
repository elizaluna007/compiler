#include"front/semantic.h"

#include<cassert>

using ir::Instruction;
using ir::Function;
using ir::Operand;
using ir::Operator;

#define TODO assert(0 && "TODO");

#define GET_CHILD_PTR(node, type, index) auto node = dynamic_cast<type*>(root->children[index]); assert(node); 
#define ANALYSIS(node, type, index) auto node = dynamic_cast<type*>(root->children[index]); assert(node); analysis##type(node, buffer);
#define COPY_EXP_NODE(from, to) to->is_computable = from->is_computable; to->v = from->v; to->t = from->t;

map<std::string,ir::Function*>* frontend::get_lib_funcs() {
    static map<std::string,ir::Function*> lib_funcs = {
        {"getint", new Function("getint", Type::Int)},
        {"getch", new Function("getch", Type::Int)},
        {"getfloat", new Function("getfloat", Type::Float)},
        {"getarray", new Function("getarray", {Operand("arr", Type::IntPtr)}, Type::Int)},
        {"getfarray", new Function("getfarray", {Operand("arr", Type::FloatPtr)}, Type::Int)},
        {"putint", new Function("putint", {Operand("i", Type::Int)}, Type::null)},
        {"putch", new Function("putch", {Operand("i", Type::Int)}, Type::null)},
        {"putfloat", new Function("putfloat", {Operand("f", Type::Float)}, Type::null)},
        {"putarray", new Function("putarray", {Operand("n", Type::Int), Operand("arr", Type::IntPtr)}, Type::null)},
        {"putfarray", new Function("putfarray", {Operand("n", Type::Int), Operand("arr", Type::FloatPtr)}, Type::null)},
    };
    return &lib_funcs;
}

// void frontend::SymbolTable::add_scope(Block* node, string name) {
//     scope_stack.push_back(ScopeInfo{0, "scope_" + name, map_str_ste()});
// }

frontend::ConstOperand::ConstOperand(void* v, Type t, std::vector<int> dimension) :v(v), t(t), dimension(dimension) {};
bool frontend::ConstOperand::isNull(){return t == Type::null;}

void frontend::SymbolTable::add_scope(std::string name) {
    scope_stack.push_back(ScopeInfo{0, name, map_str_ste()});
}

void frontend::SymbolTable::exit_scope() {
    assert(scope_stack.size()>1);
    scope_stack.erase((--scope_stack.end()));
}

string frontend::SymbolTable::get_scoped_name(string id) const {
    // int index = scope_stack.size()-1;

    // while (index >=0)
    // {
    //     if(scope_stack[index].table.find(id) != scope_stack[index].table.end()) 
    //         return id + "_" + scope_stack[index].name;
        
    //     index--;
    // }
    // return "NULL";
    return id + ":" + scope_stack[scope_stack.size() - 1].name;
}

string frontend::SymbolTable::get_var_name(string id) const {
    assert(id.length()>0);
    int cdx = 0;
    while (cdx < id.length())
    {
        if(id[cdx] == ':') break;
    }
    return id.substr(0, cdx);
}

Operand frontend::SymbolTable::get_operand(string id) const {
    int index = scope_stack.size()-1;

    while (index >=0)
    {
        if(scope_stack[index].table.find(id) != scope_stack[index].table.end()) 
            return scope_stack[index].table.at(id).operand;
        
        index--;
    }
    return Operand();
}

Operand frontend::SymbolTable::get_operand_inscope(string id) const {
    assert(scope_stack.size()>0);

    int index = scope_stack.size() - 1;

    if(scope_stack[index].table.find(id) != scope_stack[index].table.end()) 
        return scope_stack[index].table.at(id).operand;

    return Operand();
}

frontend::STE frontend::SymbolTable::get_ste(string id) const {
    int index = scope_stack.size()-1;


    while (index >=0)
    {
        if(scope_stack[index].table.find(id) != scope_stack[index].table.end()) {
            STE ste = scope_stack[index].table.at(id);
            return STE{ir::Operand( ste.operand.name + ":" + scope_stack[index].name, ste.operand.type), ste.dimension };
        }

        // if(scope_stack[index].table.find(id) != scope_stack[index].table.end()) return scope_stack[index].table.at(id);

        index--;
    }
    return STE{Operand(), vector<int>()};
}

ir::Operand frontend::SymbolTable::add_ste(std::string name, vector<int> dimension, ir::Type t){
    assert(scope_stack[scope_stack.size()-1].table.find(name) == scope_stack[scope_stack.size()-1].table.end());
    auto operand = Operand( name, t);
    scope_stack[scope_stack.size()-1].table[name] = STE{ operand, dimension };
    return ir::Operand(get_scoped_name(operand.name), operand.type);
}

ir::Operand frontend::SymbolTable::add_temp(ir::Type t){
    std::string tname = "t" + std::to_string(scope_stack[scope_stack.size()-1].cnt++);
    auto operand = Operand(get_scoped_name(tname), t);
    return operand;
}

void frontend::SymbolTable::add_const(std::string name, vector<int> dimension, void* v, ir::Type t){
    assert(scope_stack[scope_stack.size()-1].const_table.find(name) == scope_stack[scope_stack.size()-1].const_table.end());
    scope_stack[scope_stack.size()-1].const_table[name] = frontend::ConstOperand(v, t, dimension);
}

frontend::ConstOperand frontend::SymbolTable::get_const(std::string name){
    int index = scope_stack.size()-1;

    while (index >=0)
    {
        if(scope_stack[index].const_table.find(name) != scope_stack[index].const_table.end()) 
            return scope_stack[index].const_table.at(name);
        index--;
    }
    return frontend::ConstOperand();
}

frontend::ConstOperand frontend::SymbolTable::get_const_inscope(string name) {
    assert(scope_stack.size()>0);

    int index = scope_stack.size() - 1;

    if(scope_stack[index].const_table.find(name) != scope_stack[index].const_table.end()) 
        return scope_stack[index].const_table.at(name);

    return frontend::ConstOperand();
}

frontend::Analyzer::Analyzer(): tmp_cnt(0), symbol_table() {
    prog = new ir::Program();
    auto sys_func = get_lib_funcs();
    for(auto x: *sys_func) symbol_table.functions[x.first] = x.second;

    symbol_table.add_scope("global");
    curr_function = new Function("global",ir::Type::null);
    symbol_table.functions["global"] = curr_function;

    symbol_table.zero = symbol_table.add_ste("zero",vector<int>(), Type::Int);
    symbol_table.fzero = symbol_table.add_ste("fzero",vector<int>(), Type::Float);
    symbol_table.one = symbol_table.add_ste("one",vector<int>(), Type::Int);
    // prog->addGlobalVal(symbol_table.zero, 0);
    // prog->addGlobalVal(symbol_table.fzero, 0);
    // prog->addGlobalVal(symbol_table.one, 0);
    prog->globalVal.push_back(ir::GlobalVal(symbol_table.zero, 0));
    prog->globalVal.push_back(ir::GlobalVal(symbol_table.fzero, 0));
    prog->globalVal.push_back(ir::GlobalVal(symbol_table.one, 0));

    ir::Instruction* instr;
    instr = new ir::Instruction(ir::Operand("0", Type::IntLiteral), ir::Operand(), symbol_table.zero, ir::Operator::def);
    COMMIT_INSTR(instr);
    instr = new ir::Instruction(ir::Operand("0", Type::FloatLiteral), ir::Operand(), symbol_table.fzero, ir::Operator::fdef);
    COMMIT_INSTR(instr);
    instr = new ir::Instruction(ir::Operand("1", Type::IntLiteral), ir::Operand(), symbol_table.one, ir::Operator::def);
    COMMIT_INSTR(instr);
}

ir::Program frontend::Analyzer::get_ir_program(CompUnit* root) {
    transCompUnit(root, nullptr);
    assert(symbol_table.functions.find("global") != symbol_table.functions.end());
    auto global_func = symbol_table.functions["global"];
    global_func->addInst(new ir::Instruction(ir::Operand(), ir::Operand(), ir::Operand(), ir::Operator::_return));
    prog->addFunction(*global_func);

    // auto main_iter = symbol_table.functions.find("main");
    // auto mainp = main_iter->second;
    // if(main_iter != symbol_table.functions.end()){
        
    //     if(mainp->InstVec.size() == 0 || mainp->InstVec[mainp->InstVec.size() - 1]->op != ir::Operator::_return){
    //         ir::Instruction* instr = new ir::Instruction(ir::Operand("0", Type::IntLiteral), ir::Operand(), ir::Operand(), ir::Operator::_return);
    //         mainp->addInst(instr);
    //     }
    // }
    // prog->addFunction(*mainp);
    
    return *prog;
}

void frontend::Analyzer::transCompUnit(CompUnit* root, AstNode* p) {
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"CompUnit"<<std::endl;
    #endif
    assert(root->children.size() >= 1);
    assert(root->children[0]->type == NodeType::DECL || root->children[0]->type == NodeType::FUNCDEF);
    
    /**
     * @brief CompUnit -> Decl
     * 
     */
    if(root->children[0]->type == NodeType::DECL){
        curr_function = symbol_table.functions["global"];
        auto child = CVT_POINT(root->children[0], Decl);
        transDecl( child, root );
    }

    /**
     * @brief CompUnit -> FuncDef
     * 
     */
    else if(root->children[0]->type == NodeType::FUNCDEF){
        auto child = CVT_POINT(root->children[0], FuncDef);
        transFuncDef(child, root);
        if(curr_function->InstVec.size() == 0  || curr_function->InstVec[curr_function->InstVec.size() - 1]->op != ir::Operator::_return){
            switch (curr_function->returnType)
            {
                case Type::Int:{
                    ir::Instruction* instr = new ir::Instruction(symbol_table.zero, ir::Operand(), ir::Operand(), ir::Operator::_return);
                    COMMIT_INSTR(instr);
                    break;
                }
                case Type::Float:{
                    ir::Instruction* instr = new ir::Instruction(symbol_table.fzero, ir::Operand(), ir::Operand(), ir::Operator::_return);
                    COMMIT_INSTR(instr);
                    break;
                }
                case Type::null:{
                    ir::Instruction* instr = new ir::Instruction(ir::Operand(), ir::Operand(), ir::Operand(), ir::Operator::_return);
                    COMMIT_INSTR(instr);
                    break;
                }
                default: assert(0);
            }
        }
        prog->addFunction(*curr_function);
    }
    else assert(0);

    /**
     * @brief CompUnit -> [Any] CompUnit
     * 
     */
    if(root->children.size() == 2){
        transCompUnit( CVT_POINT(root->children[1], CompUnit), root);
    }
}

void frontend::Analyzer::transDecl(Decl * root, AstNode* p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"Decl"<<std::endl;
    #endif
    assert(root->children.size() == 1);

    if(root->children[0]->type == NodeType::CONSTDECL){
        root->is_const = true;

        auto child = CVT_POINT(root->children[0], ConstDecl);
        transConstDecl( child, root);

        root->decl_vars = child->decl_vars;
        root->t = child->t;
    }
    else if(root->children[0]->type == NodeType::VARDECL){
        root->is_const = false;

        auto child = CVT_POINT(root->children[0], VarDecl);
        transVarDecl( child, root );

        root->decl_vars = child->decl_vars;
        root->t = child->t;
    }
    else assert(0);
}

void frontend::Analyzer::transFuncDef(FuncDef * root, AstNode * p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"FuncDef"<<std::endl;
    #endif
    assert(root->children.size() >= 5);
    assert(root->children[0]->type == NodeType::FUNCTYPE);
    assert(root->children[1]->type == NodeType::TERMINAL && CVT_POINT(root->children[1], Term)->token.type == TokenType::IDENFR );
    assert(root->children[2]->type == NodeType::TERMINAL && CVT_POINT(root->children[2], Term)->token.type == TokenType::LPARENT );

    FuncType* functype_child = CVT_POINT(root->children[0], FuncType);
    transFuncType(functype_child, root);
    Term* ident_child = CVT_POINT(root->children[1], Term);

    symbol_table.add_scope("Block" + std::to_string(tmp_cnt++));

    if(root->children[3]->type == NodeType::FUNCFPARAMS){
        FuncFParams* params_child = CVT_POINT(root->children[3], FuncFParams);
        transFuncFParams(params_child, root);
    
        curr_function = new ir::Function(ident_child->token.value, params_child->params, functype_child->t);
        assert(symbol_table.functions.find(curr_function->name) == symbol_table.functions.end());
        symbol_table.functions[curr_function->name] = curr_function;
        if( curr_function->name == "main"){
            ir::Operand t = symbol_table.add_temp(Type::null);
            ir::Instruction* instr = new ir::CallInst(ir::Operand("global", Type::null), vector<Operand>(), t);
            COMMIT_INSTR(instr);
        }

        assert(root->children[4]->type == NodeType::TERMINAL && CVT_POINT(root->children[4], Term)->token.type == TokenType::RPARENT);
        assert(root->children[5]->type == NodeType::BLOCK);

        Block* block_child = CVT_POINT(root->children[5], Block);
        transBlock(block_child, root);
    }
    else{
        assert(root->children[3]->type == NodeType::TERMINAL && CVT_POINT(root->children[3], Term)->token.type == TokenType::RPARENT);
        assert(root->children[4]->type == NodeType::BLOCK);

        curr_function = new ir::Function(ident_child->token.value, functype_child->t);
        assert(symbol_table.functions.find(curr_function->name) == symbol_table.functions.end());
        symbol_table.functions[curr_function->name] = curr_function;
        if( curr_function->name == "main"){
            ir::Operand t = symbol_table.add_temp(Type::null);
            ir::Instruction* instr = new ir::CallInst(ir::Operand("global", Type::null), vector<Operand>(), t);
            COMMIT_INSTR(instr);
        }

        Block* block_child = CVT_POINT(root->children[4], Block);
        transBlock(block_child, root);
    }  

    // symbol_table.exit_scope();
}


void frontend::Analyzer::transBlock(Block * root, AstNode * p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"Block"<<std::endl;
    #endif
    assert(root->children.size() >= 2);
    assert(root->children[0]->type == NodeType::TERMINAL && CVT_POINT(root->children[0], Term)->token.type == TokenType::LBRACE );

    if(p->type != NodeType::FUNCDEF) symbol_table.add_scope("Block" + std::to_string(tmp_cnt++));
    // TODO;

    int index = 1;
    while(root->children[index]->type == NodeType::BLOCKITEM){
        BlockItem* blockitem = CVT_POINT(root->children[index], BlockItem);
        transBlockItem(blockitem, root);     
        index++;
    }
    assert(root->children[index]->type == NodeType::TERMINAL && CVT_POINT(root->children[index], Term)->token.type == TokenType::RBRACE );

    symbol_table.exit_scope();
}

void frontend::Analyzer::transBlockItem(BlockItem * root, AstNode * p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"BlockItem"<<std::endl;
    #endif
    assert(root->children.size() == 1);

    if(root->children[0]->type == NodeType::DECL){
        Decl* decl_child = CVT_POINT(root->children[0], Decl);
        transDecl(decl_child, root);
    }
    else if(root->children[0]->type == NodeType::STMT){
        Stmt* stmt_child = CVT_POINT(root->children[0], Stmt);
        transStmt(stmt_child, root);
    }
    else assert(0);
}


void frontend::Analyzer::transConstDecl(ConstDecl * root, AstNode* p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"ConstDecl"<<std::endl;
    #endif
    assert(root->children.size()>=3);
    assert(root->children[0]->type == NodeType::TERMINAL && CVT_POINT(root->children[0], Term)->token.type == TokenType::CONSTTK);
    assert(root->children[1]->type == NodeType::BTYPE);
    assert(root->children[2]->type == NodeType::CONSTDEF);

    BType* btype_child;
    ConstDef* constdef_child;

    btype_child = CVT_POINT(root->children[1],BType);
    transBType( btype_child, root->children[1] );
    root->t = btype_child->t;

    int index = 2;
    while (root->children[index]->type == NodeType::CONSTDEF)
    {
        constdef_child = CVT_POINT(root->children[index], ConstDef);
        transConstDef(constdef_child, root);
        
        if(root->children[index+1]->type == NodeType::TERMINAL && ((Term*)root->children[index+1])->token.type == TokenType::COMMA) index += 2;
        else break;
    }
    
    assert(root->children[index+1]->type == NodeType::TERMINAL && ((Term*)root->children[index+1])->token.type == TokenType::SEMICN);
}


void frontend::Analyzer::transBType(BType* root, AstNode* p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"BType"<<std::endl;
    #endif
    assert(root->children.size()==1);

    Term* term_child = CVT_POINT(root->children[0], Term);

    if(term_child->token.type == TokenType::INTTK) root->t = Type::Int;
    else if(term_child->token.type == TokenType::FLOATTK) root->t = Type::Float;
    else assert(0);
}

void frontend::Analyzer::transFuncType(FuncType* root, AstNode* p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"FuncType"<<std::endl;
    #endif
    assert(root->children.size()==1);

    Term* term_child = CVT_POINT(root->children[0], Term);
    if(term_child->token.type == TokenType::INTTK) root->t = Type::Int;
    else if(term_child->token.type == TokenType::FLOATTK) root->t = Type::Float;
    else if(term_child->token.type == TokenType::VOIDTK) root->t = Type::null;
    else assert(0);
}


void frontend::Analyzer::transConstDef(ConstDef * root, AstNode * p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"ConstDef"<<std::endl;
    #endif
    assert(root->children.size()>=3);

    /**
     * @brief check Ident
     * 
     */
    Term* ident_child;
    assert(root->children[0]->type == NodeType::TERMINAL && CVT_POINT(root->children[0], Term)->token.type ==TokenType::IDENFR );
    ident_child = CVT_POINT(root->children[0], Term);
    root->arr_name = ident_child->token.value;
    frontend::ConstOperand operand = symbol_table.get_const_inscope(root->arr_name);
    assert(operand.isNull());

    /**
     * @brief calculate dimension
     * 
     */
    ConstExp* constexp_child;
    vector<int>dimension;
    int maxlen = 1;
    int index = 1;
    while(root->children[index]->type == NodeType::TERMINAL && 
        CVT_POINT(root->children[index], Term)->token.type == TokenType::LBRACK){

        assert(root->children[index+1]->type == NodeType::CONSTEXP);
        assert(root->children[index+2]->type == NodeType::TERMINAL && CVT_POINT(root->children[index+2], Term)->token.type == TokenType::RBRACK);

        constexp_child = CVT_POINT(root->children[index+1], ConstExp);
        transConstExp(constexp_child, root);
        assert(constexp_child->t == Type::IntLiteral);
        int dim = std::stoi(constexp_child->v, 0, 10);
        maxlen *= dim;
        dimension.push_back(dim);

        index += 3;
    }

    /**
     * @brief get type
     * 
     */
    Type t;
    assert(CVT_POINT(p, ConstDecl)->t == Type::Int || CVT_POINT(p, ConstDecl)->t == Type::Float);
    t = CVT_POINT(p, ConstDecl)->t;
    if(CVT_POINT(p, ConstDecl)->t == Type::Int){
        if(maxlen == 1) t = Type::IntLiteral;
        else t = Type::IntPtr;
    }   
    else{
        if(maxlen == 1) t = Type::FloatLiteral;
        else t = Type::FloatPtr;
    }

    /**
     * @brief get init val
     * 
     */
    assert(root->children[index]->type == NodeType::TERMINAL &&  CVT_POINT(root->children[index], Term)->token.type == TokenType::ASSIGN);
    index++;
    assert(root->children[index]->type == NodeType::CONSTINITVAL);
    ConstInitVal* constinitval_child = CVT_POINT(root->children[index], ConstInitVal);
    transConstInitVal(constinitval_child, root);

    
    /**
     * @brief single const
     * 
     */
    if(t == Type::IntLiteral || t == Type::FloatLiteral){
        assert(constinitval_child->v.size() == 1);
        assert(constinitval_child->v[0].type == Type::IntLiteral || constinitval_child->v[0].type == Type::FloatLiteral);
        void* value;
        switch (t)
        {
            case Type::IntLiteral:{
                value = constinitval_child->v[0].type == Type::IntLiteral ? ((void *) new int(value2int(constinitval_child->v[0].name)) )
                    : ((void *) new int(int(value2float(constinitval_child->v[0].name))));
                break;
            }
            case Type::FloatLiteral:{
                value = constinitval_child->v[0].type == Type::IntLiteral ? ((void *) new double(float(value2int(constinitval_child->v[0].name))) )
                    : ((void *) new double(value2float(constinitval_child->v[0].name)));
                break;
            }
            default: assert(0);
        }
        
        symbol_table.add_const(root->arr_name, vector<int>(), value, t);
    }

    /**
     * @brief array
     * 
     */
    else{
        assert(constinitval_child->v.size() <= maxlen);
        ir::Instruction* instr;
        ir::Operand operand = symbol_table.add_ste(root->arr_name, dimension, t);
        if(curr_function->name == "global"){
            // prog->addGlobalVal(operand, maxlen);
            prog->globalVal.push_back(ir::GlobalVal(operand, maxlen));
        } 
        if(curr_function->name != "global"){
            instr = new ir::Instruction(ir::Operand(std::to_string(maxlen), Type::IntLiteral), ir::Operand(), operand, ir::Operator::alloc);
            COMMIT_INSTR(instr);
        }
        for(int i = 0; i < maxlen; i++){
            if(i < constinitval_child->v.size()){
                switch (t)
                {
                    case Type::IntPtr:{
                        switch (constinitval_child->v[i].type)
                        {
                            case Type::IntLiteral:{
                                ir::Operand temp = symbol_table.add_temp(Type::Int);
                                instr = new ir::Instruction(ir::Operand(constinitval_child->v[i].name, constinitval_child->v[i].type), ir::Operand(), temp, ir::Operator::def);
                                COMMIT_INSTR(instr);
                                instr = new ir::Instruction(ir::Operand(operand.name, operand.type), ir::Operand(std::to_string(i), Type::IntLiteral), temp, ir::Operator::store);
                                COMMIT_INSTR(instr);
                                break;
                            }
                            case Type::FloatLiteral:{
                                ir::Operand temp = symbol_table.add_temp(Type::Int);
                                instr = new ir::Instruction(ir::Operand( std::to_string(int(value2float(constinitval_child->v[i].name))), Type::IntLiteral), 
                                        ir::Operand(), temp, ir::Operator::def);
                                COMMIT_INSTR(instr);
                                instr = new ir::Instruction(ir::Operand(operand.name, operand.type), ir::Operand(std::to_string(i), Type::IntLiteral), temp, ir::Operator::store);
                                COMMIT_INSTR(instr);
                                break;
                            }
                            default: assert(0);
                        }
                        break;
                    }
                    case Type::FloatPtr:{
                        switch (constinitval_child->v[i].type)
                        {
                            case Type::IntLiteral:{
                                ir::Operand temp = symbol_table.add_temp(Type::Float);
                                instr = new ir::Instruction(ir::Operand( std::to_string(float(value2int(constinitval_child->v[i].name))), Type::FloatLiteral), 
                                        ir::Operand(), temp, ir::Operator::fdef);
                                COMMIT_INSTR(instr);
                                instr = new ir::Instruction(ir::Operand(operand.name, operand.type), ir::Operand(std::to_string(i), Type::IntLiteral), temp, ir::Operator::store);
                                COMMIT_INSTR(instr);
                                break;
                            }
                            case Type::FloatLiteral:{
                                ir::Operand temp = symbol_table.add_temp(Type::Float);
                                instr = new ir::Instruction(ir::Operand(constinitval_child->v[i].name, constinitval_child->v[i].type), ir::Operand(), temp, ir::Operator::fdef);
                                COMMIT_INSTR(instr);
                                instr = new ir::Instruction(ir::Operand(operand.name, operand.type), ir::Operand(std::to_string(i), Type::IntLiteral), temp, ir::Operator::store);
                                COMMIT_INSTR(instr);
                                break;
                            }
                            default: assert(0);
                        }
                        break;
                    }
                    default: assert(0);
                }
            }
            else{
                switch (t)
                {
                    case Type::IntPtr:{
                        instr = new ir::Instruction(ir::Operand(operand.name, operand.type), ir::Operand(std::to_string(i), Type::IntLiteral), symbol_table.zero, ir::Operator::store);
                        COMMIT_INSTR(instr);
                        break;
                    }
                    case Type::FloatPtr:{
                        instr = new ir::Instruction(ir::Operand(operand.name, operand.type), ir::Operand(std::to_string(i), Type::IntLiteral), symbol_table.fzero, ir::Operator::store);
                        COMMIT_INSTR(instr);
                        break;
                    }
                    default: assert(0);
                }
            }
        } 
    }
}


void frontend::Analyzer::transConstInitVal(ConstInitVal * root, AstNode* p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"ConstInitVal"<<std::endl;
    #endif

    /**
     * @brief ConstInitVal -> ConstExp
     * 
     */
    if(root->children.size() == 1 && root->children[0]->type == NodeType::CONSTEXP){       
        auto child = CVT_POINT(root->children[0], ConstExp);
        transConstExp(child, root);
        assert(child->t == Type::IntLiteral || child->t == Type::FloatLiteral);
        root->v.push_back( ir::Operand(child->v, child->t));
    }

    /**
     * @brief ConstInitVal -> { ConstInitVal, ConstInitVal ... }
     * 
     */
    else if(root->children.size() >= 2){
        assert(CVT_POINT(root->children[0], Term)->token.type == TokenType::LBRACE);

        int index = 1;
        while (root->children[index]->type == NodeType::CONSTINITVAL)
        {
            auto child = CVT_POINT(root->children[index], ConstInitVal);
            assert(child->children.size() == 1 && child->children[0]->type == NodeType::CONSTEXP );

            transConstInitVal( child , root);
            assert(child->v[0].type == Type::IntLiteral || child->v[0].type == Type::FloatLiteral);
            root->v.push_back(child->v[0]);
            if(root->children[index+1]->type == NodeType::TERMINAL && CVT_POINT(root->children[index+1], Term)->token.type == TokenType::COMMA) index += 2;
            else break;
        }
        assert(root->children[index+1]->type == NodeType::TERMINAL && CVT_POINT(root->children[index+1], Term)->token.type == TokenType::RBRACE);
    }
    else assert(0);
}

void frontend::Analyzer::transConstExp(ConstExp* root, AstNode* p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"ConstExp"<<std::endl;
    #endif
    assert(root->children.size() == 1 && root->children[0]->type == NodeType::ADDEXP);
    auto child = CVT_POINT(root->children[0], AddExp);
    transAddExp(child, root);
    assert(child->t ==  Type::FloatLiteral || child->t ==  Type::IntLiteral );
    root->v = child->v;
    root->t = child->t;
}

void frontend::Analyzer::transExp(Exp* root, AstNode* p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"Exp"<<std::endl;
    #endif
    assert(root->children.size() == 1);
    assert(root->children[0]->type == NodeType::ADDEXP);
    AddExp* addexp_child = CVT_POINT(root->children[0], AddExp);
    transAddExp(addexp_child, root);
    root->v = addexp_child->v;
    root->t = addexp_child->t;
}


void frontend::Analyzer::transAddExp(AddExp* root, AstNode* p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"AddExp"<<std::endl;
    #endif
    assert(root->children.size() >= 1);
    assert(root->children[0]->type == NodeType::MULEXP);
  
    MulExp* mulexp_child = CVT_POINT(root->children[0], MulExp);
    transMulExp( mulexp_child, root );

    ir::Operand t;
    ir::Instruction* instr;

    if(root->children.size() == 1){
        root->v = mulexp_child->v;
        root->t = mulexp_child->t;
        return;
    }

    // switch (mulexp_child->t)
    // {
    //     case Type::Int:{
    //         t = symbol_table.add_temp(mulexp_child->t);
    //         instr = new ir::Instruction(ir::Operand(mulexp_child->v, Type::Int), ir::Operand(), t, ir::Operator::mov);
    //         COMMIT_INSTR(instr);
    //         break;
    //     }
    //     case Type::IntLiteral:{
    //         t.name = mulexp_child->v;
    //         t.type = Type::IntLiteral;
    //         break;
    //     }
    //     case Type::Float:{
    //         t = symbol_table.add_temp(mulexp_child->t);
    //         instr = new ir::Instruction(ir::Operand(mulexp_child->v, Type::Float), ir::Operand(), t, ir::Operator::fmov);
    //         COMMIT_INSTR(instr);
    //         break;
    //     }
    //     case Type::FloatLiteral:{
    //         t.name = mulexp_child->v;
    //         t.type = Type::FloatLiteral;
    //         break;
    //     }
    //     default: assert(0);
    // }
    
    t.name = mulexp_child->v;
    t.type = mulexp_child->t;

    int index = 1;
    while ( index < root->children.size() && root->children[index]->type == NodeType::TERMINAL && (  CVT_POINT(root->children[index], Term)->token.type == TokenType::PLUS ||
        CVT_POINT(root->children[index], Term)->token.type == TokenType::MINU ) ){
        
        assert(root->children[index+1]->type == NodeType::MULEXP);
        mulexp_child = CVT_POINT(root->children[index+1], MulExp);
        transMulExp(mulexp_child, root);

        switch (t.type)
        {
            case Type::Int:{
                switch (mulexp_child->t)
                {
                    case Type::Int:{
                        auto t1 = symbol_table.add_temp(Type::Int);

                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::PLUS:{                               
                                instr = new ir::Instruction(t, ir::Operand(mulexp_child->v, Type::Int), t1, ir::Operator::add );
                                break;
                            }
                            case TokenType::MINU:{
                                instr = new ir::Instruction(t, ir::Operand(mulexp_child->v, Type::Int), t1, ir::Operator::sub );
                                break;
                            }
                            default: assert(0);
                        }

                        COMMIT_INSTR(instr);
                        t = t1;

                        break;
                    }
                    case Type::IntLiteral:{
                        auto t1 = symbol_table.add_temp(Type::Int);

                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::PLUS:{                               
                                instr = new ir::Instruction(t, ir::Operand(mulexp_child->v, Type::IntLiteral), t1, ir::Operator::addi );
                                break;
                            }
                            case TokenType::MINU:{
                                instr = new ir::Instruction(t, ir::Operand(mulexp_child->v, Type::IntLiteral), t1, ir::Operator::subi );
                                break;
                            }
                            default: assert(0);
                        }

                        COMMIT_INSTR(instr);
                        t = t1;

                        break;
                    }
                    case Type::Float:{
                        auto t1 = symbol_table.add_temp(Type::Float);
                        auto t2 = symbol_table.add_temp(Type::Float);

                        instr = new ir::Instruction( t, ir::Operand(), t2, ir::Operator::cvt_i2f );
                        COMMIT_INSTR(instr);
                        
                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::PLUS:{                               
                                instr = new ir::Instruction(t2, ir::Operand(mulexp_child->v, Type::Float), t1, ir::Operator::fadd );
                                break;
                            }
                            case TokenType::MINU:{
                                instr = new ir::Instruction(t2, ir::Operand(mulexp_child->v, Type::Float), t1, ir::Operator::fsub );
                                break;
                            }
                            default: assert(0);
                        }

                        COMMIT_INSTR(instr);
                        t = t1;

                        break;
                    }
                    case Type::FloatLiteral:{
                        auto t1 = symbol_table.add_temp(Type::Float);
                        auto t2 = symbol_table.add_temp(Type::Float);
                        auto t3 = symbol_table.add_temp(Type::Float);

                        instr = new ir::Instruction( t, ir::Operand(), t2, ir::Operator::cvt_i2f );
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction( ir::Operand(mulexp_child->v, Type::FloatLiteral), ir::Operand(), t3, ir::Operator::fdef );
                        COMMIT_INSTR(instr);

                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::PLUS:{                               
                                instr = new ir::Instruction(t2, t3, t1, ir::Operator::fadd );
                                break;
                            }
                            case TokenType::MINU:{
                                instr = new ir::Instruction(t2, t3, t1, ir::Operator::fsub );
                                break;
                            }
                            default: assert(0);
                        }

                        COMMIT_INSTR(instr);
                        t = t1;

                        break;
                    }
                    default: assert(0);
                }
                break;
            }
            case Type::IntLiteral:{
                switch (mulexp_child->t)
                {
                    case Type::Int:{
                        auto t1 = symbol_table.add_temp(Type::Int);
                        auto t2 = symbol_table.add_temp(Type::Int);

                        instr = new ir::Instruction( t, ir::Operand(), t2, ir::Operator::def );
                        COMMIT_INSTR(instr);

                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::PLUS:{                               
                                instr = new ir::Instruction(t2, ir::Operand(mulexp_child->v, Type::Int), t1, ir::Operator::add );
                                break;
                            }
                            case TokenType::MINU:{
                                instr = new ir::Instruction(t2, ir::Operand(mulexp_child->v, Type::Int), t1, ir::Operator::sub );
                                break;
                            }
                            default: assert(0);
                        }

                        COMMIT_INSTR(instr);
                        t = t1;

                        break;
                    }
                    case Type::IntLiteral:{
                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::PLUS:{                               
                                t.name = std::to_string( value2int(t.name) + value2int(mulexp_child->v) ) ;
                                break;
                            }
                            case TokenType::MINU:{
                                t.name = std::to_string( value2int(t.name) - value2int(mulexp_child->v) ) ;
                                break;
                            }
                            default: assert(0);
                        }
                        break;
                    }
                    case Type::Float:{
                        auto t1 = symbol_table.add_temp(Type::Float);
                        auto t2 = symbol_table.add_temp(Type::Int);
                        auto t3 = symbol_table.add_temp(Type::Float);

                        instr = new ir::Instruction( t, ir::Operand(), t2, ir::Operator::def );
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction( t2, ir::Operand(), t3, ir::Operator::cvt_i2f );
                        COMMIT_INSTR(instr);

                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::PLUS:{                               
                                instr = new ir::Instruction(t3, ir::Operand(mulexp_child->v, Type::Float), t1, ir::Operator::fadd );
                                break;
                            }
                            case TokenType::MINU:{
                                instr = new ir::Instruction(t3, ir::Operand(mulexp_child->v, Type::Float), t1, ir::Operator::fsub );
                                break;
                            }
                            default: assert(0);
                        }

                        COMMIT_INSTR(instr);
                        t = t1;

                        break;
                    }
                    case Type::FloatLiteral:{
                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::PLUS:{                               
                                t.name = std::to_string( value2int(t.name) + value2float(mulexp_child->v) ) ;
                                break;
                            }
                            case TokenType::MINU:{
                                t.name = std::to_string( value2int(t.name) - value2float(mulexp_child->v) ) ;
                                break;
                            }
                            default: assert(0);
                        }
                        break;
                    }
                    default: assert(0);
                }
                break;
            }
            case Type::Float:{
                switch (mulexp_child->t)
                {
                    case Type::Int:{
                        auto t1 = symbol_table.add_temp(Type::Float);
                        auto t2 = symbol_table.add_temp(Type::Float);

                        instr = new ir::Instruction( ir::Operand(mulexp_child->v, Type::Int), ir::Operand(), t2, ir::Operator::cvt_i2f );
                        COMMIT_INSTR(instr);

                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::PLUS:{                               
                                instr = new ir::Instruction(t, t2, t1, ir::Operator::fadd );
                                break;
                            }
                            case TokenType::MINU:{
                                instr = new ir::Instruction(t, t2, t1, ir::Operator::fsub );
                                break;
                            }
                            default: assert(0);
                        }

                        COMMIT_INSTR(instr);
                        t = t1;

                        break;
                    }
                    case Type::IntLiteral:{
                        auto t1 = symbol_table.add_temp(Type::Float);
                        auto t2 = symbol_table.add_temp(Type::Int);
                        auto t3 = symbol_table.add_temp(Type::Float);
                        
                        instr = new ir::Instruction( ir::Operand(mulexp_child->v, Type::IntLiteral), ir::Operand(), t2, ir::Operator::def );
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction( t2, ir::Operand(), t3, ir::Operator::cvt_i2f );
                        COMMIT_INSTR(instr);

                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::PLUS:{                               
                                instr = new ir::Instruction(t, t3, t1, ir::Operator::fadd );
                                break;
                            }
                            case TokenType::MINU:{
                                instr = new ir::Instruction(t, t3, t1, ir::Operator::fsub );
                                break;
                            }
                            default: assert(0);
                        }

                        COMMIT_INSTR(instr);
                        t = t1;

                        break;
                    }

                    case Type::Float:{
                        auto t1 = symbol_table.add_temp(Type::Float);

                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::PLUS:{                               
                                instr = new ir::Instruction(t, ir::Operand(mulexp_child->v, Type::Float), t1, ir::Operator::fadd );
                                break;
                            }
                            case TokenType::MINU:{
                                instr = new ir::Instruction(t, ir::Operand(mulexp_child->v, Type::Float), t1, ir::Operator::fsub );
                                break;
                            }
                            default: assert(0);
                        }

                        COMMIT_INSTR(instr);
                        t = t1;

                        break;
                    }
                    case Type::FloatLiteral:{
                        auto t1 = symbol_table.add_temp(Type::Float);
                        auto t2 = symbol_table.add_temp(Type::Float);

                        instr = new ir::Instruction( ir::Operand(mulexp_child->v, mulexp_child->t), ir::Operand(), t2, ir::Operator::fdef );
                        COMMIT_INSTR(instr);

                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::PLUS:{                               
                                instr = new ir::Instruction(t, t2, t1, ir::Operator::fadd );
                                break;
                            }
                            case TokenType::MINU:{
                                instr = new ir::Instruction(t, t2, t1, ir::Operator::fsub );
                                break;
                            }
                            default: assert(0);
                        }

                        COMMIT_INSTR(instr);
                        t = t1;

                        break;
                    }
                    default: assert(0);
                }
                break;
            }
            case Type::FloatLiteral:{
                switch (mulexp_child->t)
                {
                    case Type::Int:{
                        auto t1 = symbol_table.add_temp(Type::Float);
                        auto t2 = symbol_table.add_temp(Type::Float);
                        auto t3 = symbol_table.add_temp(Type::Float);

                        instr = new ir::Instruction( t, ir::Operand(), t2, ir::Operator::fdef );
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction( ir::Operand(mulexp_child->v, Type::Int), ir::Operand(), t3, ir::Operator::cvt_i2f );
                        COMMIT_INSTR(instr);

                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::PLUS:{                               
                                instr = new ir::Instruction(t2, t3, t1, ir::Operator::fadd );
                                break;
                            }
                            case TokenType::MINU:{
                                instr = new ir::Instruction(t1, t3, t1, ir::Operator::fsub );
                                break;
                            }
                            default: assert(0);
                        }

                        COMMIT_INSTR(instr);
                        t = t1;

                        break;
                    }
                    case Type::IntLiteral:{
                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::PLUS:{                               
                                t.name = std::to_string( value2float(t.name) + value2int(mulexp_child->v) ) ;
                                break;
                            }
                            case TokenType::MINU:{
                                t.name = std::to_string( value2float(t.name) - value2int(mulexp_child->v) ) ;
                                break;
                            }
                            default: assert(0);
                        }
                        break;
                    }
                    case Type::Float:{
                        auto t1 = symbol_table.add_temp(Type::Float);
                        auto t2 = symbol_table.add_temp(Type::Float);

                        instr = new ir::Instruction( t, ir::Operand(), t2, ir::Operator::fdef );
                        COMMIT_INSTR(instr);

                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::PLUS:{                               
                                instr = new ir::Instruction(t2, ir::Operand(mulexp_child->v, Type::Float), t1, ir::Operator::fadd );
                                break;
                            }
                            case TokenType::MINU:{
                                instr = new ir::Instruction(t2, ir::Operand(mulexp_child->v, Type::Float), t1, ir::Operator::fsub );
                                break;
                            }
                            default: assert(0);
                        }

                        COMMIT_INSTR(instr);
                        t = t1;

                        break;
                    }
                    case Type::FloatLiteral:{
                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::PLUS:{                               
                                t.name = std::to_string( value2float(t.name) + value2float(mulexp_child->v) ) ;
                                break;
                            }
                            case TokenType::MINU:{
                                t.name = std::to_string( value2float(t.name) - value2float(mulexp_child->v) ) ;
                                break;
                            }
                            default: assert(0);
                        }
                        break;
                    }
                    default: assert(0);
                }
                break;
            }
            default: assert(0);
        }
        index += 2;
    }
    root->v = t.name;
    root->t = t.type;
}



void frontend::Analyzer::transMulExp(MulExp* root, AstNode* p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"MulExp"<<std::endl;
    #endif

    assert(root->children.size() >= 1);
    assert(root->children[0]->type == NodeType::UNARYEXP);

    auto child = CVT_POINT(root->children[0], UnaryExp);
    transUnaryExp( child, root );
    
    ir::Operand t;
    ir::Instruction* instr;

    if(root->children.size() == 1){
        root->v = child->v;
        root->t = child->t;
        return;
    }

    // switch (child->t)
    // {
    //     case Type::Int:{
    //         t = symbol_table.add_temp(child->t );
    //         instr = new ir::Instruction(ir::Operand(child->v, Type::Int), ir::Operand(), t, ir::Operator::mov);
    //         COMMIT_INSTR(instr);
    //         break;
    //     }
    //     case Type::IntLiteral:{
    //         t.name = child->v;
    //         t.type = Type::IntLiteral;
    //         break;
    //     }
    //     case Type::Float:{
    //         t = symbol_table.add_temp(child->t );
    //         instr = new ir::Instruction(ir::Operand(child->v, Type::Float), ir::Operand(), t, ir::Operator::fmov);
    //         COMMIT_INSTR(instr);
    //         break;
    //     }
    //     case Type::FloatLiteral:{
    //         t.name = child->v;
    //         t.type = Type::FloatLiteral;
    //         break;
    //     }
    //     default: assert(0);
    // }

    t.name = child->v;
    t.type = child->t;

    int index = 1;
    while ( index < root->children.size() && root->children[index]->type == NodeType::TERMINAL && (  CVT_POINT(root->children[index], Term)->token.type == TokenType::MULT  ||
        CVT_POINT(root->children[index], Term)->token.type == TokenType::DIV || CVT_POINT(root->children[index], Term)->token.type == TokenType::MOD) ){
        
        assert(root->children[index+1]->type == NodeType::UNARYEXP);

        child = CVT_POINT(root->children[index+1], UnaryExp);
        transUnaryExp(child, root);

        switch (t.type)
        {
            case Type::Int:{
                switch (child->t)
                {
                    case Type::Int:{
                        auto t1 = symbol_table.add_temp(Type::Int);

                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::MULT:{                               
                                instr = new ir::Instruction(t, ir::Operand(child->v, Type::Int), t1, ir::Operator::mul );
                                break;
                            }
                            case TokenType::DIV:{
                                instr = new ir::Instruction(t, ir::Operand(child->v, Type::Int), t1, ir::Operator::div );
                                break;
                            }
                            case TokenType::MOD:{
                                instr = new ir::Instruction(t, ir::Operand(child->v, Type::Int), t1, ir::Operator::mod );
                                break;
                            }
                            default: assert(0);
                        }

                        COMMIT_INSTR(instr);
                        t = t1;

                        break;
                    }
                    case Type::IntLiteral:{
                        auto t1 = symbol_table.add_temp(Type::Int);
                        auto t2 = symbol_table.add_temp(Type::Int);

                        instr = new ir::Instruction( ir::Operand(child->v, Type::IntLiteral), ir::Operand(), t2, ir::Operator::def );
                        COMMIT_INSTR(instr);

                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::MULT:{                               
                                instr = new ir::Instruction(t, t2, t1, ir::Operator::mul );
                                break;
                            }
                            case TokenType::DIV:{
                                instr = new ir::Instruction(t, t2, t1, ir::Operator::div );
                                break;
                            }
                            case TokenType::MOD:{
                                instr = new ir::Instruction(t, t2, t1, ir::Operator::mod );
                                break;
                            }
                            default: assert(0);
                        }

                        COMMIT_INSTR(instr);
                        t = t1;

                        break;
                    }
                    case Type::Float:{
                        auto t1 = symbol_table.add_temp(Type::Float);
                        auto t2 = symbol_table.add_temp(Type::Float);

                        instr = new ir::Instruction( t, ir::Operand(), t2, ir::Operator::cvt_i2f );
                        COMMIT_INSTR(instr);
                        
                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::MULT:{                               
                                instr = new ir::Instruction(t2, ir::Operand(child->v, Type::Float), t1, ir::Operator::fmul );
                                break;
                            }
                            case TokenType::DIV:{
                                instr = new ir::Instruction(t2, ir::Operand(child->v, Type::Float), t1, ir::Operator::fdiv );
                                break;
                            }
                            case TokenType::MOD:{
                                assert(0);
                                break;
                            }
                            default: assert(0);
                        }

                        COMMIT_INSTR(instr);
                        t = t1;

                        break;
                    }
                    case Type::FloatLiteral:{
                        auto t1 = symbol_table.add_temp(Type::Float);
                        auto t2 = symbol_table.add_temp(Type::Float);
                        auto t3 = symbol_table.add_temp(Type::Float);

                        instr = new ir::Instruction( t, ir::Operand(), t2, ir::Operator::cvt_i2f );
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction( ir::Operand(child->v, Type::FloatLiteral), ir::Operand(), t3, ir::Operator::fdef );
                        COMMIT_INSTR(instr);

                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::MULT:{                               
                                instr = new ir::Instruction(t2, t3, t1, ir::Operator::fmul );
                                break;
                            }
                            case TokenType::DIV:{
                                instr = new ir::Instruction(t2, t3, t1, ir::Operator::fdiv );
                                break;
                            }
                            case TokenType::MOD:{
                                assert(0);
                                break;
                            }
                            default: assert(0);
                        }

                        COMMIT_INSTR(instr);
                        t = t1;

                        break;
                    }
                    default: assert(0);
                }
                break;
            }
            case Type::IntLiteral:{
                switch (child->t)
                {
                    case Type::Int:{
                        auto t1 = symbol_table.add_temp(Type::Int);
                        auto t2 = symbol_table.add_temp(Type::Int);

                        instr = new ir::Instruction( t, ir::Operand(), t2, ir::Operator::def );
                        COMMIT_INSTR(instr);

                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::MULT:{                               
                                instr = new ir::Instruction(t2, ir::Operand(child->v, Type::Int), t1, ir::Operator::mul );
                                break;
                            }
                            case TokenType::DIV:{
                                instr = new ir::Instruction(t2, ir::Operand(child->v, Type::Int), t1, ir::Operator::div );
                                break;
                            }
                            case TokenType::MOD:{
                                instr = new ir::Instruction(t2, ir::Operand(child->v, Type::Int), t1, ir::Operator::mod );
                                break;
                            }
                            default: assert(0);
                        }

                        COMMIT_INSTR(instr);
                        t = t1;

                        break;
                    }
                    case Type::IntLiteral:{
                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::MULT:{                               
                                t.name = std::to_string( value2int(t.name) * value2int(child->v) ) ;
                                break;
                            }
                            case TokenType::DIV:{
                                t.name = std::to_string( value2int(t.name) / value2int(child->v) ) ;
                                break;
                            }
                            case TokenType::MOD:{
                                t.name = std::to_string( value2int(t.name) % value2int(child->v) ) ;
                                break;
                            }
                            default: assert(0);
                        }
                        break;
                    }
                    case Type::Float:{
                        auto t1 = symbol_table.add_temp(Type::Float);
                        auto t2 = symbol_table.add_temp(Type::Int);
                        auto t3 = symbol_table.add_temp(Type::Float);

                        instr = new ir::Instruction( t, ir::Operand(), t2, ir::Operator::def );
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction( t2, ir::Operand(), t3, ir::Operator::cvt_i2f );
                        COMMIT_INSTR(instr);

                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::MULT:{                               
                                instr = new ir::Instruction(t3, ir::Operand(child->v, Type::Float), t1, ir::Operator::fmul );
                                break;
                            }
                            case TokenType::DIV:{
                                instr = new ir::Instruction(t3, ir::Operand(child->v, Type::Float), t1, ir::Operator::fdiv );
                                break;
                            }
                            case TokenType::MOD:{
                                assert(0);
                                break;
                            }
                            default: assert(0);
                        }

                        COMMIT_INSTR(instr);
                        t = t1;

                        break;
                    }
                    case Type::FloatLiteral:{
                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::MULT:{                               
                                t.name = std::to_string( value2int(t.name) * value2float(child->v) ) ;
                                t.type = Type::FloatLiteral;
                                break;
                            }
                            case TokenType::DIV:{
                                t.name = std::to_string( value2int(t.name) / value2float(child->v) ) ;
                                t.type = Type::FloatLiteral;
                                break;
                            }
                            case TokenType::MOD:{
                                assert(0);
                                break;
                            }
                            default: assert(0);
                        }
                        break;
                    }
                    default: assert(0);
                }
                break;
            }
            case Type::Float:{
                switch (child->t)
                {
                    case Type::Int:{
                        auto t1 = symbol_table.add_temp(Type::Float);
                        auto t2 = symbol_table.add_temp(Type::Float);

                        instr = new ir::Instruction( ir::Operand(child->v, Type::Int), ir::Operand(), t2, ir::Operator::cvt_i2f );
                        COMMIT_INSTR(instr);

                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::MULT:{                               
                                instr = new ir::Instruction(t, t2, t1, ir::Operator::fmul );
                                break;
                            }
                            case TokenType::DIV:{
                                instr = new ir::Instruction(t, t2, t1, ir::Operator::fdiv );
                                break;
                            }
                            case TokenType::MOD:{
                                assert(0);
                                break;
                            }
                            default: assert(0);
                        }

                        COMMIT_INSTR(instr);
                        t = t1;

                        break;
                    }
                    case Type::IntLiteral:{
                        auto t1 = symbol_table.add_temp(Type::Float);
                        auto t2 = symbol_table.add_temp(Type::Int);
                        auto t3 = symbol_table.add_temp(Type::Float);
                        
                        instr = new ir::Instruction( ir::Operand(child->v, Type::IntLiteral), ir::Operand(), t2, ir::Operator::def );
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction( t2, ir::Operand(), t3, ir::Operator::cvt_i2f );
                        COMMIT_INSTR(instr);

                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::MULT:{                               
                                instr = new ir::Instruction(t, t3, t1, ir::Operator::fmul );
                                break;
                            }
                            case TokenType::DIV:{
                                instr = new ir::Instruction(t, t3, t1, ir::Operator::fdiv );
                                break;
                            }
                            case TokenType::MOD:{
                                assert(0);
                                break;
                            }
                            default: assert(0);
                        }

                        COMMIT_INSTR(instr);
                        t = t1;

                        break;
                    }
                    case Type::Float:{
                        auto t1 = symbol_table.add_temp(Type::Float);

                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::MULT:{                               
                                instr = new ir::Instruction(t, ir::Operand(child->v, Type::Float), t1, ir::Operator::fmul );
                                break;
                            }
                            case TokenType::DIV:{
                                instr = new ir::Instruction(t, ir::Operand(child->v, Type::Float), t1, ir::Operator::fdiv );
                                break;
                            }
                            case TokenType::MOD:{
                                assert(0);
                                break;
                            }
                            default: assert(0);
                        }

                        COMMIT_INSTR(instr);
                        t = t1;

                        break;
                    }
                    case Type::FloatLiteral:{
                        auto t1 = symbol_table.add_temp(Type::Float);
                        auto t2 = symbol_table.add_temp(Type::Float);

                        instr = new ir::Instruction( ir::Operand(child->v, child->t), ir::Operand(), t2, ir::Operator::fdef );
                        COMMIT_INSTR(instr);

                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::MULT:{                               
                                instr = new ir::Instruction(t, t2, t1, ir::Operator::fmul );
                                break;
                            }
                            case TokenType::DIV:{
                                instr = new ir::Instruction(t, t2, t1, ir::Operator::fdiv );
                                break;
                            }
                            case TokenType::MOD:{
                                assert(0);
                                break;
                            }
                            default: assert(0);
                        }

                        COMMIT_INSTR(instr);
                        t = t1;

                        break;
                    }
                    default: assert(0);
                }
                break;
            }
            case Type::FloatLiteral:{
                switch (child->t)
                {
                    case Type::Int:{
                        auto t1 = symbol_table.add_temp(Type::Float);
                        auto t2 = symbol_table.add_temp(Type::Float);
                        auto t3 = symbol_table.add_temp(Type::Float);

                        instr = new ir::Instruction( t, ir::Operand(), t2, ir::Operator::fdef );
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction( ir::Operand(child->v, Type::Int), ir::Operand(), t3, ir::Operator::cvt_i2f );
                        COMMIT_INSTR(instr);

                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::MULT:{                               
                                instr = new ir::Instruction(t2, t3, t1, ir::Operator::fmul );
                                break;
                            }
                            case TokenType::DIV:{
                                instr = new ir::Instruction(t2, t3, t1, ir::Operator::fdiv );
                                break;
                            }
                            case TokenType::MOD:{
                                assert(0);
                                break;
                            }
                            default: assert(0);
                        }

                        COMMIT_INSTR(instr);
                        t = t1;

                        break;
                    }
                    case Type::IntLiteral:{
                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::MULT:{                               
                                t.name = std::to_string( value2float(t.name) * value2int(child->v) ) ;
                                break;
                            }
                            case TokenType::DIV:{
                                t.name = std::to_string( value2float(t.name) / value2int(child->v) ) ;
                                break;
                            }
                            case TokenType::MOD:{
                                assert(0);
                                break;
                            }
                            default: assert(0);
                        }
                        break;
                    }
                    case Type::Float:{
                        auto t1 = symbol_table.add_temp(Type::Float);
                        auto t2 = symbol_table.add_temp(Type::Float);

                        instr = new ir::Instruction( t, ir::Operand(), t2, ir::Operator::fdef );
                        COMMIT_INSTR(instr);

                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::MULT:{                               
                                instr = new ir::Instruction(t2, ir::Operand(child->v, Type::Float), t1, ir::Operator::fmul );
                                break;
                            }
                            case TokenType::DIV:{
                                instr = new ir::Instruction(t2, ir::Operand(child->v, Type::Float), t1, ir::Operator::fdiv );
                                break;
                            }
                            case TokenType::MOD:{
                                assert(0);
                                break;
                            }
                            default: assert(0);
                        }

                        COMMIT_INSTR(instr);
                        t = t1;

                        break;
                    }
                    case Type::FloatLiteral:{
                        switch (CVT_POINT(root->children[index], Term)->token.type)
                        {
                            case TokenType::MULT:{                               
                                t.name = std::to_string( value2float(t.name) * value2float(child->v) ) ;
                                break;
                            }
                            case TokenType::DIV:{
                                t.name = std::to_string( value2float(t.name) / value2float(child->v) ) ;
                                break;
                            }
                            case TokenType::MOD:{
                                assert(0);
                                break;
                            }
                            default: assert(0);
                        }
                        break;
                    }
                    default: assert(0);
                }
                break;
            }
            default: assert(0);
        }

        index += 2;
    }

    root->v = t.name;
    root->t = t.type;

}



void frontend::Analyzer::transUnaryExp(UnaryExp* root, AstNode* p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"UnaryExp"<<std::endl;
    #endif
    assert(root->children.size() >= 1);

    PrimaryExp* primaryexp_child;
    Term* ident_child;
    FuncRParams* funcrparams_child = nullptr;
    UnaryOp* unaryop_child;
    UnaryExp* unaryexp_child;

    /**
     * @brief UnaryExp -> PrimaryExp
     * 
     */
    if(root->children[0]->type == NodeType::PRIMARYEXP){
        assert(root->children.size() == 1);

        primaryexp_child = CVT_POINT(root->children[0], PrimaryExp);
        transPrimaryExp(primaryexp_child, root);

        root->v = primaryexp_child->v;
        root->t = primaryexp_child->t;
        
    }

    /**
     * @brief UnaryExp -> Ident (FuncRParams)
     * 
     */
    else if(root->children[0]->type == NodeType::TERMINAL && CVT_POINT(root->children[0], Term)->token.type == TokenType::IDENFR){
        
        ident_child = CVT_POINT(root->children[0],Term);
        assert(root->children[1]->type == NodeType::TERMINAL && CVT_POINT(root->children[1], Term)->token.type == TokenType::LPARENT);

        if(root->children[2]->type == NodeType::FUNCRPARAMS){
            funcrparams_child = CVT_POINT(root->children[2], FuncRParams);
            transFuncRParams(funcrparams_child, root);
            assert(root->children[3]->type == NodeType::TERMINAL && CVT_POINT(root->children[3], Term)->token.type == TokenType::RPARENT);
        }
        else assert(root->children[2]->type == NodeType::TERMINAL && CVT_POINT(root->children[2], Term)->token.type == TokenType::RPARENT);
        
        assert(symbol_table.functions.find(ident_child->token.value) != symbol_table.functions.end());
        ir::Function* function = symbol_table.functions[ident_child->token.value];
        
        ir::Operand operand = symbol_table.add_temp(function->returnType);
        
        ir::CallInst* instr;
        if(funcrparams_child == nullptr){
            instr = new ir::CallInst(ir::Operand(function->name, Type::null), operand);
            COMMIT_INSTR(instr);
        }
        else{
            vector<Operand> params;
            assert(funcrparams_child->params.size() == function->ParameterList.size());

            for (int i = 0; i < funcrparams_child->params.size(); i++){
                if(funcrparams_child->params[i].type == function->ParameterList[i].type) params.push_back(funcrparams_child->params[i]);
                else{
                    switch (function->ParameterList[i].type)
                    {
                        case Type::Int:{
                            switch (funcrparams_child->params[i].type)
                            {
                                case Type::Int:{
                                    params.push_back(funcrparams_child->params[i]);
                                    break;
                                }
                                case Type::IntLiteral:{
                                    ir::Operand temp = symbol_table.add_temp(Type::Int);
                                    ir::Instruction* inst = new ir::Instruction(ir::Operand(funcrparams_child->params[i].name, 
                                        funcrparams_child->params[i].type), ir::Operand(), temp, ir::Operator::def);
                                    COMMIT_INSTR(inst);
                                    params.push_back(temp);
                                    break;
                                }
                                case Type::Float:{
                                    ir::Operand temp = symbol_table.add_temp(Type::Int);
                                    ir::Instruction* inst = new ir::Instruction(ir::Operand(funcrparams_child->params[i].name, 
                                        funcrparams_child->params[i].type), ir::Operand(), temp, ir::Operator::cvt_f2i);
                                    COMMIT_INSTR(inst);
                                    params.push_back(temp);
                                    break;
                                }
                                case Type::FloatLiteral:{
                                    ir::Operand temp = symbol_table.add_temp(Type::Int);
                                    ir::Instruction* inst = new ir::Instruction(ir::Operand(std::to_string(int(value2float(funcrparams_child->params[i].name))), 
                                        Type::IntLiteral), ir::Operand(), temp, ir::Operator::def);
                                    COMMIT_INSTR(inst);
                                    params.push_back(temp);
                                    break;
                                }
                                default: assert(0);
                            }
                            break;
                        }
                        case Type::Float:{
                            switch (funcrparams_child->params[i].type)
                            {
                                case Type::Int:{
                                    ir::Operand temp = symbol_table.add_temp(Type::Float);
                                    ir::Instruction* inst = new ir::Instruction(ir::Operand(funcrparams_child->params[i].name, 
                                        funcrparams_child->params[i].type), ir::Operand(), temp, ir::Operator::cvt_i2f);
                                    COMMIT_INSTR(inst);
                                    params.push_back(temp);
                                    break;
                                }
                                case Type::IntLiteral:{
                                    ir::Operand temp = symbol_table.add_temp(Type::Float);
                                    ir::Instruction* inst = new ir::Instruction(ir::Operand(std::to_string(float(value2int(funcrparams_child->params[i].name))), 
                                        funcrparams_child->params[i].type), ir::Operand(), temp, ir::Operator::fdef);
                                    COMMIT_INSTR(inst);
                                    params.push_back(temp);
                                    break;
                                }
                                case Type::Float:{
                                    params.push_back(funcrparams_child->params[i]);
                                    break;
                                }
                                case Type::FloatLiteral:{
                                    ir::Operand temp = symbol_table.add_temp(Type::Float);
                                    ir::Instruction* inst = new ir::Instruction(ir::Operand(funcrparams_child->params[i].name, 
                                        funcrparams_child->params[i].type), ir::Operand(), temp, ir::Operator::fdef);
                                    COMMIT_INSTR(inst);
                                    params.push_back(temp);
                                    break;
                                }
                                default: assert(0);
                            }
                            break;
                        }
                        case Type::IntPtr:{
                            assert(funcrparams_child->params[i].type == Type::IntPtr);
                            params.push_back(funcrparams_child->params[i]);
                            break;
                        }
                        case Type::FloatPtr:{
                            assert(funcrparams_child->params[i].type == Type::FloatPtr);
                            params.push_back(funcrparams_child->params[i]);
                            break;
                        }
                        default: assert(0);
                    }
                }
            }
            instr = new ir::CallInst(ir::Operand(function->name, Type::null), params, operand);
            COMMIT_INSTR(instr);
        }  
        
        root->v = operand.name;
        root->t = operand.type;
    }

    /**
     * @brief UnaryExp -> PrimaryExp
     * 
     */
    else if(root->children[0]->type == NodeType::UNARYOP){
        assert(root->children[1]->type == NodeType::UNARYEXP);

        unaryop_child = CVT_POINT(root->children[0], UnaryOp);
        transUnaryOp(unaryop_child, root);
        unaryexp_child = CVT_POINT(root->children[1], UnaryExp);
        transUnaryExp(unaryexp_child, root);

        switch (unaryop_child->op)
        {
            case TokenType::PLUS:{
                root->v = unaryexp_child->v;
                root->t = unaryexp_child->t;
                break;
            }
            case TokenType::MINU:{
                switch (unaryexp_child->t)
                {
                    case Type::Int:{
                        ir::Operand operand = symbol_table.add_temp(Type::Int);
                        ir::Operand operand_zero = symbol_table.add_temp(Type::Int);
                        ir::Instruction* instr;

                        instr = new ir::Instruction( ir::Operand("0", Type::IntLiteral), ir::Operand(), operand_zero, ir::Operator::def);
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction( operand_zero, ir::Operand(unaryexp_child->v, Type::Int), operand, ir::Operator::sub );
                        COMMIT_INSTR(instr);

                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    case Type::IntLiteral:{
                        root->v = std::to_string( - value2int(unaryexp_child->v) );
                        root->t = Type::IntLiteral;
                        break;
                    }
                    case Type::Float:{
                        ir::Operand operand = symbol_table.add_temp(Type::Float);
                        ir::Operand operand_zero = symbol_table.add_temp(Type::Float);
                        ir::Instruction* instr;

                        instr = new ir::Instruction( ir::Operand("0", Type::FloatLiteral), ir::Operand(), operand_zero, ir::Operator::fdef);
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction( operand_zero, ir::Operand(unaryexp_child->v, Type::Float), operand, ir::Operator::fsub );
                        COMMIT_INSTR(instr);

                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    case Type::FloatLiteral:{
                        root->v = std::to_string( - value2float(unaryexp_child->v) );
                        root->t = Type::IntLiteral;
                        break;
                    }
                    default: assert(0);
                }
                break;
            }
            case TokenType::NOT:{
                switch (unaryexp_child->t)
                {
                    case Type::Int:{
                        ir::Operand operand = symbol_table.add_temp(Type::Int);
                        ir::Instruction* instr;

                        instr = new ir::Instruction( ir::Operand(unaryexp_child->v, Type::Int), ir::Operand(), operand, ir::Operator::_not );
                        COMMIT_INSTR(instr);

                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    
                    case Type::IntLiteral:{
                        root->v = value2int(unaryexp_child->v) ? "0" : "1";
                        root->t = Type::IntLiteral;
                        break;
                    }
                    case Type::Float:{
                        ir::Operand operand = symbol_table.add_temp(Type::Int);
                        ir::Operand operand_zero = symbol_table.add_temp(Type::Float);
                        ir::Instruction* instr;

                        instr = new ir::Instruction( ir::Operand("0", Type::FloatLiteral), ir::Operand(), operand_zero, ir::Operator::fdef );
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction( ir::Operand(unaryexp_child->v, Type::Float), operand_zero, operand, ir::Operator::feq );
                        COMMIT_INSTR(instr);

                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    case Type::FloatLiteral:{
                        root->v = value2float(unaryexp_child->v) != 0 ? "0" : "1";
                        root->t = Type::FloatLiteral;
                        break;
                    }
                    default: assert(0);
                }
                break;
            } 
            default: assert(0);
        }
    }
    else assert(0);
}

void frontend::Analyzer::transPrimaryExp(PrimaryExp* root, AstNode* p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"PrimaryExp"<<std::endl;
    #endif
    assert(root->children.size() >= 1);
    
    /**
     * @brief PrimaryExp -> (Exp)
     * 
     */
    if(root->children[0]->type == NodeType::TERMINAL && CVT_POINT(root->children[0], Term)->token.type == TokenType::LPARENT){
        assert(root->children[1]->type == NodeType::EXP);
        assert(root->children[2]->type == NodeType::TERMINAL && CVT_POINT(root->children[2], Term)->token.type == TokenType::RPARENT);

        Exp* exp_child = CVT_POINT(root->children[1], Exp);
        transExp(exp_child, root);

        root->v = exp_child->v;
        root->t = exp_child->t;
    }

    /**
     * @brief PrimaryExp -> LVal
     * 
     */
    else if(root->children[0]->type == NodeType::LVAL){
        assert(root->children.size() == 1);

        LVal* lval_child = CVT_POINT(root->children[0], LVal);
        transLVal(lval_child, root);
        if(lval_child->t == Type::Int || lval_child->t == Type::Float || lval_child->t == Type::IntLiteral || lval_child->t == Type::FloatLiteral){     
            root->v = lval_child->v;
            root->t = lval_child->t;
        }
        else if(lval_child->t == Type::IntPtr){
            if(lval_child->it == Type::null){
                root->v = lval_child->v;
                root->t = lval_child->t;
            }
            else{
                ir::Operand operand = symbol_table.add_temp(Type::Int);
                ir::Operand index;
                if(lval_child->it == Type::Int){
                    index = ir::Operand(lval_child->i, lval_child->it);
                }
                else if(lval_child->it == Type::IntLiteral){
                    index = symbol_table.add_temp(Type::Int);
                    ir::Instruction* instr =  new ir::Instruction(ir::Operand(lval_child->i, lval_child->it), ir::Operand(), index, ir::Operator::def);
                    COMMIT_INSTR(instr);   
                }
                else assert(0);
                ir::Instruction* instr =  new ir::Instruction(ir::Operand(lval_child->v, Type::IntPtr), index, operand, ir::Operator::load);
                COMMIT_INSTR(instr);

                root->v = operand.name;
                root->t = operand.type;
            }
        }   
        else if(lval_child->t == Type::FloatPtr){
            if(lval_child->it == Type::null){
                root->v = lval_child->v;
                root->t = lval_child->t;
            }
            else{
                ir::Operand operand = symbol_table.add_temp(Type::Float);
                ir::Operand index;
                if(lval_child->it == Type::Int){
                    index = ir::Operand(lval_child->i, lval_child->it);
                }
                else if(lval_child->it == Type::IntLiteral){
                    index = symbol_table.add_temp(Type::Int);
                    ir::Instruction* instr =  new ir::Instruction(ir::Operand(lval_child->i, lval_child->it), ir::Operand(), index, ir::Operator::def);
                    COMMIT_INSTR(instr);   
                }
                else assert(0);
                ir::Instruction* instr =  new ir::Instruction(ir::Operand(lval_child->v, Type::FloatPtr), index, operand, ir::Operator::load);
                COMMIT_INSTR(instr);

                root->v = operand.name;
                root->t = operand.type;
            }
        }  
        else assert(0);
    }

    /**
     * @brief PrimaryExp -> Number
     * 
     */
    else if(root->children[0]->type == NodeType::NUMBER){
        assert(root->children.size() == 1);

        Number* number_child = CVT_POINT(root->children[0], Number);
        transNumber(number_child, root);

        root->v = number_child->v;
        root->t = number_child->t;
    }

    else assert(0);
}

void frontend::Analyzer::transLVal(LVal* root, AstNode* p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"LVal"<<std::endl;
    #endif
    assert(root->children.size() >= 1);

    Term* ident_child;
    assert(root->children[0]->type == NodeType::TERMINAL && CVT_POINT(root->children[0], Term)->token.type == TokenType::IDENFR);
    ident_child = CVT_POINT(root->children[0], Term);

    STE ste = symbol_table.get_ste(ident_child->token.value);
    frontend::ConstOperand constop = symbol_table.get_const(ident_child->token.value);
    Type t;
    if(!(ste.operand.type == Type::null)) t = ste.operand.type;
    else if(!(constop.t == Type::null)) t =  constop.t;
    else assert(0);


    Exp* exp_child;

    /**
     * @brief single variable
     * 
     */
    if(t == Type::Int || t == Type::Float){
        root->v = ste.operand.name;
        root->t = ste.operand.type;
        root->i = "0";
        root->it = Type::null;
    }

    /**
     * @brief const
     * 
     */
    else if(t == Type::IntLiteral || t == Type::FloatLiteral){
        
        root->v = t == Type::IntLiteral ? std::to_string(*((int*) constop.v)) : std::to_string(*((double*) constop.v));
        root->t = constop.t;
        root->i = "0";
        root->it = Type::null;
    }

    /**
     * @brief array
     * 
     */
    else if(t == Type::IntPtr || t == Type::FloatPtr){
        
        if(root->children.size() == 1){
            root->v = ste.operand.name;
            root->t = ste.operand.type;
            root->i = "0";
            root->it = Type::null;
            return;
        }

        root->v = ste.operand.name;
        root->t = t;
        if(ste.dimension.size() == 1){
            assert(root->children[1]->type == NodeType::TERMINAL && CVT_POINT(root->children[1], Term)->token.type == TokenType::LBRACK);      
            assert(root->children[2]->type == NodeType::EXP);
            assert(root->children[3]->type == NodeType::TERMINAL && CVT_POINT(root->children[3], Term)->token.type == TokenType::RBRACK);
            
            Exp* exp_child = CVT_POINT(root->children[2], Exp);
            transExp(exp_child, root);
            
            root->i = exp_child->v;
            root->it = exp_child->t;      
        }
        else{
            assert(root->children[1]->type == NodeType::TERMINAL && CVT_POINT(root->children[1], Term)->token.type == TokenType::LBRACK);
            assert(root->children[2]->type == NodeType::EXP);
            assert(root->children[3]->type == NodeType::TERMINAL && CVT_POINT(root->children[3], Term)->token.type == TokenType::RBRACK);
            assert(root->children[4]->type == NodeType::TERMINAL && CVT_POINT(root->children[4], Term)->token.type == TokenType::LBRACK);
            assert(root->children[5]->type == NodeType::EXP);
            assert(root->children[6]->type == NodeType::TERMINAL && CVT_POINT(root->children[6], Term)->token.type == TokenType::RBRACK);
            Exp* exp_child0 = CVT_POINT(root->children[2], Exp);
            Exp* exp_child1 = CVT_POINT(root->children[5], Exp);
            transExp(exp_child0, root);
            transExp(exp_child1, root);
            if(exp_child0->t == Type::IntLiteral && exp_child1->t == Type::IntLiteral){
                root->i = std::to_string(value2int(exp_child0->v) * ste.dimension[1] + value2int(exp_child1->v));
                root->it = Type::IntLiteral;
            }
            else if(exp_child0->t == Type::IntLiteral && exp_child1->t == Type::Int){
                ir::Operand operand = symbol_table.add_temp(Type::Int);
                ir::Instruction* instr = new ir::Instruction( ir::Operand(exp_child1->v, exp_child1->t) , 
                                ir::Operand(std::to_string(value2int(exp_child0->v) * ste.dimension[1]), Type::IntLiteral), operand, ir::Operator::addi);
                COMMIT_INSTR(instr);
                root->i = operand.name;
                root->it = Type::Int;
            }
            else if(exp_child0->t == Type::Int && exp_child1->t == Type::IntLiteral){
                ir::Operand operand = symbol_table.add_temp(Type::Int);
                ir::Operand dim = symbol_table.add_temp(Type::Int);
                ir::Operand res = symbol_table.add_temp(Type::Int);
                ir::Instruction* instr = new ir::Instruction( ir::Operand(std::to_string(ste.dimension[1]), Type::IntLiteral), ir::Operand(), dim, ir::Operator::def);
                COMMIT_INSTR(instr);
                instr = new ir::Instruction( ir::Operand(exp_child0->v, exp_child0->t), dim, operand, ir::Operator::mul);
                COMMIT_INSTR(instr);
                instr = new ir::Instruction( operand, ir::Operand(exp_child1->v, exp_child1->t), res, ir::Operator::addi);
                COMMIT_INSTR(instr);
                root->i = res.name;
                root->it = Type::Int;
            }
            else if(exp_child0->t == Type::Int && exp_child1->t == Type::Int){
                ir::Operand operand = symbol_table.add_temp(Type::Int);
                ir::Operand dim = symbol_table.add_temp(Type::Int);
                ir::Operand res = symbol_table.add_temp(Type::Int);
                ir::Instruction* instr = new ir::Instruction( ir::Operand(std::to_string(ste.dimension[1]), Type::IntLiteral), ir::Operand(), dim, ir::Operator::def);
                COMMIT_INSTR(instr);
                instr = new ir::Instruction( ir::Operand(exp_child0->v, exp_child0->t), dim, operand, ir::Operator::mul);
                COMMIT_INSTR(instr);
                instr = new ir::Instruction( operand, ir::Operand(exp_child1->v, exp_child1->t), res, ir::Operator::add);
                COMMIT_INSTR(instr);
                root->i = res.name;
                root->it = Type::Int;
            }
            else assert(0);
        }
    }
    else assert(0);
    
    
}




void frontend::Analyzer::transUnaryOp(UnaryOp* root, AstNode* p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"UnaryOp"<<std::endl;
    #endif
    assert(root->children.size() == 1);

    Term* child = CVT_POINT(root->children[0], Term);


    assert(child->token.type == TokenType::PLUS || child->token.type == TokenType::MINU || child->token.type == TokenType::NOT);
    root->op = child->token.type;
}

void frontend::Analyzer::transNumber(Number* root, AstNode* p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"Number"<<std::endl;
    #endif
    assert(root->children.size() == 1);

    auto child = CVT_POINT(root->children[0], Term);

    if(child->token.type == TokenType::INTLTR){
        root->v = std::to_string(value2int(child->token.value)) ;
        root->t = Type::IntLiteral;
    }
    else if(child->token.type == TokenType::FLOATLTR){
        root->v = std::to_string(value2float(child->token.value)) ;
        root->t = Type::FloatLiteral;
    }
    else assert(0);

}

void frontend::Analyzer::transFuncFParam(FuncFParam* root, AstNode* p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"FuncFParam"<<std::endl;
    #endif
    BType* btype_child;
    Term* ident_child;
    Exp* exp_child;

    assert(root->children.size() >= 2);
    assert(root->children[0]->type == NodeType::BTYPE);
    assert(root->children[1]->type == NodeType::TERMINAL && CVT_POINT(root->children[1], Term)->token.type == TokenType::IDENFR);

    btype_child = CVT_POINT(root->children[0], BType);
    transBType(btype_child, root);
    assert(btype_child->t == Type::Int || btype_child->t == Type::Float);
    ident_child = CVT_POINT(root->children[1], Term);

    if(root->children.size() >2 && root->children[2]->type == NodeType::TERMINAL && CVT_POINT(root->children[2], Term)->token.type == TokenType::LBRACK){
        
        assert(root->children[3]->type == NodeType::TERMINAL && CVT_POINT(root->children[3], Term)->token.type == TokenType::RBRACK);
        vector<int> dimension;
        dimension.push_back(0);
        if(root->children.size() > 4 && root->children[4]->type == NodeType::TERMINAL && CVT_POINT(root->children[2], Term)->token.type == TokenType::LBRACK){
            exp_child = CVT_POINT(root->children[5], Exp);
            transExp(exp_child, root);
            assert(exp_child->t == Type::IntLiteral);
            dimension.push_back(value2int(exp_child->v));
            assert(root->children[4]->type == NodeType::TERMINAL && CVT_POINT(root->children[2], Term)->token.type == TokenType::RBRACK);
        }
        root->param = symbol_table.add_ste(ident_child->token.value, dimension, TO_PTR_TYPE(btype_child->t));
    }
    else{
        
        assert(symbol_table.get_operand_inscope(ident_child->token.value).type == Type::null);
        root->param = symbol_table.add_ste(ident_child->token.value, vector<int>(), btype_child->t);
    }
    
}

void frontend::Analyzer::transFuncFParams(FuncFParams* root, AstNode* p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"FuncFParams"<<std::endl;
    #endif
    assert(root->children.size() >= 1);
    
    FuncFParam* funcfparam_child  = CVT_POINT(root->children[0], FuncFParam);
    transFuncFParam(funcfparam_child, root);
    root->params.push_back(funcfparam_child->param);

    int index = 1;
    while (index < root->children.size()&& root->children[index]->type == NodeType::TERMINAL && CVT_POINT(root->children[index], Term)->token.type == TokenType::COMMA)
    {
        assert(root->children[index+1]->type == NodeType::FUNCFPARAM);
        funcfparam_child  = CVT_POINT(root->children[index+1], FuncFParam);
        transFuncFParam(funcfparam_child, root);
        root->params.push_back(funcfparam_child->param);
        index += 2;
    }
    
}

void frontend::Analyzer::transStmt(Stmt* root, AstNode* p){
    
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"Stmt"<<std::endl;
    #endif
    assert(root->children.size() >= 1);

    if(root->children[0]->type == NodeType::LVAL){
        assert(root->children[1]->type == NodeType::TERMINAL && CVT_POINT(root->children[1], Term)->token.type == TokenType::ASSIGN);
        assert(root->children[2]->type == NodeType::EXP);

        LVal* lval_child = CVT_POINT(root->children[0], LVal);
        transLVal(lval_child, root);
        Exp* exp_child = CVT_POINT(root->children[2], Exp);
        transExp(exp_child, root);


        ir::Instruction* instr;
        switch (lval_child->t)
        {
            case Type::Int:{
                switch (exp_child->t)
                {
                    case Type::Int:{
                        instr = new ir::Instruction(ir::Operand(exp_child->v, exp_child->t), ir::Operand(), ir::Operand(lval_child->v, lval_child->t), ir::Operator::mov);
                        COMMIT_INSTR(instr);
                        break;
                    }
                    case Type::IntLiteral:{
                        instr = new ir::Instruction(ir::Operand(exp_child->v, exp_child->t), ir::Operand(), ir::Operand(lval_child->v, lval_child->t), ir::Operator::def);
                        COMMIT_INSTR(instr);
                        break;
                    }
                    case Type::Float:{
                        instr = new ir::Instruction(ir::Operand(exp_child->v, exp_child->t), ir::Operand(), ir::Operand(lval_child->v, lval_child->t), ir::Operator::cvt_f2i);
                        COMMIT_INSTR(instr);
                        break;
                    }
                    case Type::FloatLiteral:{
                        ir::Operand temp = symbol_table.add_temp(Type::Float);
                        instr = new ir::Instruction(ir::Operand(exp_child->v, exp_child->t), ir::Operand(), temp, ir::Operator::fdef);
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction(temp, ir::Operand(), ir::Operand(lval_child->v, lval_child->t), ir::Operator::cvt_f2i);
                        COMMIT_INSTR(instr);
                        break;
                    }
                    default: assert(0);
                }
                break;
            }
            case Type::Float:{
                switch (exp_child->t)
                {
                    case Type::Int:{
                        instr = new ir::Instruction(ir::Operand(exp_child->v, exp_child->t), ir::Operand(), ir::Operand(lval_child->v, lval_child->t), ir::Operator::cvt_i2f);
                        COMMIT_INSTR(instr);
                        break;
                    }
                    case Type::IntLiteral:{
                        ir::Operand temp = symbol_table.add_temp(Type::Int);
                        instr = new ir::Instruction(ir::Operand(exp_child->v, exp_child->t), ir::Operand(), temp, ir::Operator::def);
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction(temp, ir::Operand(), ir::Operand(lval_child->v, lval_child->t), ir::Operator::cvt_i2f);
                        COMMIT_INSTR(instr);
                        break;
                    }
                    case Type::Float:{
                        instr = new ir::Instruction(ir::Operand(exp_child->v, exp_child->t), ir::Operand(), ir::Operand(lval_child->v, lval_child->t), ir::Operator::fmov);
                        COMMIT_INSTR(instr);
                        break;
                    }
                    case Type::FloatLiteral:{
                        instr = new ir::Instruction(ir::Operand(exp_child->v, exp_child->t), ir::Operand(), ir::Operand(lval_child->v, lval_child->t), ir::Operator::fdef);
                        COMMIT_INSTR(instr);
                        break;
                    }
                    default: assert(0);
                }
                break;
            }
            case Type::IntPtr:{
                switch (exp_child->t)
                {
                    case Type::Int:{
                        instr = new ir::Instruction(ir::Operand(lval_child->v, lval_child->t), ir::Operand(lval_child->i, lval_child->it), 
                                                    ir::Operand(exp_child->v, exp_child->t), ir::Operator::store);
                        COMMIT_INSTR(instr);
                        break;
                    }
                    case Type::Float:{
                        ir::Operand temp = symbol_table.add_temp(Type::Int);
                        instr = new ir::Instruction(ir::Operand(exp_child->v, exp_child->t), ir::Operand(), temp, ir::Operator::cvt_f2i);
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction(ir::Operand(lval_child->v, lval_child->t), ir::Operand(lval_child->i, lval_child->it), 
                                                    temp, ir::Operator::store);
                        COMMIT_INSTR(instr);
                        break;
                    }
                    case Type::IntLiteral:{
                        ir::Operand temp = symbol_table.add_temp(Type::Int);
                        instr = new ir::Instruction(ir::Operand(exp_child->v, exp_child->t), ir::Operand(), temp, ir::Operator::def);
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction(ir::Operand(lval_child->v, lval_child->t), ir::Operand(lval_child->i, lval_child->it), 
                                                    temp, ir::Operator::store);
                        COMMIT_INSTR(instr);
                        break;
                    }
                    case Type::FloatLiteral:{
                        ir::Operand temp = symbol_table.add_temp(Type::Float);
                        instr = new ir::Instruction(ir::Operand(exp_child->v, exp_child->t), ir::Operand(), temp, ir::Operator::fdef);   
                        COMMIT_INSTR(instr);
                        ir::Operand temp1 = symbol_table.add_temp(Type::Int);
                        instr = new ir::Instruction(temp, ir::Operand(), temp1, ir::Operator::cvt_f2i);   
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction(ir::Operand(lval_child->v, lval_child->t), ir::Operand(lval_child->i, lval_child->it), 
                                                    temp1, ir::Operator::store);
                        COMMIT_INSTR(instr);
                    }
                    default: assert(0);
                }
                break;
            }
            case Type::FloatPtr:{
                switch (exp_child->t)
                {
                    case Type::Int:{
                        ir::Operand temp = symbol_table.add_temp(Type::Float);
                        instr = new ir::Instruction(ir::Operand(exp_child->v, exp_child->t), ir::Operand(), temp, ir::Operator::cvt_i2f);
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction(ir::Operand(lval_child->v, lval_child->t), ir::Operand(lval_child->i, lval_child->it), 
                                                    temp, ir::Operator::store);
                        COMMIT_INSTR(instr);
                        break;
                    }
                    case Type::Float:{
                        instr = new ir::Instruction(ir::Operand(lval_child->v, lval_child->t), ir::Operand(lval_child->i, lval_child->it), 
                                                    ir::Operand(exp_child->v, exp_child->t), ir::Operator::store);
                        COMMIT_INSTR(instr);
                        break;
                    }
                    case Type::IntLiteral:{
                        ir::Operand temp = symbol_table.add_temp(Type::Int);
                        instr = new ir::Instruction(ir::Operand(exp_child->v, exp_child->t), ir::Operand(), temp, ir::Operator::def);
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction(ir::Operand(lval_child->v, lval_child->t), ir::Operand(lval_child->i, lval_child->it), 
                                                    temp, ir::Operator::store);
                        COMMIT_INSTR(instr);
                        break;
                    }
                    case Type::FloatLiteral:{
                        ir::Operand temp = symbol_table.add_temp(Type::Float);
                        instr = new ir::Instruction(ir::Operand(exp_child->v, exp_child->t), ir::Operand(), temp, ir::Operator::fdef);   
                        COMMIT_INSTR(instr);
                        ir::Operand temp1 = symbol_table.add_temp(Type::Int);
                        instr = new ir::Instruction(temp, ir::Operand(), temp1, ir::Operator::cvt_f2i);   
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction(ir::Operand(lval_child->v, lval_child->t), ir::Operand(lval_child->i, lval_child->it), 
                                                    temp1, ir::Operator::store);
                        COMMIT_INSTR(instr);
                    }
                    default: assert(0);
                }
                break;
            }
            default: assert(0);
        }
    }
    else if(root->children[0]->type == NodeType::BLOCK){
        Block* block_child = CVT_POINT(root->children[0], Block);
        transBlock(block_child, root);
    }
    else if(root->children[0]->type == NodeType::TERMINAL && CVT_POINT(root->children[0], Term)->token.type == TokenType::IFTK){
        assert(root->children.size() >= 5);
        assert(root->children[1]->type == NodeType::TERMINAL && CVT_POINT(root->children[1], Term)->token.type == TokenType::LPARENT);
        assert(root->children[2]->type == NodeType::COND);
        assert(root->children[3]->type == NodeType::TERMINAL && CVT_POINT(root->children[3], Term)->token.type == TokenType::RPARENT);
        assert(root->children[4]->type == NodeType::STMT);
        
        Cond* cond_child = CVT_POINT(root->children[2], Cond);
        Stmt* stmt_child = CVT_POINT(root->children[4], Stmt);
        transCond(cond_child, root);

        ir::Instruction* instr;
        int goto0_label;
        int goto1_label;
        int end_label;

        switch (cond_child->t)
        {
            case Type::Int:{
                ir::Operand temp = symbol_table.add_temp(Type::Int);
                instr = new ir::Instruction(ir::Operand(cond_child->v, cond_child->t), ir::Operand(), temp, ir::Operator::_not);
                COMMIT_INSTR(instr);
                instr = new ir::Instruction(temp, ir::Operand(), ir::Operand(), ir::Operator::_goto);
                COMMIT_INSTR(instr);
                break;
            }
            case Type::IntLiteral:{
                instr = value2int(cond_child->v) != 0 ? new ir::Instruction(symbol_table.zero, ir::Operand(), ir::Operand(), ir::Operator::_goto)
                    : new ir::Instruction(symbol_table.one, ir::Operand(), ir::Operand(), ir::Operator::_goto);
                COMMIT_INSTR(instr);  
                break;
            }
            case Type::Float:{
                ir::Operand temp = symbol_table.add_temp(Type::Int);
                instr = new ir::Instruction(ir::Operand(cond_child->v, cond_child->t), symbol_table.fzero, temp, ir::Operator::feq);
                COMMIT_INSTR(instr);
                instr = new ir::Instruction(temp, ir::Operand(), ir::Operand(), ir::Operator::_goto);
                COMMIT_INSTR(instr);
                break;
            }
            case Type::FloatLiteral:{
                instr = value2float(cond_child->v) != 0 ? new ir::Instruction(symbol_table.zero, ir::Operand(), ir::Operand(), ir::Operator::_goto)
                    : new ir::Instruction(symbol_table.one, ir::Operand(), ir::Operand(), ir::Operator::_goto);
                COMMIT_INSTR(instr);
                break;
            }
            default: assert(0);
        }
        goto0_label = curr_function->InstVec.size() - 1;

        transStmt(stmt_child, root);

        instr = new ir::Instruction(symbol_table.one, ir::Operand(), ir::Operand(), ir::Operator::_goto);
        COMMIT_INSTR(instr);
        goto1_label = curr_function->InstVec.size() - 1;

        instr = new ir::Instruction(ir::Operand(), ir::Operand(), ir::Operand(), ir::Operator::__unuse__);
        COMMIT_INSTR(instr);
        curr_function->InstVec[goto0_label]->des = ir::Operand(std::to_string(goto1_label - goto0_label + 1), Type::IntLiteral);

        if(root->children.size() == 7){
            assert(root->children[5]->type == NodeType::TERMINAL && CVT_POINT(root->children[5], Term)->token.type == TokenType::ELSETK);
            assert(root->children[6]->type == NodeType::STMT);
            stmt_child = CVT_POINT(root->children[6], Stmt);
            transStmt(stmt_child, root); 
            instr = new ir::Instruction(ir::Operand(), ir::Operand(), ir::Operand(), ir::Operator::__unuse__);  
            COMMIT_INSTR(instr);    
        }     

        curr_function->InstVec[goto1_label]->des = ir::Operand(std::to_string(curr_function->InstVec.size() -1 - goto1_label), Type::IntLiteral);
    }
    else if(root->children[0]->type == NodeType::TERMINAL && CVT_POINT(root->children[0], Term)->token.type == TokenType::WHILETK){
        assert(root->children.size() == 5);
        assert(root->children[1]->type == NodeType::TERMINAL && CVT_POINT(root->children[1], Term)->token.type == TokenType::LPARENT);
        assert(root->children[2]->type == NodeType::COND);
        assert(root->children[3]->type == NodeType::TERMINAL && CVT_POINT(root->children[3], Term)->token.type == TokenType::RPARENT);
        assert(root->children[4]->type == NodeType::STMT);

        int start_label;
        int end_label;

        ir::Instruction* instr = new ir::Instruction(ir::Operand(), ir::Operand(), ir::Operand(), ir::Operator::__unuse__);
        COMMIT_INSTR(instr);
        start_label = curr_function->InstVec.size() - 1;

        Cond* cond_child = CVT_POINT(root->children[2], Cond);
        transCond(cond_child, root);
        
        switch (cond_child->t)
        {
            case Type::Int:{
                ir::Operand temp = symbol_table.add_temp(Type::Int);
                instr = new ir::Instruction(ir::Operand(cond_child->v, cond_child->t), ir::Operand(), temp, ir::Operator::_not);
                COMMIT_INSTR(instr);
                instr = new ir::Instruction(temp, ir::Operand("break", Type::null), ir::Operand(), ir::Operator::_goto);
                COMMIT_INSTR(instr);
                break;
            }
            case Type::IntLiteral:{
                instr = value2int(cond_child->v) != 0 ? new ir::Instruction(symbol_table.zero, ir::Operand(), ir::Operand(), ir::Operator::_goto)
                    : new ir::Instruction(symbol_table.one, ir::Operand("break", Type::null), ir::Operand(), ir::Operator::_goto);
                COMMIT_INSTR(instr);  
                break;
            }
            case Type::Float:{
                ir::Operand temp = symbol_table.add_temp(Type::Int);
                instr = new ir::Instruction(ir::Operand(cond_child->v, cond_child->t), symbol_table.fzero, temp, ir::Operator::feq);
                COMMIT_INSTR(instr);
                instr = new ir::Instruction(temp, ir::Operand("break", Type::null), ir::Operand(), ir::Operator::_goto);
                COMMIT_INSTR(instr);
                break;
            }
            case Type::FloatLiteral:{
                instr = value2float(cond_child->v) != 0 ? new ir::Instruction(symbol_table.zero, ir::Operand(), ir::Operand(), ir::Operator::_goto)
                    : new ir::Instruction(symbol_table.one, ir::Operand("break", Type::null), ir::Operand(), ir::Operator::_goto);
                COMMIT_INSTR(instr);
                break;
            }
            default: assert(0);
        }

        Stmt* stmt_child = CVT_POINT(root->children[4], Stmt);
        transStmt(stmt_child, root);

        instr = new ir::Instruction(symbol_table.one, ir::Operand("continue", Type::null), ir::Operand(), ir::Operator::_goto);
        COMMIT_INSTR(instr);
        instr = new ir::Instruction(ir::Operand(), ir::Operand(), ir::Operand(), ir::Operator::__unuse__);
        COMMIT_INSTR(instr);
        end_label = curr_function->InstVec.size() - 1;

        for(int i = start_label; i <= end_label; i++){
            ir::Instruction* instr = curr_function->InstVec[i];
            if(instr->op == ir::Operator::_goto && instr->op2.name == "break"){
                instr->op2 = ir::Operand();
                instr->des = ir::Operand(std::to_string(end_label - i), Type::IntLiteral);
            }
            else if(instr->op == ir::Operator::_goto && instr->op2.name == "continue"){
                instr->op2 = ir::Operand();
                instr->des = ir::Operand(std::to_string(start_label - i), Type::IntLiteral);
            }
        }
    }
    else if(root->children[0]->type == NodeType::TERMINAL && CVT_POINT(root->children[0], Term)->token.type == TokenType::BREAKTK){
        ir::Instruction* instr = new ir::Instruction(symbol_table.one, ir::Operand("break", Type::null), ir::Operand(), ir::Operator::_goto);
        COMMIT_INSTR(instr);
    }
    else if(root->children[0]->type == NodeType::TERMINAL && CVT_POINT(root->children[0], Term)->token.type == TokenType::CONTINUETK){
        ir::Instruction* instr = new ir::Instruction(symbol_table.one, ir::Operand("continue", Type::null), ir::Operand(), ir::Operator::_goto);
        COMMIT_INSTR(instr);
    }
    else if(root->children[0]->type == NodeType::TERMINAL && CVT_POINT(root->children[0], Term)->token.type == TokenType::RETURNTK){
        Exp* exp_child;
        ir::Instruction* instr;
        if(root->children.size() == 2){
            instr = new ir::Instruction(ir::Operand("", Type::null), ir::Operand(), ir::Operand(), ir::Operator::_return);
            COMMIT_INSTR(instr);
            assert(root->children[1]->type == NodeType::TERMINAL && CVT_POINT(root->children[1], Term)->token.type == TokenType::SEMICN);
        }
        else if(root->children.size() == 3){
            exp_child = CVT_POINT(root->children[1], Exp);
            transExp(exp_child, root);

            ir::Operand operand;
            switch (curr_function->returnType)
            {
                case Type::Int:{
                    switch (exp_child->t)
                    {
                        case Type::Int:{
                            operand = ir::Operand(exp_child->v, exp_child->t);
                            break;
                        }
                        case Type::IntLiteral:{
                            operand = symbol_table.add_temp(Type::Int);
                            ir::Instruction* instr = new ir::Instruction(ir::Operand(exp_child->v, exp_child->t), ir::Operand(), operand, ir::Operator::def);
                            COMMIT_INSTR(instr);
                            break;
                        }
                        case Type::Float:{
                            operand = symbol_table.add_temp(Type::Int);
                            ir::Instruction* instr = new ir::Instruction(ir::Operand(exp_child->v, exp_child->t), ir::Operand(), operand, ir::Operator::cvt_f2i);
                            COMMIT_INSTR(instr);
                            break;
                        }
                        case Type::FloatLiteral:{
                            operand = symbol_table.add_temp(Type::Int);
                            ir::Instruction* instr = new ir::Instruction(ir::Operand(std::to_string(int(value2float(exp_child->v))), Type::IntLiteral), 
                                                    ir::Operand(), operand, ir::Operator::def);
                            COMMIT_INSTR(instr);
                            break;
                        }
                        default: assert(0);
                    }
                    break;
                }
                case Type::Float:{
                    switch (exp_child->t)
                    {
                        case Type::Int:{
                            operand = symbol_table.add_temp(Type::Float);
                            ir::Instruction* instr = new ir::Instruction(ir::Operand(exp_child->v, exp_child->t), ir::Operand(), operand, ir::Operator::cvt_i2f);
                            COMMIT_INSTR(instr);
                            break;
                        }
                        case Type::IntLiteral:{
                            operand = symbol_table.add_temp(Type::Float);
                            ir::Instruction* instr = new ir::Instruction(ir::Operand(std::to_string(float(value2int(exp_child->v))), Type::FloatLiteral), 
                                                    ir::Operand(), operand, ir::Operator::fdef);
                            COMMIT_INSTR(instr);
                            break;
                        }
                        case Type::Float:{
                            operand = ir::Operand(exp_child->v, exp_child->t);
                            break;
                        }
                        case Type::FloatLiteral:{
                            operand = symbol_table.add_temp(Type::Float);
                            ir::Instruction* instr = new ir::Instruction(ir::Operand(exp_child->v, exp_child->t), ir::Operand(), operand, ir::Operator::fdef);
                            COMMIT_INSTR(instr);
                            break;
                        }
                        default: assert(0);
                    }
                    break;
                }
                default: assert(0);
            }

            instr = new ir::Instruction(operand, ir::Operand(), ir::Operand(), ir::Operator::_return);
            COMMIT_INSTR(instr);
            assert(root->children[2]->type == NodeType::TERMINAL && CVT_POINT(root->children[2], Term)->token.type == TokenType::SEMICN);
        }
        else assert(0);
    }
    else if(root->children[0]->type == NodeType::TERMINAL && CVT_POINT(root->children[0], Term)->token.type == TokenType::SEMICN){
        
    }
    else if(root->children[0]->type == NodeType::EXP){
        assert(root->children.size() == 2);
        assert(root->children[1]->type == NodeType::TERMINAL && CVT_POINT(root->children[1], Term)->token.type == TokenType::SEMICN);
        Exp* exp_child = CVT_POINT(root->children[0], Exp);
        transExp(exp_child, root);
    }
    else assert(0);
}

void frontend::Analyzer::transCond(Cond* root, AstNode* p){
    LOrExp* lorexp_child;
    assert(root->children.size() == 1);
    assert(root->children[0]->type == NodeType::LOREXP);
    lorexp_child = CVT_POINT(root->children[0], LOrExp);
    transLOrExp(lorexp_child, root);

    switch (lorexp_child->t)
    {
        case Type::Int:{
            root->v = lorexp_child->v;
            root->t = lorexp_child->t;
            break;
        }
        case Type::IntLiteral:{
            root->v = value2int(lorexp_child->v) !=0 ? symbol_table.one.name : symbol_table.zero.name;
            root->t = Type::Int;
            break;
        }
        case Type::Float:{
            ir::Operand temp = symbol_table.add_temp(Type::Float);
            ir::Operand operand = symbol_table.add_temp(Type::Int);
            ir::Instruction* instr = new ir::Instruction(ir::Operand(lorexp_child->v, lorexp_child->t), symbol_table.fzero, temp, ir::Operator::fneq);
            COMMIT_INSTR(instr);
            instr = new ir::Instruction(temp, ir::Operand(), operand, ir::Operator::cvt_f2i);
            COMMIT_INSTR(instr);
            root->v = operand.name;
            root->t = operand.type;
            break;
        }
        case Type::FloatLiteral:{
            root->v = value2float(lorexp_child->v) !=0 ? symbol_table.one.name : symbol_table.zero.name;
            root->t = Type::Int;
            break;
        }
        default: assert(0);
    }
}

void frontend::Analyzer::transFuncRParams(FuncRParams* root, AstNode* p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"FuncRParams"<<std::endl;
    #endif

    assert(root->children.size() >=1);

    Exp* exp_child = CVT_POINT(root->children[0], Exp);
    transExp(exp_child, root);
    root->params.push_back(ir::Operand(exp_child->v, exp_child->t));

    int index = 1;
    while(index < root->children.size() && root->children[index]->type == NodeType::TERMINAL && CVT_POINT(root->children[index], Term)->token.type == TokenType::COMMA){
        assert(root->children[index+1]->type == NodeType::EXP);

        exp_child = CVT_POINT(root->children[index+1], Exp);
        transExp(exp_child, root);
        root->params.push_back(ir::Operand(exp_child->v, exp_child->t));
        
        index += 2;   
    }

}

void frontend::Analyzer::transRelExp(RelExp* root, AstNode* p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"RelExp"<<std::endl;
    #endif
    assert(root->children.size() >=1);
    assert(root->children[0]->type == NodeType::ADDEXP);

    AddExp* addexp_child = CVT_POINT(root->children[0], AddExp);
    transAddExp(addexp_child, root);
    root->v = addexp_child->v;
    root->t = addexp_child->t;

    int index = 1;
    while(index < root->children.size()){
        assert(root->children[index]->type == NodeType::TERMINAL && 
            (CVT_POINT(root->children[index], Term)->token.type == TokenType::LSS || CVT_POINT(root->children[index], Term)->token.type == TokenType::GTR)
            || CVT_POINT(root->children[index], Term)->token.type == TokenType::LEQ || CVT_POINT(root->children[index], Term)->token.type == TokenType::GEQ);
        assert(root->children[index+1]->type == NodeType::ADDEXP);

        Term* term_child = CVT_POINT(root->children[index], Term);
        addexp_child = CVT_POINT(root->children[index+1], AddExp);
        transAddExp(addexp_child, root);

        ir::Instruction* instr;
        switch (root->t)
        {
            case Type::Int:{
                switch (addexp_child->t)
                {
                    case Type::Int:{
                        ir::Operand operand = symbol_table.add_temp(Type::Int);
                        switch (term_child->token.type)
                        {
                            case TokenType::LSS:{
                                instr = new ir::Instruction(ir::Operand(root->v, root->t), ir::Operand(addexp_child->v, addexp_child->t), operand, ir::Operator::lss);
                                break;
                            }
                            case TokenType::GTR:{
                                instr = new ir::Instruction(ir::Operand(root->v, root->t), ir::Operand(addexp_child->v, addexp_child->t), operand, ir::Operator::gtr);
                                break;
                            }
                            case TokenType::LEQ:{
                                instr = new ir::Instruction(ir::Operand(root->v, root->t), ir::Operand(addexp_child->v, addexp_child->t), operand, ir::Operator::leq);
                                break;
                            }
                            case TokenType::GEQ:{
                                instr = new ir::Instruction(ir::Operand(root->v, root->t), ir::Operand(addexp_child->v, addexp_child->t), operand, ir::Operator::geq);
                                break;
                            }
                            default: assert(0);
                        }
                        COMMIT_INSTR(instr);
                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    case Type::IntLiteral:{
                        ir::Operand operand = symbol_table.add_temp(Type::Int);
                        ir::Operand temp = symbol_table.add_temp(Type::Int);
                        instr = new ir::Instruction(ir::Operand(addexp_child->v, addexp_child->t), ir::Operand(), temp, ir::Operator::def);
                        COMMIT_INSTR(instr);
                        switch (term_child->token.type)
                        {
                            case TokenType::LSS:{
                                instr = new ir::Instruction(ir::Operand(root->v, root->t), temp, operand, ir::Operator::lss);
                                break;
                            }
                            case TokenType::GTR:{
                                instr = new ir::Instruction(ir::Operand(root->v, root->t), temp, operand, ir::Operator::gtr);
                                break;
                            }
                            case TokenType::LEQ:{
                                instr = new ir::Instruction(ir::Operand(root->v, root->t), temp, operand, ir::Operator::leq);
                                break;
                            }
                            case TokenType::GEQ:{
                                instr = new ir::Instruction(ir::Operand(root->v, root->t), temp, operand, ir::Operator::geq);
                                break;
                            }
                            default: assert(0);
                        }
                        COMMIT_INSTR(instr);
                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    case Type::Float:{
                        ir::Operand operand = symbol_table.add_temp(Type::Float);
                        ir::Operand temp = symbol_table.add_temp(Type::Float);
                        instr = new ir::Instruction(ir::Operand(root->v, root->t), ir::Operand(), temp, ir::Operator::cvt_i2f);
                        COMMIT_INSTR(instr);
                        switch (term_child->token.type)
                        {
                            case TokenType::LSS:{
                                instr = new ir::Instruction(temp, ir::Operand(addexp_child->v, addexp_child->t), operand, ir::Operator::flss);
                                break;
                            }
                            case TokenType::GTR:{
                                instr = new ir::Instruction(temp, ir::Operand(addexp_child->v, addexp_child->t), operand, ir::Operator::fgtr);
                                break;
                            }
                            case TokenType::LEQ:{
                                instr = new ir::Instruction(temp, ir::Operand(addexp_child->v, addexp_child->t), operand, ir::Operator::fgeq);
                                break;
                            }
                            case TokenType::GEQ:{
                                instr = new ir::Instruction(temp, ir::Operand(addexp_child->v, addexp_child->t), operand, ir::Operator::fgeq);
                                break;
                            }
                            default: assert(0);
                        }
                        COMMIT_INSTR(instr);
                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    case Type::FloatLiteral:{
                        ir::Operand operand = symbol_table.add_temp(Type::Float);
                        ir::Operand temp = symbol_table.add_temp(Type::Float);
                        ir::Operand temp1 = symbol_table.add_temp(Type::Float);
                        instr = new ir::Instruction(ir::Operand(root->v, root->t), ir::Operand(), temp, ir::Operator::cvt_i2f);
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction(ir::Operand(addexp_child->v, addexp_child->t), ir::Operand(), temp1, ir::Operator::fdef);
                        COMMIT_INSTR(instr);
                        switch (term_child->token.type)
                        {
                            case TokenType::LSS:{
                                instr = new ir::Instruction(temp, temp1, operand, ir::Operator::flss);
                                break;
                            }
                            case TokenType::GTR:{
                                instr = new ir::Instruction(temp, temp1, operand, ir::Operator::fgtr);
                                break;
                            }
                            case TokenType::LEQ:{
                                instr = new ir::Instruction(temp, temp1, operand, ir::Operator::fgeq);
                                break;
                            }
                            case TokenType::GEQ:{
                                instr = new ir::Instruction(temp, temp1, operand, ir::Operator::fgeq);
                                break;
                            }
                            default: assert(0);
                        }
                        COMMIT_INSTR(instr);
                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    default: assert(0);
                }
                break;
            }
            case Type::IntLiteral:{
                switch (addexp_child->t)
                {
                    case Type::Int:{
                        ir::Operand operand = symbol_table.add_temp(Type::Int);
                        ir::Operand temp = symbol_table.add_temp(Type::Int);
                        instr = new ir::Instruction(ir::Operand(root->v, root->t), ir::Operand(), temp, ir::Operator::def);
                        COMMIT_INSTR(instr);
                        switch (term_child->token.type)
                        {
                            case TokenType::LSS:{
                                instr = new ir::Instruction(temp, ir::Operand(addexp_child->v, addexp_child->t), operand, ir::Operator::lss);
                                break;
                            }
                            case TokenType::GTR:{
                                instr = new ir::Instruction(temp, ir::Operand(addexp_child->v, addexp_child->t), operand, ir::Operator::gtr);
                                break;
                            }
                            case TokenType::LEQ:{
                                instr = new ir::Instruction(temp, ir::Operand(addexp_child->v, addexp_child->t), operand, ir::Operator::geq);
                                break;
                            }
                            case TokenType::GEQ:{
                                instr = new ir::Instruction(temp, ir::Operand(addexp_child->v, addexp_child->t), operand, ir::Operator::geq);
                                break;
                            }
                            default: assert(0);
                        }
                        COMMIT_INSTR(instr);
                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    case Type::IntLiteral:{
                        switch (term_child->token.type)
                        {
                            case TokenType::LSS:{
                                root->v = std::to_string(value2int(root->v) < value2int(addexp_child->v));
                                break;
                            }
                            case TokenType::GTR:{
                                root->v = std::to_string(value2int(root->v) > value2int(addexp_child->v));
                                break;
                            }
                            case TokenType::LEQ:{
                                root->v = std::to_string(value2int(root->v) <= value2int(addexp_child->v));
                                break;
                            }
                            case TokenType::GEQ:{
                                root->v = std::to_string(value2int(root->v) >= value2int(addexp_child->v));
                                break;
                            }
                            default: assert(0);
                        }
                        root->t = Type::IntLiteral;
                        break;
                    }
                    case Type::Float:{
                        ir::Operand operand = symbol_table.add_temp(Type::Float);
                        ir::Operand temp = symbol_table.add_temp(Type::Int);
                        ir::Operand temp1 = symbol_table.add_temp(Type::Float);
                        instr = new ir::Instruction(ir::Operand(root->v, root->t), ir::Operand(), temp, ir::Operator::def);
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction(temp, ir::Operand(), temp1, ir::Operator::cvt_i2f);
                        COMMIT_INSTR(instr);
                        switch (term_child->token.type)
                        {
                            case TokenType::LSS:{
                                instr = new ir::Instruction(temp1, ir::Operand(addexp_child->v, addexp_child->t), operand, ir::Operator::flss);
                                break;
                            }
                            case TokenType::GTR:{
                                instr = new ir::Instruction(temp1, ir::Operand(addexp_child->v, addexp_child->t), operand, ir::Operator::fgtr);
                                break;
                            }
                            case TokenType::LEQ:{
                                instr = new ir::Instruction(temp1, ir::Operand(addexp_child->v, addexp_child->t), operand, ir::Operator::fgeq);
                                break;
                            }
                            case TokenType::GEQ:{
                                instr = new ir::Instruction(temp1, ir::Operand(addexp_child->v, addexp_child->t), operand, ir::Operator::fgeq);
                                break;
                            }
                            default: assert(0);
                        }
                        COMMIT_INSTR(instr);
                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    case Type::FloatLiteral:{
                        switch (term_child->token.type)
                        {
                            case TokenType::LSS:{
                                root->v = std::to_string(value2int(root->v) < value2float(addexp_child->v));
                                break;
                            }
                            case TokenType::GTR:{
                                root->v = std::to_string(value2int(root->v) > value2float(addexp_child->v));
                                break;
                            }
                            case TokenType::LEQ:{
                                root->v = std::to_string(value2int(root->v) <= value2float(addexp_child->v));
                                break;
                            }
                            case TokenType::GEQ:{
                                root->v = std::to_string(value2int(root->v) >= value2float(addexp_child->v));
                                break;
                            }
                            default: assert(0);
                        }
                        root->t = Type::IntLiteral;
                        break;
                    }
                    default: assert(0);
                }
                break;
            }
            case Type::Float:{
                switch (addexp_child->t)
                {
                    case Type::Int:{
                        ir::Operand operand = symbol_table.add_temp(Type::Float);
                        ir::Operand temp = symbol_table.add_temp(Type::Float);
                        instr = new ir::Instruction(ir::Operand(addexp_child->v, addexp_child->t), ir::Operand(), temp, ir::Operator::cvt_i2f);
                        COMMIT_INSTR(instr);
                        switch (term_child->token.type)
                        {
                            case TokenType::LSS:{
                                instr = new ir::Instruction(ir::Operand(root->v, root->t), temp, operand, ir::Operator::flss);
                                break;
                            }
                            case TokenType::GTR:{
                                instr = new ir::Instruction(ir::Operand(root->v, root->t), temp, operand, ir::Operator::fgtr);
                                break;
                            }
                            case TokenType::LEQ:{
                                instr = new ir::Instruction(ir::Operand(root->v, root->t), temp, operand, ir::Operator::fleq);
                                break;
                            }
                            case TokenType::GEQ:{
                                instr = new ir::Instruction(ir::Operand(root->v, root->t), temp, operand, ir::Operator::fgeq);
                                break;
                            }
                            default: assert(0);
                        }
                        COMMIT_INSTR(instr);
                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    case Type::IntLiteral:{
                        ir::Operand operand = symbol_table.add_temp(Type::Float);
                        ir::Operand temp = symbol_table.add_temp(Type::Int);
                        ir::Operand temp1 = symbol_table.add_temp(Type::Float);
                        instr = new ir::Instruction(ir::Operand(addexp_child->v, addexp_child->t), ir::Operand(), temp, ir::Operator::def);
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction(temp, ir::Operand(), temp1, ir::Operator::cvt_i2f);
                        COMMIT_INSTR(instr);
                        switch (term_child->token.type)
                        {
                            case TokenType::LSS:{
                                instr = new ir::Instruction(ir::Operand(root->v, root->t), temp1, operand, ir::Operator::flss);
                                break;
                            }
                            case TokenType::GTR:{
                                instr = new ir::Instruction(ir::Operand(root->v, root->t), temp1, operand, ir::Operator::fgtr);
                                break;
                            }
                            case TokenType::LEQ:{
                                instr = new ir::Instruction(ir::Operand(root->v, root->t), temp1, operand, ir::Operator::fleq);
                                break;
                            }
                            case TokenType::GEQ:{
                                instr = new ir::Instruction(ir::Operand(root->v, root->t), temp1, operand, ir::Operator::fgeq);
                                break;
                            }
                            default: assert(0);
                        }
                        COMMIT_INSTR(instr);
                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    case Type::Float:{
                        ir::Operand operand = symbol_table.add_temp(Type::Float);
                        switch (term_child->token.type)
                        {
                            case TokenType::LSS:{
                                instr = new ir::Instruction(ir::Operand(root->v, root->t), ir::Operand(addexp_child->v, addexp_child->t), operand, ir::Operator::flss);
                                break;
                            }
                            case TokenType::GTR:{
                                instr = new ir::Instruction(ir::Operand(root->v, root->t), ir::Operand(addexp_child->v, addexp_child->t), operand, ir::Operator::fgtr);
                                break;
                            }
                            case TokenType::LEQ:{
                                instr = new ir::Instruction(ir::Operand(root->v, root->t), ir::Operand(addexp_child->v, addexp_child->t), operand, ir::Operator::fleq);
                                break;
                            }
                            case TokenType::GEQ:{
                                instr = new ir::Instruction(ir::Operand(root->v, root->t), ir::Operand(addexp_child->v, addexp_child->t), operand, ir::Operator::fgeq);
                                break;
                            }
                            default: assert(0);
                        }
                        COMMIT_INSTR(instr);
                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    case Type::FloatLiteral:{
                        ir::Operand operand = symbol_table.add_temp(Type::Float);
                        ir::Operand temp = symbol_table.add_temp(Type::Float);
                        instr = new ir::Instruction(ir::Operand(addexp_child->v, addexp_child->t), ir::Operand(), temp, ir::Operator::fdef);
                        COMMIT_INSTR(instr);
                        switch (term_child->token.type)
                        {
                            case TokenType::LSS:{
                                instr = new ir::Instruction(ir::Operand(root->v, root->t), temp, operand, ir::Operator::flss);
                                break;
                            }
                            case TokenType::GTR:{
                                instr = new ir::Instruction(ir::Operand(root->v, root->t), temp, operand, ir::Operator::fgtr);
                                break;
                            }
                            case TokenType::LEQ:{
                                instr = new ir::Instruction(ir::Operand(root->v, root->t), temp, operand, ir::Operator::fleq);
                                break;
                            }
                            case TokenType::GEQ:{
                                instr = new ir::Instruction(ir::Operand(root->v, root->t), temp, operand, ir::Operator::fgeq);
                                break;
                            }
                            default: assert(0);
                        }
                        COMMIT_INSTR(instr);
                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    default: assert(0);
                }
                break;
            }
            case Type::FloatLiteral:{
                switch (addexp_child->t)
                {
                    case Type::Int:{
                        ir::Operand operand = symbol_table.add_temp(Type::Float);
                        ir::Operand temp = symbol_table.add_temp(Type::Float);
                        ir::Operand temp1 = symbol_table.add_temp(Type::Float);
                        instr = new ir::Instruction(ir::Operand(root->v, root->t), ir::Operand(), temp, ir::Operator::fdef);
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction(ir::Operand(addexp_child->v, addexp_child->t), ir::Operand(), temp1, ir::Operator::cvt_i2f);
                        COMMIT_INSTR(instr);
                        switch (term_child->token.type)
                        {
                            case TokenType::LSS:{
                                instr = new ir::Instruction(temp, temp1, operand, ir::Operator::flss);
                                break;
                            }
                            case TokenType::GTR:{
                                instr = new ir::Instruction(temp, temp1, operand, ir::Operator::fgtr);
                                break;
                            }
                            case TokenType::LEQ:{
                                instr = new ir::Instruction(temp, temp1, operand, ir::Operator::fgeq);
                                break;
                            }
                            case TokenType::GEQ:{
                                instr = new ir::Instruction(temp, temp1, operand, ir::Operator::fgeq);
                                break;
                            }
                            default: assert(0);
                        }
                        COMMIT_INSTR(instr);
                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    case Type::IntLiteral:{
                        switch (term_child->token.type)
                        {
                            case TokenType::LSS:{
                                root->v = std::to_string(value2float(root->v) < value2int(addexp_child->v));
                                break;
                            }
                            case TokenType::GTR:{
                                root->v = std::to_string(value2float(root->v) > value2int(addexp_child->v));
                                break;
                            }
                            case TokenType::LEQ:{
                                root->v = std::to_string(value2float(root->v) <= value2int(addexp_child->v));
                                break;
                            }
                            case TokenType::GEQ:{
                                root->v = std::to_string(value2float(root->v) >= value2int(addexp_child->v));
                                break;
                            }
                            default: assert(0);
                        }
                        root->t = Type::IntLiteral;
                        break;
                        break;
                    }
                    case Type::Float:{
                        ir::Operand operand = symbol_table.add_temp(Type::Float);
                        ir::Operand temp = symbol_table.add_temp(Type::Float);
                        instr = new ir::Instruction(ir::Operand(root->v, root->t), ir::Operand(), temp, ir::Operator::fdef);
                        COMMIT_INSTR(instr);
                        switch (term_child->token.type)
                        {
                            case TokenType::LSS:{
                                instr = new ir::Instruction(temp, ir::Operand(addexp_child->v, addexp_child->t), operand, ir::Operator::flss);
                                break;
                            }
                            case TokenType::GTR:{
                                instr = new ir::Instruction(temp, ir::Operand(addexp_child->v, addexp_child->t), operand, ir::Operator::fgtr);
                                break;
                            }
                            case TokenType::LEQ:{
                                instr = new ir::Instruction(temp, ir::Operand(addexp_child->v, addexp_child->t), operand, ir::Operator::fgeq);
                                break;
                            }
                            case TokenType::GEQ:{
                                instr = new ir::Instruction(temp, ir::Operand(addexp_child->v, addexp_child->t), operand, ir::Operator::fgeq);
                                break;
                            }
                            default: assert(0);
                        }
                        COMMIT_INSTR(instr);
                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    case Type::FloatLiteral:{
                        switch (term_child->token.type)
                        {
                            case TokenType::LSS:{
                                root->v = std::to_string(value2float(root->v) < value2float(addexp_child->v));
                                break;
                            }
                            case TokenType::GTR:{
                                root->v = std::to_string(value2float(root->v) > value2float(addexp_child->v));
                                break;
                            }
                            case TokenType::LEQ:{
                                root->v = std::to_string(value2float(root->v) <= value2float(addexp_child->v));
                                break;
                            }
                            case TokenType::GEQ:{
                                root->v = std::to_string(value2float(root->v) >= value2float(addexp_child->v));
                                break;
                            }
                            default: assert(0);
                        }
                        root->t = Type::IntLiteral;
                        break;
                    }
                    default: assert(0);
                }
                break;
            }
            default: assert(0);
        }
        index += 2;
    }
}

void frontend::Analyzer::transEqExp(EqExp* root, AstNode* p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"EqExp"<<std::endl;
    #endif
    assert(root->children.size() >=1);
    assert(root->children[0]->type == NodeType::RELEXP);

    RelExp* relexp_child = CVT_POINT(root->children[0], RelExp);
    transRelExp(relexp_child, root);
    root->v = relexp_child->v;
    root->t = relexp_child->t;

    int index = 1;
    while(index < root->children.size()){
        assert(root->children[index]->type == NodeType::TERMINAL && 
            (CVT_POINT(root->children[index], Term)->token.type == TokenType::EQL || CVT_POINT(root->children[index], Term)->token.type == TokenType::NEQ));
        assert(root->children[index+1]->type == NodeType::RELEXP);

        Term* term_child = CVT_POINT(root->children[index], Term);
        relexp_child = CVT_POINT(root->children[index+1], RelExp);
        transRelExp(relexp_child, root);

        ir::Instruction* instr;
        switch (root->t)
        {
            case Type::Int:{
                switch (relexp_child->t)
                {
                    case Type::Int:{
                        ir::Operand operand = symbol_table.add_temp(Type::Int);
                        instr = term_child->token.type == TokenType::EQL ?
                                new ir::Instruction(ir::Operand(root->v, root->t), ir::Operand(relexp_child->v, relexp_child->t), operand, ir::Operator::eq)
                                : new ir::Instruction(ir::Operand(root->v, root->t), ir::Operand(relexp_child->v, relexp_child->t), operand, ir::Operator::neq);
                        COMMIT_INSTR(instr);
                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    case Type::IntLiteral:{
                        ir::Operand operand = symbol_table.add_temp(Type::Int);
                        ir::Operand temp = symbol_table.add_temp(Type::Int);
                        instr = new ir::Instruction(ir::Operand(relexp_child->v, relexp_child->t), ir::Operand(), temp, ir::Operator::def);
                        COMMIT_INSTR(instr);
                        instr = term_child->token.type == TokenType::EQL ?
                                            new ir::Instruction(ir::Operand(root->v, root->t), temp, operand, ir::Operator::eq)
                                            : new ir::Instruction(ir::Operand(root->v, root->t), temp, operand, ir::Operator::neq);
                        COMMIT_INSTR(instr);
                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    case Type::Float:{
                        ir::Operand operand = symbol_table.add_temp(Type::Float);
                        ir::Operand temp = symbol_table.add_temp(Type::Float);
                        instr = new ir::Instruction(ir::Operand(root->v, root->t), ir::Operand(), temp, ir::Operator::cvt_i2f);
                        COMMIT_INSTR(instr);
                        instr = term_child->token.type == TokenType::EQL ?
                                            new ir::Instruction(temp, ir::Operand(root->v, root->t), operand, ir::Operator::feq)
                                            : new ir::Instruction(temp, ir::Operand(root->v, root->t), operand, ir::Operator::fneq);
                        COMMIT_INSTR(instr);
                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    case Type::FloatLiteral:{
                        ir::Operand operand = symbol_table.add_temp(Type::Float);
                        ir::Operand temp = symbol_table.add_temp(Type::Float);
                        ir::Operand temp1 = symbol_table.add_temp(Type::Float);
                        instr = new ir::Instruction(ir::Operand(root->v, root->t), ir::Operand(), temp, ir::Operator::cvt_i2f);
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction(ir::Operand(relexp_child->v, relexp_child->t), ir::Operand(), temp1, ir::Operator::fdef);
                        COMMIT_INSTR(instr);
                        instr = term_child->token.type == TokenType::EQL ?
                                            new ir::Instruction(ir::Operand(root->v, root->t), temp, operand, ir::Operator::feq)
                                            : new ir::Instruction(ir::Operand(root->v, root->t), temp, operand, ir::Operator::fneq);
                        COMMIT_INSTR(instr);
                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    default: assert(0);
                }
                break;
            }
            case Type::IntLiteral:{
                switch (relexp_child->t)
                {
                    case Type::Int:{
                        ir::Operand operand = symbol_table.add_temp(Type::Int);
                        ir::Operand temp = symbol_table.add_temp(Type::Int);
                        instr = new ir::Instruction(ir::Operand(root->v, root->t), ir::Operand(), temp, ir::Operator::def);
                        COMMIT_INSTR(instr);
                        instr = term_child->token.type == TokenType::EQL ?
                                            new ir::Instruction(temp, ir::Operand(relexp_child->v, relexp_child->t), operand, ir::Operator::eq)
                                            : new ir::Instruction(temp, ir::Operand(relexp_child->v, relexp_child->t), operand, ir::Operator::neq);
                        COMMIT_INSTR(instr);
                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    case Type::IntLiteral:{
                        root->v = term_child->token.type == TokenType::EQL ? std::to_string(value2int(root->v) == value2int(relexp_child->v)) 
                                : std::to_string(value2int(root->v) != value2int(relexp_child->v));
                        root->t = Type::IntLiteral;
                        break;
                    }
                    case Type::Float:{
                        ir::Operand operand = symbol_table.add_temp(Type::Float);
                        ir::Operand temp = symbol_table.add_temp(Type::Int);
                        ir::Operand temp1 = symbol_table.add_temp(Type::Float);
                        instr = new ir::Instruction(ir::Operand(root->v, root->t), ir::Operand(), temp, ir::Operator::def);
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction(temp, ir::Operand(), temp1, ir::Operator::cvt_i2f);
                        COMMIT_INSTR(instr);
                        instr = term_child->token.type == TokenType::EQL ?
                                            new ir::Instruction(temp1, ir::Operand(relexp_child->v, relexp_child->t), operand, ir::Operator::feq)
                                            : new ir::Instruction(temp1, ir::Operand(relexp_child->v, relexp_child->t), operand, ir::Operator::fneq);
                        COMMIT_INSTR(instr);
                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    case Type::FloatLiteral:{
                        root->v = term_child->token.type == TokenType::EQL ? std::to_string(value2int(root->v) == value2float(relexp_child->v)) 
                                : std::to_string(value2int(root->v) != value2float(relexp_child->v));
                        root->t = Type::IntLiteral;
                        break;
                    }
                    default: assert(0);
                }
                break;
            }
            case Type::Float:{
                switch (relexp_child->t)
                {
                    case Type::Int:{
                        ir::Operand operand = symbol_table.add_temp(Type::Float);
                        ir::Operand temp = symbol_table.add_temp(Type::Float);
                        instr = new ir::Instruction(ir::Operand(relexp_child->v, relexp_child->t), ir::Operand(), temp, ir::Operator::cvt_i2f);
                        COMMIT_INSTR(instr);
                        instr = term_child->token.type == TokenType::EQL ?
                                            new ir::Instruction(ir::Operand(root->v, root->t), temp, operand, ir::Operator::feq)
                                            : new ir::Instruction(ir::Operand(root->v, root->t), temp, operand, ir::Operator::fneq);
                        COMMIT_INSTR(instr);
                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    case Type::IntLiteral:{
                        ir::Operand operand = symbol_table.add_temp(Type::Float);
                        ir::Operand temp = symbol_table.add_temp(Type::Int);
                        ir::Operand temp1 = symbol_table.add_temp(Type::Float);
                        instr = new ir::Instruction(ir::Operand(relexp_child->v, relexp_child->t), ir::Operand(), temp, ir::Operator::def);
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction(temp, ir::Operand(), temp1, ir::Operator::cvt_i2f);
                        COMMIT_INSTR(instr);
                        instr = term_child->token.type == TokenType::EQL ?
                                            new ir::Instruction(ir::Operand(root->v, root->t), temp1, operand, ir::Operator::feq)
                                            : new ir::Instruction(ir::Operand(root->v, root->t), temp1, operand, ir::Operator::fneq);
                        COMMIT_INSTR(instr);
                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    case Type::Float:{
                        ir::Operand operand = symbol_table.add_temp(Type::Float);
                        instr = term_child->token.type == TokenType::EQL ?
                                new ir::Instruction(ir::Operand(root->v, root->t), ir::Operand(relexp_child->v, relexp_child->t), operand, ir::Operator::feq)
                                : new ir::Instruction(ir::Operand(root->v, root->t), ir::Operand(relexp_child->v, relexp_child->t), operand, ir::Operator::fneq);
                        COMMIT_INSTR(instr);
                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    case Type::FloatLiteral:{
                        ir::Operand operand = symbol_table.add_temp(Type::Float);
                        ir::Operand temp = symbol_table.add_temp(Type::Float);
                        instr = new ir::Instruction(ir::Operand(relexp_child->v, relexp_child->t), ir::Operand(), temp, ir::Operator::fdef);
                        COMMIT_INSTR(instr);
                        instr = term_child->token.type == TokenType::EQL ?
                                            new ir::Instruction(ir::Operand(root->v, root->t), temp, operand, ir::Operator::feq)
                                            : new ir::Instruction(ir::Operand(root->v, root->t), temp, operand, ir::Operator::fneq);
                        COMMIT_INSTR(instr);
                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    default: assert(0);
                }
                break;
            }
            case Type::FloatLiteral:{
                switch (relexp_child->t)
                {
                    case Type::Int:{
                        ir::Operand operand = symbol_table.add_temp(Type::Float);
                        ir::Operand temp = symbol_table.add_temp(Type::Float);
                        ir::Operand temp1 = symbol_table.add_temp(Type::Float);
                        instr = new ir::Instruction(ir::Operand(root->v, root->t), ir::Operand(), temp, ir::Operator::fdef);
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction(ir::Operand(relexp_child->v, relexp_child->t), ir::Operand(), temp1, ir::Operator::cvt_i2f);
                        COMMIT_INSTR(instr);
                        instr = term_child->token.type == TokenType::EQL ?
                                            new ir::Instruction(temp, temp1, operand, ir::Operator::feq)
                                            : new ir::Instruction(temp, temp1, operand, ir::Operator::fneq);
                        COMMIT_INSTR(instr);
                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    case Type::IntLiteral:{
                        root->v = term_child->token.type == TokenType::EQL ? std::to_string(value2float(root->v) == value2int(relexp_child->v)) 
                                : std::to_string(value2float(root->v) != value2int(relexp_child->v));
                        root->t = Type::IntLiteral;
                        break;
                        break;
                    }
                    case Type::Float:{
                        ir::Operand operand = symbol_table.add_temp(Type::Float);
                        ir::Operand temp = symbol_table.add_temp(Type::Float);
                        instr = new ir::Instruction(ir::Operand(root->v, root->t), ir::Operand(), temp, ir::Operator::fdef);
                        COMMIT_INSTR(instr);
                        instr = term_child->token.type == TokenType::EQL ?
                                            new ir::Instruction(temp, ir::Operand(relexp_child->v, relexp_child->t), operand, ir::Operator::feq)
                                            : new ir::Instruction(temp, ir::Operand(relexp_child->v, relexp_child->t), operand, ir::Operator::fneq);
                        COMMIT_INSTR(instr);
                        root->v = operand.name;
                        root->t = operand.type;
                        break;
                    }
                    case Type::FloatLiteral:{
                        root->v = term_child->token.type == TokenType::EQL ? std::to_string(value2float(root->v) == value2float(relexp_child->v)) 
                                : std::to_string(value2float(root->v) != value2float(relexp_child->v));
                        root->t = Type::IntLiteral;
                        break;
                    }
                    default: assert(0);
                }
                break;
            }
            default: assert(0);
        }
        index += 2;
    }
}

void frontend::Analyzer::transLAndExp(LAndExp* root, AstNode* p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"LAndExp"<<std::endl;
    #endif
    assert(root->children.size() >= 1);
    assert(root->children[0]->type == NodeType::EQEXP);
    EqExp* eqexp_child = CVT_POINT(root->children[0], EqExp);
    transEqExp(eqexp_child, root);

    if(root->children.size() == 3 && root->children[1]->type == NodeType::TERMINAL && CVT_POINT(root->children[1], Term)->token.type == TokenType::AND){
        assert(root->children[2]->type == NodeType::LANDEXP);

        LAndExp* landexp_child = CVT_POINT(root->children[2], LAndExp);
        
        switch (eqexp_child->t)
        {
            case Type::Int:{
                ir::Operand operand = symbol_table.add_temp(Type::Int);
                ir::Operand temp = symbol_table.add_temp(Type::Int);
                ir::Instruction* instr;
                instr = new ir::Instruction(ir::Operand(eqexp_child->v, eqexp_child->t), ir::Operand(), operand, ir::Operator::mov);
                COMMIT_INSTR(instr);
                instr = new ir::Instruction(operand, ir::Operand(), temp, ir::Operator::_not);
                COMMIT_INSTR(instr);
                instr = new ir::Instruction(temp, ir::Operand(), ir::Operand(), ir::Operator::_goto);
                COMMIT_INSTR(instr);
                int label = curr_function->InstVec.size() - 1;
                transLAndExp(landexp_child, root);
                switch (landexp_child->t)
                {
                    case Type::Int:{
                        instr = new ir::Instruction(operand, ir::Operand(landexp_child->v, landexp_child->t), operand, ir::Operator::_and);
                        COMMIT_INSTR(instr);
                        break;
                    }
                    case Type::IntLiteral:{
                        if(value2int(landexp_child->v) == 0){
                            operand = ir::Operand("0", Type::IntLiteral);
                        }
                        break;
                    }
                    case Type::Float:{
                        ir::Operand temp = symbol_table.add_temp(Type::Float);
                        ir::Operand temp1 = symbol_table.add_temp(Type::Int);
                        instr = new ir::Instruction(ir::Operand(landexp_child->v, landexp_child->t), 
                                                                    symbol_table.fzero, temp, ir::Operator::fneq);
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction(temp, ir::Operand() , temp1, ir::Operator::cvt_f2i);
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction(operand, temp1 , operand, ir::Operator::_and);
                        COMMIT_INSTR(instr);
                        break;
                    }
                    case Type::FloatLiteral:{
                        if(value2float(landexp_child->v) == 0){
                            operand = ir::Operand("0", Type::IntLiteral);
                        }
                        break;
                    }
                    default: assert(0);
                }
                instr = new ir::Instruction(ir::Operand(), ir::Operand(), ir::Operand(), ir::Operator::__unuse__);
                COMMIT_INSTR(instr);
                curr_function->InstVec[label]->des = ir::Operand(std::to_string(curr_function->InstVec.size() - 1 - label), Type::IntLiteral);

                root->v = operand.name;
                root->t = operand.type;
                break;
            }
            case Type::IntLiteral:{
                if(value2int(eqexp_child->v) == 0){
                    root->v = "0";
                    root->t = Type::IntLiteral;
                }
                else{
                    transLAndExp(landexp_child, root);
                    root->v = landexp_child->v;
                    root->t = landexp_child->t;
                }
                break;
            }
            case Type::Float:{
                ir::Operand operand = symbol_table.add_temp(Type::Int);
                ir::Operand temp = symbol_table.add_temp(Type::Float);
                ir::Operand temp1 = symbol_table.add_temp(Type::Int);
                ir::Instruction* instr;
                instr = new ir::Instruction(ir::Operand(eqexp_child->v, eqexp_child->t), ir::Operand(), temp, ir::Operator::fneq);
                COMMIT_INSTR(instr);
                instr = new ir::Instruction(temp, ir::Operand(), operand, ir::Operator::cvt_f2i);
                COMMIT_INSTR(instr);
                instr = new ir::Instruction(operand, ir::Operand(), temp1, ir::Operator::_not);
                COMMIT_INSTR(instr);
                instr = new ir::Instruction(temp1, ir::Operand(), ir::Operand(), ir::Operator::_goto);
                COMMIT_INSTR(instr);
                int label = curr_function->InstVec.size() - 1;
                transLAndExp(landexp_child, root);
                switch (landexp_child->t)
                {
                    case Type::Int:{
                        instr = new ir::Instruction(operand, ir::Operand(landexp_child->v, landexp_child->t), operand, ir::Operator::_and);
                        COMMIT_INSTR(instr);
                        break;
                    }
                    case Type::IntLiteral:{
                        if(value2int(landexp_child->v) == 0){
                            operand = ir::Operand("0", Type::IntLiteral);
                        }
                        break;
                    }
                    case Type::Float:{
                        ir::Operand temp = symbol_table.add_temp(Type::Float);
                        ir::Operand temp1 = symbol_table.add_temp(Type::Int);
                        instr = new ir::Instruction(ir::Operand(landexp_child->v, landexp_child->t), 
                                                                    symbol_table.fzero, temp, ir::Operator::fneq);
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction(temp, ir::Operand() , temp1, ir::Operator::cvt_f2i);
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction(operand, temp1 , operand, ir::Operator::_and);
                        COMMIT_INSTR(instr);
                        break;
                    }
                    case Type::FloatLiteral:{
                        if(value2float(landexp_child->v) == 0){
                            operand = ir::Operand("0", Type::IntLiteral);
                        }
                        break;
                    }
                    default: assert(0);
                }

                instr = new ir::Instruction(ir::Operand(), ir::Operand(), ir::Operand(), ir::Operator::__unuse__);
                COMMIT_INSTR(instr);
                curr_function->InstVec[label]->des = ir::Operand(std::to_string(curr_function->InstVec.size() - 1 - label), Type::IntLiteral);

                root->v = operand.name;
                root->t = operand.type;
                break;
            }
            case Type::FloatLiteral:{
                if(value2float(eqexp_child->v) == 0){
                    root->v = "0";
                    root->t = Type::IntLiteral;
                }
                else{
                    transLAndExp(landexp_child, root);
                    root->v = landexp_child->v;
                    root->t = landexp_child->t;
                }
                break;
            }
            default: assert(0);
        }
    }
    else{
        root->v = eqexp_child->v;
        root->t = eqexp_child->t;
    }
}

void frontend::Analyzer::transLOrExp(LOrExp* root, AstNode* p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"LOrExp"<<std::endl;
    #endif
    assert(root->children.size() >= 1);
    assert(root->children[0]->type == NodeType::LANDEXP);
    LAndExp* landexp_child = CVT_POINT(root->children[0], LAndExp);
    transLAndExp(landexp_child, root);

    if(root->children.size() == 3 && root->children[1]->type == NodeType::TERMINAL && CVT_POINT(root->children[1], Term)->token.type == TokenType::OR){
        assert(root->children[2]->type == NodeType::LOREXP);

        LOrExp* lorexp_child = CVT_POINT(root->children[2], LOrExp);
     
        switch (landexp_child->t)
        {
            case Type::Int:{
                ir::Operand operand = symbol_table.add_temp(Type::Int);
                ir::Instruction* instr;
                instr = new ir::Instruction(ir::Operand(landexp_child->v, landexp_child->t), ir::Operand(), operand, ir::Operator::mov);
                COMMIT_INSTR(instr);
                instr = new ir::Instruction(operand, ir::Operand(), ir::Operand(), ir::Operator::_goto);
                COMMIT_INSTR(instr);
                int label = curr_function->InstVec.size() - 1;
                transLOrExp(lorexp_child, root);
                switch (lorexp_child->t)
                {
                    case Type::Int:{
                        instr = new ir::Instruction(operand, ir::Operand(lorexp_child->v, lorexp_child->t), operand, ir::Operator::_or);
                        COMMIT_INSTR(instr);
                        break;
                    }
                    case Type::IntLiteral:{
                        if(value2int(lorexp_child->v) != 0){
                            operand = ir::Operand("1", Type::IntLiteral);
                        }
                        break;
                    }
                    case Type::Float:{
                        ir::Operand temp = symbol_table.add_temp(Type::Float);
                        ir::Operand temp1 = symbol_table.add_temp(Type::Int);
                        instr = new ir::Instruction(ir::Operand(lorexp_child->v, lorexp_child->t), 
                                                                    symbol_table.fzero, temp, ir::Operator::fneq);
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction(temp, ir::Operand() , temp1, ir::Operator::cvt_f2i);
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction(operand, temp1 , operand, ir::Operator::_or);
                        COMMIT_INSTR(instr);
                        break;
                    }
                    case Type::FloatLiteral:{
                        if(value2float(lorexp_child->v) != 0){
                            operand = ir::Operand("1", Type::IntLiteral);
                        }
                        break;
                    }
                    default: assert(0);
                }
                instr = new ir::Instruction(ir::Operand(), ir::Operand(), ir::Operand(), ir::Operator::__unuse__);
                COMMIT_INSTR(instr);
                curr_function->InstVec[label]->des = ir::Operand(std::to_string(curr_function->InstVec.size() - 1 - label), Type::IntLiteral);

                root->v = operand.name;
                root->t = operand.type;
                break;
            }
            case Type::IntLiteral:{
                if(value2int(landexp_child->v) != 0){
                    root->v = "1";
                    root->t = Type::IntLiteral;
                }
                else{
                    transLOrExp(lorexp_child, root);
                    root->v = lorexp_child->v;
                    root->t = lorexp_child->t;
                }
                break;
            }
            case Type::Float:{
                ir::Operand operand = symbol_table.add_temp(Type::Int);
                ir::Operand temp = symbol_table.add_temp(Type::Float);
                ir::Instruction* instr;
                instr = new ir::Instruction(ir::Operand(landexp_child->v, landexp_child->t), ir::Operand(), temp, ir::Operator::fneq);
                COMMIT_INSTR(instr);
                instr = new ir::Instruction(temp, ir::Operand(), operand, ir::Operator::cvt_f2i);
                COMMIT_INSTR(instr);
                instr = new ir::Instruction(operand, ir::Operand(), ir::Operand(), ir::Operator::_goto);
                COMMIT_INSTR(instr);
                int label = curr_function->InstVec.size() - 1;
                transLOrExp(lorexp_child, root);
                switch (lorexp_child->t)
                {
                    case Type::Int:{
                        instr = new ir::Instruction(operand, ir::Operand(lorexp_child->v, lorexp_child->t), operand, ir::Operator::_or);
                        COMMIT_INSTR(instr);
                        break;
                    }
                    case Type::IntLiteral:{
                        if(value2int(lorexp_child->v) != 0){
                            operand = ir::Operand("1", Type::IntLiteral);
                        }
                        break;
                    }
                    case Type::Float:{
                        ir::Operand temp = symbol_table.add_temp(Type::Float);
                        ir::Operand temp1 = symbol_table.add_temp(Type::Int);
                        instr = new ir::Instruction(ir::Operand(lorexp_child->v, lorexp_child->t), 
                                                                    symbol_table.fzero, temp, ir::Operator::fneq);
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction(temp, ir::Operand() , temp1, ir::Operator::cvt_f2i);
                        COMMIT_INSTR(instr);
                        instr = new ir::Instruction(operand, temp1 , operand, ir::Operator::_or);
                        COMMIT_INSTR(instr);
                        break;
                    }
                    case Type::FloatLiteral:{
                        if(value2float(lorexp_child->v) != 0){
                            operand = ir::Operand("1", Type::IntLiteral);
                        }
                        break;
                    }
                    default: assert(0);
                }

                instr = new ir::Instruction(ir::Operand(), ir::Operand(), ir::Operand(), ir::Operator::__unuse__);
                COMMIT_INSTR(instr);
                curr_function->InstVec[label]->des = ir::Operand(std::to_string(curr_function->InstVec.size() - 1 - label), Type::IntLiteral);

                root->v = operand.name;
                root->t = operand.type;
                break;
            }
            case Type::FloatLiteral:{
                if(value2float(landexp_child->v) != 0){
                    root->v = "1";
                    root->t = Type::IntLiteral;
                }
                else{
                    transLOrExp(lorexp_child, root);
                    root->v = lorexp_child->v;
                    root->t = lorexp_child->t;
                }
                break;
            }
            default: assert(0);
        }

    }
    else{
        root->v = landexp_child->v;
        root->t = landexp_child->t;
    }
}



void frontend::Analyzer::transVarDecl(VarDecl* root, AstNode* p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"VarDecl"<<std::endl;
    #endif
    assert(root->children.size()>=3);
    assert(root->children[0]->type == NodeType::BTYPE);
    assert(root->children[1]->type == NodeType::VARDEF);

    BType* btype_child;
    VarDef* vardef_child;

    btype_child = CVT_POINT(root->children[0],BType);
    transBType( btype_child, root->children[0] );
    root->t = btype_child->t;

    int index = 1;
    while (root->children[index]->type == NodeType::VARDEF)
    {
        vardef_child = CVT_POINT(root->children[index], VarDef);
        transVarDef(vardef_child, root);

        if(root->children[index+1]->type == NodeType::TERMINAL && ((Term*)root->children[index+1])->token.type == TokenType::COMMA) index += 2;
        else break;
    }
    
    assert(root->children[index+1]->type == NodeType::TERMINAL && ((Term*)root->children[index+1])->token.type == TokenType::SEMICN);
}


void frontend::Analyzer::transVarDef(VarDef* root, AstNode* p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"VarDef"<<std::endl;
    #endif
    assert(root->children.size()>=1);

    Term* ident_child;
    ConstExp* constexp_child;
    InitVal* initval_child;
    ir::Operand operand;
    ir::Instruction* instr;

    assert(root->children[0]->type == NodeType::TERMINAL && CVT_POINT(root->children[0], Term)->token.type ==TokenType::IDENFR );
    ident_child = CVT_POINT(root->children[0], Term);
    root->arr_name = ident_child->token.value;

    vector<int>dimension;
    int maxlen = 0;

    int index = 1;
    if(index < root->children.size() && root->children[index]->type == NodeType::TERMINAL && CVT_POINT(root->children[index], Term)->token.type == TokenType::LBRACK) maxlen++;
    while(index < root->children.size() && root->children[index]->type == NodeType::TERMINAL && 
        CVT_POINT(root->children[index], Term)->token.type == TokenType::LBRACK){
        
        assert(root->children[index+1]->type == NodeType::CONSTEXP);
        assert(root->children[index+2]->type == NodeType::TERMINAL && CVT_POINT(root->children[index+2], Term)->token.type == TokenType::RBRACK);

        constexp_child = CVT_POINT(root->children[index+1], ConstExp);
        transConstExp(constexp_child, root);
        assert(constexp_child->t == Type::IntLiteral);
        int dim = std::stoi(constexp_child->v, 0, 10);
        maxlen *= dim;
        dimension.push_back(dim);

        index += 3;
    }

    auto ptype = CVT_POINT(p, VarDecl)->t;
    if(ptype == Type::Int && maxlen == 0) root->t = Type::Int;
    else if(ptype == Type::Int && maxlen > 0) root->t = Type::IntPtr;
    else if(ptype == Type::Float && maxlen == 0) root->t = Type::Float;
    else if(ptype == Type::Float && maxlen > 0) root->t = Type::FloatPtr;
    else assert(0);
    

    assert(symbol_table.get_operand_inscope(root->arr_name).type == Type::null);
    if(maxlen == 0){
        operand = symbol_table.add_ste(root->arr_name, dimension, root->t );
        if(curr_function->name == "global"){
            // prog->addGlobalVal(operand, 0);
            prog->globalVal.push_back(ir::GlobalVal(operand, 0));
        } 
        if(index < root->children.size() && root->children[index]->type == NodeType::TERMINAL &&  
                CVT_POINT(root->children[index], Term)->token.type == TokenType::ASSIGN){
            index++;
            assert(root->children[index]->type == NodeType::INITVAL);
            initval_child = CVT_POINT(root->children[index], InitVal);
            transInitVal(initval_child, root);

            switch (root->t)
            {
                case Type::Int:{
                    switch (initval_child->v[0].type)
                    {
                        case Type::Int:{
                            instr = new ir::Instruction(initval_child->v[0], ir::Operand(), operand, ir::Operator::mov);
                            COMMIT_INSTR(instr);
                            break;
                        }
                        case Type::IntLiteral:{
                            instr = new ir::Instruction(initval_child->v[0], ir::Operand(), operand, ir::Operator::def);
                            COMMIT_INSTR(instr);
                            break;
                        }
                        case Type::Float:{
                            instr = new ir::Instruction(initval_child->v[0], ir::Operand(), operand, ir::Operator::cvt_f2i);
                            COMMIT_INSTR(instr);
                            break;
                        }
                        case Type::FloatLiteral:{
                            auto temp = symbol_table.add_temp(Type::Float);
                            instr = new ir::Instruction(initval_child->v[0], ir::Operand(), temp, ir::Operator::fdef);
                            COMMIT_INSTR(instr);
                            instr = new ir::Instruction(temp, ir::Operand(), operand, ir::Operator::cvt_f2i);
                            COMMIT_INSTR(instr);
                            break;
                        }
                        default: assert(0);
                    }
                    break;
                }
                case Type::Float:{
                    switch (initval_child->v[0].type)
                    {
                        case Type::Int:{
                            instr = new ir::Instruction(initval_child->v[0], ir::Operand(), operand, ir::Operator::cvt_i2f);
                            COMMIT_INSTR(instr);
                            break;
                        }
                        case Type::IntLiteral:{
                            auto temp = symbol_table.add_temp(Type::Int);
                            instr = new ir::Instruction(initval_child->v[0], ir::Operand(), temp, ir::Operator::def);
                            COMMIT_INSTR(instr);
                            instr = new ir::Instruction(temp, ir::Operand(), operand, ir::Operator::cvt_i2f);
                            COMMIT_INSTR(instr);
                            break;
                        }
                        case Type::Float:{
                            instr = new ir::Instruction(initval_child->v[0], ir::Operand(), operand, ir::Operator::fmov);
                            COMMIT_INSTR(instr);
                            break;
                        }
                        case Type::FloatLiteral:{
                            instr = new ir::Instruction(initval_child->v[0], ir::Operand(), operand, ir::Operator::fdef);
                            COMMIT_INSTR(instr);
                            break;
                        }
                        default: assert(0);
                    }
                    break;
                }
                default: assert(0);
            }
        }
    } 
    else{
        operand = symbol_table.add_ste(root->arr_name, dimension, root->t );
        if(curr_function->name == "global"){
            // prog->addGlobalVal(operand, maxlen);
            prog->globalVal.push_back(ir::GlobalVal(operand, maxlen));
        } 
        if(curr_function->name != "global"){
            instr = new ir::Instruction(ir::Operand(std::to_string(maxlen), Type::IntLiteral), ir::Operand(), operand, ir::Operator::alloc);
            COMMIT_INSTR(instr);
        }

        if(index < root->children.size() && root->children[index]->type == NodeType::TERMINAL &&  
                CVT_POINT(root->children[index], Term)->token.type == TokenType::ASSIGN){
            index++;
            assert(root->children[index]->type == NodeType::INITVAL);
            initval_child = CVT_POINT(root->children[index], InitVal);
            transInitVal(initval_child, root);
            
            assert(initval_child->v.size() <= maxlen);
            for(int i = 0; i < maxlen; i++){
                if(i < initval_child->v.size()){
                    switch (root->t)
                    {
                        case Type::IntPtr:{
                            switch (initval_child->v[i].type)
                            {
                                case Type::Int:{
                                    instr = new ir::Instruction(operand, ir::Operand(std::to_string(i), Type::IntLiteral), initval_child->v[i], ir::Operator::store);
                                    COMMIT_INSTR(instr);
                                    break;
                                }
                                case Type::IntLiteral:{
                                    auto temp = symbol_table.add_temp(Type::Int);
                                    instr = new ir::Instruction(initval_child->v[i], ir::Operand(), temp, ir::Operator::def);
                                    COMMIT_INSTR(instr);
                                    instr = new ir::Instruction(operand, ir::Operand(std::to_string(i), Type::IntLiteral), temp, ir::Operator::store);
                                    COMMIT_INSTR(instr);
                                    break;
                                }
                                case Type::Float:{
                                    auto temp = symbol_table.add_temp(Type::Int);
                                    instr = new ir::Instruction(initval_child->v[i], ir::Operand(), temp, ir::Operator::cvt_f2i);
                                    COMMIT_INSTR(instr);
                                    instr = new ir::Instruction(operand, ir::Operand(std::to_string(i), Type::IntLiteral), temp, ir::Operator::store);
                                    COMMIT_INSTR(instr);
                                    break;
                                }
                                case Type::FloatLiteral:{
                                    auto temp = symbol_table.add_temp(Type::Float);
                                    auto temp1 = symbol_table.add_temp(Type::Int);
                                    instr = new ir::Instruction(initval_child->v[i], ir::Operand(), temp, ir::Operator::fdef);
                                    COMMIT_INSTR(instr);
                                    instr = new ir::Instruction(temp, ir::Operand(), temp1, ir::Operator::cvt_f2i);
                                    COMMIT_INSTR(instr);
                                    instr = new ir::Instruction(operand, ir::Operand(std::to_string(i), Type::IntLiteral), temp1, ir::Operator::store);
                                    COMMIT_INSTR(instr);
                                    break;
                                }
                                default: assert(0);
                            }
                            break;
                        }
                        case Type::FloatPtr:{
                            switch (initval_child->v[i].type)
                            {
                                case Type::Int:{
                                    auto temp = symbol_table.add_temp(Type::Float);
                                    instr = new ir::Instruction(initval_child->v[i], ir::Operand(), temp, ir::Operator::cvt_i2f);
                                    COMMIT_INSTR(instr);
                                    instr = new ir::Instruction(operand, ir::Operand(std::to_string(i), Type::IntLiteral), temp, ir::Operator::store);
                                    COMMIT_INSTR(instr);
                                    break;
                                }
                                case Type::IntLiteral:{
                                    auto temp = symbol_table.add_temp(Type::Int);
                                    auto temp1 = symbol_table.add_temp(Type::Float);
                                    instr = new ir::Instruction(initval_child->v[i], ir::Operand(), temp, ir::Operator::def);
                                    COMMIT_INSTR(instr);
                                    instr = new ir::Instruction(temp, ir::Operand(), temp1, ir::Operator::cvt_i2f);
                                    COMMIT_INSTR(instr);
                                    instr = new ir::Instruction(operand, ir::Operand(std::to_string(i), Type::IntLiteral), temp1, ir::Operator::store);
                                    COMMIT_INSTR(instr);
                                    break;
                                }
                                case Type::Float:{
                                    instr = new ir::Instruction(operand, ir::Operand(std::to_string(i), Type::IntLiteral), initval_child->v[i], ir::Operator::store);
                                    COMMIT_INSTR(instr);
                                    break;
                                }
                                case Type::FloatLiteral:{
                                    auto temp = symbol_table.add_temp(Type::Float);
                                    instr = new ir::Instruction(initval_child->v[i], ir::Operand(), temp, ir::Operator::fdef);
                                    COMMIT_INSTR(instr);
                                    instr = new ir::Instruction(operand, ir::Operand(std::to_string(i), Type::IntLiteral), temp, ir::Operator::store);
                                    COMMIT_INSTR(instr);
                                    break;
                                }
                                default: assert(0);
                            }
                            break;
                        }
                        default: assert(0);
                    }
                }
                else{
                    instr = root->t == Type::IntPtr ? new ir::Instruction(operand, ir::Operand(std::to_string(i), Type::IntLiteral), symbol_table.zero, ir::Operator::store)
                            : new ir::Instruction(operand, ir::Operand(std::to_string(i), Type::IntLiteral), symbol_table.fzero, ir::Operator::store);
                    COMMIT_INSTR(instr);
                }               
            } 
        }
    }
    
}


void frontend::Analyzer::transInitVal(InitVal* root, AstNode* p){
    #ifdef SEMANTIC_DEBUG  
    std::cout<<"InitVal"<<std::endl;
    #endif

    /**
     * @brief single literal/variable
     * 
     */
    if(root->children.size() == 1){
        assert(root->children[0]->type == NodeType::EXP);
        Exp* exp_child = CVT_POINT(root->children[0], Exp);
        transExp(exp_child, root);
        root->v.push_back(ir::Operand(exp_child->v, exp_child->t));
        // if(exp_child->t == Type::Int || exp_child->t == Type::Float){
        //     root->v.push_back(ir::Operand(exp_child->v, exp_child->t));
        //     root->t = exp_child->t;
        // }
        // else if(exp_child->t == Type::IntLiteral){
        //     ir::Operand operand = symbol_table.add_temp(Type::Int);
        //     ir::Instruction* instr = new ir::Instruction(ir::Operand(exp_child->v, Type::IntLiteral), ir::Operand(), operand, ir::Operator::def);
        //     COMMIT_INSTR(instr);
        //     root->v.push_back(operand);
        //     root->t = Type::Int;
        // }
        // else if(exp_child->t == Type::FloatLiteral){
        //     ir::Operand operand = symbol_table.add_temp(Type::Float);
        //     ir::Instruction* instr = new ir::Instruction(ir::Operand(exp_child->v, Type::FloatLiteral), ir::Operand(), operand, ir::Operator::fdef);
        //     COMMIT_INSTR(instr);
        //     root->v.push_back(operand);
        //     root->t = Type::Float;
        // }
        // else assert(0);
    }

    /**
     * @brief complex variables
     * 
     */
    else{
  
        assert(root->children[0]->type == NodeType::TERMINAL && CVT_POINT(root->children[0], Term)->token.type == TokenType::LBRACE);
        if(root->children[1]->type == NodeType::TERMINAL && CVT_POINT(root->children[1], Term)->token.type == TokenType::RBRACE) return;
        assert(root->children[1]->type == NodeType::INITVAL);

        InitVal* initval_child = CVT_POINT(root->children[1], InitVal);
        transInitVal(initval_child, root);
        assert(initval_child->v.size() == 1);
        root->v.push_back(initval_child->v[0]);

        int index = 2;
        while (index < root->children.size() && 
            root->children[index]->type == NodeType::TERMINAL && CVT_POINT(root->children[index], Term)->token.type == TokenType::COMMA){
            initval_child = CVT_POINT(root->children[index+1], InitVal);
            transInitVal(initval_child, root);
            assert(initval_child->v.size() == 1);         
            root->v.push_back(initval_child->v[0]);
            index += 2;
        }
        
    }
}


int frontend::value2int(std::string value){
    if(value.length() == 1) return std::stoi(value, 0, 10);
    else if(value.length() > 1){
        if(value[0] == '0'){
            if(value[1] == 'b') return std::stoi(value.substr(2, value.length() - 2), 0, 2);
            else if(value[1] == 'x') return std::stoi(value.substr(2, value.length() - 2), 0, 16);
            else return std::stoi(value.substr(1, value.length() - 1), 0, 8);
        }
        else return std::stoi(value, 0, 10);
    }
}

double frontend::value2float(std::string value){
    return std::atof(value.c_str());
}