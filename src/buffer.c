#include "../include/buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* file_reader()
{
    // 打开文件
    FILE* input = fopen("skin.ini", "rb");

    if (input == NULL)
        return NULL;

    // 获取文件大小以读取整个文件
    fseek(input, 0, SEEK_END);
    int fileSize = 0;
    fileSize = ftell(input);
    if (fileSize <= 0) {
        fclose(input);
        return NULL;
    }
    fseek(input, 0, SEEK_SET);

    // 读取
    char* buffer = (char*)malloc(fileSize + 1);

    size_t bufferSize = fread(buffer, 1, fileSize, input);

    if (bufferSize != (size_t)fileSize) {
        fclose(input);
        free(buffer);
        return NULL;
    }

    buffer[fileSize] = '\0';

    size_t sizeWithoutR;
    for (int i = 0; i < fileSize; i++)
        if (buffer[i] != '\r')
            sizeWithoutR++;

    char* finalBuffer = (char*)malloc(sizeWithoutR + 1);

    int j = 0;
    for (int i = 0; i < fileSize; i++)
        if (buffer[i] != '\r')
            finalBuffer[j++] = buffer[i];
    finalBuffer[sizeWithoutR] = '\0';

    free(buffer);
    fclose(input);
    return finalBuffer;
}

void create_backup()
{
    time_t now_time = time(NULL);
    struct tm date = *localtime(&now_time);
    char timeStr[32];
    char command[256];

    strftime(timeStr, sizeof(timeStr), "%Y_%m_%d_%H_%M_%S", &date);

#ifdef _WIN32
    sprintf(command, "copy skin.ini skin.ini_backup_%s", timeStr);
    system(command);
#else
    sprintf(command, "cp skin.ini skin.ini_backup_%s", timeStr);
    system(command);
#endif

    printf("备份已创建，文件名：skin.ini_backup_%s\n", timeStr);
}
