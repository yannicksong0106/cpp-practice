// 任务2：链队列基础操作实现（提高必做）
// 带头结点链队列，front/rear 私有封装；入队尾插新结点、出队删除队首结点、取队头、判空

#include <iostream>
using namespace std;

// 链队列结点：数据域 + 指针域
struct LinkQNode {
    int data;
    LinkQNode* next;
};

// 链队列类：front 指向头结点，rear 指向队尾结点
class LinkQueueClass {
public:
    // 初始化：动态申请头结点，front 与 rear 同时指向它，代表空队列
    LinkQueueClass() {
        front = rear = new LinkQNode{0, nullptr};
    }
    ~LinkQueueClass() { Destroy(); }                     // 析构自动释放全部结点

    bool Empty() const { return front == rear; }         // 带头结点：front==rear 为空

    // 入队：队尾插入新结点并更新尾指针，链队列无容量上限
    void EnQueue(int x) {
        LinkQNode* s = new LinkQNode{x, nullptr};
        rear->next = s;
        rear = s;
    }

    // 出队：删除头结点后的队首结点并释放；队列变空时重置尾指针到头结点
    bool DeQueue(int& x) {
        if (Empty()) {
            cout << "下溢：队列为空，出队失败！" << endl;
            return false;
        }
        LinkQNode* p = front->next;      // 队首结点
        x = p->data;
        front->next = p->next;           // 摘链
        if (rear == p) rear = front;     // 出队后队列为空：rear 重置到头结点
        delete p;                        // 释放结点，避免内存泄漏
        return true;
    }

    // 取队头：只读取队首结点数据，不修改指针
    bool GetFront(int& x) const {
        if (Empty()) {
            cout << "下溢：队列为空，取队头失败！" << endl;
            return false;
        }
        x = front->next->data;
        return true;
    }

    // 输出队列元素（队头→队尾），便于观察 FIFO 特性
    void PrintQueue() const {
        cout << "当前链队列（队头→队尾）：";
        if (Empty()) {
            cout << "（空队列）" << endl;
            return;
        }
        for (LinkQNode* p = front->next; p != nullptr; p = p->next) {
            cout << p->data;
            if (p->next != nullptr) cout << " ";
        }
        cout << endl;
    }

    // 销毁：从头结点开始逐个释放所有结点
    void Destroy() {
        while (front != nullptr) {
            LinkQNode* p = front;
            front = front->next;
            delete p;
        }
        rear = nullptr;
    }

private:
    LinkQNode* front;   // 队头指针：指向头结点
    LinkQNode* rear;    // 队尾指针：指向队尾结点
};

int main() {
    LinkQueueClass Q;

    // 1. 初始化 + 判空
    cout << "== 初始化：带头结点空链队列创建完成 ==" << endl;
    cout << "队列是否为空：" << (Q.Empty() ? "是" : "否") << endl;
    Q.PrintQueue();

    // 2. 批量入队（尾插法），依次输出入队元素
    cout << "\n== 批量入队（尾插法）：1 2 3 4 5 ==" << endl;
    for (int i = 1; i <= 5; i++) {
        Q.EnQueue(i);
        cout << "元素 " << i << " 入队成功（动态申请结点）" << endl;
    }
    Q.PrintQueue();

    // 3. 取队头：只读，不改变队列
    cout << "\n== 取队头（只读） ==" << endl;
    int x = 0;
    if (Q.GetFront(x)) cout << "当前队头元素：" << x << endl;

    // 4. 出队：删除队首结点并释放，先进先出
    cout << "\n== 出队操作（删除队首结点并释放） ==" << endl;
    if (Q.DeQueue(x)) cout << "出队元素：" << x << endl;
    if (Q.DeQueue(x)) cout << "出队元素：" << x << endl;
    Q.PrintQueue();

    // 5. 继续入队：链队列无固定容量限制
    cout << "\n== 继续入队：6 7（无容量上限） ==" << endl;
    Q.EnQueue(6);
    Q.EnQueue(7);
    Q.PrintQueue();

    // 6. 连续出队直到空队列，观察完整 FIFO 顺序
    cout << "\n== 连续出队至空队列 ==" << endl;
    cout << "出队顺序：";
    while (!Q.Empty()) {
        Q.DeQueue(x);
        cout << x << " ";
    }
    cout << endl;
    cout << "队列是否为空：" << (Q.Empty() ? "是" : "否") << endl;

    // 7. 边界处理：出队变空后再次入队，验证尾指针已正确重置
    cout << "\n== 边界验证：空队列再次入队 ==" << endl;
    Q.EnQueue(8);
    cout << "元素 8 入队成功（rear 已重置，队列恢复正常）" << endl;
    if (Q.GetFront(x)) cout << "当前队头元素：" << x << endl;
    Q.DeQueue(x);

    // 8. 下溢判定：空队列出队
    cout << "\n== 下溢判定：空队列继续出队 ==" << endl;
    Q.DeQueue(x);

    cout << "\n对比：链队列无固定容量、不存在上溢；每个元素多存一个指针域。" << endl;
    cout << "时间复杂度：入队、出队、取队头、判空均 O(1)；遍历 O(n)。" << endl;
    return 0;
}
