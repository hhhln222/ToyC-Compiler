cmake_minimum_required(VERSION 3.5)
project(antlr_parser)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)

# 添加可执行文件
add_executable(parser
    main.cpp
    generated/ToyCLexer.cpp
    generated/ToyCParser.cpp
    generated/SemanticAnalyzer.cpp
)

# 添加带IR生成的可执行文件
add_executable(parser_with_ir
    generated/main_with_ir.cpp
    generated/ToyCLexer.cpp
    generated/ToyCParser.cpp
    generated/SemanticAnalyzer.cpp
    generated/IRGenerator.cpp
)

# 链接 ANTLR4 库 
target_link_libraries(parser antlr4-runtime)
target_link_libraries(parser_with_ir antlr4-runtime)