#include "IROptimizer.h"
#include <algorithm>
#include <sstream>

void IROptimizer::optimize(std::vector<FunctionInfo>& functions) {
    for (auto& func : functions) {
        bool changed = false;
        constexpr int MAX_ITERATIONS = 100; 
        int iterationCount = 0;
        do {
            if (++iterationCount > MAX_ITERATIONS) {
                break;
            }
            LiveAnalyzer liveAnalyzer;
            liveAnalyzer.analyze(func.instructions);
            changed = false;
            // 1. 分割为基本块并构建CFG
            auto blocks = splitIntoBasicBlocks(func);
            buildCFG(blocks);

            // 2. 对每个基本块应用优化
            for (auto& block : blocks) {
                algebraicSimplification(block, changed);
                constantFolding(block, changed);
                copyPropagation(block, changed);
                // commonSubexpressionElimination(block, changed);
            }

            // 3. 基于CFG的优化（如跨块死代码消除）
            deadCodeElimination(blocks, liveAnalyzer, changed);

            // 4. 合并基本块回函数
            mergeBasicBlocks(func, blocks);

        } while (changed);
        updateVariableCounts(func);
    }
}

// 分割函数指令为基本块
std::vector<BasicBlock> IROptimizer::splitIntoBasicBlocks(FunctionInfo& func) {
    std::vector<BasicBlock> blocks;
    if (func.instructions.empty()) return blocks;

    std::unordered_map<std::string, size_t> labelMap;
    for (size_t i = 0; i < func.instructions.size(); ++i) {
        if (func.instructions[i].opcode == IROpcode::LABEL) {
            labelMap[func.instructions[i].label] = i;
        }
    }

    // 第一步：标记所有基本块的入口点
    std::unordered_set<size_t> entryPoints;
    entryPoints.insert(0);  // 函数第一条指令是入口

    for (size_t i = 0; i < func.instructions.size(); ++i) {
        const auto& inst = func.instructions[i];
        if (inst.opcode == IROpcode::GOTO || inst.opcode == IROpcode::IF_GOTO) {
            if (auto it = labelMap.find(inst.label); it != labelMap.end()) {
                entryPoints.insert(it->second); // O(1)查找
            }
            // 跳转指令的下一条是入口点
            if (i + 1 < func.instructions.size()) {
                entryPoints.insert(i + 1);
            }
            // 跳转目标标号所在指令是入口点
            for (size_t j = 0; j < func.instructions.size(); ++j) {
                if (func.instructions[j].opcode == IROpcode::LABEL && 
                    func.instructions[j].label == inst.label) {
                    entryPoints.insert(j);
                    break;
                }
            }
        } else if (inst.opcode == IROpcode::LABEL) {
            // 标号指令本身是入口点
            entryPoints.insert(i);
        }
    }

    // 第二步：根据入口点分割基本块
    BasicBlock currentBlock;
    for (size_t i = 0; i < func.instructions.size(); ++i) {
        if (entryPoints.count(i) && i != 0) {
            // 遇到新入口点，保存当前块并开始新块
            blocks.push_back(std::move(currentBlock));
            currentBlock = BasicBlock();
        }

        const auto& inst = func.instructions[i];
        if (inst.opcode == IROpcode::LABEL) {
            currentBlock.label = inst.label;  // 记录块入口标号
        }
        currentBlock.instructions.push_back(inst);

        // 跳转指令结束当前块
        if (inst.opcode == IROpcode::GOTO || inst.opcode == IROpcode::IF_GOTO || 
            inst.opcode == IROpcode::RETURN) {
            blocks.push_back(std::move(currentBlock));
            currentBlock = BasicBlock();
        }
    }

    // 处理剩余指令
    if (!currentBlock.instructions.empty()) {
        blocks.push_back(std::move(currentBlock));
    }

    return blocks;
}

// 构建控制流图（CFG）
void IROptimizer::buildCFG(std::vector<BasicBlock>& blocks) {
    if (blocks.empty()) return;

    // 建立标号到基本块的映射
    std::unordered_map<std::string, BasicBlock*> labelToBlock;
    for (auto& block : blocks) {
        if (!block.label.empty()) {
            labelToBlock[block.label] = &block;
        }
    }

    // 为每个基本块设置前驱和后继
    for (size_t i = 0; i < blocks.size(); ++i) {
        auto& block = blocks[i];
        if (block.instructions.empty()) continue;

        const auto& lastInst = block.instructions.back();
        switch (lastInst.opcode) {
            case IROpcode::GOTO: {
                // 无条件跳转：后继为目标标号块
                auto it = labelToBlock.find(lastInst.label);
                if (it != labelToBlock.end()) {
                    BasicBlock* succ = it->second;
                    block.successors.insert(succ);
                    succ->predecessors.insert(&block);
                }
                break;
            }
            case IROpcode::IF_GOTO: {
                // 条件跳转：后继为目标标号块和下一个基本块
                auto it = labelToBlock.find(lastInst.label);
                if (it != labelToBlock.end()) {
                    BasicBlock* succ = it->second;
                    block.successors.insert(succ);
                    succ->predecessors.insert(&block);
                }
                if (i + 1 < blocks.size()) {
                    BasicBlock* nextBlock = &blocks[i + 1];
                    block.successors.insert(nextBlock);
                    nextBlock->predecessors.insert(&block);
                }
                break;
            }
            case IROpcode::RETURN: {
                // 返回指令：无后继
                break;
            }
            default: {
                // 顺序执行：后继为下一个基本块
                if (i + 1 < blocks.size()) {
                    BasicBlock* nextBlock = &blocks[i + 1];
                    block.successors.insert(nextBlock);
                    nextBlock->predecessors.insert(&block);
                }
            }
        }
    }
}

// 合并基本块回函数指令列表
void IROptimizer::mergeBasicBlocks(FunctionInfo& func, const std::vector<BasicBlock>& blocks) {
    size_t total_instructions = 0;
    for (const auto& block : blocks) {
        total_instructions += block.instructions.size();
    }
    func.instructions.clear();
    func.instructions.reserve(total_instructions); // 预分配内存
    
    for (const auto& block : blocks) {
        func.instructions.insert( // 批量移动
            func.instructions.end(),
            std::make_move_iterator(block.instructions.begin()),
            std::make_move_iterator(block.instructions.end())
        );
    }
}

// 修改常量折叠函数
void IROptimizer::constantFolding(BasicBlock& block, bool& changed) {
    for (auto& inst : block.instructions) {
        // 处理二元运算指令
        if (inst.opcode == IROpcode::ADD    || inst.opcode == IROpcode::SUB ||
            inst.opcode == IROpcode::MUL    || inst.opcode == IROpcode::DIV ||
            inst.opcode == IROpcode::MOD    || inst.opcode == IROpcode::AND ||
            inst.opcode == IROpcode::OR     || inst.opcode == IROpcode::LT  ||
            inst.opcode == IROpcode::GT     || inst.opcode == IROpcode::LE  ||
            inst.opcode == IROpcode::GE     || inst.opcode == IROpcode::EQ  ||
            inst.opcode == IROpcode::NE) {

            auto computed = computeBinaryOp(inst.opcode, inst.arg1, inst.arg2);
            if (computed) {
                // std::cout << "old: " << inst.toString() << std::endl;
                inst = IRInstruction(IROpcode::ASSIGN, inst.result, computed);
                inst.result->value = computed->value;//绑定
                // std::cout << "new: " << inst.toString() << std::endl;
                changed = true;
            }
        }
        // 单独处理一元运算NOT指令
        else if (inst.opcode == IROpcode::NOT) {
            // 检查操作数是否为常量
            if (inst.arg1->isConstant()) {
                int val = inst.arg1->getConstantValue();
                // 计算NOT结果（逻辑非：0→1，非0→0）
                int result = (val == 0) ? 1 : 0;
                
                // std::cout << "old: " << inst.toString() << std::endl;
                inst = IRInstruction(IROpcode::ASSIGN, inst.result, createConstant(result));
                inst.result->value = result;//绑定
                // std::cout << "new: " << inst.toString() << std::endl;
                changed = true;
            }
        }
    }
}

// 复制传播：用原始值替换复制变量
void IROptimizer::copyPropagation(BasicBlock& block, bool& changed) {
    // 复制映射表：目标变量 -> 源操作数（支持常量传播）
    std::unordered_map<std::string, std::shared_ptr<Operand>> copyMap;
    
    for (auto& inst : block.instructions) {
        // 如果是赋值指令，记录复制/常量关系（支持传递性）
        if (inst.opcode == IROpcode::ASSIGN) {
            if (inst.arg1->isVar() || 
                inst.arg1->isConstant() ||
                inst.arg1->isTEMP()) {
                // 查找传递后的源操作数（处理间接引用，如a=b, b=5，则a直接映射到5）
                std::shared_ptr<Operand> source = inst.arg1;
                // 递归查找最终源（如果是变量/临时变量且存在映射）
                while (source->isVar() || source->isTEMP()) {
                    auto it = copyMap.find(source->toString());
                    if (it != copyMap.end()) {
                        source = it->second; // 传递映射关系
                    } else {
                        break; // 没有更多映射，停止查找
                    }
                }
                // 记录最终映射关系（可能是常量）
                copyMap[inst.result->toString()] = source;
            }
        }
        // 其他指令可能破坏复制/常量关系
        else if (inst.opcode != IROpcode::PARAM) {
            // 如果指令修改了结果变量，从映射中移除
            if (inst.result) {
                copyMap.erase(inst.result->toString());
            }
            // 有副作用的指令（如函数调用）会破坏所有映射关系
            if (inst.opcode == IROpcode::CALL){
                //   (inst.opcode == IROpcode::PARAM)  ||   
                //   (inst.opcode == IROpcode::RETURN) ||  
                //   (inst.opcode == IROpcode::GOTO)   || 
                //   (inst.opcode == IROpcode::IF_GOTO)   ||
                //   (inst.opcode == IROpcode::LABEL)) {
                copyMap.clear();
            }
        }
        
        // 替换操作数：使用映射表中的值（可能是常量）替换变量
        auto replaceOperand = [&](std::shared_ptr<Operand>& arg) {
            if (arg && (arg->isVar() || arg->isTEMP())) {
                auto it = copyMap.find(arg->toString());
                if (it != copyMap.end()) {
                    // 找到映射值（可能是常量），进行替换
                    arg = it->second;
                    changed = true;
                }
            }
        };
        
        // 对两个操作数都进行替换处理
        replaceOperand(inst.arg1);
        replaceOperand(inst.arg2);
    }
}

// 死代码消除函数
void IROptimizer::deadCodeElimination(std::vector<BasicBlock>& blocks, const LiveAnalyzer& liveAnalyzer,bool& changed){
    if (blocks.empty()) return;

    // 仅保留：收集所有被使用的变量（包括普通变量和临时变量）
    std::unordered_set<std::string> usedVars;
    for (const auto& block : blocks) {
        for (const auto& inst : block.instructions) {
            auto collectUsed = [&](const std::shared_ptr<Operand>& op) {
                if (!op) return;
                // 只关注变量和临时变量的使用
                if (op->isVar() || op->isTEMP()) {
                    usedVars.insert(op->toString());
                }
            };
            collectUsed(inst.arg1);   // 收集操作数1中使用的变量
            collectUsed(inst.arg2);   // 收集操作数2中使用的变量
        }
    }

    // 仅保留：删除“定义了未使用变量且无副作用”的指令
    for (auto& block : blocks) {
        std::vector<IRInstruction> optimizedInsts;
        for (auto& inst : block.instructions) {
            bool keep = true;

            // 判断指令是否定义了变量/临时变量，且该变量未被使用
            if (inst.result && 
                (inst.result->isVar() || inst.result->isTEMP())) {
                
                std::string varName = inst.result->toString();
                // 若变量未被使用，且指令无副作用，则删除
                if (!usedVars.count(varName)) {
                    bool hasSideEffect = (inst.opcode == IROpcode::CALL)    ||  // 函数调用有副作用
                                         (inst.opcode == IROpcode::PARAM)   ||  // 参数传递有副作用
                                         (inst.opcode == IROpcode::RETURN)  ||  // 返回指令有副作用
                                         (inst.opcode == IROpcode::GOTO)    ||  // 跳转指令影响控制流
                                         (inst.opcode == IROpcode::IF_GOTO) ||  // 条件跳转影响控制流
                                         (inst.opcode == IROpcode::LABEL);     // 标号指令是控制流标记

                    if (!hasSideEffect) {
                        changed = true;  // 标记有修改
                        keep = false;    // 不保留该指令
                    }
                }
            }

            // 保留有用的指令
            if (keep) {
                optimizedInsts.push_back(std::move(inst));
            }
        }
        block.instructions = optimizedInsts;
    }
}

// 代数化简：简化常见代数模式 (如 x+0, x*1 等)
void IROptimizer::algebraicSimplification(BasicBlock& block, bool& changed) {
    for (auto& inst : block.instructions) {
        switch (inst.opcode) {
            case IROpcode::ADD:
                // x + 0 = x
                if (inst.arg2->isConstant() && inst.arg2->getConstantValue() == 0) {
                    // std::cout<<"old: " + inst.toString()<<std::endl;
                    inst = IRInstruction(IROpcode::ASSIGN, inst.result, inst.arg1);
                    // std::cout<<"new: " + inst.toString()<<std::endl;
                    changed = true;
                }
                // 0 + x = x
                else if (inst.arg1->isConstant() && inst.arg1->getConstantValue() == 0) {
                    // std::cout<<"old: " + inst.toString()<<std::endl;
                    inst = IRInstruction(IROpcode::ASSIGN, inst.result, inst.arg2);
                    // std::cout<<"new: " + inst.toString()<<std::endl;
                    changed = true;
                }
                break;
                
            case IROpcode::SUB:
                // x - 0 = x
                if (inst.arg2->isConstant() && inst.arg2->getConstantValue() == 0) {
                    // std::cout<<"old: " + inst.toString()<<std::endl;
                    inst = IRInstruction(IROpcode::ASSIGN, inst.result, inst.arg1);
                    // std::cout<<"new: " + inst.toString()<<std::endl;
                    changed = true;
                }
                // x - x = 0
                else if (inst.arg1->toString() == inst.arg2->toString()) {
                    // std::cout<<"old: " + inst.toString()<<std::endl;
                    inst = IRInstruction(IROpcode::ASSIGN, inst.result, createConstant(0));
                    // std::cout<<"new: " + inst.toString()<<std::endl;
                    changed = true;
                }
                break;
                
            case IROpcode::MUL:
                // x * 0 = 0
                if ((inst.arg1->isConstant() && inst.arg1->getConstantValue() == 0) ||
                    (inst.arg2->isConstant() && inst.arg2->getConstantValue() == 0)) {
                    // std::cout<<"old: " + inst.toString()<<std::endl;
                    inst = IRInstruction(IROpcode::ASSIGN, inst.result, createConstant(0));
                    // std::cout<<"new: " + inst.toString()<<std::endl;
                    changed = true;
                }
                // x * 1 = x
                else if (inst.arg2->isConstant() && inst.arg2->getConstantValue() == 1) {
                    // std::cout<<"old: " + inst.toString()<<std::endl;
                    inst = IRInstruction(IROpcode::ASSIGN, inst.result, inst.arg1);
                    // std::cout<<"new: " + inst.toString()<<std::endl;
                    changed = true;
                }
                // 1 * x = x
                else if (inst.arg1->isConstant() && inst.arg1->getConstantValue() == 1) {
                    // std::cout<<"old: " + inst.toString()<<std::endl;
                    inst = IRInstruction(IROpcode::ASSIGN, inst.result, inst.arg2);
                    // std::cout<<"new: " + inst.toString()<<std::endl;
                    changed = true;
                }
                break;
                
            case IROpcode::DIV:
                // 0 / x = 0 (x != 0)
                if (inst.arg1->isConstant() && inst.arg1->getConstantValue() == 0) {
                    // std::cout<<"old: " + inst.toString()<<std::endl;
                    inst = IRInstruction(IROpcode::ASSIGN, inst.result, createConstant(0));
                    // std::cout<<"new: " + inst.toString()<<std::endl;
                    changed = true;
                }
                // x / 1 = x
                else if (inst.arg2->isConstant() && inst.arg2->getConstantValue() == 1) {
                    // std::cout<<"old: " + inst.toString()<<std::endl;
                    inst = IRInstruction(IROpcode::ASSIGN, inst.result, inst.arg1);
                    // std::cout<<"new: " + inst.toString()<<std::endl;
                    changed = true;
                }
                // x / x = 1
                else if (inst.arg1->toString() == inst.arg2->toString()) {
                    // std::cout<<"old: " + inst.toString()<<std::endl;
                    inst = IRInstruction(IROpcode::ASSIGN, inst.result, createConstant(1));
                    // std::cout<<"new: " + inst.toString()<<std::endl;
                    changed = true;
                }
                break;
                
            default:
                break;
        }
    }
}

void IROptimizer::commonSubexpressionElimination(BasicBlock& block, bool& changed) {
    // 定义缓存条目结构
    struct CacheEntry {
        std::shared_ptr<Operand> result;
        size_t index;
        std::unordered_set<std::string> dependencies; // 依赖的变量集合
    };
    
    std::unordered_map<std::string, CacheEntry> exprCache;
    std::unordered_map<std::string, std::unordered_set<std::string>> varToExprs;
    
    for (size_t i = 0; i < block.instructions.size(); i++) {
        auto& inst = block.instructions[i];
        
        // 只处理可缓存的二元运算
        if (inst.opcode >= IROpcode::ADD && inst.opcode <= IROpcode::EQ) {
            // 创建表达式签名
            std::string signature = std::to_string(static_cast<int>(inst.opcode)) + 
                                   "_" + inst.arg1->toString() + 
                                   "_" + inst.arg2->toString();
            
            // 收集依赖变量
            std::unordered_set<std::string> deps;
            auto addDep = [&](const std::shared_ptr<Operand>& op) {
                if (op && (op->isVar() || op->isTEMP())) {
                    deps.insert(op->toString());
                }
            };
            addDep(inst.arg1);
            addDep(inst.arg2);
            
            // 如果表达式已计算过
            if (exprCache.find(signature) != exprCache.end()) {
                auto& cachedEntry = exprCache[signature];
                
                // 用之前的结果替换当前计算
                inst = IRInstruction(IROpcode::ASSIGN, inst.result, cachedEntry.result);
                changed = true;
                
                // 不需要更新缓存，因为结果相同
            }
            // 如果是新表达式，添加到缓存
            else {
                // 添加新缓存项
                exprCache[signature] = {inst.result, i, deps};
                
                // 更新反向索引
                for (const auto& var : deps) {
                    varToExprs[var].insert(signature);
                }
            }
        }
        
        // 当变量被重新定义时，精确清理缓存
        if (inst.result) {
            std::string definedVar = inst.result->toString();
            
            // 检查是否有表达式依赖此变量
            if (auto it = varToExprs.find(definedVar); it != varToExprs.end()) {
                // 收集所有受影响的表达式签名
                std::vector<std::string> exprsToRemove(it->second.begin(), it->second.end());
                
                for (const auto& sig : exprsToRemove) {
                    if (exprCache.find(sig) != exprCache.end()) {
                        // 从所有依赖项中移除
                        for (const auto& var : exprCache[sig].dependencies) {
                            if (varToExprs.find(var) != varToExprs.end()) {
                                varToExprs[var].erase(sig);
                            }
                        }
                        exprCache.erase(sig);
                    }
                }
                varToExprs.erase(definedVar);
            }
        }
    }
}

std::shared_ptr<Operand> IROptimizer::computeBinaryOp(
    IROpcode opcode, 
    const std::shared_ptr<Operand>& arg1, 
    const std::shared_ptr<Operand>& arg2
) {
    if (!arg1->isConstant() || !arg2->isConstant()) {
        return nullptr; // 非常量，无法计算
    }
    int val1 = arg1->getConstantValue();
    int val2 = arg2->getConstantValue();
    if (opcode == IROpcode::DIV && val2 == 0) {
        // return nullptr; // 避免除零
        return createConstant(0);//返回0
        // throw std::runtime_error("Division by zero detected during constant folding");//报错
    }
    int result;
    switch (opcode) {
        case IROpcode::ADD: result = val1 + val2; break;
        case IROpcode::SUB: result = val1 - val2; break;
        case IROpcode::MUL: result = val1 * val2; break;
        case IROpcode::DIV: result = val1 / val2; break;
        case IROpcode::MOD: result = val1 % val2; break;
        case IROpcode::AND: result = (val1 && val2) ? 1 : 0;; break;
        case IROpcode::OR:  result = (val1 || val2) ? 1 : 0; break;
        case IROpcode::LT:  result = (val1 < val2) ? 1 : 0; break;
        case IROpcode::GT:  result = (val1 > val2) ? 1 : 0; break;
        case IROpcode::LE:  result = (val1 <= val2) ? 1 : 0; break;
        case IROpcode::GE:  result = (val1 >= val2) ? 1 : 0; break;
        case IROpcode::EQ:  result = (val1 == val2) ? 1 : 0; break;
        case IROpcode::NE:  result = (val1 != val2) ? 1 : 0; break;
        default: return nullptr;
    }
    return createConstant(result);
}

void IROptimizer::printIR(const std::string& outputFile,std::vector<FunctionInfo>& functions) {
    std::ofstream out(outputFile);
    if (!out.is_open()) {
        std::cerr << "无法打开文件: " << outputFile << std::endl;
        return;
    }
    for (const auto& func : functions) {
        out << "\n=== Function: " << func.name << " ===" << std::endl;
        out << "Return type: " << func.returnType << std::endl;
        out << "Number of variables (including parameters): " << func.varCount << std::endl;
        int tempCount = func.tempVarCount;
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

void IROptimizer::updateVariableCounts(FunctionInfo& func) {
    std::unordered_set<std::string> variableIds;  // 普通变量（含参数）ID集合
    std::unordered_set<int> tempIds;              // 临时变量ID（数字）集合

    // 处理操作数的lambda函数
    auto processOperand = [&](const std::shared_ptr<Operand>& op) {
        if (!op) return;

        if (op->isVar() || op->type == OperandType::PARAM) {
            // 普通变量：直接用字符串ID去重
            variableIds.insert(op->toString());
        } else if (op->isTEMP()) {
            // 临时变量：解析ID为整数（假设格式为"0", "1", ...）
            try {
                int tempId = std::stoi(op->value);
                tempIds.insert(tempId);  // 用整数ID去重
            } catch (const std::invalid_argument& e) {
                std::cerr << "警告：无效的临时变量ID格式: " << op->toString() << std::endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "警告：临时变量ID超出范围: " << op->toString() << std::endl;
            }
        }
    };

    // 遍历所有指令的操作数（result、arg1、arg2）
    for (const auto& inst : func.instructions) {
        processOperand(inst.result);
        processOperand(inst.arg1);
        processOperand(inst.arg2);
    }

    // 更新普通变量数量（正确）
    func.varCount = variableIds.size();

    // 更新临时变量数量
    func.tempVarCount = tempIds.size();  // 直接用唯一ID的数量作为实际数量

    // 维护start/end计数器（用于后续生成新临时变量，不影响当前计数）
    if (tempIds.empty()) {
        func.startTempCounter = 0;
        func.endTempCounter = 0;
    } else {
        int minTemp = *std::min_element(tempIds.begin(), tempIds.end());
        int maxTemp = *std::max_element(tempIds.begin(), tempIds.end());
        func.startTempCounter = minTemp;
        func.endTempCounter = maxTemp + 1;  // 确保新生成的ID不重复
    }
}

void IROptimizer::printBasicBlocks(const std::string& outputFile, const std::vector<BasicBlock>& blocks) {
    std::ofstream out(outputFile);
    if (!out.is_open()) {
        std::cerr << "无法打开基本块输出文件: " << outputFile << std::endl;
        return;
    }

    out << "=== 基本块列表 ===" << std::endl;
    for (size_t i = 0; i < blocks.size(); ++i) {
        const auto& block = blocks[i];
        out << "基本块 " << i << " (入口标号: " << (block.label.empty() ? "无" : block.label) << ")" << std::endl;
        out << "  前驱: ";
        for (auto* pred : block.predecessors) {
            auto it = std::find_if(blocks.begin(), blocks.end(), [pred](const BasicBlock& b) { return &b == pred; });
            if (it != blocks.end()) {
                out << std::distance(blocks.begin(), it) << " ";
            }
        }
        out << std::endl;
        out << "  后继: ";
        for (auto* succ : block.successors) {
            auto it = std::find_if(blocks.begin(), blocks.end(), [succ](const BasicBlock& b) { return &b == succ; });
            if (it != blocks.end()) {
                out << std::distance(blocks.begin(), it) << " ";
            }
        }
        out << std::endl;
        out << "  指令:" << std::endl;
        for (const auto& inst : block.instructions) {
            out << "    " << inst.toString() << std::endl;
        }
    }
    out.close();
}

void LiveAnalyzer::analyze(const std::vector<IRInstruction>& instructions) {
    std::map<std::string, int> firstUse;
    std::map<std::string, int> lastUse;
    
    // 第一次遍历：记录首次和最后使用位置
    for (int i = 0; i < instructions.size(); i++) {
        const auto& inst = instructions[i];
        
        // 处理结果变量（定义点）
        if (inst.result) {
            const std::string var = inst.result->toString();
            if (firstUse.find(var) == firstUse.end()) {
                firstUse[var] = i;
            }
            lastUse[var] = i;
        }
        
        // 处理操作数（使用点）
        auto processOperand = [&](const std::shared_ptr<Operand> op) {
            if (op && op->type != OperandType::CONSTANT) {
                const std::string var = op->toString();
                lastUse[var] = i; // 更新最后使用位置
                if (firstUse.find(var) == firstUse.end()) {
                    firstUse[var] = i;
                }
            }
        };
        
        processOperand(inst.arg1);
        processOperand(inst.arg2);
    }
    
    // 构建生存期范围
    for (const auto& [var, first] : firstUse) {
        liveRanges[var] = {first, lastUse[var]};
    }
}

bool LiveAnalyzer::canShareSlot(const std::string& var1, const std::string& var2) const {
    if (!liveRanges.count(var1) || !liveRanges.count(var2)) 
        return false;
    
    const auto& range1 = liveRanges.at(var1);
    const auto& range2 = liveRanges.at(var2);
    
    // 检查生存期是否重叠
    return (range1.end < range2.start) || (range2.end < range1.start);
}

const std::map<std::string, LiveRange>& LiveAnalyzer::getLiveRanges() const {
    return liveRanges;
}