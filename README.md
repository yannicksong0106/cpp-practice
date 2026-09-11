# Data Structures Labs

数据结构与算法课程实验工程仓库。

## 目录约定

```
labNN-<topic>/     # 按实验编号 + 主题命名（kebab-case）
  docs/            # 实验报告、实验手册
  src/taskNN-*/    # 每个任务一个可执行目标
  CMakeLists.txt   # 该实验的构建脚本
  README.md
```

命名规范：

- 英文 kebab-case
- 实验编号两位：`lab01`、`lab02`…
- 任务编号两位：`task01`、`task02`…

## 实验列表

| 目录 | 主题 |
|------|------|
| [lab01-structure-basics](lab01-structure-basics/) | 数据结构基础：概念、顺序存储、复杂度 |

## 构建（单个实验）

```powershell
cd lab01-structure-basics
cmake -B build
cmake --build build
.\build\Debug\task01-student-info.exe   # Windows (MSVC)
# 或 .\build\task01-student-info.exe     # MinGW / Ninja
```

需要 CMake ≥ 3.16 与支持 C++17 的编译器。
