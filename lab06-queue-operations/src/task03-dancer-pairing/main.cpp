// 任务3：队列经典算法综合应用——舞伴配对问题（拓展必做）
// 男、女两个链队列分别按到场顺序入队；两队非空时队头同时出队配对；某队空则停止并输出剩余人员

#include <iostream>
using namespace std;

// 链队列结点：数据域 + 指针域
struct LinkQNode {
    int data;
    LinkQNode* next;
};

// 带头结点链队列（front 指向头结点，rear 指向队尾结点）
class LinkQueueClass {
public:
    LinkQueueClass() {
        front = rear = new LinkQNode{0, nullptr};
    }
    ~LinkQueueClass() { Destroy(); }

    bool Empty() const { return front == rear; }

    // 入队：队尾插入新结点
    void EnQueue(int x) {
        LinkQNode* s = new LinkQNode{x, nullptr};
        rear->next = s;
        rear = s;
    }

    // 出队：删除队首结点并释放；队列变空时重置尾指针
    bool DeQueue(int& x) {
        if (Empty()) return false;
        LinkQNode* p = front->next;
        x = p->data;
        front->next = p->next;
        if (rear == p) rear = front;
        delete p;
        return true;
    }

    // 销毁：释放全部结点
    void Destroy() {
        while (front != nullptr) {
            LinkQNode* p = front;
            front = front->next;
            delete p;
        }
        rear = nullptr;
    }

private:
    LinkQNode* front;
    LinkQNode* rear;
};

int main() {
    LinkQueueClass menQueue;     // 男生队列
    LinkQueueClass womenQueue;   // 女生队列

    // 1. 模拟到场：男、女生按顺序分别入队（男生 5 人，女生 4 人）
    cout << "== 舞会开始，人员按到场顺序入队 ==" << endl;
    cout << "男生入场：";
    for (int i = 1; i <= 5; i++) {
        menQueue.EnQueue(i);
        cout << i << " 号 ";
    }
    cout << endl;
    cout << "女生入场：";
    for (int i = 1; i <= 4; i++) {
        womenQueue.EnQueue(i);
        cout << i << " 号 ";
    }
    cout << endl;

    // 2. 配对：只要两队都不为空，同时取出两队队头组成舞伴
    cout << "\n== 开始配对（两队队头依次出队） ==" << endl;
    int m = 0, w = 0, pairs = 0;
    while (!menQueue.Empty() && !womenQueue.Empty()) {
        menQueue.DeQueue(m);
        womenQueue.DeQueue(w);
        pairs++;
        cout << "第 " << pairs << " 对：男生 " << m << " 号 —— 女生 " << w << " 号" << endl;
    }

    // 3. 终止条件触发：某一队为空，输出另一队剩余未配对人员
    cout << "\n== 配对结束：共配对 " << pairs << " 对 ==" << endl;
    if (!menQueue.Empty()) {
        cout << "男生队列剩余（按排队顺序）：";
        while (!menQueue.Empty()) {
            menQueue.DeQueue(m);
            cout << m << " 号 ";
        }
        cout << "等待下一轮" << endl;
    }
    if (!womenQueue.Empty()) {
        cout << "女生队列剩余（按排队顺序）：";
        while (!womenQueue.Empty()) {
            womenQueue.DeQueue(w);
            cout << w << " 号 ";
        }
        cout << "等待下一轮" << endl;
    }

    cout << "\n算法流程：入队 O(1)、配对 O(1)，整体时间复杂度 O(n+m)（n、m 为男女总人数）。" << endl;
    cout << "空间复杂度 O(n+m)：两个链队列各存一份到场人员结点，无固定容量上限。" << endl;
    cout << "应用价值：队列保证先来先配对，天然契合排队、叫号、任务调度等场景。" << endl;
    return 0;
}
