// 任务1：单链表基础操作实现（基础必做）
// 带表头结点的单链表：尾插法批量录入 VR 物体 ID，纯指针只读遍历

#include <iostream>
using namespace std;

// 结点类：数据域 + 指针域
template <typename DataType>
struct Node {
    DataType data;    // 数据域：物体 ID
    Node* next;       // 指针域：指向后继结点

    Node() : data(DataType()), next(nullptr) {}
    explicit Node(DataType v) : data(v), next(nullptr) {}
};

// 单链表类：带表头结点，表头仅作占位标识，不存有效数据
template <typename DataType>
class LinkList {
public:
    LinkList() : length(0) { head = new Node<DataType>(); }   // 初始化：建立空链表

    ~LinkList() {                                             // 逐结点释放，不留野指针
        Node<DataType>* p = head;
        while (p != nullptr) {
            Node<DataType>* q = p->next;
            delete p;
            p = q;
        }
    }

    // 尾插法入库：纯指针从表头走到表尾，把新结点挂到尾部
    void PushBack(DataType x) {
        Node<DataType>* p = head;
        while (p->next != nullptr) p = p->next;
        p->next = new Node<DataType>(x);
        length++;
    }

    bool Empty() const { return head->next == nullptr; }

    // 只读遍历：从第一个有效结点走到表尾，不修改链表结构与数据
    void Traverse() const {
        if (Empty()) {
            cout << "当前为空场景，暂无任何物体资源！" << endl;
            return;
        }
        cout << "场景物体ID清单（共 " << length << " 个，数据状态：已入库）：" << endl;
        int idx = 0;
        for (Node<DataType>* p = head->next; p != nullptr; p = p->next) {
            cout << "  [" << ++idx << "] ID: " << p->data << "  <已入库>" << endl;
        }
    }

private:
    Node<DataType>* head;   // 表头指针
    int length;             // 有效元素个数
};

int main() {
    // 1. 初始化：建立带表头的空链表，先验证空场景判断
    LinkList<int> scene;
    cout << "== 场景初始化：带表头空链表创建完成 ==" << endl;
    scene.Traverse();

    // 2. 尾插法模拟 VR 引擎资源依次入库（不借助数组中转）
    cout << "\n== VR物体资源依次入库：1001 1002 1003 1004 1005 ==" << endl;
    scene.PushBack(1001);   // 地面
    scene.PushBack(1002);   // 墙体
    scene.PushBack(1003);   // 静态摆件A
    scene.PushBack(1004);   // 静态摆件B
    scene.PushBack(1005);   // 氛围光源

    // 3. 只读遍历，输出场景资源清单核对
    cout << "\n== 场景资源清单核查 ==" << endl;
    scene.Traverse();

    return 0;
}
