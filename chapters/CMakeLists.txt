# chapters/CMakeLists.txt

# 使用 file(GLOB) 查找所有符合命名模式的章节子目录
# 例如，我们假设章节目录都以两位数字开头，后跟一个减号 (例如 "01-Introduction", "02-Arrays")
file(GLOB CHAPTER_FOLDERS LIST_DIRECTORIES true RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "[0-9]-*")
# LIST_DIRECTORIES true: 只获取目录
# RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}": 获取相对于当前目录的路径
# "[0-9][0-9]-*": 匹配模式，例如 "01-", "02-", 等开头的目录

# 对找到的每个潜在章节目录进行处理
foreach(CHAPTER_FOLDER ${CHAPTER_FOLDERS})
    # 确保它确实是一个目录并且包含它自己的 CMakeLists.txt 文件
    if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${CHAPTER_FOLDER}" AND
       EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${CHAPTER_FOLDER}/CMakeLists.txt")
        message(STATUS "Found and adding chapter: ${CHAPTER_FOLDER}")
        add_subdirectory(${CHAPTER_FOLDER})
    else()
        message(WARNING "Directory '${CHAPTER_FOLDER}' looks like a chapter but is missing a CMakeLists.txt or is not a directory.")
    endif()
endforeach()

# 如果没有找到任何章节目录，可以打印一条消息
if(NOT CHAPTER_FOLDERS)
    message(STATUS "No chapter subdirectories found matching the pattern in ${CMAKE_CURRENT_SOURCE_DIR}")
endif()