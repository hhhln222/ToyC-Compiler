#include <iostream>
#include <fstream>
#include <string>

// ANTLR 运行时头文件
#include "antlr4-runtime.h"
using namespace antlr4;

// ANTLR 生成的 Lexer 和 Parser 头文件
#include "ToyCLexer.h"
#include "ToyCParser.h"

// 你的语义分析器头文件
#include "SemanticAnalyzer.h"

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];

    // 1. 创建输入流
    std::ifstream stream;
    stream.open(inputFile);
    if (!stream.is_open()) {
        std::cerr << "Error: Could not open input file " << inputFile << std::endl;
        return 1;
    }
    ANTLRInputStream input(stream);

    // 2. 创建词法分析器 (Lexer)
    ToyCLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    // 3. 创建语法分析器 (Parser)
    ToyCParser parser(&tokens);

    // 移除默认错误监听器，如果你想完全自定义错误输出
    // parser.removeErrorListeners();
    // lexer.removeErrorListeners();

    // 4. 调用起始规则获取解析树
    ToyCParser::CompUnitContext* tree = parser.compUnit();

    // 5. 进行语义分析
    SemanticAnalyzer analyzer;
    analyzer.visit(tree); // 启动访问者模式，遍历解析树并进行语义检查

    // 6. 报告语义分析结果
    if (analyzer.getErrorCount() == 0) {
        std::cout << "Semantic analysis completed successfully with no errors." << std::endl;
    } else {
        std::cout << "Semantic analysis completed with " << analyzer.getErrorCount() << " errors." << std::endl;
        return 2; // 标记有语义错误
    }

    return 0;
}