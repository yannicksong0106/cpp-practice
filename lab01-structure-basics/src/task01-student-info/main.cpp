// 任务1：识别数据结构基本概念
// 结构体与面向对象两版 Student；区分数据 / 数据元素 / 数据项

#include <iostream>
#include <string>

// —— 结构体版（存储层面）——
struct StudentStruct {
    std::string id;    // 数据项：学号
    std::string name;  // 数据项：姓名
    int age;           // 数据项：年龄
};

// —— 面向对象版：属性私有化，成员函数输出 ——
class Student {
public:
    Student(std::string id, std::string name, int age)
        : id_(std::move(id)), name_(std::move(name)), age_(age) {}

    void print() const {
        std::cout << "学号: " << id_
                  << ", 姓名: " << name_
                  << ", 年龄: " << age_ << '\n';
    }

    const std::string& id() const { return id_; }
    const std::string& name() const { return name_; }
    int age() const { return age_; }

private:
    std::string id_;
    std::string name_;
    int age_;
};

int main() {
    // 自定义数据元素并测试
    StudentStruct s1{"20250101", "张三", 18};
    StudentStruct s2{"20250102", "李四", 19};

    std::cout << "== 结构体版 ==\n";
    std::cout << "学号: " << s1.id << ", 姓名: " << s1.name
              << ", 年龄: " << s1.age << '\n';
    std::cout << "学号: " << s2.id << ", 姓名: " << s2.name
              << ", 年龄: " << s2.age << '\n';

    std::cout << "\n== 类封装版 ==\n";
    Student c1("20250101", "张三", 18);
    Student c2("20250102", "李四", 19);
    c1.print();
    c2.print();

    return 0;
}
