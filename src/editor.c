#include "my_head.h"

// 修改轨道起始位置
char* edit_column_start(char* buffer, int key, int position)
{
    // 找stage开始位置
    int columnStartPosition;
    columnStartPosition = search_string("\nColumnStart:", buffer, position, "\n[");

    if (columnStartPosition == -1) {
        printf("警告：你的%d键部分没有轨道开始位置设置，将返回主界面\n", key);
        return buffer;
    }

    columnStartPosition += strlen("\nColumnStart:");

    int choice;

    // 输入分辨率
    printf("为了计算你的打图界面宽度，需要osu界面分辨率宽高比\n");
    int resolutionWidth, resolutionHeight;

    while (1) {
        printf("输入分辨率宽：");
        scanf("%d", &resolutionWidth);
        clearInputBuffer();

        printf("输入分辨率高：");
        scanf("%d", &resolutionHeight);
        clearInputBuffer();

        printf("输入的分辨率为%dx%d\n", resolutionWidth, resolutionHeight);
        printf("1. 确认\n");
        printf("2. 重输\n");

        choice = make_choice(1, 2);
        if (choice == 1)
            break;
    }
    split_screen();

    // 计算界面宽度
    int width = 480 * resolutionWidth / resolutionHeight;
    printf("你的界面宽度为：%d（丢弃小数）\n", width);

    // 获取stage宽度
    int stageWidth = 0;
    int columnWidthPosition = search_string("\nColumnWidth:", buffer, position, "\n[");

    if (columnWidthPosition == -1) // 无设置
        stageWidth = key * 30;
    else {

        columnWidthPosition += strlen("\nColumnWidth:"); // 挪动指针
        int tempNumber = read_number(buffer, columnWidthPosition); // 尝试读第一个数值

        if (tempNumber == INT_MAX) // 有设置但值为空
            stageWidth = key * 30;
        else { // 有设置

            while (buffer[columnWidthPosition] >= '0' && buffer[columnWidthPosition] <= '9') { // 挪动指针
                if (buffer[columnWidthPosition] == '\n') {
                    printf("错误：你的轨道宽度设置有语法错误，即将退回主界面\n");
                    return buffer;
                }
                columnWidthPosition++;
            }
            stageWidth += tempNumber;

            for (int i = 0; i < key - 1; i++) {
                tempNumber = read_number(buffer, columnWidthPosition);

                if (tempNumber == INT_MAX) {
                    printf("错误：你的轨道宽度设置有语法错误，即将退回主界面\n");
                    return buffer;
                }

                stageWidth += tempNumber;

                if (i != key - 1) {
                    while (buffer[columnWidthPosition] >= '0' && buffer[columnWidthPosition] <= '9') {
                        if (buffer[columnWidthPosition] == '\n') {
                            printf("错误：你的轨道宽度设置有语法错误，即将退回主界面\n");
                            return buffer;
                        }
                        columnWidthPosition++;
                    }
                }
            }
        }
    }

    printf("你的stage宽度为：%d（不包含分隔线宽）\n", stageWidth);

    // 功能部分
    while (1) {

        // 选择功能
        printf("1. 居中轨道\n");
        printf("2. 自定义轨道起始位置\n");
        printf("3. 返回主界面\n");

        choice = make_choice(1, 3);

        if (choice == 3)
            return buffer;

        // 居中轨道
        if (choice == 1) {

            // 计算居中位置
            int stageMidPosition = (width - stageWidth) / 2;
            printf("居中的开始位置为：%d\n", stageMidPosition);

            char stageMidPositionStr[20];
            sprintf(stageMidPositionStr, " %d", stageMidPosition);
            buffer = replace_string(buffer, stageMidPositionStr, columnStartPosition);
        } else {
            // 输入开始位置
            int inputPosition;
            printf("输入开始位置：");
            scanf("%d", &inputPosition);
            clearInputBuffer();

            char inputPositionStr[20];
            sprintf(inputPositionStr, " %d", inputPosition);
            buffer = replace_string(buffer, inputPositionStr, columnStartPosition);
        }

        split_screen();
        printf("修改成功，如果osu正在运行，按shift+alt+ctrl+s来重载皮肤，以使修改生效\n");
        printf("1. 继续修改轨道开始位置\n");
        printf("2. 退回功能选择\n");

        choice = make_choice(1, 2);

        if (choice == 1)
            continue;
        else
            return buffer;
    }
}

// 修改轨道宽
char* edit_column_width(char* buffer, int key, int position)
{
    int columnWidthPosition = search_string("\nColumnWidth:", buffer, position, "\n[");

    if (columnWidthPosition == -1) {
        printf("你的%d键部分没有轨道宽度设置，将返回主界面\n", key);
        return buffer;
    }
    columnWidthPosition += strlen("\nColumnWidth:");

    // 功能部分
    while (1) {
        printf("选择输入模式\n");
        printf("1. 所有轨道统一宽度\n");
        printf("2. 分别输入各轨道宽度\n");
        printf("3. 返回\n");

        int choice = make_choice(1, 3);

        if (choice == 3)
            return buffer;

        // 统一宽度
        if (choice == 1) {
            int columnWidth;

            printf("输入轨道宽度：");

            scanf("%d", &columnWidth);
            clearInputBuffer();

            // 替换部分
            char newStr[key * 12 + 1];
            int pos = 0;
            for (int i = 0; i < key; i++) {
                if (i == 0)
                    pos += snprintf(newStr + pos, sizeof(newStr) - pos, " %d,", columnWidth);
                else if (i == key - 1)
                    pos += snprintf(newStr + pos, sizeof(newStr) - pos, "%d", columnWidth);
                else
                    pos += snprintf(newStr + pos, sizeof(newStr) - pos, "%d,", columnWidth);
            }

            buffer = replace_string(buffer, newStr, columnWidthPosition);

        }
        // 分别输入
        else {
            int width[key];

            for (int i = 0; i < key; i++) {
                printf("输入轨道%d宽度：", i + 1);
                scanf("%d", &width[i]);
                clearInputBuffer();
            }

            // 替换部分
            char newStr[key * 12 + 1];
            int pos = 0;
            for (int i = 0; i < key; i++) {
                if (i == 0)
                    pos += snprintf(newStr + pos, sizeof(newStr) - pos, " %d,", width[i]);
                else if (i == key - 1)
                    pos += snprintf(newStr + pos, sizeof(newStr) - pos, "%d", width[i]);
                else
                    pos += snprintf(newStr + pos, sizeof(newStr) - pos, "%d,", width[i]);
            }
            buffer = replace_string(buffer, newStr, columnWidthPosition);
        }

        // 结尾
        split_screen();
        printf("修改成功，如果osu正在运行，按shift+alt+ctrl+s来重载皮肤，以使修改生效\n");
        printf("1. 继续修改轨道宽度\n");
        printf("2. 退回功能选择\n");

        choice = make_choice(1, 2);

        if (choice == 1)
            continue;
        else
            return buffer;
    }
}

// 开关小节线
char* disable_barline(char* buffer, int key, int position)
{
    int barlinePosition = search_string("\nBarlineHeight:", buffer, position, "\n[");

    if (barlinePosition == -1) {
        printf("你的%d键部分没有小节线设置，将返回主界面\n", key);
        return buffer;
    }

    barlinePosition += strlen("\nBarlineHeight:");

    while (1) {
        printf("1. 关闭小节线\n");
        printf("2. 启用小节线\n");

        int choice = make_choice(1, 2);

        if (choice == 1)
            buffer = replace_string(buffer, " 0", barlinePosition);
        else
            buffer = replace_string(buffer, " 1", barlinePosition);

        // 结尾
        split_screen();
        printf("修改成功，如果osu正在运行，按shift+alt+ctrl+s来重载皮肤，以使修改生效\n");
        printf("1. 继续修改\n");
        printf("2. 退回功能选择\n");

        choice = make_choice(1, 2);

        if (choice == 1)
            continue;
        else
            return buffer;
    }
}

// 修改打击位置和轨道光位置
char* edit_hitposition_and_lightposition(char* buffer, int key, int position)
{
    printf("提示：HitPosition是判定线位置以及打击特效图片显示的位置，LightPosition是轨道光显示的位置，如果你的皮肤轨道光被替换为透明图片，可忽视此设置\n");

    // 功能部分
    while (1) {
        printf("1. 修改HitPosition\n");
        printf("2. 修改LightPosition\n");

        int choice = make_choice(1, 2);

        // 功能1
        if (choice == 1) {

            int hitPosition = search_string("\nHitPosition:", buffer, position, "\n[");

            if (hitPosition == -1) {
                printf("你的%d键部分没有HitPosition设置，将返回上一个选择\n", key);
                continue;
            }

            hitPosition += strlen("\nHitPosition:");

            // 输入新数值
            int newHeight;
            printf("输入新的HitPosition（范围0～480，数值越大越接近屏幕底部）：");

            scanf("%d", &newHeight);
            clearInputBuffer();

            char newHeightStr[20];
            sprintf(newHeightStr, " %d", newHeight);
            buffer = replace_string(buffer, newHeightStr, hitPosition);

        }
        // 功能2
        else {
            int lightPosition = search_string("\nLightPosition:", buffer, position, "\n[");

            if (lightPosition == -1) {
                printf("你的%d键部分没有LightPosition设置，将返回上一个选择\n", key);
                continue;
            }

            lightPosition += strlen("\nLightPosition:");

            // 输入新数值
            int newHeight;
            printf("输入新的LightPosition（范围0～480，数值越大越接近屏幕底部）：");

            scanf("%d", &newHeight);
            clearInputBuffer();

            char newHeightStr[20];
            sprintf(newHeightStr, " %d", newHeight);
            buffer = replace_string(buffer, newHeightStr, lightPosition);
        }

        // 结尾
        split_screen();
        printf("修改成功，如果osu正在运行，按shift+alt+ctrl+s来重载皮肤，以使修改生效\n");
        printf("1. 继续修改\n");
        printf("2. 退回功能选择\n");

        choice = make_choice(1, 2);

        if (choice == 1)
            continue;
        else
            return buffer;
    }
}
char* edit_score_and_combo_position(char* buffer, int key, int position)
{
    // 功能部分
    while (1) {
        printf("1. 修改连击数字位置\n");
        printf("2. 修改判定图片位置\n");

        int choice = make_choice(1, 2);

        // 功能1
        if (choice == 1) {

            int comboPosition = search_string("\nComboPosition:", buffer, position, "\n[");

            if (comboPosition == -1) {
                printf("你的%d键部分没有ComboPosition设置，将返回上一个选择\n", key);
                continue;
            }

            comboPosition += strlen("\nComboPosition:");

            // 输入新数值
            int newHeight;
            printf("输入新的ComboPosition（范围0～480，数值越大越接近屏幕底部）：");

            scanf("%d", &newHeight);
            clearInputBuffer();

            char newHeightStr[20];
            sprintf(newHeightStr, " %d", newHeight);
            buffer = replace_string(buffer, newHeightStr, comboPosition);

        }
        // 功能2
        else {
            int scorePosition = search_string("\nScorePosition:", buffer, position, "\n[");

            if (scorePosition == -1) {
                printf("你的%d键部分没有ScorePosition设置，将返回上一个选择\n", key);
                continue;
            }

            scorePosition += strlen("\nScorePosition:");

            // 输入新数值
            int newHeight;
            printf("输入新的ScorePosition（范围0～480，数值越大越接近屏幕底部）：");

            scanf("%d", &newHeight);
            clearInputBuffer();

            char newHeightStr[20];
            sprintf(newHeightStr, " %d", newHeight);
            buffer = replace_string(buffer, newHeightStr, scorePosition);
        }

        // 结尾
        split_screen();
        printf("修改成功，如果osu正在运行，按shift+alt+ctrl+s来重载皮肤，以使修改生效\n");
        printf("1. 继续修改\n");
        printf("2. 退回功能选择\n");

        choice = make_choice(1, 2);

        if (choice == 1)
            continue;
        else
            return buffer;
    }
}
