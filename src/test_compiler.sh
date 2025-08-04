#!/bin/bash

echo "Testing modified compiler with stdin/stdout..."

# 进入src目录
cd src

# 编译程序
if [ ! -d "build" ]; then
    mkdir build
fi

cd build
cmake ..
make

# 测试1：简单的阶乘程序
echo "=== Test 1: Factorial Program ==="
cat << 'EOF' | ./parser_with_ir
int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main() {
    int x = 5;
    int result = factorial(x);
    return result;
}
EOF

echo -e "\n=== Test 1 completed ===\n"

# 测试2：算术运算程序
echo "=== Test 2: Arithmetic Operations ==="
cat << 'EOF' | ./parser_with_ir
int add(int a, int b) {
    return a + b;
}

int main() {
    int x = 10;
    int y = 20;
    int sum = add(x, y);
    return sum;
}
EOF

echo -e "\n=== Test 2 completed ===\n"

# 测试3：循环和条件语句
echo "=== Test 3: Loops and Conditionals ==="
cat << 'EOF' | ./parser_with_ir
int main() {
    int i = 0;
    int sum = 0;
    while (i < 10) {
        if (i % 2 == 0) {
            sum = sum + i;
        }
        i = i + 1;
    }
    return sum;
}
EOF

echo -e "\n=== Test 3 completed ===" 