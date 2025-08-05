#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// ANTLR 运行时头文件
#include "antlr4-runtime.h"
using namespace antlr4;

// ANTLR 生成的 Lexer 和 Parser 头文件
#include "ToyCLexer.h"
#include "ToyCParser.h"

// 语义分析器和IR生成器头文件
#include "SemanticAnalyzer.h"
#include "IRGenerator.h"
#include "codegenerator.h"

int main(int argc, const char* argv[]) {
    // 从标准输入读取源代码
    std::stringstream sourceCode;
    std::string line;
    
    // 读取所有输入行
    while (std::getline(std::cin, line)) {
        sourceCode << line << "\n";
    }
    
    // 创建ANTLR输入流
    std::string inputString = sourceCode.str();
    ANTLRInputStream input(inputString);

    // 2. 创建词法分析器 (Lexer)
    ToyCLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    // 3. 创建语法分析器 (Parser)
    ToyCParser parser(&tokens);

    // 4. 调用起始规则获取解析树
    ToyCParser::CompUnitContext* tree = parser.compUnit();

    // 5. 进行语义分析
    SemanticAnalyzer analyzer;
    analyzer.visit(tree);

    // 6. 检查语义分析结果
    if (analyzer.getErrorCount() > 0) {
        std::cerr << "Semantic analysis completed with " << analyzer.getErrorCount() << " errors." << std::endl;
        return 2; // 标记有语义错误
    }

    // 7. 生成IR代码
    IRGenerator irGenerator;
    irGenerator.visit(tree);
    irGenerator.printIR(); // 输出IR到output.txt

    // 8. 生成目标代码
    CodeGenerator codeGen;
    codeGen.generate(irGenerator.getFunctions());
    std::string assemblyCode = codeGen.getAssemblyCode();
    
    // 9. 向标准输出写入汇编代码
    std::cout << assemblyCode;
    
    return 0;
} 