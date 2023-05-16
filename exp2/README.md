# 语义分析的 executor 分析
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

*改变框架
..\bin\compiler.exe .\testcase\basic\04_arr_defn3.sy -e -o .\output\basic\04_arr_defn3.out
通过7个/修改load
..\bin\compiler.exe .\testcase\basic\06_const_var_defn2.sy -e -o .\output\basic\06_const_var_defn2.out
通过11个/修改ConstDef
..\bin\compiler.exe .\testcase\basic\08_const_array_defn.sy -e -o .\output\basic\08_const_array_defn.out
通过14个/全局变量添加问题
..\bin\compiler.exe .\testcase\basic\09_func_defn.sy -e -o .\output\basic\09_func_defn.out
通过15个/全局变量添加问题
..\bin\compiler.exe .\testcase\basic\10_var_defn_func.sy -e -o .\output\basic\10_var_defn_func.out
通过16个/函数未成功添加到table中
..\bin\compiler.exe .\testcase\basic\13_sub2.sy -e -o .\output\basic\13_sub2.out
通过17个/少了subi
..\bin\compiler.exe .\testcase\basic\16_mulc.sy -e -o .\output\basic\16_mulc.out
通过18个/mul需要对常数先定义
..\bin\compiler.exe .\testcase\basic\21_if_test2.sy -e -o .\output\basic\21_if_test2.out
通过22个/==以及||有问题/or结果未放入table

修改指令放入顺序
第一个就出现问题cur_ctx->pc < cur_ctx->pfunc->InstVec.size()
..\bin\compiler.exe .\testcase\basic\00_main.sy -e -o .\output\basic\00_main.out
成功解决(……)

..\bin\compiler.exe .\testcase\basic\21_if_test2.sy -e -o .\output\basic\21_if_test2.out
通过22个/==以及||有问题/or结果未放入table/goto跳转问题
..\bin\compiler.exe .\testcase\basic\22_if_test3.sy -e -o .\output\basic\22_if_test3.out
通过24个/primaryexp未复制
..\bin\compiler.exe .\testcase\basic\25_while_if.sy -e -o .\output\basic\25_while_if.out
通过27个/while问题
..\bin\compiler.exe .\testcase\basic\29_break.sy -e -o .\output\basic\29_break.out
通过38个/数据类型问题
..\bin\compiler.exe .\testcase\basic\40_unary_op.sy -e -o .\output\basic\40_unary_op.out
通过39个/not
..\bin\compiler.exe .\testcase\basic\41_unary_op2.sy -e -o .\output\basic\41_unary_op2.out
通过40个/前一个为常数的sub
..\bin\compiler.exe .\testcase\function\34_arr_expr_len.sy -e -o .\output\function\34_arr_expr_len.out
通过41个
..\bin\compiler.exe .\testcase\function\38_op_priority4.sy -e -o .\output\function\38_op_priority4.out
通过42个/neq

09和33一会可以一会不可以？？
..\bin\compiler.exe .\testcase\basic\09_func_defn.sy -e -o .\output\basic\09_func_defn.out
..\bin\compiler.exe .\testcase\basic\33_while_if_test3.sy -e -o .\output\basic\33_while_if_test3.out

 ..\bin\compiler.exe .\testcase\function\50_short_circuit.sy -e -o .\output\function\50_short_circuit.out
通过47个/
..\bin\compiler.exe .\testcase\function\51_short_circuit3.sy -e -o .\output\function\51_short_circuit3.out
通过48个




docker pull frankd35/demo:v3
docker run -it -v D:\360MoveData\Users\Luna\Desktop\compiler\exp_2_process:/coursegrader frankd35/demo:v3
docker run -it -v /mnt/d/360MoveData/Users/Luna/Desktop/compiler/exp_2_process:/coursegrader frankd35/demo:v3
cd coursegrader/test
python3 test.py s2

当你想用VMware
bcdedit /set hypervisorlaunchtype off

当你想用Docker
bcdedit /set hypervisorlaunchtype auto


