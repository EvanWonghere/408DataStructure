cmake_minimum_required(VERSION 4.0) # 推荐使用较新的CMake版本
project(408DataStructure CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # 推荐关闭编译器特定扩展，使用标准C++

# 通用编译选项 (根据需要调整)
if(MSVC)
    # MSVC 编译选项
    add_compile_options(/W4 /WX) # W4警告等级, /WX将警告视为错误
else()
    # GCC/Clang 编译选项
    add_compile_options(-Wall -Wextra -Wpedantic -Werror) # 开启常用警告并将警告视为错误
endif()

# 添加调试信息 (Debug模式下)
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type (Debug, Release, RelWithDebInfo, MinSizeRel)")
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    add_compile_options(-g)
endif()

# 提供选项来控制是否构建习题和示例
option(BUILD_EXERCISES "Build chapter exercises" ON)
option(BUILD_EXAMPLES "Build chapter examples" ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake") # 将 cmake 目录添加到模块路径
include(ChapterBuilder) # 包含定义的模块

# 添加 common 子目录，它会构建一个通用库
add_subdirectory(common)

# 添加 chapters 子目录，它将负责管理所有具体的章节
add_subdirectory(chapters)

# (可选) 如果你使用CTest进行测试
# enable_testing()