// 任务1：顺序表初始化、赋值与遍历
// 静态数组 + 模板类 SeqList；位序从 1 开始（打印时按存储下标）

#include <iostream>
using namespace std;

const int MaxSize = 100;

template <typename DataType>
class SeqList {
public:
    SeqList() { length = 0; }

    SeqList(DataType a[], int n) {
        if (n > MaxSize) n = MaxSize;
        for (int i = 0; i < n; i++) data[i] = a[i];
        length = n;
    }

    void PrintList() const {
        cout << "顺序表元素（共 " << length << " 个）：";
        for (int i = 0; i < length; i++) {
            cout << data[i];
            if (i + 1 < length) cout << " ";
        }
        cout << endl;
    }

private:
    DataType data[MaxSize];
    int length;
};

int main() {
    int a[8] = {12, 7, 25, 3, 18, 42, 9, 16};
    SeqList<int> emptyList;
    cout << "== 默认构造（空表） ==" << endl;
    emptyList.PrintList();

    SeqList<int> L(a, 8);
    cout << "== 带参构造（批量赋值 8 个整数） ==" << endl;
    L.PrintList();
    return 0;
}
