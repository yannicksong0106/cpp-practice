// 任务2：逻辑结构与存储结构
// 逻辑结构：线性结构（5 个整数）
// 存储结构：顺序存储（普通数组）
// 不使用链表，不使用 STL 容器

#include <iostream>

int main() {
    const int n = 5;
    int a[n];  // 顺序存储

    // 赋值
    a[0] = 12;
    a[1] = 7;
    a[2] = 25;
    a[3] = 3;
    a[4] = 18;

    // 遍历输出
    std::cout << "顺序存储的 5 个整数：";
    for (int i = 0; i < n; ++i) {
        std::cout << a[i];
        if (i + 1 < n) {
            std::cout << ' ';
        }
    }
    std::cout << '\n';

    return 0;
}
