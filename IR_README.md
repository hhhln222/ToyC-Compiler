# ToyC编译器IR生成器说明

## 概述

本IR生成器将ToyC语言的源代码经过词法分析、语法分析、**严格的语义分析**后，生成三地址码（Three-Address Code, TAC）形式的中间代码（IR）。

## 主流程

1. **词法/语法分析**：由ANTLR自动生成的Lexer和Parser将源代码转为AST（抽象语法树）。
2. **语义分析**：`SemanticAnalyzer`对AST进行严格的ToyC语义规则检查（main唯一性、变量作用域、函数声明、return路径等）。
3. **IR生成**：`IRGenerator`遍历AST，将每个语句、表达式翻译为三地址码指令，输出到output.txt。

## 语义约束（由SemanticAnalyzer实现）
- 必须有且只有一个`int main()`，无参数。
- 所有函数只能在全局作用域声明，名称唯一。
- int型函数所有路径必须return int，void型return不能有返回值。
- 变量声明必须初始化，且不能重复声明。
- break/continue只能在循环中。
- if/while条件、赋值右值不能为void型函数调用。
- 变量必须先声明后使用，作用域与C一致。
- 函数调用必须在被调函数声明之后。

## IR生成逻辑（IRGenerator核心逻辑）

### 1. 函数与主程序
- 只为合法的函数（通过语义分析）生成IR。
- 每个函数生成独立的IR指令序列，参数和局部变量作用域分明。
- `main`函数作为程序入口。

### 2. 变量与作用域
- 变量声明时分配名字，必须初始化。
- 作用域用栈管理，内层可屏蔽外层同名变量。
- 临时变量（t0, t1, ...）用于表达式中间结果。

### 3. 赋值与声明
- 变量声明如`int x = expr;`生成：
  ```
  t0 = expr
  x = t0
  ```
- 赋值语句`x = expr;`生成：
  ```
  t0 = expr
  x = t0
  ```

### 4. 表达式
- 所有表达式都分解为三地址码，复杂表达式用临时变量保存中间结果。
- 算术、关系、逻辑运算符均生成对应的TAC指令。
- 变量引用、字面值直接作为操作数。

### 5. if/while/return等语句
- **if语句**：
  - 条件表达式生成临时变量`tcond`。
  - 生成条件跳转、else分支和结束标签：
    ```
    if tcond goto Ltrue
    goto Lfalse
    Ltrue:
      ...then分支...
    goto Lend
    Lfalse:
      ...else分支...
    Lend:
    ```
- **while语句**：
  - 生成循环头、条件判断、体、跳转和结束标签：
    ```
    Lloop:
      tcond = ...
      if tcond goto Lbody
      goto Lend
    Lbody:
      ...循环体...
      goto Lloop
    Lend:
    ```
- **break/continue**：
  - break跳转到循环外的Lend，continue跳转到循环头。
- **return语句**：
  - int型return返回表达式值，void型return无值。

### 6. 函数调用
- 参数依次生成`param`指令。
- 生成`call`指令，返回值存入临时变量：
  ```
  param arg1
  param arg2
  t0 = call func(arg1, arg2)
  ```

### 7. 逻辑与/或短路计算
- 逻辑与（&&）、或（||）采用短路跳转：
  - 逻辑与：先判断左侧，若为假直接跳转Lfalse，否则计算右侧。
  - 逻辑或：先判断左侧，若为真直接跳转Ltrue，否则计算右侧。
- 生成的IR会有多个标签和条件跳转，保证短路语义。

### 8. 错误输出与IR输出
- 所有语义错误、IR代码均输出到`output.txt`。
- 语义分析通过后，IR代码紧随其后输出。

## 例子

### 输入ToyC代码
```c
int main() {
    int x = 10;
    int y = 20;
    int z = x + y * 2;
    if (z > 30) {
        z = z - 1;
    } else {
        z = z + 1;
    }
    return z;
}
```

### 生成的IR代码（output.txt）
```
Semantic analysis completed successfully with no errors.

=== Generating IR Code ===
=== Function: main ===
Return type: int
Instructions:
  0: x = 10
  1: y = 20
  2: t0 = y * 2
  3: t1 = x + t0
  4: z = t1
  5: t2 = z > 30
  6: if t2 goto L0
  7: goto L1
  8: L0:
  9: t3 = z - 1
 10: z = t3
 11: goto L2
 12: L1:
 13: t4 = z + 1
 14: z = t4
 15: L2:
 16: return z
```

## 结论

本IR生成器严格遵循ToyC语言规范，所有语义约束和三地址码生成逻辑均已实现。你可以直接用`parser_with_ir`编译并运行ToyC源代码，所有输出（包括错误和IR）都在`output.txt`中查看。 