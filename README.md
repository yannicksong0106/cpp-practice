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
| [lab02-sequential-list](lab02-sequential-list/) | 顺序表操作：初始化、插删查、菜单综合 |

## 构建

### Visual Studio 2022（推荐）

打开对应实验目录下的 `.sln`，例如：

```
lab01-structure-basics/lab01-structure-basics.sln
lab02-sequential-list/lab02-sequential-list.sln
```

需要 VS2022 +「使用 C++ 的桌面开发」工作负载。

### 命令行

```powershell
cd lab02-sequential-list
msbuild lab02-sequential-list.sln /p:Configuration=Release /p:Platform=x64
```

也保留 CMake，可用 CMake 生成其他工程。
