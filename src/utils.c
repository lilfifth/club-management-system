#include "common.h"
#include <string.h>
#include <ctype.h>

// 清除屏幕
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// 暂停系统等待用户输入
void pause_system() {
    printf("\n按任意键继续...");
    getchar();
}

// 打印分隔符
void print_separator() {
    printf("================================================================================\n");
}

// 格式化时间显示
char* format_time(time_t timestamp) {
    static char time_str[100];
    struct tm* tm_info = localtime(&timestamp);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);
    return time_str;
}

// 验证邮箱格式
int validate_email(const char* email) {
    if (!email || strlen(email) == 0) {
        return 0;
    }

    const char* at_pos = strchr(email, '@');
    const char* dot_pos = strrchr(email, '.');

    if (!at_pos || !dot_pos || at_pos == email || dot_pos < at_pos + 1) {
        return 0;
    }

    // 检查基本格式（简单验证）
    return strlen(email) <= MAX_NAME_LEN;
}

// 验证日期字符串并转换为时间戳
int validate_date(const char* date_str, time_t* timestamp) {
    if (!date_str || !timestamp) {
        return 0;
    }

    struct tm tm_time = {0};
    int year, month, day, hour = 0, min = 0, sec = 0;

    // 支持多种日期格式：YYYY-MM-DD 或 YYYY-MM-DD HH:MM:SS
    int result;
    if (strchr(date_str, ':')) {
        result = sscanf(date_str, "%d-%d-%d %d:%d:%d",
                       &year, &month, &day, &hour, &min, &sec);
        if (result != 6) return 0;
    } else {
        result = sscanf(date_str, "%d-%d-%d", &year, &month, &day);
        if (result != 3) return 0;
    }

    // 验证日期范围
    if (year < 2000 || year > 2100 || month < 1 || month > 12 ||
        day < 1 || day > 31 || hour < 0 || hour > 23 ||
        min < 0 || min > 59 || sec < 0 || sec > 59) {
        return 0;
    }

    tm_time.tm_year = year - 1900;
    tm_time.tm_mon = month - 1;
    tm_time.tm_mday = day;
    tm_time.tm_hour = hour;
    tm_time.tm_min = min;
    tm_time.tm_sec = sec;

    *timestamp = mktime(&tm_time);
    return *timestamp != -1;
}

// 去除字符串首尾空格
void trim_whitespace(char* str) {
    if (!str) return;

    // 去除前导空格
    char* start = str;
    while (*start && isspace(*start)) {
        start++;
    }

    // 去除尾随空格
    char* end = str + strlen(str) - 1;
    while (end > start && isspace(*end)) {
        *end-- = '\0';
    }

    // 移动字符串
    if (start != str) {
        memmove(str, start, strlen(start) + 1);
    }
}
