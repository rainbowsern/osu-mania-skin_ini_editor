#!/bin/bash
mkdir -p build
if cd build; then
	cmake -DCMAKE_BUILD_TYPE=Release ..
	cmake --build .
	echo "构建完成！可执行文件在 bin/skin_ini_editor"
else
	echo "cd 失败"
fi
