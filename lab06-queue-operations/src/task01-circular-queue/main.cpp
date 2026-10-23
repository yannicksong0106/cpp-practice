// 任务1：循环顺序队列基础操作（基础必做）
// 静态数组模拟循环队列，牺牲一个单元区分空与满；入队/出队/取队头/判空/判满 + 上溢、下溢判定

#include <iostream>
using namespace std;

const int MaxSize = 100;

// 循环顺序队列类：静态数组模拟环形存储空间，front 指向队头，rear 指向队尾的下一个位置
template <typename DataType>
class SqQueueClass {
public:
    SqQueueClass() : front(0), rear(0) {}                // 初始化：front=rear=0 为空队列

    bool Empty() const { return front == rear; }                     // 判空
    bool Full() const { return (rear + 1) % MaxSize == front; }      // 判满：牺牲一个单元

    // 入队：队尾写入后 rear 取模后移实现循环；队满报上溢
    bool EnQueue(DataType x) {
        if (Full()) {
            cout << "上溢：队列已满，元素 " << x << " 入队失败！" << endl;
            return false;
        }
        data[rear] = x;
        rear = (rear + 1) % MaxSize;
        return true;
    }

    // 出队：取出 front 位置元素，front 取模后移；队列空报下溢
    bool DeQueue(DataType& x) {
        if (Empty()) {
            cout << "下溢：队列为空，出队失败！" << endl;
            return false;
        }
        x = data[front];
        front = (front + 1) % MaxSize;
        return true;
    }

    // 取队头：只读取队头元素，不修改指针
    bool GetFront(DataType& x) const {
        if (Empty()) {
            cout << "下溢：队列为空，取队头失败！" << endl;
            return false;
        }
        x = data[front];
        return true;
    }

    // 输出队列元素（队头→队尾），便于观察 FIFO 特性
    void PrintQueue() const {
        cout << "当前队列（队头→队尾）：";
        if (Empty()) {
            cout << "（空队列）" << endl;
            return;
        }
        for (int i = front; i != rear; i = (i + 1) % MaxSize) {
            cout << data[i];
            if ((i + 1) % MaxSize != rear) cout << " ";
        }
        cout << "   (front=" << front << ", rear=" << rear << ")" << endl;
    }

private:
    DataType data[MaxSize];   // 静态数组：固定容量环形存储空间
    int front;                // 队头下标：指向队首元素
    int rear;                 // 队尾下标：指向队尾元素的下一个位置
};

int main() {
    SqQueueClass<int> Q;

    // 1. 初始化 + 判空
    cout << "== 初始化：空循环队列创建完成 ==" << endl;
    cout << "队列是否为空：" << (Q.Empty() ? "是" : "否") << endl;
    Q.PrintQueue();

    // 2. 批量入队，依次输出入队元素
    cout << "\n== 批量入队：10 20 30 40 50 ==" << endl;
    int a[5] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        Q.EnQueue(a[i]);
        cout << "元素 " << a[i] << " 入队成功" << endl;
    }
    Q.PrintQueue();

    // 3. 取队头：只读，不改变队列
    cout << "\n== 取队头（只读，不改变队列） ==" << endl;
    int x = 0;
    if (Q.GetFront(x)) cout << "当前队头元素：" << x << endl;

    // 4. 出队：先进先出
    cout << "\n== 出队操作（先进先出） ==" << endl;
    if (Q.DeQueue(x)) cout << "出队元素：" << x << endl;
    if (Q.DeQueue(x)) cout << "出队元素：" << x << endl;
    Q.PrintQueue();

    // 5. 继续入队，rear 取模后移实现循环
    cout << "\n== 继续入队：60 70（rear 取模循环） ==" << endl;
    Q.EnQueue(60);
    Q.EnQueue(70);
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

    // 7. 下溢判定：空队列出队 / 取队头
    cout << "\n== 下溢判定：空队列继续出队 ==" << endl;
    Q.DeQueue(x);
    cout << "== 下溢判定：空队列取队头 ==" << endl;
    Q.GetFront(x);

    // 8. 上溢判定：静默填满 MaxSize-1 个元素后再入队
    cout << "\n== 上溢判定：连续入队直至队满（MaxSize=" << MaxSize << "，牺牲一个单元） ==" << endl;
    int n = 0;
    while (!Q.Full()) Q.EnQueue(n++ * 2);
    cout << "已入队 " << n << " 个元素，队列是否已满：" << (Q.Full() ? "是" : "否") << endl;
    Q.EnQueue(9999);   // 再次入队触发上溢

    cout << "\n时间复杂度：入队、出队、取队头、判空、判满均为 O(1)；打印遍历为 O(n)。" << endl;
    return 0;
}
