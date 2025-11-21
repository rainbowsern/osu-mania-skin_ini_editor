#ifndef MY_HEAD_H
#define MY_HEAD_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#endif

// ------ editor.c功能实现函数声明 ------

char *edit_column_start(char *buffer, int key, int position);
char *edit_column_width(char *buffer, int key, int position);
char *disable_barline(char *buffer, int key, int position);
char *edit_hitposition_and_lightposition(char *buffer, int key, int position);
char *edit_score_and_combo_position(char *buffer, int key, int position);

// ------ buffer.c:缓冲区操作函数声明 ------

char *file_reader();
void create_backup();

// ------ tool.c:工具函数声明 ------

void print_introduction();
void clearInputBuffer();
int read_key();
void split_screen();
int search_string(const char *targetStr, char *sourceStr, int startPosition,
                  const char *border); // 在范围内查找子串
int make_choice(int left, int right);
int read_number(char *buffer, int position);
void win_error_pause();
void init_console_style(); // 初始化Windows控制台外观
void malloc_error();
char *replace_string(char *buffer, const char *newStr, int position);

#endif
