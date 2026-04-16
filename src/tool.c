#include "my_head.h"

void print_introduction()
{
    for (int i = 0; i < 10; i++)
        printf("=");
    printf("程序介绍和说明");
    for (int i = 0; i < 10; i++)
        printf("=");
    printf("\n\n");

    printf("  开发者信息：\n");
    printf("    - 开发维护：[GB]80zero\n");
    printf("    - B站介绍视频：https://www.bilibili.com/video/BV1tsxfzhECY\n");
    printf("    - GitHub源码：https://github.com/rainbowsern/osu-mania-skin.ini-editor\n\n");

    printf("  重要提示：\n");
    printf("    1. 请确保程序与 skin.ini 文件在同一目录下运行，否则程序无法正常工作\n");
    printf("    2. 本程序假定你的 skin.ini 无语法错误，仅修改现有设置（不创建新设置条目）\n");
    printf("    3. 若出现意外情况，请优先检查 skin.ini 的语法完整性\n");
    printf("    4. 在未进行备份且已进行修改或者正在修改中，最好不要强制退出程序，否则可能导致skin.ini内容异常或缺失\n\n");
}

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

void split_screen()
{
    printf("\n");

    for (int i = 0; i < 10; i++)
        printf("=");
    printf("分割线");
    for (int i = 0; i < 10; i++)
        printf("=");

    printf("\n");
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

        // 存在边界，并且找到边界才退出
        if (borderLen != 0) {
            if (restLen >= borderLen && ((strncmp(&sourceStr[position], border, borderLen)) == 0))
                return -1;
        }

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

    return choice;
}

int read_number(char* buffer, int position)
{
    while (buffer[position] < '0' || buffer[position] > '9') {
        if (buffer[position] == '\n')
            return INT_MAX;
        position++;
    }

    int number = 0;

    while (buffer[position] >= '0' && buffer[position] <= '9')
        number = number * 10 + (buffer[position++] - '0');

    return number;
}

void win_error_pause()
{
#ifdef _WIN32
    system("pause");
#endif
}

// 初始化Windows控制台外观
void init_console_style()
{
#ifdef _WIN32
    // 设置UTF-8
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    system("color 02");
#endif
}

void malloc_error()
{
    printf("错误：malloc失败\n");
    win_error_pause();
    exit(1);
}

char* replace_string(char* buffer, const char* newStr, int position)
{
    // 计算新旧字符串长度
    int oldStrLen = position;
    while (buffer[oldStrLen] != '\n' && buffer[oldStrLen] != '\0')
        oldStrLen++;
    oldStrLen -= position;

    int newStrLen = strlen(newStr);

    // 创建新缓冲区，开始写入和修改
    char* newBuffer = (char*)malloc(strlen(buffer) - (oldStrLen - newStrLen) + 1);
    if (newBuffer == NULL)
        malloc_error();

    // 复制替换前部分
    strncpy(newBuffer, buffer, position);

    // 替换部分
    strcpy(newBuffer + position, newStr);

    // 剩余部分
    strcpy(newBuffer + position + newStrLen, buffer + position + oldStrLen);

    // 写入
    FILE* output = fopen("skin.ini", "w");
    if (output == NULL) {
        printf("错误：新建或覆盖skin.ini失败\n");
        free(newBuffer);
        return NULL;
    }

    free(buffer);
    fputs(newBuffer, output);
    fclose(output);

    return newBuffer;
}
