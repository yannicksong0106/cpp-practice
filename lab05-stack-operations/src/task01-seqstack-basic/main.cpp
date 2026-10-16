// 任务1：顺序栈初始化与基础操作（基础必做）
// 静态数组模拟顺序栈，top=-1 为空栈；入栈/出栈/取栈顶/判空 + 上溢、下溢判定

#include <iostream>
using namespace std;

const int MaxSize = 100;

// 顺序栈类：静态数组模拟连续存储空间，top 标记栈顶下标
template <typename DataType>
class SqStackClass {
public:
    SqStackClass() : top(-1) {}                          // 初始化：top=-1 为空栈

    bool Empty() const { return top == -1; }             // 判空
    bool Full() const { return top == MaxSize - 1; }     // 判满

    // 入栈：栈未满时 top 上移一位存入元素；栈满报上溢
    bool Push(DataType x) {
        if (Full()) {
            cout << "上溢：栈已满，元素 " << x << " 入栈失败！" << endl;
            return false;
        }
        data[++top] = x;
        return true;
    }

    // 出栈：栈非空时取出栈顶元素并 top 下移一位；栈空报下溢
    bool Pop(DataType& x) {
        if (Empty()) {
            cout << "下溢：栈为空，出栈失败！" << endl;
            return false;
        }
        x = data[top--];
        return true;
    }

    // 取栈顶：只读取 top 位置元素，不修改 top
    bool GetTop(DataType& x) const {
        if (Empty()) {
            cout << "下溢：栈为空，取栈顶失败！" << endl;
            return false;
        }
        x = data[top];
        return true;
    }

    // 输出栈内元素（栈底→栈顶），便于观察 LIFO 特性
    void PrintStack() const {
        cout << "当前栈（栈底→栈顶）：";
        if (Empty()) {
            cout << "（空栈）" << endl;
            return;
        }
        for (int i = 0; i <= top; i++) {
            cout << data[i];
            if (i < top) cout << " ";
        }
        cout << "   (top=" << top << ")" << endl;
    }

private:
    DataType data[MaxSize];   // 静态数组：固定容量连续存储空间
    int top;                  // 栈顶下标，-1 表示空栈
};

int main() {
    SqStackClass<int> S;

    // 1. 初始化 + 判空
    cout << "== 初始化：空顺序栈创建完成 ==" << endl;
    cout << "栈是否为空：" << (S.Empty() ? "是" : "否") << endl;
    S.PrintStack();

    // 2. 批量入栈，依次输出入栈元素
    cout << "\n== 批量入栈：10 20 30 40 50 ==" << endl;
    int a[5] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        S.Push(a[i]);
        cout << "元素 " << a[i] << " 入栈成功" << endl;
    }
    S.PrintStack();

    // 3. 出栈：后进先出
    cout << "\n== 出栈操作（后进先出） ==" << endl;
    int x = 0;
    if (S.Pop(x)) cout << "出栈元素：" << x << endl;
    if (S.Pop(x)) cout << "出栈元素：" << x << endl;
    S.PrintStack();

    // 4. 取栈顶：只读，不改变栈
    cout << "\n== 取栈顶（只读，不改变栈） ==" << endl;
    if (S.GetTop(x)) cout << "当前栈顶元素：" << x << endl;

    // 5. 连续出栈直到空栈，观察完整 LIFO 顺序
    cout << "\n== 连续出栈至空栈 ==" << endl;
    cout << "出栈顺序：";
    while (!S.Empty()) {
        S.Pop(x);
        cout << x << " ";
    }
    cout << endl;
    cout << "栈是否为空：" << (S.Empty() ? "是" : "否") << endl;

    // 6. 下溢判定：空栈出栈 / 取栈顶
    cout << "\n== 下溢判定：空栈继续出栈 ==" << endl;
    S.Pop(x);
    cout << "== 下溢判定：空栈取栈顶 ==" << endl;
    S.GetTop(x);

    // 7. 上溢判定：静默压满 MaxSize 个元素后再入栈
    cout << "\n== 上溢判定：连续入栈直至栈满（MaxSize=" << MaxSize << "） ==" << endl;
    for (int i = 0; i < MaxSize; i++) S.Push(i * 2);
    cout << "已压入 " << MaxSize << " 个元素，栈是否已满：" << (S.Full() ? "是" : "否") << endl;
    S.Push(9999);   // 再次入栈触发上溢

    cout << "\n时间复杂度：入栈、出栈、取栈顶、判空只操作栈顶，均为 O(1)。" << endl;
    return 0;
}
