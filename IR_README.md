


ir主要通过函数与指令的结构体来对三地址码进行存储
// 函数信息结构
struct FunctionInfo {
    std::string name;
    std::string returnType;
    std::vector<std::string> params;
    std::vector<IRInstruction> instructions;
    
    FunctionInfo(const std::string& n, const std::string& rt) 
        : name(n), returnType(rt) {}
};
以上为函数的数据结构，包含函数名，返回值，参数和指令数组
struct IRInstruction {
    IROpcode opcode;
    std::shared_ptr<Operand> result;    // 结果操作数
    std::shared_ptr<Operand> arg1;      // 第一个操作数
    std::shared_ptr<Operand> arg2;      // 第二个操作数
    std::string label;                  // 标签（用于跳转指令）
    }指令的基本数据如上，包含三地址码所需的各类操作数
    ir的基本操作就是irgennerator作为ToyCBaseVisitor的子类访问之前生成的ast，也就是各种调用visit函数
    在进行访问之后解析读取生成三地址码供目标代码生成使用

    
**指令生成过程**：
1. 每个语法节点被访问时，生成相应的IR指令
2. 指令被添加到`instructions`向量中
3. 临时变量自动分配（t0, t1, t2, ...）
4. 标签自动分配（L0, L1, L2, ...）

生成器使用栈来管理跳转控制
struct LoopLabels {
    std::string loopLabel;    // 循环开始标签
    std::string bodyLabel;    // 循环体标签
    std::string endLabel;     // 循环结束标签
};

class IRGenerator {
private:
    std::vector<LoopLabels> loopStack;  // 循环标签栈
    int labelCounter;                   // 标签计数器
    
    std::string generateLabel() {
        return "L" + std::to_string(labelCounter++);
    }
};
而对于不同作用域的变量，也使用栈来进行管理，也就是在退出作用域时，该作用域的变量会被弹出，而失效，进入时如果有重新定义则会在作用域之内使用重新定义的
 作用域处理流程：
class IRGenerator {
private:
    std::vector<std::unordered_map<std::string, std::string>> symbolTableStack;  // 作用域栈
    std::unordered_map<std::string, int> varVersion;                             // 变量版本计数器
    
    // 作用域管理方法
    void enterScope();                    // 进入新作用域
    void exitScope();                     // 退出当前作用域
    std::string addVariable(const std::string& name);  // 添加变量到当前作用域
    std::string lookupVariable(const std::string& name);  // 查找变量（从内到外）
};
1. 进入作用域：
   ```cpp
   void enterScope() {
       symbolTableStack.push_back(std::unordered_map<std::string, std::string>());
   }
   ```

2. 变量声明：
   std::string addVariable(const std::string& name) {
       varVersion[name]++;
       std::string uniqueName = name + "_" + std::to_string(varVersion[name]);
       symbolTableStack.back()[name] = uniqueName;
       return uniqueName;
   }


3. 变量查找：
   std::string lookupVariable(const std::string& name) {
       for (int i = symbolTableStack.size() - 1; i >= 0; i--) {
           auto it = symbolTableStack[i].find(name);
           if (it != symbolTableStack[i].end()) {
               return it->second;
           }
       }
       return name;  // 如果没找到，返回原名（可能是全局变量）
   }


4. 退出作用域：
   void exitScope() {
       symbolTableStack.pop_back();
   }
   ```

作用域示例：

int main() {
    int x = 1;        // x_1
    {
        int x = 2;    // x_2 (屏蔽外层的x_1)
        x = x + 1;    // 使用x_2
    }
    return x;         // 使用x_1
}


生成的IR：

0: x_1 = 1
1: x_2 = 2
2: t0 = x_2 + 1
3: x_2 = t0
4: return x_1




