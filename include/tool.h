#ifndef TOOL_H
#define TOOL_H

void clearInputBuffer();
int read_key();
void clear_screen();

// 在范围内查找子串
int search_string(const char* targetStr, char* sourceStr, int startPosition, const char* border);

int make_choice(int left, int right);
int read_number(char* buffer, int position);
char* replace_number(char* buffer, int newNumber, int position);

// 用于windows的报错暂停
void winpause();

#endif
