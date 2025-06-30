cmake_minimum_required(VERSION 3.5)
project(antlr_parser)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)

# 添加可执行文件
add_executable(parser
    main.cpp
    generated/ToyCLexer.cpp
    generated/ToyCParser.cpp
)

# 链接 ANTLR4 库 
target_link_libraries(parser antlr4-runtime)