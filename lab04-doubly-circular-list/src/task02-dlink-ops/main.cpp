// 任务2：双向链表删除、查找与修改（提高）
// 按位置查找返回结点地址、按值查找返回位序；删除时双指针联动；修改后遍历验证

#include <iostream>
using namespace std;

template <typename DataType>
struct DNode {
    DataType data;
    DNode* prev;
    DNode* next;

    DNode() : prev(nullptr), next(nullptr) {}
    explicit DNode(DataType v) : data(v), prev(nullptr), next(nullptr) {}
};

template <typename DataType>
class DoubleLinkList {
public:
    DoubleLinkList() : length(0) { head = new DNode<DataType>(); }

    ~DoubleLinkList() {
        DNode<DataType>* p = head;
        while (p != nullptr) {
            DNode<DataType>* q = p->next;
            delete p;
            p = q;
        }
    }

    void PushBack(DataType x) {
        DNode<DataType>* p = head;
        while (p->next != nullptr) p = p->next;
        DNode<DataType>* s = new DNode<DataType>(x);
        p->next = s;
        s->prev = p;
        length++;
    }

    // 按位置查找：返回第 i 个结点地址（位序从 1 开始），不合法返回 nullptr
    DNode<DataType>* GetNode(int i) const {
        if (i < 1 || i > length) return nullptr;
        DNode<DataType>* p = head->next;
        for (int k = 1; k < i; k++) p = p->next;
        return p;
    }

    // 按值查找：返回位序，找不到返回 0
    int Locate(DataType x) const {
        int idx = 0;
        for (DNode<DataType>* p = head->next; p != nullptr; p = p->next) {
            idx++;
            if (p->data == x) return idx;
        }
        return 0;
    }

    // 删除位序 i：前驱的后继跨过 p，后继的前驱指回前驱，再释放 p
    bool Delete(int i, DataType& x) {
        DNode<DataType>* p = GetNode(i);
        if (p == nullptr) {
            cout << "删除失败：位置 " << i << " 不合法" << endl;
            return false;
        }
        p->prev->next = p->next;    // ① 前驱结点的后继指向 p 的后继
        if (p->next != nullptr)     // ② p 若有后继，其后继的前驱指回 p 的前驱
            p->next->prev = p->prev;
        x = p->data;
        delete p;                   // ③ 释放结点，避免内存泄漏
        length--;
        return true;
    }

    // 修改位序 i 的结点数据
    bool Modify(int i, DataType x) {
        DNode<DataType>* p = GetNode(i);
        if (p == nullptr) {
            cout << "修改失败：位置 " << i << " 不合法" << endl;
            return false;
        }
        p->data = x;
        return true;
    }

    void TraverseForward() const {
        cout << "正向遍历：";
        for (DNode<DataType>* p = head->next; p != nullptr; p = p->next) cout << p->data << " ";
        cout << "  (length=" << length << ")" << endl;
    }

    void TraverseBackward() const {
        if (head->next == nullptr) { cout << "链表为空！" << endl; return; }
        DNode<DataType>* p = head->next;
        while (p->next != nullptr) p = p->next;
        cout << "逆向遍历：";
        for (; p != head; p = p->prev) cout << p->data << " ";
        cout << endl;
    }

private:
    DNode<DataType>* head;
    int length;
};

int main() {
    DoubleLinkList<int> L;
    int a[6] = {10, 20, 30, 40, 50, 60};
    for (int i = 0; i < 6; i++) L.PushBack(a[i]);
    cout << "== 初始链表（尾插 10 20 30 40 50 60） ==" << endl;
    L.TraverseForward();

    cout << "\n== 按值查找 40 ==" << endl;
    int pos = L.Locate(40);
    if (pos) cout << "40 在位序 " << pos << endl;
    else cout << "未找到 40" << endl;

    cout << "\n== 按位置查找位序 2（返回结点地址） ==" << endl;
    DNode<int>* p = L.GetNode(2);
    if (p) cout << "位序 2 结点地址: " << p << "，数据: " << p->data << endl;

    cout << "\n== 删除位序 3 和位序 1 ==" << endl;
    int x = 0;
    if (L.Delete(3, x)) cout << "被删元素: " << x << endl;
    if (L.Delete(1, x)) cout << "被删元素: " << x << endl;
    L.TraverseForward();
    L.TraverseBackward();

    cout << "\n== 修改位序 1 为 5、位序 4 为 45，遍历验证 ==" << endl;
    L.Modify(1, 5);
    L.Modify(4, 45);
    L.TraverseForward();

    return 0;
}
