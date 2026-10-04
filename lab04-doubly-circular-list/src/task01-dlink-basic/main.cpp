// 任务1：双向链表初始化、插入与遍历（基础必做）
// 结点含前驱 prev、后继 next 双指针；尾插 + 按位序插入；正向/逆向遍历

#include <iostream>
using namespace std;

// 双向链表结点：数据域 + 前驱指针 + 后继指针
template <typename DataType>
struct DNode {
    DataType data;
    DNode* prev;    // 前驱指针
    DNode* next;    // 后继指针

    DNode() : prev(nullptr), next(nullptr) {}
    explicit DNode(DataType v) : data(v), prev(nullptr), next(nullptr) {}
};

// 带表头结点的双向链表：表头仅占位，不存有效数据
template <typename DataType>
class DoubleLinkList {
public:
    DoubleLinkList() : length(0) { head = new DNode<DataType>(); }   // 初始化空链表

    ~DoubleLinkList() {                                              // 逐结点释放
        DNode<DataType>* p = head;
        while (p != nullptr) {
            DNode<DataType>* q = p->next;
            delete p;
            p = q;
        }
    }

    // 尾部插入：纯指针走到表尾，同时修改尾结点后继与新结点前驱
    void PushBack(DataType x) {
        DNode<DataType>* p = head;
        while (p->next != nullptr) p = p->next;
        DNode<DataType>* s = new DNode<DataType>(x);
        p->next = s;
        s->prev = p;
        length++;
    }

    // 在位序 i 插入（1 ≤ i ≤ length+1）：先定位第 i 个结点 p，再改双指针
    bool Insert(int i, DataType x) {
        if (i < 1 || i > length + 1) {
            cout << "插入失败：位置 " << i << " 不合法" << endl;
            return false;
        }
        DNode<DataType>* p = head->next;
        for (int k = 1; k < i && p != nullptr; k++) p = p->next;   // p 指向第 i 个结点（i=length+1 时 p 为空）
        DNode<DataType>* s = new DNode<DataType>(x);
        s->prev = p->prev;          // ① 新结点前驱指向原第 i 个结点的前驱
        s->next = p;                // ② 新结点后继指向原第 i 个结点
        p->prev->next = s;          // ③ 前驱结点的后继改指新结点
        p->prev = s;                // ④ 原结点的前驱改指新结点
        length++;
        return true;
    }

    bool Empty() const { return head->next == nullptr; }

    // 正向遍历：从第一个有效结点沿 next 走到表尾（只读）
    void TraverseForward() const {
        if (Empty()) { cout << "链表为空！" << endl; return; }
        cout << "正向遍历：";
        for (DNode<DataType>* p = head->next; p != nullptr; p = p->next) cout << p->data << " ";
        cout << endl;
    }

    // 逆向遍历：先走到表尾，再沿 prev 逐个回走（只读）
    void TraverseBackward() const {
        if (Empty()) { cout << "链表为空！" << endl; return; }
        DNode<DataType>* p = head->next;
        while (p->next != nullptr) p = p->next;
        cout << "逆向遍历：";
        for (; p != head; p = p->prev) cout << p->data << " ";
        cout << endl;
    }

private:
    DNode<DataType>* head;   // 表头指针
    int length;              // 有效元素个数
};

int main() {
    DoubleLinkList<int> L;
    cout << "== 初始化：带表头双向链表创建完成 ==" << endl;
    L.TraverseForward();

    cout << "\n== 尾部批量插入：10 20 30 40 50 ==" << endl;
    L.PushBack(10);
    L.PushBack(20);
    L.PushBack(30);
    L.PushBack(40);
    L.PushBack(50);
    L.TraverseForward();
    L.TraverseBackward();

    cout << "\n== 在位序 3 插入 25，在位序 1 插入 5 ==" << endl;
    L.Insert(3, 25);
    L.Insert(1, 5);
    L.TraverseForward();
    L.TraverseBackward();

    return 0;
}
