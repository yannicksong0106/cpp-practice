// 任务4：分式化简
// 输入：分子 分母（如 6 8）
// 输出：化简结果（如 3/4）
// 时间复杂度：O(log min(a,b))，欧几里得算法

#include <iostream>
#include <cstdlib>

int gcd(int a, int b) {
    a = std::abs(a);
    b = std::abs(b);
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    int a = 0, b = 0;
    std::cout << "请输入分子 分母: ";
    if (!(std::cin >> a >> b) || b == 0) {
        std::cerr << "分母不能为 0\n";
        return 1;
    }

    // 约定：分母保持为正
    if (b < 0) {
        a = -a;
        b = -b;
    }

    int g = gcd(a, b);
    int na = a / g;
    int nb = b / g;

    std::cout << "化简结果：" << na << "/" << nb << '\n';
    return 0;
}
