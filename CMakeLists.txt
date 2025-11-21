cmake_minimum_required(VERSION 3.10)
project(skin_ini_editor C)

# 根据平台设置不同的编译选项
if(WIN32)
    # Windows 设置
    set(EXECUTABLE_NAME skin_ini_editor.exe)
    # add_definitions(-DWIN32_LEAN_AND_MEAN)
else()
    # Linux 设置
    set(EXECUTABLE_NAME skin_ini_editor)
endif()

# 包含源文件目录
include_directories(src)

# 收集所有源文件
file(GLOB SOURCES "src/*.c")

# 创建可执行文件
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# 创建bin目录
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 设置输出目录
set_target_properties(
    ${EXECUTABLE_NAME}
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)
