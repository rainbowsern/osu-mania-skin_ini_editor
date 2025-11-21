#include "my_head.h"

char* file_reader()
{
    // 打开文件
    FILE* input = fopen("skin.ini", "rb");

    if (input == NULL) {
        printf("错误：fopen错误，请检查程序与文件是否在同一目录下\n");
        return NULL;
    }

    // 获取文件大小以读取整个文件
    fseek(input, 0, SEEK_END);
    int fileSize = 0;
    fileSize = ftell(input);
    if (fileSize <= 0) {
        fclose(input);
        printf("错误：ftell失败\n");
        return NULL;
    }
    fseek(input, 0, SEEK_SET);

    // 读取
    char* buffer = (char*)malloc(fileSize + 1);
    if (buffer == NULL)
        malloc_error();

    size_t bufferSize = fread(buffer, 1, fileSize, input);

    if (bufferSize != (size_t)fileSize) {
        printf("错误：fread时出错\n");
        fclose(input);
        free(buffer);
        return NULL;
    }

    buffer[fileSize] = '\0';

    size_t sizeWithoutR = 0;
    for (int i = 0; i < fileSize; i++)
        if (buffer[i] != '\r')
            sizeWithoutR++;

    char* finalBuffer = (char*)malloc(sizeWithoutR + 1);
    if (finalBuffer == NULL)
        malloc_error();

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
    // 生成当前时间字符串
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
