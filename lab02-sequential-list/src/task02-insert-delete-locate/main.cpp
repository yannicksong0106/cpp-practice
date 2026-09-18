// 任务2：顺序表插入、删除、按值查找
// 位序 i 从 1 开始

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

    // 在位序 i 插入 x
    bool Insert(int i, DataType x) {
        if (length >= MaxSize) {
            cout << "插入失败：表已满" << endl;
            return false;
        }
        if (i < 1 || i > length + 1) {
            cout << "插入失败：位置 " << i << " 不合法" << endl;
            return false;
        }
        for (int j = length; j >= i; j--) data[j] = data[j - 1];
        data[i - 1] = x;
        length++;
        return true;
    }

    // 删除位序 i，返回被删元素
    bool Delete(int i, DataType &x) {
        if (length == 0 || i < 1 || i > length) {
            cout << "删除失败：位置 " << i << " 不合法" << endl;
            return false;
        }
        x = data[i - 1];
        for (int j = i; j < length; j++) data[j - 1] = data[j];
        length--;
        return true;
    }

    // 按值查找，返回位序；找不到返回 0
    int Locate(DataType x) const {
        for (int i = 0; i < length; i++) {
            if (data[i] == x) return i + 1;
        }
        return 0;
    }

    void PrintList() const {
        cout << "顺序表（length=" << length << "）：";
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
    int a[6] = {10, 20, 30, 40, 50, 60};
    SeqList<int> L(a, 6);

    cout << "== 初始顺序表 ==" << endl;
    L.PrintList();

    cout << "\n== 在位序 3 插入 25 ==" << endl;
    L.Insert(3, 25);
    L.PrintList();

    cout << "\n== 在位序 1 插入 5 ==" << endl;
    L.Insert(1, 5);
    L.PrintList();

    cout << "\n== 删除位序 4 的元素 ==" << endl;
    int x = 0;
    if (L.Delete(4, x)) cout << "被删元素: " << x << endl;
    L.PrintList();

    cout << "\n== 删除位序 1 的元素 ==" << endl;
    if (L.Delete(1, x)) cout << "被删元素: " << x << endl;
    L.PrintList();

    cout << "\n== 按值查找 40 ==" << endl;
    int pos = L.Locate(40);
    if (pos) cout << "40 在位序 " << pos << endl;
    else cout << "未找到 40" << endl;

    cout << "\n== 按值查找 99 ==" << endl;
    pos = L.Locate(99);
    if (pos) cout << "99 在位序 " << pos << endl;
    else cout << "未找到 99" << endl;

    return 0;
}
