#include <iostream>
#include <fstream>
#include "antlr4-runtime.h"
#include "generated/ToyCLexer.h"     
#include "generated/ToyCParser.h"    

using namespace antlr4;

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input-file>\n";
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile) {
        std::cerr << "Error: Cannot open input file: " << argv[1] << "\n";
        return 2;
    }

    try {
        // 创建输入流
        ANTLRInputStream input(inputFile);
        
        // 创建词法分析器
        ToyCLexer lexer(&input);
        CommonTokenStream tokens(&lexer);
        
        // 创建语法分析器
        ToyCParser parser(&tokens);
        
        // 从起始规则开始解析
        auto parseTree = parser.compUnit();
        
        // 打印解析树
        std::cout << "Parse Tree:\n" << parseTree->toStringTree(&parser) << "\n";
        
        std::cout << "Parsing completed successfully!\n";
        
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 3;
    }

    return 0;
}