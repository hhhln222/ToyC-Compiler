#ifndef IR_GENERATOR_H
#define IR_GENERATOR_H

#include "antlr4-runtime.h"
#include "ToyCBaseVisitor.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <memory>

// 三地址码指令类型
enum class IROpcode {
    // 算术运算
    ADD, SUB, MUL, DIV, MOD,
    // 逻辑运算
    AND, OR, NOT,
    // 关系运算
    LT, GT, LE, GE, EQ, NE,
    // 赋值和跳转
    ASSIGN, GOTO, IF_GOTO, LABEL,
    // 函数调用
    CALL, PARAM, RETURN,
    // 其他
    NOP
};

// 操作数类型
enum class OperandType {
    VARIABLE,    // 变量
    CONSTANT,    // 常量
    TEMP,        // 临时变量
    LABEL,        // 标签
    PARAM
};

// 操作数结构
struct Operand {
    OperandType type;
    std::string value;
    int index;
    
    Operand(OperandType t, const std::string& v, int idx = -1) : type(t), value(v), index(idx) {}
    
    std::string toString() const {
        switch (type) {
            case OperandType::VARIABLE: return value;
            case OperandType::CONSTANT: return value;
            case OperandType::TEMP: return "t" + value;
            case OperandType::LABEL: return "L" + value;
            case OperandType::PARAM: return value;
            default: return "unknown";
        }
    }
};

// 三地址码指令结构
struct IRInstruction {
    IROpcode opcode;
    std::shared_ptr<Operand> result;    // 结果操作数
    std::shared_ptr<Operand> arg1;      // 第一个操作数
    std::shared_ptr<Operand> arg2;      // 第二个操作数
    std::string label;                  // 标签（用于跳转指令）
    bool isLeader = false;              // 标记是否为基本块入口

    // 构造函数
    IRInstruction(IROpcode op, std::shared_ptr<Operand> res = nullptr,
                  std::shared_ptr<Operand> a1 = nullptr,
                  std::shared_ptr<Operand> a2 = nullptr)
        : opcode(op), result(res), arg1(a1), arg2(a2), label("") {}
    IRInstruction(IROpcode op, const std::string& lbl)
        : opcode(op), result(nullptr), arg1(nullptr), arg2(nullptr), label(lbl) {}
    IRInstruction(IROpcode op, std::shared_ptr<Operand> res,
                  std::shared_ptr<Operand> a1,
                  std::shared_ptr<Operand> a2,
                  const std::string& lbl)
        : opcode(op), result(res), arg1(a1), arg2(a2), label(lbl) {}
    
    std::string toString() const {
        std::string result_str = result ? result->toString() : "";
        std::string arg1_str = arg1 ? arg1->toString() : "";
        std::string arg2_str = arg2 ? arg2->toString() : "";
        
        switch (opcode) {
            case IROpcode::ASSIGN:
                return result_str + " = " + arg1_str;
            case IROpcode::ADD:
                return result_str + " = " + arg1_str + " + " + arg2_str;
            case IROpcode::SUB:
                return result_str + " = " + arg1_str + " - " + arg2_str;
            case IROpcode::MUL:
                return result_str + " = " + arg1_str + " * " + arg2_str;
            case IROpcode::DIV:
                return result_str + " = " + arg1_str + " / " + arg2_str;
            case IROpcode::MOD:
                return result_str + " = " + arg1_str + " % " + arg2_str;
            case IROpcode::AND:
                return result_str + " = " + arg1_str + " && " + arg2_str;
            case IROpcode::OR:
                return result_str + " = " + arg1_str + " || " + arg2_str;
            case IROpcode::NOT:
                return result_str + " = !" + arg1_str;
            case IROpcode::LT:
                return result_str + " = " + arg1_str + " < " + arg2_str;
            case IROpcode::GT:
                return result_str + " = " + arg1_str + " > " + arg2_str;
            case IROpcode::LE:
                return result_str + " = " + arg1_str + " <= " + arg2_str;
            case IROpcode::GE:
                return result_str + " = " + arg1_str + " >= " + arg2_str;
            case IROpcode::EQ:
                return result_str + " = " + arg1_str + " == " + arg2_str;
            case IROpcode::NE:
                return result_str + " = " + arg1_str + " != " + arg2_str;
            case IROpcode::GOTO:
                return "goto " + label;
            case IROpcode::IF_GOTO:
                return "if " + arg1_str + " goto " + label;
            case IROpcode::LABEL:
                return label + ":";
            case IROpcode::CALL:
                return result_str + " = call " + arg1_str + ", " + arg2_str;
            case IROpcode::PARAM:
                return "param " + arg1_str;
            case IROpcode::RETURN:
                return "return " + (arg1_str.empty() ? "" : arg1_str);
            case IROpcode::NOP:
                return "nop";
            default:
                return "unknown";
        }
    }
};

// 函数信息结构
struct FunctionInfo {
    std::string name;
    std::string returnType;
    std::vector<std::shared_ptr<Operand>> params;
    std::vector<IRInstruction> instructions;
    int varCount;          // 变量（包括参数和局部变量）的总数
    int startTempCounter;   // 函数开始时的临时变量计数器值
    int endTempCounter;     // 函数结束时的临时变量计数器值
    
    FunctionInfo(const std::string& n, const std::string& rt) 
        : name(n), returnType(rt), varCount(0), startTempCounter(0), endTempCounter(0) {}
};

// IR生成器类
class IRGenerator : public ToyCBaseVisitor {
public:
    IRGenerator() : tempCounter(0), labelCounter(0), currentFunction(nullptr) {}
    
    // 获取生成的IR代码
    std::vector<FunctionInfo> getFunctions() const { return functions; }
    
    // 打印IR代码
    void printIR(const std::string& outputFile = "output.txt") const;
    
    // --- 访问方法重写 ---
    
    // 访问编译单元
    virtual std::any visitCompUnit(ToyCParser::CompUnitContext *ctx) override;
    
    // 访问函数定义
    virtual std::any visitFuncDef(ToyCParser::FuncDefContext *ctx) override;
    
    // 访问变量声明语句
    virtual std::any visitDeclStmt(ToyCParser::DeclStmtContext *ctx) override;
    
    // 访问赋值语句
    virtual std::any visitAssignStmt(ToyCParser::AssignStmtContext *ctx) override;
    
    // 访问if语句
    virtual std::any visitIfStmt(ToyCParser::IfStmtContext *ctx) override;
    
    // 访问while语句
    virtual std::any visitWhileStmt(ToyCParser::WhileStmtContext *ctx) override;
    
    // 访问return语句
    virtual std::any visitReturnStmt(ToyCParser::ReturnStmtContext *ctx) override;
    
    // 访问代码块
    virtual std::any visitBlock(ToyCParser::BlockContext *ctx) override;
    
    // 访问表达式
    virtual std::any visitExpr(ToyCParser::ExprContext *ctx) override;
    
    // 访问标识符
    virtual std::any visitIdentifier(ToyCParser::IdentifierContext *ctx) override;
    
    // 访问数字字面量
    virtual std::any visitNumberLiteral(ToyCParser::NumberLiteralContext *ctx) override;
    
    // 访问函数调用
    virtual std::any visitFunctionCall(ToyCParser::FunctionCallContext *ctx) override;
    
    // 访问各种表达式类型
    virtual std::any visitMulAddExpr(ToyCParser::MulAddExprContext *ctx) override;
    virtual std::any visitSingleAdd(ToyCParser::SingleAddContext *ctx) override;
    virtual std::any visitSingleMul(ToyCParser::SingleMulContext *ctx) override;
    virtual std::any visitMulMulExpr(ToyCParser::MulMulExprContext *ctx) override;
    virtual std::any visitSingleRel(ToyCParser::SingleRelContext *ctx) override;
    virtual std::any visitMulRelExpr(ToyCParser::MulRelExprContext *ctx) override;
    virtual std::any visitSingleLAnd(ToyCParser::SingleLAndContext *ctx) override;
    virtual std::any visitMulLAndExpr(ToyCParser::MulLAndExprContext *ctx) override;
    virtual std::any visitSingleLOr(ToyCParser::SingleLOrContext *ctx) override;
    virtual std::any visitMulLOrExpr(ToyCParser::MulLOrExprContext *ctx) override;
    virtual std::any visitSingleUnary(ToyCParser::SingleUnaryContext *ctx) override;
    virtual std::any visitMulUnaryOp(ToyCParser::MulUnaryOpContext *ctx) override;
    virtual std::any visitParenthesizedExpr(ToyCParser::ParenthesizedExprContext *ctx) override;
    
    // 其他必要的访问方法
    virtual std::any visitBlockStmt(ToyCParser::BlockStmtContext *ctx) override;
    virtual std::any visitEmptyStmt(ToyCParser::EmptyStmtContext *ctx) override;
    virtual std::any visitExprStmt(ToyCParser::ExprStmtContext *ctx) override;
    virtual std::any visitBreakStmt(ToyCParser::BreakStmtContext *ctx) override;
    virtual std::any visitContinueStmt(ToyCParser::ContinueStmtContext *ctx) override;
    virtual std::any visitParam(ToyCParser::ParamContext *ctx) override;

private:
    std::vector<FunctionInfo> functions;           // 所有函数信息
    FunctionInfo* currentFunction;                 // 当前正在处理的函数
    int tempCounter;                               // 临时变量计数器
    int labelCounter;                              // 标签计数器
    
    // 循环标签栈，用于处理break和continue语句
    struct LoopLabels {
        std::string loopLabel;    // 循环开始标签
        std::string bodyLabel;    // 循环体标签  
        std::string endLabel;     // 循环结束标签
    };
    std::vector<LoopLabels> loopStack;            // 循环标签栈
    //用于变量作用域的书写
    std::vector<std::unordered_map<std::string, std::string>> symbolTableStack; // 作用域栈
    std::unordered_map<std::string, int> varVersion; // 变量名到版本号
    void enterScope();
    void exitScope();
    std::string addVariable(const std::string& name);
    std::string lookupVariable(const std::string& name);
    
    // 辅助方法
    std::string generateTemp();                    // 生成临时变量名
    std::string generateLabel();                   // 生成标签名
    void addInstruction(const IRInstruction& inst); // 添加指令到当前函数
    std::shared_ptr<Operand> createOperand(const std::string& value, OperandType type, int index = -1);
};

#endif // IR_GENERATOR_H 