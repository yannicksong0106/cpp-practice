// 任务3：循环链表综合实操（拓展）
// 单向循环链表：尾结点后继指回表头形成闭环，遍历终止条件 p != head
// 双向循环链表：首尾双向互指闭环，支持双向遍历与定点增删

#include <iostream>
using namespace std;

// —— 单向循环链表（带表头，尾结点 next 指回 head） ——
class CircularLinkList {
public:
    CircularLinkList() : length(0) { head = new Node(); head->next = head; }   // 初始化：头自指成环

    ~CircularLinkList() {
        Node* p = head->next;
        while (p != head) {          // 终止条件：绕回表头即停，规避死循环
            Node* q = p->next;
            delete p;
            p = q;
        }
        delete head;
    }

    // 尾插：沿环走到尾（p->next == head），接上新结点后保持闭环
    void PushBack(int x) {
        Node* p = head;
        while (p->next != head) p = p->next;
        Node* s = new Node(x);
        p->next = s;
        s->next = head;              // 闭环修复：新尾的后继指回表头
        length++;
    }

    // 在位序 i 插入（1 ≤ i ≤ length+1）
    bool Insert(int i, int x) {
        if (i < 1 || i > length + 1) return false;
        Node* p = head;
        for (int k = 1; k < i; k++) p = p->next;   // p 停在第 i-1 个结点
        Node* s = new Node(x);
        s->next = p->next;
        p->next = s;
        length++;
        return true;
    }

    // 删除位序 i，闭环修复
    bool Delete(int i, int& x) {
        if (i < 1 || i > length) return false;
        Node* p = head;
        for (int k = 1; k < i; k++) p = p->next;
        Node* d = p->next;
        p->next = d->next;           // 摘下结点，环自动保持
        x = d->data;
        delete d;
        length--;
        return true;
    }

    // 遍历：从第一个有效结点出发，绕回表头即终止
    void Traverse() const {
        cout << "单向循环链表：";
        for (Node* p = head->next; p != head; p = p->next) cout << p->data << " ";
        cout << "  (尾结点next->" << (TailNextIsHead() ? "head，闭环正常" : "其他，闭环异常！") << ")" << endl;
    }

    bool TailNextIsHead() const {
        Node* p = head;
        while (p->next != head) p = p->next;
        return p->next == head;
    }

private:
    struct Node {
        int data;
        Node* next;
        Node(int v = 0) : data(v), next(nullptr) {}
    };
    Node* head;
    int length;
};

// —— 双向循环链表（带表头，首尾双向互指） ——
class DoubleCircularList {
public:
    DoubleCircularList() : length(0) {
        head = new DNode();
        head->next = head;           // 空表：头结点前后都指向自己
        head->prev = head;
    }

    ~DoubleCircularList() {
        DNode* p = head->next;
        while (p != head) {
            DNode* q = p->next;
            delete p;
            p = q;
        }
        delete head;
    }

    void PushBack(int x) {
        DNode* tail = head->prev;    // 表头前驱即尾结点
        DNode* s = new DNode(x);
        s->prev = tail;
        s->next = head;
        tail->next = s;
        head->prev = s;              // 双向闭环修复
        length++;
    }

    bool Insert(int i, int x) {
        if (i < 1 || i > length + 1) return false;
        DNode* p = head->next;
        for (int k = 1; k < i; k++) p = p->next;   // 第 i 个结点（可绕回 head）
        DNode* s = new DNode(x);
        s->prev = p->prev;
        s->next = p;
        p->prev->next = s;
        p->prev = s;
        length++;
        return true;
    }

    bool Delete(int i, int& x) {
        if (i < 1 || i > length) return false;
        DNode* p = head->next;
        for (int k = 1; k < i; k++) p = p->next;
        p->prev->next = p->next;
        p->next->prev = p->prev;
        x = p->data;
        delete p;
        length--;
        return true;
    }

    void TraverseForward() const {
        cout << "双向循环-正向：";
        for (DNode* p = head->next; p != head; p = p->next) cout << p->data << " ";
        cout << endl;
    }

    void TraverseBackward() const {
        cout << "双向循环-逆向：";
        for (DNode* p = head->prev; p != head; p = p->prev) cout << p->data << " ";
        cout << endl;
    }

    bool ClosureOK() const {
        DNode* tail = head->prev;
        return head->prev == tail && tail->next == head;
    }

private:
    struct DNode {
        int data;
        DNode* prev;
        DNode* next;
        DNode(int v = 0) : data(v), prev(nullptr), next(nullptr) {}
    };
    DNode* head;
    int length;
};

int main() {
    cout << "== 单向循环链表（内置 1 3 5 7 9） ==" << endl;
    CircularLinkList C;
    int a1[5] = {1, 3, 5, 7, 9};
    for (int i = 0; i < 5; i++) C.PushBack(a1[i]);
    C.Traverse();

    cout << "\n-- 在位序 2 插入 2，删除位序 5 --" << endl;
    C.Insert(2, 2);
    int x = 0;
    C.Delete(5, x);
    cout << "被删元素: " << x << endl;
    C.Traverse();

    cout << "\n== 双向循环链表（内置 1 3 5 7 9） ==" << endl;
    DoubleCircularList D;
    for (int i = 0; i < 5; i++) D.PushBack(a1[i]);
    D.TraverseForward();
    D.TraverseBackward();

    cout << "\n-- 在位序 1 插入 0，删除位序 3 --" << endl;
    D.Insert(1, 0);
    D.Delete(3, x);
    cout << "被删元素: " << x << endl;
    D.TraverseForward();
    D.TraverseBackward();

    cout << "\n== 闭环校验与对比 ==" << endl;
    cout << "双向循环链表首尾互指: " << (D.ClosureOK() ? "正常" : "异常！") << endl;
    cout << "对比：普通链表遍历以 nullptr 为界，循环链表以\"绕回表头\"为界；" << endl;
    cout << "循环链表可从任一结点出发访问全表，适合环形轮转调度场景，但增删时须修复闭环防死循环。" << endl;

    return 0;
}
