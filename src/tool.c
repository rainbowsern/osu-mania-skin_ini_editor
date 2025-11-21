#include "../include/tool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int read_key()
{
    int key = 0;

    while (1) {

        printf("输入要修改的键数（1～18）：");

        scanf("%d", &key);
        clearInputBuffer();

        if (key < 1 || key > 18)
            printf("无效的键数\n");
        else
            break;
    }
    return key;
}

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// 在范围内查找子串
int search_string(const char* targetStr, char* sourceStr, int startPosition, const char* border)
{
    size_t sourceLen = strlen(sourceStr);
    size_t targetLen = strlen(targetStr);
    size_t restLen = sourceLen - startPosition - 1;
    size_t borderLen = strlen(border);

    int position = startPosition;

    while (restLen >= targetLen) {
        if (strncmp(&sourceStr[position], targetStr, targetLen) == 0)
            return position;

        else if (borderLen != 0 && restLen >= borderLen && ((strncmp(&sourceStr[position], border, borderLen)) == 0))
            return -1;
        restLen--;
        position++;
    }

    return -1;
}

int make_choice(int left, int right)
{
    int choice;

    while (1) {

        printf("输入数字：");

        scanf("%d", &choice);
        clearInputBuffer();

        if (choice < left || choice > right)
            printf("无效输入\n");
        else
            break;
    }

    printf("\n");
    return choice;
}

int read_number(char* buffer, int position)
{
    while (buffer[position] < '0' || buffer[position] > '9')
        position++;

    int number = 0;

    while (buffer[position] >= '0' && buffer[position] <= '9')
        number = number * 10 + (buffer[position++] - '0');

    return number;
}

char* replace_number(char* buffer, int newNumber, int position)
{
    // 计算新旧数值长度
    int oldNumberLen = 0;
    for (int i = position; buffer[i] >= '0' && buffer[i] <= '9'; i++)
        oldNumberLen++;

    int newNumberLen = snprintf(NULL, 0, "%d", newNumber);

    // 创建新缓冲区，开始写入和修改
    char* newBuffer = (char*)malloc(strlen(buffer) - (oldNumberLen - newNumberLen) + 1);
    if (newBuffer == NULL) {
        printf("内存分配失败，将终止程序\n");
        exit(1);
    }

    int i = 0;
    int j = 0;
    while (i != position)
        newBuffer[i++] = buffer[j++];

    // 替换部分
    j += oldNumberLen;

    char newNumberStr[newNumberLen + 1];
    sprintf(newNumberStr, "%d", newNumber);
    newNumberStr[newNumberLen] = '\0';

    for (int m = 0; m < newNumberLen; m++)
        newBuffer[i++] = newNumberStr[m];

    // 剩余部分
    while (buffer[j] != '\0')
        newBuffer[i++] = buffer[j++];
    newBuffer[i] = '\0';
    free(buffer);

    // 写入
    FILE* output = fopen("skin.ini", "w");
    fputs(newBuffer, output);
    fclose(output);

    return newBuffer;
}

// 用于windows的报错暂停
void winpause()
{
#ifdef _WIN32
    system("pause");
#endif
}
