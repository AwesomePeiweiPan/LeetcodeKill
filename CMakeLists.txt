# 最低要求的CMake版本
cmake_minimum_required(VERSION 3.10)

# 工程名称和版本
project(mainProj VERSION 1.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置编译选项，启用调试信息
set(CMAKE_CXX_FLAGS_DEBUG "-g")

# 添加可执行文件
add_executable(mainExe main.cpp)
