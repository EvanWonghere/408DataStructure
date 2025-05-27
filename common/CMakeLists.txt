# common/CMakeLists.txt

# 收集所有 common/src 下的源文件
file(GLOB COMMON_SOURCES src/*.cpp examples/*.cpp examples/utils/*.cpp) # 根据你的目录结构调整

# 添加一个静态库 ds_common
add_library(ds_common STATIC ${COMMON_SOURCES})

# 指定 ds_common 库的 publicly accessible include 目录
# PUBLIC意味着链接到 ds_common 的目标也会自动获得这个包含路径
target_include_directories(ds_common
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  # 构建时包含路径
        # $<INSTALL_INTERFACE:include> # 如果将来需要安装，这是安装时的包含路径
)

# 如果 common 库本身依赖其他库 (不太可能在这个项目中发生)
# target_link_libraries(ds_common PUBLIC other_dependency)