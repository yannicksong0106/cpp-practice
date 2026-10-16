// 任务2：链栈基础操作实现（提高）
// 头插法入栈、摘链出栈并释放结点；栈顶指针 top 为空即空链栈

#include <iostream>
using namespace std;

// 链栈结点：数据域 + 指针域
template <typename DataType>
struct LinkNode {
    DataType data;      // 数据域
    LinkNode* next;     // 指针域：指向原栈顶结点

    LinkNode() : data(DataType()), next(nullptr) {}
    explicit LinkNode(DataType v) : data(v), next(nullptr) {}
};

// 链栈类：top 直指栈顶结点，动态申请/释放结点
template <typename DataType>
class LinkStackClass {
public:
    LinkStackClass() : top(nullptr) {}   // 初始化：top=nullptr 为空链栈

    ~LinkStackClass() {                  // 析构：逐个摘链释放所有结点
        while (top != nullptr) {
            LinkNode<DataType>* p = top;
            top = top->next;
            delete p;
        }
    }

    bool Empty() const { return top == nullptr; }   // 判空

    // 入栈：头插法，新结点插入到原栈顶之前，成为新栈顶
    void Push(DataType x) {
        LinkNode<DataType>* s = new LinkNode<DataType>(x);   // 动态申请结点
        s->next = top;
        top = s;
    }

    // 出栈：取出栈顶数据，top 移到下一结点，释放原栈顶结点
    bool Pop(DataType& x) {
        if (Empty()) {
            cout << "下溢：链栈为空，出栈失败！" << endl;
            return false;
        }
        LinkNode<DataType>* p = top;
        x = p->data;
        top = top->next;
        delete p;                    // 释放结点，避免内存泄漏
        return true;
    }

    // 取栈顶：只读取，不修改 top
    bool GetTop(DataType& x) const {
        if (Empty()) {
            cout << "下溢：链栈为空，取栈顶失败！" << endl;
            return false;
        }
        x = top->data;
        return true;
    }

    // 输出链栈（栈顶→栈底），观察头插后结点的链接顺序
    void PrintStack() const {
        cout << "当前链栈（栈顶→栈底）：";
        if (Empty()) {
            cout << "（空栈）" << endl;
            return;
        }
        for (LinkNode<DataType>* p = top; p != nullptr; p = p->next) cout << p->data << " ";
        cout << endl;
    }

private:
    LinkNode<DataType>* top;   // 栈顶指针
};

int main() {
    LinkStackClass<int> S;

    // 1. 初始化 + 判空
    cout << "== 初始化：空链栈创建完成（top = nullptr） ==" << endl;
    cout << "栈是否为空：" << (S.Empty() ? "是" : "否") << endl;

    // 2. 头插法批量入栈
    cout << "\n== 头插法入栈：1 2 3 4 5 ==" << endl;
    for (int i = 1; i <= 5; i++) {
        S.Push(i);
        cout << "元素 " << i << " 入栈成功（动态申请结点）" << endl;
    }
    S.PrintStack();

    // 3. 取栈顶：只读
    cout << "\n== 取栈顶（只读） ==" << endl;
    int x = 0;
    if (S.GetTop(x)) cout << "栈顶元素：" << x << endl;

    // 4. 出栈：摘链并释放结点
    cout << "\n== 出栈（摘链并释放结点） ==" << endl;
    if (S.Pop(x)) cout << "出栈元素：" << x << endl;
    if (S.Pop(x)) cout << "出栈元素：" << x << endl;
    S.PrintStack();

    // 5. 连续出栈直到空栈
    cout << "\n== 连续出栈至空栈 ==" << endl;
    cout << "出栈顺序：";
    while (!S.Empty()) {
        S.Pop(x);
        cout << x << " ";
    }
    cout << endl;
    cout << "栈是否为空：" << (S.Empty() ? "是" : "否") << endl;

    // 6. 下溢判定：空栈出栈
    cout << "\n== 下溢判定：空栈再次出栈 ==" << endl;
    S.Pop(x);

    // 7. 对比顺序栈与链栈
    cout << "\n== 对比：链栈与顺序栈 ==" << endl;
    cout << "顺序栈：静态数组，空间预先分配，有最大容量，存在栈满上溢。" << endl;
    cout << "链栈：动态申请结点，只受系统内存限制，不存在栈满问题；" << endl;
    cout << "      每入栈一个元素多存一个指针域，空间开销略大，但无需预先估计容量。" << endl;
    cout << "两者入栈/出栈/取栈顶/判空时间复杂度均为 O(1)。" << endl;

    return 0;
}
