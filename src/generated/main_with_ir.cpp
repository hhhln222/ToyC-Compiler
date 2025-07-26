#include <iostream>
#include <fstream>
#include <string>

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
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];

    // 打开输出文件并重定向cout和cerr
    std::ofstream outFile("output.txt");
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open output.txt for writing." << std::endl;
        return 1;
    }
    std::streambuf* coutBuf = std::cout.rdbuf();
    std::streambuf* cerrBuf = std::cerr.rdbuf();
    std::cout.rdbuf(outFile.rdbuf());
    std::cerr.rdbuf(outFile.rdbuf());

    // 1. 创建输入流
    std::ifstream stream;
    stream.open(inputFile);
    if (!stream.is_open()) {
        std::cerr << "Error: Could not open input file " << inputFile << std::endl;
        // 恢复输出
        std::cout.rdbuf(coutBuf);
        std::cerr.rdbuf(cerrBuf);
        return 1;
    }
    ANTLRInputStream input(stream);

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

    // 6. 报告语义分析结果
    if (analyzer.getErrorCount() > 0) {
        std::cout << "Semantic analysis completed with " << analyzer.getErrorCount() << " errors." << std::endl;
        // 恢复输出
        std::cout.rdbuf(coutBuf);
        std::cerr.rdbuf(cerrBuf);
        return 2; // 标记有语义错误
    }
    
    std::cout << "Semantic analysis completed successfully with no errors." << std::endl;

    // 7. 生成IR代码
    std::cout << "\n=== Generating IR Code ===" << std::endl;
    IRGenerator irGenerator;
    irGenerator.visit(tree);

    // 8. 打印生成的IR代码
    // std::cout << "\n=== Generating RISC-V Assembly ===" << std::endl;
    // 8. 生成目标代码
 std::cout << "\n=== Generating RISC-V Assembly ===" << std::endl;
    CodeGenerator codeGen;
    codeGen.generate(irGenerator.getFunctions());
    std::string assemblyCode = codeGen.getAssemblyCode();
    std::cout << assemblyCode << std::endl;

    // 8. 将汇编代码写入文件
    std::ofstream asmFile("output.s");
    asmFile << assemblyCode;
    asmFile.close();

    // 恢复输出
    std::cout.rdbuf(coutBuf);
    std::cerr.rdbuf(cerrBuf);

    // 9. 调用汇编器和模拟器
    system("riscv32-unknown-elf-gcc -o output output.s");
    system("spike pk output");
    return 0;
} 