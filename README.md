# compiler

### 实验一：词法分析——lexical.cpp

#### (1)从文件流中读取的字符串末尾加"\n"，否则最后一个 token 无法成功读出

#### (2)增加整数类型，如 0x,0b 开头的整数

#### (3)对于前面为 Empty 状态的现状态来说,cur_str 直接等于现在的 value，而不是相加，这里可能会出问题

#### (4)区分 op 时修改为识别到两个相邻 op 可以组成 op，直接输出然后 reset()以下，如果只识别一个 op，则待定，等待第二个读入，做一个判断（当然这里也可以直接识别第一个 op 是不是仅单符号操作数，直接考虑是否输出）

### 实验一：语法分析——abstract_syntax_tree.h/abstract_syntax_tree.cpp/syntax.h/syntax.cpp

#### (1)修改 abstract_syntax_tree.h 中的 COMPUINT 为 COMPUNIT(8/47)

#### (2)修改 parseCompUnit，明确开头是 Decl 还是 FuncDef(9/47)

#### (3)删除多余的 else 条件(23/47)

#### (4)修改 parseStmt，增加判断首个是否是';'(24/47)——run 部分全部成功

#### (5)8 错误，去修改 ConstDef-->LBRACK 写成了 LBRACE(25/47)

#### (6)21 错误，去修改 Stmt-->忘记加'('和')'(35/47)

#### (7)25 错误，去修改 Stmt-->忘记加'('和')'(47/47)——全过了

### 实验二：语义分析——semantic.cpp

#### 通过 58 个测试点：修改原本词法和语法分析

#### diff -u file1.txt file2.txt > diff.txt

#### 词法分析 95 错，修改 op 后是'.'

#### 语法分析 62 错，修改 UnaryExp

### 实验三：汇编——generator.cpp

```
set(CMAKE_C_COMPILER    "/usr/bin/x86_64-linux-gnu-gcc-7")
set(CMAKE_CXX_COMPILER  "/usr/bin/x86_64-linux-gnu-g++-7")
```



```
当你想用VMware
bcdedit /set hypervisorlaunchtype off

当你想用Docker
bcdedit /set hypervisorlaunchtype auto
```

```
docker run -it -v D:\360MoveData\Users\Luna\Desktop\compiler\exp_3:/coursegrader frankd35/demo:v3
cd coursegrader/test
```

```
python3 test.py S
```

```
../bin/compiler ../test.sy -s0 -o ../test.tk 
../bin/compiler ../test.sy -s1 -o ../test.json 
../bin/compiler ../test.sy -s2 -o ../test.out 


../bin/compiler ../test.sy -S -o ../test.s 
riscv32-unknown-linux-gnu-gcc ../test.s sylib-riscv-linux.a -o ../test.exe
qemu-riscv32.sh ../test.exe < ../test.in > ../test.out
```

成功读取全局变量

```
 Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rd, inst.op1.name));
 Instr.push_back(rv::rv_inst(rv::rvOPCODE::LW, rd, rd, 0));
```

成功存入全局变量

```
 Instr.push_back(rv::rv_inst(rv::rvOPCODE::LA, rs1, inst.op1.name));
 Instr.push_back(rv::rv_inst(rv::rvOPCODE::SW, rd, rs1, 0));
```

最后四个错误点

../bin/compiler ./testcase/function/64_calculator.sy -S -o ./output/function/64_calculator.s

../bin/compiler ./testcase/function/66_exgcd.sy -S -o ./output/function/66_exgcd.s

../bin/compiler ./testcase/function/89_many_globals.sy -S -o ./output/function/89_many_globals.s（多个函数参数）

../bin/compiler ./testcase/function/95_float.sy -S -o ./output/function/95_float.s

```
直接生成汇编
riscv64-linux-gnu-gcc -S 89.c -o 89.s
```

