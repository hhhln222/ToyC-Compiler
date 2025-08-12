cmake_minimum_required(VERSION 3.5)
project(toyC_compiler)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

add_executable(toyC_compiler
    main.cpp
    ${SOURCES} 
    ${HEADERS}
)

target_include_directories(toyC_compiler PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}       
    ${CMAKE_CURRENT_SOURCE_DIR}/src/fronted 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/semantic
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ir 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/riscv
)



# 链接 ANTLR4 库 
#target_link_libraries(parser antlr4-runtime)
target_link_libraries(toyC_compiler antlr4-runtime)