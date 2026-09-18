// 任务3：顺序表菜单综合操作
// 内置初始表 {1,3,5,7,9}，菜单插入/删除/查找，输入 0 退出

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

    int Locate(DataType x) const {
        for (int i = 0; i < length; i++) {
            if (data[i] == x) return i + 1;
        }
        return 0;
    }

    void PrintList() const {
        cout << "当前线性表：";
        for (int i = 0; i < length; i++) {
            cout << data[i];
            if (i + 1 < length) cout << " ";
        }
        cout << "  (length=" << length << ")" << endl;
    }

private:
    DataType data[MaxSize];
    int length;
};

void ShowMenu() {
    cout << "\n======== 顺序表操作菜单 ========" << endl;
    cout << "1. 插入元素" << endl;
    cout << "2. 删除元素" << endl;
    cout << "3. 查找元素" << endl;
    cout << "0. 退出程序" << endl;
    cout << "================================" << endl;
    cout << "请选择操作：";
}

int main() {
    int init[5] = {1, 3, 5, 7, 9};
    SeqList<int> L(init, 5);

    cout << "初始线性表创建完成（内置元素 1,3,5,7,9）" << endl;
    L.PrintList();

    int choice = -1;
    while (true) {
        ShowMenu();
        if (!(cin >> choice)) break;
        if (choice == 0) {
            cout << "程序结束，再见！" << endl;
            break;
        }
        if (choice == 1) {
            int pos, val;
            cout << "请输入插入位序和元素值（如: 3 4）：";
            cin >> pos >> val;
            if (L.Insert(pos, val)) {
                cout << "插入成功：在位序 " << pos << " 插入 " << val << endl;
                L.PrintList();
            }
        } else if (choice == 2) {
            int pos, val;
            cout << "请输入删除位序：";
            cin >> pos;
            if (L.Delete(pos, val)) {
                cout << "删除成功：删除了位序 " << pos << " 的元素 " << val << endl;
                L.PrintList();
            }
        } else if (choice == 3) {
            int val;
            cout << "请输入要查找的元素值：";
            cin >> val;
            int pos = L.Locate(val);
            if (pos) cout << "查找成功：" << val << " 在位序 " << pos << endl;
            else cout << "查找失败：" << val << " 不在线性表中" << endl;
            L.PrintList();
        } else {
            cout << "无效选择，请重新输入。" << endl;
        }
    }
    return 0;
}
