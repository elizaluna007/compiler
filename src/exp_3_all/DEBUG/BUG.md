..\bin\compiler.exe .\testcase\function\34_arr_expr_len.sy -e -o .\output\function\34_arr_expr_len.out

..\bin\compiler.exe .\testcase\function\62_percolation.sy -e -o .\output\function\62_percolation.out
..\bin\compiler.exe .\testcase\function\70_dijkstra.sy -e -o .\output\function\70_dijkstra.out
..\bin\compiler.exe .\testcase\function\78_side_effect.sy -e -o .\output\function\78_side_effect.out



..\bin\compiler.exe .\testcase\function\79_var_name.sy -e -o .\output\function\79_var_name.out
..\bin\compiler.exe .\testcase\function\95_float.sy -e -o .\output\function\95_float.out

..\bin\compiler.exe ..\DEBUG\test.sy -e -o ..\DEBUG\test.out

Windows平台编译器有问题

换到Linux虚拟机上

出现问题的代码如下：34/62/70/78

python3 test.py s2

../bin/compiler ./testcase/function/34_arr_expr_len.sy -e -o ./output/function/34_arr_expr_len.out

../bin/compiler ./testcase/function/62_percolation.sy -e -o ./output/function/62_percolation.out

../bin/compiler ./testcase/function/70_dijkstra.sy -e -o ./output/function/70_dijkstra.out

../bin/compiler ./testcase/function/78_side_effect.sy -e -o ./output/function/78_side_effect.out



..\bin\compiler.exe .\testcase\function\95_float.sy -e -o .\output\function\95_float.out

95是平台问题



现在还剩两个

64、70

..\bin\compiler.exe .\testcase\function\64_calculator.sy -e -o .\output\function\64_calculator.out

../bin/compiler ./testcase/function/70_dijkstra.sy -e -o ./output/function/70_dijkstra.out





..\bin\compiler.exe ..\test.sy -e -o ..\test.out



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
