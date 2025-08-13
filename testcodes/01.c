// 包含常量传播典型场景的函数

int test_optimize(int x) {
    int a = 3 + 5;                  // 可常量折叠
    int b = a * 2;                  // 可常量传播（a为常量）
    int c = x + 0;                  // 可代数简化（x+0→x）
    int d = b + c;                  
    int e = b + c;                  // 可公共子表达式消除（与d相同）
    int f = 10;                     
    if (f > 20) {                   // 可常量条件判断（永远为假）
        return 0;                   // 死代码（永远不执行）
    } else {
        return d + e;
    }
}

int main(){
    int x = test_optimize(10);
    return x;
}

// test_optimize.c
int main() {
    int a = 5;
    int b = 0;
    int d = b * 1;      // 可化简为 d = c（代数化简：x*1=x）
    int e = d - 0;      // 可化简为 e = d（代数化简：x-0=x）
    
    return e;           // 最终返回5
}