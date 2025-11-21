@echo off
mkdir bin 2>nul
mkdir obj 2>nul

echo Building osu!mania skin.ini editor...

gcc -c src/main.c -o obj/main.o
gcc -c src/buffer.c -o obj/buffer.o
gcc -c src/editor.c -o obj/editor.o
gcc -c src/tool.c -o obj/tool.o

gcc obj/main.o obj/buffer.o obj/editor.o obj/tool.o -o bin/skin_ini_editor.exe

echo Build completed: bin/skin_ini_editor.exe
pause
