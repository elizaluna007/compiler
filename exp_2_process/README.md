# 语义分析的executor分析
##### // init global variables
#####     for(const auto& gte: program->globalVal) {                                  //遍历全局变量
#####         std::pair<std::string, Value> entry = {gte.val.name, {gte.val.type, 0}};//得到全局变量的名称和{类型,值}
#####         if (gte.maxlen) {                                                       //如果全局变量存在并且是数组
#####             if (gte.val.type == Type::IntPtr) {                                 //整型指针
#####                 entry.second._val.iptr = new int[gte.maxlen];                   //值为整型数组
##### 
#####             }
#####             else if (gte.val.type == Type::FloatPtr) {                          //浮点型指针
#####                 entry.second._val.fptr = new float[gte.maxlen];                 //值为浮点形数组
#####             }
#####             else {
#####                 assert(0 && "wrong global value type with maxlen > 0");
#####             }
#####         }
#####         global_vars.insert(entry);                                               //全局变量的{名称,{类型,值}}添加到global_vars中
#####     }

##### // find main function and set cur_cxt
#####     for(const auto& f: program->functions) {                                    //遍历函数块
#####         if (f.name == "main") {                                                 //找到main函数块
#####             cur_ctx = new Context(&f);
#####             break;
#####         }
#####     }


ir::Program *program = new ir::Program();             // 产生一个程序体
    ir::Function function = ir::Function();               // 产生一个函数块
    ir::Instruction *instruction = new ir::Instruction(); // 产生一条指令
    std::queue<AstNode *> Q;                              // 产生一个queue用来遍历语法树
    Q.push(root);                                         // 将root放入queue
    program->addFunction(function);                       // 程序体肯定存在一个函数块
    function.addInst(instruction);                        // 这个函数块肯定存在一条指令
    while (!Q.empty())
    {
        for (auto &child : Q.front()->children)
        {
            Q.push(child);
        }
        auto node = Q.front();
        Q.pop();
        switch (node->type)
        {
        case NodeType::COMPUNIT: // 找到了新的函数块，创建新的函数块并放入其中
        {
            function = ir::Function();
            program->addFunction(function);
        }
        case NodeType::TERMINAL:
        {
        }
        }
    }



宏定义：

TODO: 这个宏定义表示 "to do"，在代码中表示这部分代码需要进行补充。当代码执行到这里时，会抛出一个 assertion failed 的错误，提醒程序员需要在这里进行代码的实现。
函数定义：

map<std::string, ir::Function *> *frontend::get_lib_funcs(): 这个函数返回一个指向字符串和 IR 函数对应的 map 的指针。这个 map 存储了一些内置函数，比如 getint、putint 等等。
void frontend::SymbolTable::add_scope(Block *node): 这个函数的作用是向符号表中添加一个新的作用域，参数 node 表示这个作用域对应的语法树节点。
void frontend::SymbolTable::exit_scope(): 这个函数的作用是退出当前作用域，在符号表中删除当前作用域对应的内容。
string frontend::SymbolTable::get_scoped_name(string id) const: 这个函数的作用是根据一个标识符 id 获取它在符号表中的作用域限定名。例如，如果 id 是 "x"，而在当前作用域中已经有了一个同名变量，则返回 "scope_x"。
Operand frontend::SymbolTable::get_operand(string id) const: 这个函数的作用是根据一个标识符 id 获取它对应的操作数。如果这个标识符是一个变量，则返回一个寄存器或栈上的位置，如果是一个常量，则返回它的值。
frontend::STE frontend::SymbolTable::get_ste(string id) const: 这个函数的作用是根据一个标识符 id 获取它在符号表中对应的符号表项。
除了这些函数之外，我们还可以看到一个类 Analyzer 的定义。这个类是语义分析器的主体部分，它有一个私有变量 symbol_table，表示语义分析过程中的符号表，以及一个私有变量 tmp_cnt，表示生成临时变量时使用的计数器。这个类中最重要的函数是 get_ir_program，它接受一个根节点 root，返回一个 IR 程序。这个函数会递归地遍历整棵语法树，并调用一些辅助函数来实现不同类型的语义分析。在这里，我们看到的 TODO 就表示这些辅助函数还需要进行实现。