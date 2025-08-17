#include "IRGenerator.h"
#include <sstream>
#include <fstream>
#include <iostream>

// 辅助方法实现
std::string IRGenerator::generateTemp() {
    return std::to_string(tempCounter++);
}

std::string IRGenerator::generateLabel() {
    return std::to_string(labelCounter++);
}

void IRGenerator::addInstruction(const IRInstruction& inst) {
    if (currentFunction) {
        currentFunction->instructions.push_back(inst);
    }
}

std::shared_ptr<Operand> IRGenerator::createOperand(const std::string& value, OperandType type, int index) {
    return std::make_shared<Operand>(type, value, index);
}

// 打印IR代码
void IRGenerator::printIR(const std::string& outputFile) {
    std::ofstream out(outputFile);
    if (!out.is_open()) {
        std::cerr << "无法打开文件: " << outputFile << std::endl;
        return;
    }
    for (const auto& func : functions) {
        out << "\n=== Function: " << func.name << " ===" << std::endl;
        out << "Return type: " << func.returnType << std::endl;
        out << "Number of variables (including parameters): " << func.varCount << std::endl;
        int tempCount = func.endTempCounter - func.startTempCounter;
        out << "Number of temporary variables: " << tempCount << std::endl;
        if (!func.params.empty()) {
            out << "Parameters: ";
            for (size_t i = 0; i < func.params.size(); ++i) {
                if (i > 0) out << ", ";
                out << func.params[i]->toString();
            }
            out << std::endl;
        }
        out << "Instructions:" << std::endl;
        
        for (size_t i = 0; i < func.instructions.size(); ++i) {
            out << "  " << i << ": " << func.instructions[i].toString() << std::endl;
        }
    }
    out.close();
}

// 访问编译单元
std::any IRGenerator::visitCompUnit(ToyCParser::CompUnitContext *ctx) {
    // 访问所有函数定义
    for (auto funcDef : ctx->funcDef()) {
        visit(funcDef);
    }
    return nullptr;
}

// 访问函数定义
std::any IRGenerator::visitFuncDef(ToyCParser::FuncDefContext *ctx) {
    std::string funcName = ctx->ID()->getText();
    std::string returnType = ctx->INT() ? "int" : "void";
    
    // 创建新函数
    functions.emplace_back(funcName, returnType);
    currentFunction = &functions.back();

    currentFunction->startTempCounter = tempCounter;
    currentFunction->varCount = ctx->param().size();
    // 进入函数作用域
    enterScope();
    
    // 收集参数
    for (size_t i = 0; i < ctx->param().size(); ++i) {
        auto param = ctx->param()[i];
        std::string paramName = param->ID()->getText();
        // std::string uniqueName = addVariable(paramName);
        currentFunction->params.push_back(createOperand(paramName, OperandType::PARAM, i));
    }
    // 访问函数体
    visit(ctx->block());

    exitScope();
    
    currentFunction->endTempCounter = tempCounter;
    currentFunction = nullptr;
    return nullptr;
}

// 访问变量声明语句
std::any IRGenerator::visitDeclStmt(ToyCParser::DeclStmtContext *ctx) {
    std::string varName = ctx->ID()->getText();
    std::string uniqueName = addVariable(varName);
    
    // 如果有初始化表达式
    if (ctx->expr()) {
        auto exprResult = visit(ctx->expr());
        if (exprResult.has_value()) {
            auto operand = std::any_cast<std::shared_ptr<Operand>>(exprResult);
            auto varOperand = createOperand(uniqueName, OperandType::VARIABLE);
            addInstruction(IRInstruction(IROpcode::ASSIGN, varOperand, operand));
        }
    }
    
    return nullptr;
}

// 访问赋值语句
std::any IRGenerator::visitAssignStmt(ToyCParser::AssignStmtContext *ctx) {
    std::string varName = ctx->ID()->getText();
    std::string uniqueName = lookupVariable(varName);
    auto varOperand = createOperand(uniqueName, OperandType::VARIABLE);
    
    auto exprResult = visit(ctx->expr());
    if (exprResult.has_value()) {
        auto operand = std::any_cast<std::shared_ptr<Operand>>(exprResult);
        addInstruction(IRInstruction(IROpcode::ASSIGN, varOperand, operand));
    }
    
    return nullptr;
}

// 访问if语句
std::any IRGenerator::visitIfStmt(ToyCParser::IfStmtContext *ctx) {
    // 计算条件表达式
    auto condResult = visit(ctx->expr());
    if (condResult.has_value()) {
        auto condOperand = std::any_cast<std::shared_ptr<Operand>>(condResult);

        if (ctx->stmt().size() > 1) {
            // 有else部分的if语句
            std::string thenLabel = generateLabel();
            std::string elseLabel = generateLabel();
            std::string endLabel = generateLabel();
            
            // 如果条件为真，跳转到then部分
            addInstruction(IRInstruction(IROpcode::IF_GOTO, nullptr, condOperand, nullptr, thenLabel));
            
            // 否则跳转到else部分
            addInstruction(IRInstruction(IROpcode::GOTO, nullptr, nullptr, nullptr, elseLabel));
            
            // then部分标签
            addInstruction(IRInstruction(IROpcode::LABEL, nullptr, nullptr, nullptr, thenLabel));
            
            // 访问then部分
            visit(ctx->stmt(0));
            
            // 检查then部分是否以跳转指令结束
            bool thenEndsWithJump = false;
            if (!currentFunction->instructions.empty()) {
                auto& lastInstruction = currentFunction->instructions.back();
                if (lastInstruction.opcode == IROpcode::GOTO || 
                    lastInstruction.opcode == IROpcode::IF_GOTO ||
                    lastInstruction.opcode == IROpcode::RETURN) {
                    thenEndsWithJump = true;
                }
            }
            
            // 只有当then部分不以跳转结束时，才添加跳转到endLabel
            if (!thenEndsWithJump) {
                addInstruction(IRInstruction(IROpcode::GOTO, nullptr, nullptr, nullptr, endLabel));
            }
            
            // else部分标签
            addInstruction(IRInstruction(IROpcode::LABEL, nullptr, nullptr, nullptr, elseLabel));
            visit(ctx->stmt(1));
            
            // 结束标签
            addInstruction(IRInstruction(IROpcode::LABEL, nullptr, nullptr, nullptr, endLabel));
        } else {
            // 没有else部分的if语句 - 使用更简单的结构
            std::string thenLabel = generateLabel();
            std::string endLabel = generateLabel();
            
            // 如果条件为真，跳转到then部分
            addInstruction(IRInstruction(IROpcode::IF_GOTO, nullptr, condOperand, nullptr, thenLabel));
            
            // 否则跳转到结束
            addInstruction(IRInstruction(IROpcode::GOTO, nullptr, nullptr, nullptr, endLabel));
            
            // then部分标签
            addInstruction(IRInstruction(IROpcode::LABEL, nullptr, nullptr, nullptr, thenLabel));
            
            // 访问then部分
            visit(ctx->stmt(0));
            
            // 检查then部分是否以跳转指令结束
            bool thenEndsWithJump = false;
            if (!currentFunction->instructions.empty()) {
                auto& lastInstruction = currentFunction->instructions.back();
                if (lastInstruction.opcode == IROpcode::GOTO || 
                    lastInstruction.opcode == IROpcode::IF_GOTO ||
                    lastInstruction.opcode == IROpcode::RETURN) {
                    thenEndsWithJump = true;
                }
            }
            
            // 只有当then部分不以跳转结束时，才添加跳转到endLabel
            if (!thenEndsWithJump) {
                addInstruction(IRInstruction(IROpcode::GOTO, nullptr, nullptr, nullptr, endLabel));
            }
            
            // 结束标签
            addInstruction(IRInstruction(IROpcode::LABEL, nullptr, nullptr, nullptr, endLabel));
        }
    }
    
    return nullptr;
}

// 访问while语句
std::any IRGenerator::visitWhileStmt(ToyCParser::WhileStmtContext *ctx) {
    std::string loopLabel = generateLabel();
    std::string bodyLabel = generateLabel();
    std::string endLabel = generateLabel();
    
    // 将循环标签压入栈
    loopStack.push_back({loopLabel, bodyLabel, endLabel});
    
    // 循环开始标签
    addInstruction(IRInstruction(IROpcode::LABEL, nullptr, nullptr, nullptr, loopLabel));
    
    // 计算条件表达式
    auto condResult = visit(ctx->expr());
    if (condResult.has_value()) {
        auto condOperand = std::any_cast<std::shared_ptr<Operand>>(condResult);
        
        // 如果条件为真，跳转到循环体
        addInstruction(IRInstruction(IROpcode::IF_GOTO, nullptr, condOperand, nullptr, bodyLabel));
        
        // 否则跳转到结束
        addInstruction(IRInstruction(IROpcode::GOTO, nullptr, nullptr, nullptr, endLabel));
        
        // 循环体标签
        addInstruction(IRInstruction(IROpcode::LABEL, nullptr, nullptr, nullptr, bodyLabel));
        
        // 访问循环体
        visit(ctx->stmt());
        
        // 跳回循环开始
        addInstruction(IRInstruction(IROpcode::GOTO, nullptr, nullptr, nullptr, loopLabel));
        
        // 结束标签
        addInstruction(IRInstruction(IROpcode::LABEL, nullptr, nullptr, nullptr, endLabel));
    }
    
    // 弹出循环标签栈
    loopStack.pop_back();
    
    return nullptr;
}

// 访问return语句
std::any IRGenerator::visitReturnStmt(ToyCParser::ReturnStmtContext *ctx) {
    if (ctx->expr()) {
        auto exprResult = visit(ctx->expr());
        if (exprResult.has_value()) {
            auto operand = std::any_cast<std::shared_ptr<Operand>>(exprResult);
            addInstruction(IRInstruction(IROpcode::RETURN, nullptr, operand));
        }
    } else {
        addInstruction(IRInstruction(IROpcode::RETURN));
    }
    
    return nullptr;
}

// 访问代码块
std::any IRGenerator::visitBlock(ToyCParser::BlockContext *ctx) {
    enterScope();
    for (auto stmt : ctx->stmt()) {
        visit(stmt);
    }
    exitScope();
    return nullptr;
}

// 访问表达式
std::any IRGenerator::visitExpr(ToyCParser::ExprContext *ctx) {
    return visit(ctx->lOrExpr());
}

// 访问标识符
std::any IRGenerator::visitIdentifier(ToyCParser::IdentifierContext *ctx) {
    std::string varName = ctx->ID()->getText();
    std::string uniqueName = lookupVariable(varName);
    return std::make_any<std::shared_ptr<Operand>>(createOperand(uniqueName, OperandType::VARIABLE));
}

// 访问数字字面量
std::any IRGenerator::visitNumberLiteral(ToyCParser::NumberLiteralContext *ctx) {
    std::string value = ctx->NUMBER()->getText();
    return std::make_any<std::shared_ptr<Operand>>(createOperand(value, OperandType::CONSTANT));
}

// 访问函数调用
std::any IRGenerator::visitFunctionCall(ToyCParser::FunctionCallContext *ctx) {
    std::string funcName = ctx->ID()->getText();
    auto funcOperand = createOperand(funcName, OperandType::VARIABLE);
    
    // 处理参数
    std::string paramList = "";
    for (size_t i = 0; i < ctx->expr().size(); ++i) {
        auto paramResult = visit(ctx->expr(i));
        if (paramResult.has_value()) {
            auto paramOperand = std::any_cast<std::shared_ptr<Operand>>(paramResult);
            addInstruction(IRInstruction(IROpcode::PARAM, nullptr, paramOperand));
            if (i > 0) paramList += ", ";
            paramList += paramOperand->toString();
        }
    }
    
    // 生成临时变量存储返回值
    std::string tempVar = generateTemp();
    auto tempOperand = createOperand(tempVar, OperandType::TEMP);
    auto paramListOperand = createOperand(paramList, OperandType::CONSTANT);
    int paramCount = ctx->expr().size();
    auto paramCountOperand = createOperand(std::to_string(paramCount), OperandType::CONSTANT);
    
    addInstruction(IRInstruction(IROpcode::CALL, tempOperand, funcOperand, paramCountOperand));
    
    return std::make_any<std::shared_ptr<Operand>>(tempOperand);
}

// 访问算术表达式
std::any IRGenerator::visitMulAddExpr(ToyCParser::MulAddExprContext *ctx) {
    auto leftResult = visit(ctx->addExpr());
    auto rightResult = visit(ctx->mulExpr());
    
    if (leftResult.has_value() && rightResult.has_value()) {
        auto leftOperand = std::any_cast<std::shared_ptr<Operand>>(leftResult);
        auto rightOperand = std::any_cast<std::shared_ptr<Operand>>(rightResult);
        
        // 常量折叠优化
        if (leftOperand->type == OperandType::CONSTANT && 
            rightOperand->type == OperandType::CONSTANT) {
            int leftVal = std::stoi(leftOperand->value);
            int rightVal = std::stoi(rightOperand->value);
            int resultVal;
            
            if (ctx->ADD()) resultVal = leftVal + rightVal;
            else resultVal = leftVal - rightVal;
            
            return createOperand(std::to_string(resultVal), OperandType::CONSTANT);
        }

        // 代数简化：x + 0 = x, x - 0 = x
        if (rightOperand->type == OperandType::CONSTANT && 
            std::stoi(rightOperand->value) == 0) {
            return leftResult;
        }
        
        // 代数简化：0 + x = x
        if (leftOperand->type == OperandType::CONSTANT && 
            std::stoi(leftOperand->value) == 0 && ctx->ADD()) {
            return rightResult;
        }

        std::string tempVar = generateTemp();
        auto tempOperand = createOperand(tempVar, OperandType::TEMP);
        
        IROpcode opcode;
        if (ctx->ADD()) opcode = IROpcode::ADD;
        else opcode = IROpcode::SUB;
        
        addInstruction(IRInstruction(opcode, tempOperand, leftOperand, rightOperand));
        return std::make_any<std::shared_ptr<Operand>>(tempOperand);
    }
    
    return std::any();
}

std::any IRGenerator::visitSingleAdd(ToyCParser::SingleAddContext *ctx) {
    return visit(ctx->mulExpr());
}

std::any IRGenerator::visitSingleMul(ToyCParser::SingleMulContext *ctx) {
    return visit(ctx->unaryExpr());
}

std::any IRGenerator::visitMulMulExpr(ToyCParser::MulMulExprContext *ctx) {
    auto leftResult = visit(ctx->mulExpr());
    auto rightResult = visit(ctx->unaryExpr());
    
    if (leftResult.has_value() && rightResult.has_value()) {
        auto leftOperand = std::any_cast<std::shared_ptr<Operand>>(leftResult);
        auto rightOperand = std::any_cast<std::shared_ptr<Operand>>(rightResult);
        
        // 常量折叠优化
        if (leftOperand->type == OperandType::CONSTANT && 
            rightOperand->type == OperandType::CONSTANT) {
            int leftVal = std::stoi(leftOperand->value);
            int rightVal = std::stoi(rightOperand->value);
            int resultVal;
            
            if (ctx->MUL()) resultVal = leftVal * rightVal;
            else if (ctx->DIV()) {
                if(rightVal == 0) resultVal = 0;
                else resultVal = leftVal / rightVal;
            }
            else {
                if(rightVal == 0) resultVal = 0;
                else resultVal = leftVal % rightVal;
            }

            return createOperand(std::to_string(resultVal), OperandType::CONSTANT);
        }

        // 代数简化：x * 1 = x, x / 1 = x
        if (rightOperand->type == OperandType::CONSTANT && 
            std::stoi(rightOperand->value) == 1) {
            return leftResult;
        }
        
        // 代数简化：x * 0 = 0
        if (ctx->MUL() && 
            ((leftOperand->type == OperandType::CONSTANT && 
              std::stoi(leftOperand->value) == 0) ||
             (rightOperand->type == OperandType::CONSTANT && 
              std::stoi(rightOperand->value) == 0))) {
            return std::make_any<std::shared_ptr<Operand>>(
                createOperand("0", OperandType::CONSTANT)
            );
        }

        std::string tempVar = generateTemp();
        auto tempOperand = createOperand(tempVar, OperandType::TEMP);
        
        IROpcode opcode;
        if (ctx->MUL()) opcode = IROpcode::MUL;
        else if (ctx->DIV()) opcode = IROpcode::DIV;
        else opcode = IROpcode::MOD;
        
        addInstruction(IRInstruction(opcode, tempOperand, leftOperand, rightOperand));
        return std::make_any<std::shared_ptr<Operand>>(tempOperand);
    }
    
    return std::any();
}

// 访问关系表达式
std::any IRGenerator::visitSingleRel(ToyCParser::SingleRelContext *ctx) {
    return visit(ctx->addExpr());
}

std::any IRGenerator::visitMulRelExpr(ToyCParser::MulRelExprContext *ctx) {
    auto leftResult = visit(ctx->relExpr());
    auto rightResult = visit(ctx->addExpr());
    
    if (leftResult.has_value() && rightResult.has_value()) {
        auto leftOperand = std::any_cast<std::shared_ptr<Operand>>(leftResult);
        auto rightOperand = std::any_cast<std::shared_ptr<Operand>>(rightResult);
        
        // 常量折叠优化
        if (leftOperand->type == OperandType::CONSTANT && 
            rightOperand->type == OperandType::CONSTANT) {
            int leftVal = std::stoi(leftOperand->value);
            int rightVal = std::stoi(rightOperand->value);
            bool resultVal;

            if (ctx->LT()) resultVal = (leftVal < rightVal);
            else if (ctx->GT()) resultVal = (leftVal > rightVal);
            else if (ctx->LE()) resultVal = (leftVal <= rightVal);
            else if (ctx->GE()) resultVal = (leftVal >= rightVal);
            else if (ctx->EQ()) resultVal = (leftVal == rightVal);
            else resultVal = (leftVal != rightVal);

            // 布尔值转换为整数常量1或0
            return std::make_any<std::shared_ptr<Operand>>(
                createOperand(std::to_string(resultVal?1:0), OperandType::CONSTANT)
            );
        }

        std::string tempVar = generateTemp();
        auto tempOperand = createOperand(tempVar, OperandType::TEMP);
        
        IROpcode opcode;
        if (ctx->LT()) opcode = IROpcode::LT;
        else if (ctx->GT()) opcode = IROpcode::GT;
        else if (ctx->LE()) opcode = IROpcode::LE;
        else if (ctx->GE()) opcode = IROpcode::GE;
        else if (ctx->EQ()) opcode = IROpcode::EQ;
        else opcode = IROpcode::NE;
        
        addInstruction(IRInstruction(opcode, tempOperand, leftOperand, rightOperand));
        return std::make_any<std::shared_ptr<Operand>>(tempOperand);
    }
    
    return std::any();
}

// 访问逻辑表达式
std::any IRGenerator::visitSingleLAnd(ToyCParser::SingleLAndContext *ctx) {
    return visit(ctx->relExpr());
}

// 处理逻辑与（&&），实现短路判断
std::any IRGenerator::visitMulLAndExpr(ToyCParser::MulLAndExprContext *ctx) {
    auto leftResult = visit(ctx->lAndExpr());
    if (!leftResult.has_value()) return std::any(); // 左操作数无效
    auto leftOperand = std::any_cast<std::shared_ptr<Operand>>(leftResult);

    // 常量折叠：左操作数为常量
    if (leftOperand->type == OperandType::CONSTANT) {
        int leftVal = std::stoi(leftOperand->value);
        
        // 左为假（0），直接返回0（短路）
        if (leftVal == 0) {
            return std::make_any<std::shared_ptr<Operand>>(
                createOperand("0", OperandType::CONSTANT)
            );
        }
        // 左为真（非0），结果取决于右操作数
        else {
            auto rightResult = visit(ctx->relExpr());
            if (rightResult.has_value()) {
                return rightResult;
            }
        }
        return std::any();
    }

    // 生成临时变量存储最终结果
    std::string tempVar = generateTemp();
    auto resultOperand = createOperand(tempVar, OperandType::TEMP);

    // 生成标签：左为假时跳转（短路）、计算右操作数、结束
    std::string leftFalseLabel = generateLabel();  // 左操作数为假时进入
    std::string computeRightLabel = generateLabel(); // 左为真，需要计算右操作数
    std::string endLabel = generateLabel();        // 统一结束点

    auto zeroOperand = createOperand("0", OperandType::CONSTANT);
    auto isLeftFalse = createOperand(generateTemp(), OperandType::TEMP);
    addInstruction(IRInstruction(IROpcode::EQ, isLeftFalse, leftOperand, zeroOperand));
    addInstruction(IRInstruction(IROpcode::IF_GOTO, nullptr, isLeftFalse, nullptr, leftFalseLabel));
    addInstruction(IRInstruction(IROpcode::GOTO, nullptr, nullptr, nullptr, computeRightLabel));
    addInstruction(IRInstruction(IROpcode::LABEL, nullptr, nullptr, nullptr, leftFalseLabel));
    addInstruction(IRInstruction(IROpcode::ASSIGN, resultOperand, zeroOperand)); // 结果为假
    addInstruction(IRInstruction(IROpcode::GOTO, nullptr, nullptr, nullptr, endLabel));
    addInstruction(IRInstruction(IROpcode::LABEL, nullptr, nullptr, nullptr, computeRightLabel));
    
    auto rightResult = visit(ctx->relExpr());
    if (!rightResult.has_value()) return std::any(); // 右操作数无效
    auto rightOperand = std::any_cast<std::shared_ptr<Operand>>(rightResult);
    addInstruction(IRInstruction(IROpcode::AND, resultOperand, leftOperand, rightOperand));
    addInstruction(IRInstruction(IROpcode::GOTO, nullptr, nullptr, nullptr, endLabel));
    addInstruction(IRInstruction(IROpcode::LABEL, nullptr, nullptr, nullptr, endLabel));

    return std::make_any<std::shared_ptr<Operand>>(resultOperand);
}

std::any IRGenerator::visitSingleLOr(ToyCParser::SingleLOrContext *ctx) {
    return visit(ctx->lAndExpr());
}

// 处理逻辑或（||），实现短路判断
std::any IRGenerator::visitMulLOrExpr(ToyCParser::MulLOrExprContext *ctx) {
    std::string trueLabel = generateLabel();  // 结果为真的标签
    std::string endLabel = generateLabel();   // 结束标签

    // 1. 计算左操作数
    auto leftResult = visit(ctx->lOrExpr());
    if (!leftResult.has_value()) return std::any();
    auto leftOperand = std::any_cast<std::shared_ptr<Operand>>(leftResult);

    // 常量折叠：左操作数为常量
    if (leftOperand->type == OperandType::CONSTANT) {
        int leftVal = std::stoi(leftOperand->value);
        
        // 左为真（非0），直接返回1（短路）
        if (leftVal != 0) {
            return std::make_any<std::shared_ptr<Operand>>(
                createOperand("1", OperandType::CONSTANT)
            );
        }
        // 左为假（0），结果取决于右操作数
        else {
            auto rightResult = visit(ctx->lAndExpr());
            if (rightResult.has_value()) {
                return rightResult;
            }
        }
        return std::any();
    }

    // 直接检查左操作数是否为真（短路优化）
    addInstruction(IRInstruction(IROpcode::IF_GOTO, nullptr, leftOperand, nullptr, trueLabel));

    // 左为假：计算右操作数
    auto rightResult = visit(ctx->lAndExpr());
    if (!rightResult.has_value()) return std::any();
    auto rightOperand = std::any_cast<std::shared_ptr<Operand>>(rightResult);

    // 创建结果临时变量（重用右操作数）
    std::string tempVar = generateTemp();
    auto resultOperand = createOperand(tempVar, OperandType::TEMP);
    addInstruction(IRInstruction(IROpcode::ASSIGN, resultOperand, rightOperand));
    addInstruction(IRInstruction(IROpcode::GOTO, nullptr, nullptr, nullptr, endLabel));

    // 左为真：直接设置结果为1（短路）
    addInstruction(IRInstruction(IROpcode::LABEL, nullptr, nullptr, nullptr, trueLabel));
    auto oneOperand = createOperand("1", OperandType::CONSTANT);
    addInstruction(IRInstruction(IROpcode::ASSIGN, resultOperand, oneOperand));

    addInstruction(IRInstruction(IROpcode::LABEL, nullptr, nullptr, nullptr, endLabel));

    return std::make_any<std::shared_ptr<Operand>>(resultOperand);
}

// 访问一元表达式
std::any IRGenerator::visitSingleUnary(ToyCParser::SingleUnaryContext *ctx) {
    return visit(ctx->primaryExpr());
}

std::any IRGenerator::visitMulUnaryOp(ToyCParser::MulUnaryOpContext *ctx) {
    auto operandResult = visit(ctx->unaryExpr());
    
    if (operandResult.has_value()) {
        auto operand = std::any_cast<std::shared_ptr<Operand>>(operandResult);
        
        // 常量折叠优化
        if (operand->type == OperandType::CONSTANT) {
            int val = std::stoi(operand->value);
            int resultVal;
            
            if (ctx->ADD()) resultVal = val;        // +x = x
            else if (ctx->SUB()) resultVal = -val;   // -x
            else if (ctx->NOT()) resultVal = !val;   // !x
            
            return std::make_any<std::shared_ptr<Operand>>(
                createOperand(std::to_string(resultVal), OperandType::CONSTANT)
            );
        }
        
        // 代数简化：-(-x) = x
        if (ctx->SUB() && operand->type == OperandType::TEMP) {
            // 检查前一条指令是否是负号操作
            if (!currentFunction->instructions.empty()) {
                auto& lastInst = currentFunction->instructions.back();
                if (lastInst.opcode == IROpcode::SUB && 
                    lastInst.arg1->value == "0" && 
                    lastInst.arg2->toString() == operand->toString()) {
                    return std::make_any<std::shared_ptr<Operand>>(lastInst.arg2);
                }
            }
        }

        std::string tempVar = generateTemp();
        auto tempOperand = createOperand(tempVar, OperandType::TEMP);
        
        IROpcode opcode;
        if (ctx->ADD()) {
            // 正号，直接赋值
            addInstruction(IRInstruction(IROpcode::ASSIGN, tempOperand, operand));
        } else if (ctx->SUB()) {
            // 负号，0减去操作数
            auto zeroOperand = createOperand("0", OperandType::CONSTANT);
            addInstruction(IRInstruction(IROpcode::SUB, tempOperand, zeroOperand, operand));
        } else if (ctx->NOT()) {
            // 逻辑非
            addInstruction(IRInstruction(IROpcode::NOT, tempOperand, operand));
        }
        
        return std::make_any<std::shared_ptr<Operand>>(tempOperand);
    }
    
    return std::any();
}

// 访问括号表达式
std::any IRGenerator::visitParenthesizedExpr(ToyCParser::ParenthesizedExprContext *ctx) {
    return visit(ctx->expr());
}

// 其他必要的访问方法实现
std::any IRGenerator::visitBlockStmt(ToyCParser::BlockStmtContext *ctx) {
    return visit(ctx->block());
}

std::any IRGenerator::visitEmptyStmt(ToyCParser::EmptyStmtContext *ctx) {
    return nullptr;
}

std::any IRGenerator::visitExprStmt(ToyCParser::ExprStmtContext *ctx) {
    return visit(ctx->expr());
}

std::any IRGenerator::visitBreakStmt(ToyCParser::BreakStmtContext *ctx) {
    // 检查是否在循环中
    if (loopStack.empty()) {
        std::cerr << "错误: break语句不在循环中" << std::endl;
        return nullptr;
    }
    
    // 跳转到当前循环的结束标签
    std::string endLabel = loopStack.back().endLabel;
    addInstruction(IRInstruction(IROpcode::GOTO, nullptr, nullptr, nullptr, endLabel));
    
    return nullptr;
}

std::any IRGenerator::visitContinueStmt(ToyCParser::ContinueStmtContext *ctx) {
    // 检查是否在循环中
    if (loopStack.empty()) {
        std::cerr << "错误: continue语句不在循环中" << std::endl;
        return nullptr;
    }
    
    // 跳转到当前循环的开始标签
    std::string loopLabel = loopStack.back().loopLabel;
    addInstruction(IRInstruction(IROpcode::GOTO, nullptr, nullptr, nullptr, loopLabel));
    
    return nullptr;
}

std::any IRGenerator::visitParam(ToyCParser::ParamContext *ctx) {
    return visitChildren(ctx);
} 

void IRGenerator::enterScope() {
    symbolTableStack.push_back({});
}

void IRGenerator::exitScope() {
    symbolTableStack.pop_back();
}

std::string IRGenerator::addVariable(const std::string& name) {
    int version = ++varVersion[name];
    std::string uniqueName = name + "_" + std::to_string(version);
    symbolTableStack.back()[name] = uniqueName;
    if (currentFunction) {
        currentFunction->varCount++;
    }
    return uniqueName;
}

std::string IRGenerator::lookupVariable(const std::string& name) {
    for (auto it = symbolTableStack.rbegin(); it != symbolTableStack.rend(); ++it) {
        if (it->count(name)) return it->at(name);
    }
    return name;
} 