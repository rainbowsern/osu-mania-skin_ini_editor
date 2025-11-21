#!/bin/bash

# 创建必要目录
mkdir -p bin obj

# 正常版本

echo "构建正常版本"

gcc -c src/main.c -o obj/main.o
gcc -c src/buffer.c -o obj/buffer.o
gcc -c src/editor.c -o obj/editor.o
gcc -c src/tool.c -o obj/tool.o

gcc obj/main.o obj/buffer.o obj/editor.o obj/tool.o -o bin/skin_ini_editor

echo "构建完成：bin/skin_ini_editor"

#win版本

if command -v x86_64-w64-mingw32-gcc >/dev/null 2>&1; then

    echo "构建windows版本"

    x86_64-w64-mingw32-gcc -c src/main.c -o obj/main.o
    x86_64-w64-mingw32-gcc -c src/buffer.c -o obj/buffer.o
    x86_64-w64-mingw32-gcc -c src/editor.c -o obj/editor.o
    x86_64-w64-mingw32-gcc -c src/tool.c -o obj/tool.o

    x86_64-w64-mingw32-gcc obj/main.o obj/buffer.o obj/editor.o obj/tool.o -o bin/skin_ini_editor.exe

    echo "构建完成：bin/skin_ini_editor.exe"

else
    echo "错误：未找到mingw交叉编译器，跳过windows构建"
    echo "在Ubuntu/Debian上可以运行：sudo apt install mingw-w64来安装"
fi

echo "构建完成"
