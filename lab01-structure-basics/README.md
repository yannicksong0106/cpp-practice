# Lab 01 — 数据结构基础

课程：数据结构与算法（18BJ004）

## 用 Visual Studio 打开（推荐）

双击打开：

```
lab01-structure-basics.sln
```

需要 **Visual Studio 2022**，并勾选工作负载 **「使用 C++ 的桌面开发」**。

- 配置选 `Release | x64`（或 `Debug | x64`）
- `生成 → 生成解决方案`（Ctrl+Shift+B）
- 在解决方案资源管理器中右键某个任务 → **设为启动项目** → F5 运行

输出目录：各项目下的 `x64\Release\` 或 `x64\Debug\`。

## 任务一览

| 项目 | 说明 |
|------|------|
| `task01-student-info` | 结构体 / 类，数据元素与数据项 |
| `task02-sequential-storage` | 普通数组顺序存储 5 个整数 |
| `task03-sum-complexity` | 1~n 累加（迭代 vs 公式）与复杂度 |
| `task04-fraction-simplify` | 真分数化简 |
| `task05-min-max` | 数组最大值、最小值 |

## 文档

- `docs/lab-manual.docx` — 实验手册
- `docs/lab-report.docx` — 实验报告（待填写）

## 命令行编译（可选）

```powershell
msbuild lab01-structure-basics.sln /p:Configuration=Release /p:Platform=x64
```

也保留了 `CMakeLists.txt`，可用 CMake 生成其他工程：

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
```
