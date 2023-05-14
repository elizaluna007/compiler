# 语义分析的 executor 分析

##### // init global variables

##### for(const auto& gte: program->globalVal) { //遍历全局变量

##### std::pair<std::string, Value> entry = {gte.val.name, {gte.val.type, 0}};//得到全局变量的名称和{类型,值}

##### if (gte.maxlen) { //如果全局变量存在并且是数组

##### if (gte.val.type == Type::IntPtr) { //整型指针

##### entry.second.\_val.iptr = new int[gte.maxlen]; //值为整型数组

#####

##### }

##### else if (gte.val.type == Type::FloatPtr) { //浮点型指针

##### entry.second.\_val.fptr = new float[gte.maxlen]; //值为浮点形数组

##### }

##### else {

##### assert(0 && "wrong global value type with maxlen > 0");

##### }

##### }

##### global_vars.insert(entry); //全局变量的{名称,{类型,值}}添加到 global_vars 中

##### }

##### // find main function and set cur_cxt

##### for(const auto& f: program->functions) { //遍历函数块

##### if (f.name == "main") { //找到 main 函数块

##### cur_ctx = new Context(&f);

##### break;

##### }

##### }

ir::Program *program = new ir::Program(); // 产生一个程序体
ir::Function function = ir::Function(); // 产生一个函数块
ir::Instruction *instruction = new ir::Instruction(); // 产生一条指令
std::queue<AstNode \*> Q; // 产生一个 queue 用来遍历语法树
Q.push(root); // 将 root 放入 queue
program->addFunction(function); // 程序体肯定存在一个函数块
function.addInst(instruction); // 这个函数块肯定存在一条指令
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
void frontend::SymbolTable::add_scope(Block \*node): 这个函数的作用是向符号表中添加一个新的作用域，参数 node 表示这个作用域对应的语法树节点。
void frontend::SymbolTable::exit_scope(): 这个函数的作用是退出当前作用域，在符号表中删除当前作用域对应的内容。
string frontend::SymbolTable::get_scoped_name(string id) const: 这个函数的作用是根据一个标识符 id 获取它在符号表中的作用域限定名。例如，如果 id 是 "x"，而在当前作用域中已经有了一个同名变量，则返回 "scope_x"。
Operand frontend::SymbolTable::get_operand(string id) const: 这个函数的作用是根据一个标识符 id 获取它对应的操作数。如果这个标识符是一个变量，则返回一个寄存器或栈上的位置，如果是一个常量，则返回它的值。
frontend::STE frontend::SymbolTable::get_ste(string id) const: 这个函数的作用是根据一个标识符 id 获取它在符号表中对应的符号表项。
除了这些函数之外，我们还可以看到一个类 Analyzer 的定义。这个类是语义分析器的主体部分，它有一个私有变量 symbol_table，表示语义分析过程中的符号表，以及一个私有变量 tmp_cnt，表示生成临时变量时使用的计数器。这个类中最重要的函数是 get_ir_program，它接受一个根节点 root，返回一个 IR 程序。这个函数会递归地遍历整棵语法树，并调用一些辅助函数来实现不同类型的语义分析。在这里，我们看到的 TODO 就表示这些辅助函数还需要进行实现。

构建符号表：遍历语法树，识别变量、函数等声明，并在符号表中记录它们的信息，如名称、类型、作用域等。符号表是一个数据结构，用于管理标识符的信息。

类型检查：遍历语法树，对于每个表达式、赋值语句等，检查其类型是否符合语言规定。例如，检查运算符是否应用于正确类型的操作数，检查赋值是否类型兼容等。

作用域检查：遍历语法树时，跟踪当前作用域。检查变量和函数的作用域是否合法，例如，变量是否在其作用域内定义和使用，函数是否调用正确等。

错误处理：在进行语义分析的过程中，如果发现不符合语义规则的代码，如类型不匹配、未声明的变量等，需要生成错误信息并进行相应的错误处理。

生成中间代码或目标代码：根据语义分析的结果，可以生成中间代码或目标代码，用于进一步的优化和执行。

CompUnit -> (Decl | FuncDef) [CompUnit]
Decl -> ConstDecl | VarDecl
ConstDecl -> 'const' BType ConstDef { ',' ConstDef } ';'
BType -> 'int' | 'float'
ConstDef -> Ident { '[' ConstExp ']' } '=' ConstInitVal
ConstInitVal -> ConstExp | '{' [ ConstInitVal { ',' ConstInitVal } ] '}'
VarDecl -> BType VarDef { ',' VarDef } ';'
VarDef -> Ident { '[' ConstExp ']' } [ '=' InitVal ]
InitVal -> Exp | '{' [ InitVal { ',' InitVal } ] '}'
FuncDef -> FuncType Ident '(' [FuncFParams] ')' Block
FuncType -> 'void' | 'int' | 'float'
FuncFParam -> BType Ident ['[' ']' { '[' Exp ']' }]
FuncFParams -> FuncFParam { ',' FuncFParam }
Block -> '{' { BlockItem } '}'
BlockItem -> Decl | Stmt
Stmt -> LVal '=' Exp ';' | Block | 'if' '(' Cond ')' Stmt [ 'else' Stmt ] | 'while' '(' Cond ')' Stmt | 'break' ';' | 'continue' ';' | 'return' [Exp] ';' | [Exp] ';'
Exp -> AddExp
Cond -> LOrExp
LVal -> Ident {'[' Exp ']'}
Number -> IntConst | floatConst
PrimaryExp -> '(' Exp ')' | LVal | Number
UnaryExp -> PrimaryExp | Ident '(' [FuncRParams] ')' | UnaryOp UnaryExp
UnaryOp -> '+' | '-' | '!'
FuncRParams -> Exp { ',' Exp }
MulExp -> UnaryExp { ('\*' | '/' | '%') UnaryExp }
AddExp -> MulExp { ('+' | '-') MulExp }
RelExp -> AddExp { ('<' | '>' | '<=' | '>=') AddExp }
EqExp -> RelExp { ('==' | '!=') RelExp }
LAndExp -> EqExp [ '&&' LAndExp ]
LOrExp -> LAndExp [ '||' LOrExp ]
ConstExp -> AddExp

ir::Program program;
ir::Function globalFunc("global", ir::Type::null);
全局变量赋值在 CompUnit 之后的 Decl 中发生
全局的函数在 CompUnit 之后的 FuncDef 中发生

python test.py s2

..\bin\compiler.exe ../test.sy -s2 -o ../test.out
..\bin\compiler.exe ../test.sy -e -o ../test.out

..\bin\compiler.exe .\testcase\basic\01_var_defn2.sy -s2 -o .\output\basic\01_var_defn2.out
..\bin\compiler.exe .\testcase\basic\01_var_defn2.sy -e -o .\output\basic\01_var_defn2.out
通过2个
..\bin\compiler.exe .\testcase\basic\02_var_defn3.sy -e -o .\output\basic\02_var_defn3.out
通过10个
..\bin\compiler.exe .\testcase\basic\03_arr_defn2.sy -e -o .\output\basic\03_arr_defn2.out
通过11个
..\bin\compiler.exe .\testcase\basic\04_arr_defn3.sy -e -o .\output\basic\04_arr_defn3.out

..\bin\compiler.exe .\testcase\basic\08_const_array_defn.sy -e -o .\output\basic\08_const_array_defn.out

..\bin\compiler.exe .\testcase\basic\10_var_defn_func.sy -e -o .\output\basic\10_var_defn_func.out

..\bin\compiler.exe .\testcase\basic\07_const_var_defn3.sy -e -o .\output\basic\07_const_var_defn3.out




docker pull frankd35/demo:v3
docker run -it -v D:\360MoveData\Users\Luna\Desktop\compiler\exp_2_process:/coursegrader frankd35/demo:v3
docker run -it -v /mnt/d/360MoveData/Users/Luna/Desktop/compiler/exp_2_process:/coursegrader frankd35/demo:v3
cd coursegrader/test
python3 test.py s2

当你想用VMware
bcdedit /set hypervisorlaunchtype off

当你想用Docker
bcdedit /set hypervisorlaunchtype auto


//助教给的docker的cmake版本过低，出现问题，先升级
apt-get update
apt-get install -y wget
wget https://github.com/Kitware/CMake/releases/download/v3.21.3/cmake-3.21.3-Linux-x86_64.tar.gz
tar -xzvf cmake-3.21.3-Linux-x86_64.tar.gz
cp -r cmake-3.21.3-Linux-x86_64/bin/* /usr/bin/
cmake --version

apt remove cmake
ln -s /usr/share/cmake-3.21 /usr/share/cmake