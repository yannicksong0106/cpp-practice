// 任务3：1~n 累加与复杂度分析
// 实现1：循环迭代 —— 时间 O(n)，空间 O(1)
// 实现2：公式 n*(n+1)/2 —— 时间 O(1)，空间 O(1)

#include <iostream>

// 循环迭代
long long sum_iterative(int n) {
    long long s = 0;
    for (int i = 1; i <= n; ++i) {
        s += i;
    }
    return s;
}

// 数学公式
long long sum_formula(int n) {
    return 1LL * n * (n + 1) / 2;
}

int main() {
    int n = 0;
    std::cout << "请输入 n: ";
    if (!(std::cin >> n) || n < 1) {
        std::cerr << "n 必须为正整数\n";
        return 1;
    }

    std::cout << "循环迭代: " << sum_iterative(n) << '\n';
    std::cout << "公式计算: " << sum_formula(n) << '\n';

    return 0;
}
