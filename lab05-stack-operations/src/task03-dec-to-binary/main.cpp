// 任务3：栈经典算法综合应用——十进制转二进制（拓展）
// 基于顺序栈：除2取余、余数入栈、逆序出栈输出，0 作特殊情况直接输出

#include <iostream>
#include <string>
using namespace std;

const int MaxSize = 100;

// 顺序栈（本任务只用初始化/入栈/出栈/判空）
template <typename DataType>
class SqStackClass {
public:
    SqStackClass() : top(-1) {}

    bool Empty() const { return top == -1; }

    bool Push(DataType x) {
        if (top == MaxSize - 1) return false;   // 上溢：非负 int 的二进制位数远小于 100
        data[++top] = x;
        return true;
    }

    bool Pop(DataType& x) {
        if (Empty()) return false;
        x = data[top--];
        return true;
    }

private:
    DataType data[MaxSize];
    int top;
};

// 十进制转二进制：除2取余、余数入栈、逆序出栈
void DecToBin(int n) {
    if (n == 0) {                        // 特殊情况：0 直接输出 0
        cout << "特殊情况：0 的二进制直接为 0" << endl;
        cout << "结果：0 的二进制 = 0" << endl;
        return;
    }

    SqStackClass<int> S;
    int m = n, bits = 0;

    cout << "转换过程（除2取余，余数依次入栈）：" << endl;
    while (m > 0) {
        int r = m % 2;                   // 取余数：先得到的是低位
        S.Push(r);                       // 余数入栈
        bits++;
        cout << "  " << m << " / 2 = " << m / 2 << " 余 " << r << "，余数 " << r << " 入栈" << endl;
        m /= 2;                          // 商继续除2
    }
    cout << "商为 0，转换结束，共得到 " << bits << " 位二进制数" << endl;

    string bin;
    int x = 0;
    while (S.Pop(x)) bin += char('0' + x);   // 出栈：高位先出，天然逆序

    cout << "依次出栈（逆序输出）：" << bin << endl;
    cout << "结果：" << n << " 的二进制 = " << bin << endl;
}

int main() {
    cout << "== 十进制整数转二进制（栈：除2取余 + 逆序出栈） ==" << endl;

    cout << "\n-- 示例1：156 --" << endl;
    DecToBin(156);

    cout << "\n-- 示例2：0（特殊情况） --" << endl;
    DecToBin(0);

    cout << "\n算法分析：" << endl;
    cout << "时间复杂度 O(log n)：循环 k = log2(n) + 1 次，每次 O(1)。" << endl;
    cout << "空间复杂度 O(log n)：栈中最多保存 k 个余数。" << endl;
    cout << "栈的价值：先得到的余数是低位、后得到的是高位，" << endl;
    cout << "入栈后逆序出栈使高位先输出，天然适合逆序处理类问题。" << endl;

    return 0;
}
