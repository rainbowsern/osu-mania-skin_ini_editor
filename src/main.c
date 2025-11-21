#include "my_head.h"

int main()
{
    init_console_style();
    print_introduction();

    int choice;

    printf("1. 继续\n");
    printf("2. 退出\n");

    choice = make_choice(1, 2);
    if (choice == 2)
        return 0;

    split_screen();

    // 读取整个文件到缓冲区
    char* buffer = file_reader();

    if (buffer == NULL) {
        printf("错误：读取文件时发生错误，程序即将退出\n");
        win_error_pause();
        return 1;
    }
    printf("读取文件成功\n");

    // 创建备份
    printf("是否创建原skin.ini备份？（强烈建议创建）\n");
    printf("1. 创建\n");
    printf("2. 不创建\n");

    choice = make_choice(1, 2);
    if (choice == 1)
        create_backup();

    // 选择功能并调用
    while (1) {

        // 选择键数
        int position;
        int key = read_key();

        // 查找此键数设置位置
        char targetStr[20];
        sprintf(targetStr, "\nKeys: %d", key);

        position = search_string(targetStr, buffer, 0, "\0");

        // 如果没有设置
        if (position == -1) {
            printf("你的skin.ini没有这部分设置，重选其他键数\n");
            continue;
        }

        split_screen();

        // 主要功能
        while (1) {
            printf("读取到的键数：%d\n", key);
            printf("选择功能\n");
            printf("1. 修改轨道起始位置或居中轨道\n");
            printf("2. 修改轨道宽度\n");
            printf("3. 显示或关闭小节线\n");
            printf("4. 修改打击和轨道光位置\n");
            printf("5. 修改判定图片和连击数字显示位置\n");
            printf("6. 返回重选键数\n");
            printf("7. 退出程序\n");

            choice = make_choice(1, 7);
            split_screen();
            if (choice == 6)
                break;
            if (choice == 7)
                exit(0);

            // 调用功能
            switch (choice) {
            case 1:
                buffer = edit_column_start(buffer, key, position);
                break;
            case 2:
                buffer = edit_column_width(buffer, key, position);
                break;
            case 3:
                buffer = disable_barline(buffer, key, position);
                break;
            case 4:
                buffer = edit_hitposition_and_lightposition(buffer, key, position);
                break;
            case 5:
                buffer = edit_score_and_combo_position(buffer, key, position);
                break;
            default:
                printf("错误：无法到达的位置\n");
            }

            split_screen();
        }
    }
    return 0;
}
