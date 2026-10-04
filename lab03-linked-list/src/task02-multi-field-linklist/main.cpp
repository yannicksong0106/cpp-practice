// 任务2：单链表基础操作实现（拓展：多字段数据元素）
// 双层封装：VRResource 资源类 + Node 结点类 + LinkList 管理类
// 带表头结点，尾插法批量入库，纯指针只读遍历，格式化输出全量属性

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// —— 数据元素类：封装一个 VR 场景物体的多字段属性 ——
class VRResource {
public:
    VRResource(int id = 0, string name = "", string type = "",
               double x = 0.0, double y = 0.0, double z = 0.0)
        : id_(id), name_(move(name)), type_(move(type)), x_(x), y_(y), z_(z) {}

    // 格式化输出本物体的全部字段（seq 为资源序号）
    void Print(int seq) const {
        cout << "  [" << seq << "] ID: " << id_
             << "  名称: " << left << setw(16) << name_
             << " 类型: " << setw(11) << type_
             << " 坐标: (" << fixed << setprecision(1) << x_ << ", " << y_ << ", " << z_ << ")"
             << "  <已入库>" << endl;
    }

private:
    int id_;            // 物体 ID
    string name_;       // 物体名称
    string type_;       // 资源类型
    double x_, y_, z_;  // 场景坐标
};

// —— 结点类：数据域（VRResource）+ 指针域 ——
struct Node {
    VRResource data;
    Node* next;
    explicit Node(const VRResource& r) : data(r), next(nullptr) {}
};

// —— 单链表管理类：带表头结点（仅占位，不存有效资源） ——
class LinkList {
public:
    LinkList() : length(0) { head = new Node(VRResource()); }   // 初始化空链表

    ~LinkList() {                                               // 逐结点释放，无断链、无野指针
        Node* p = head;
        while (p != nullptr) {
            Node* q = p->next;
            delete p;
            p = q;
        }
    }

    // 尾插法入库：纯指针走到表尾再挂载新结点
    void PushBack(const VRResource& r) {
        Node* p = head;
        while (p->next != nullptr) p = p->next;
        p->next = new Node(r);
        length++;
    }

    bool Empty() const { return head->next == nullptr; }

    // 只读遍历：从第一个有效数据结点走到表尾，不增删改任何结点
    void Traverse() const {
        if (Empty()) {
            cout << "当前为空场景，未录入任何资源！" << endl;
            return;
        }
        cout << "================ VR场景资源清单 ================" << endl;
        int idx = 0;
        for (Node* p = head->next; p != nullptr; p = p->next) {
            p->data.Print(++idx);
        }
        cout << "------------------------------------------------" << endl;
        cout << "共 " << length << " 项资源，状态：全部已入库" << endl;
    }

private:
    Node* head;   // 表头指针
    int length;   // 有效资源数
};

int main() {
    // 1. 初始化：建立带表头的空链表，验证空场景兼容提示
    LinkList scene;
    cout << "== 场景初始化：带表头空链表创建完成 ==" << endl;
    scene.Traverse();

    // 2. 尾插法批量录入多字段物体，模拟资源依次入库
    cout << "\n== VR物体资源依次入库（5 项） ==" << endl;
    scene.PushBack(VRResource(1001, "Ground",        "StaticMesh", 0.0, 0.0, 0.0));   // 地面
    scene.PushBack(VRResource(1002, "Wall_North",    "StaticMesh", 0.0, 3.0, -8.0));  // 墙体
    scene.PushBack(VRResource(1003, "Prop_Statue",   "StaticMesh", 4.5, 0.0, 2.0));   // 静态摆件
    scene.PushBack(VRResource(1004, "Light_Ambient01", "Light",    0.0, 6.0, 0.0));   // 氛围光源
    scene.PushBack(VRResource(1005, "Prop_Crate",    "StaticMesh", -3.0, 0.5, 1.5));  // 静态摆件

    // 3. 只读遍历，输出全量属性清单
    cout << "\n== 场景资源全量信息核查 ==" << endl;
    scene.Traverse();

    return 0;
}
