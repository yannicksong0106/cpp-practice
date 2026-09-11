cmake_minimum_required(VERSION 3.16)
project(lab01-structure-basics LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
  add_compile_options(/utf-8)
endif()

add_executable(task01-student-info
    src/task01-student-info/main.cpp
)

add_executable(task02-sequential-storage
    src/task02-sequential-storage/main.cpp
)

add_executable(task03-sum-complexity
    src/task03-sum-complexity/main.cpp
)

add_executable(task04-fraction-simplify
    src/task04-fraction-simplify/main.cpp
)

add_executable(task05-min-max
    src/task05-min-max/main.cpp
)
