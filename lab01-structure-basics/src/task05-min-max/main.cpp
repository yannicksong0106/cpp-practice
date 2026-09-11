// 任务5：求数组最大值与最小值
// 自定义函数封装；一次遍历同时求最大最小
// 时间复杂度：最好/最坏/平均均为 O(n)

#include <iostream>

void find_min_max(const int r[], int n, int& min_val, int& max_val) {
    if (n <= 0) {
        return;
    }
    min_val = max_val = r[0];
    for (int i = 1; i < n; ++i) {
        if (r[i] < min_val) {
            min_val = r[i];
        }
        if (r[i] > max_val) {
            max_val = r[i];
        }
    }
}

int main() {
    const int n = 8;
    int r[n] = {42, 7, 19, 3, 88, 15, 64, 1};

    int min_val = 0, max_val = 0;
    find_min_max(r, n, min_val, max_val);

    std::cout << "数组：";
    for (int i = 0; i < n; ++i) {
        std::cout << r[i];
        if (i + 1 < n) {
            std::cout << ' ';
        }
    }
    std::cout << '\n';
    std::cout << "最小值: " << min_val << '\n';
    std::cout << "最大值: " << max_val << '\n';

    return 0;
}
