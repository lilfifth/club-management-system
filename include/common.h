#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// 系统常量定义
#define MAX_NAME_LEN 50
#define MAX_DESC_LEN 200
#define MAX_USERS 1000
#define MAX_ACTIVITIES 500
#define MAX_FINANCE_RECORDS 2000
#define MAX_FILENAME_LEN 100

// 用户角色定义
#define ROLE_ADMIN 1
#define ROLE_MEMBER 0

// 活动状态定义
#define ACTIVITY_PENDING 0
#define ACTIVITY_ACTIVE 1
#define ACTIVITY_COMPLETED 2
#define ACTIVITY_CANCELLED 3

// 财务类型定义
#define FINANCE_INCOME 1
#define FINANCE_EXPENSE 0

// 文件名定义
#define USER_DATA_FILE "users.txt"
#define ACTIVITY_DATA_FILE "activities.txt"
#define FINANCE_DATA_FILE "finance.txt"

// 用户结构体
typedef struct {
    int id;
    char username[MAX_NAME_LEN];
    char password[MAX_NAME_LEN];
    char name[MAX_NAME_LEN];
    char email[MAX_NAME_LEN];
    int role; // 0:普通成员 1:管理员
    time_t register_time;
    int is_active; // 1:活跃 0:已删除
} User;

// 活动结构体
typedef struct {
    int id;
    char title[MAX_NAME_LEN];
    char description[MAX_DESC_LEN];
    char organizer[MAX_NAME_LEN];
    time_t create_time;
    time_t start_time;
    time_t end_time;
    char location[MAX_NAME_LEN];
    int max_participants;
    int current_participants;
    int status; // 0:待开始 1:进行中 2:已完成 3:已取消
    int is_active; // 1:活跃 0:已删除
} Activity;

// 财务记录结构体
typedef struct {
    int id;
    char description[MAX_DESC_LEN];
    double amount;
    int type; // 0:支出 1:收入
    char category[MAX_NAME_LEN];
    char operator_name[MAX_NAME_LEN];
    time_t record_time;
    int is_active; // 1:活跃 0:已删除
} FinanceRecord;

// 统计信息结构体
typedef struct {
    int total_users;
    int active_users;
    int total_activities;
    int active_activities;
    int total_income;
    int total_expense;
    double balance;
} Statistics;

// 全局变量声明
extern User current_user;

// 工具函数声明
void clear_screen();
void pause_system();
void print_separator();
char* format_time(time_t timestamp);
int validate_email(const char* email);
int validate_date(const char* date_str, time_t* timestamp);
void trim_whitespace(char* str);

// 错误处理
#define ERROR_INVALID_INPUT "输入无效，请重新输入"
#define ERROR_FILE_NOT_FOUND "文件不存在"
#define ERROR_PERMISSION_DENIED "权限不足"
#define ERROR_OPERATION_FAILED "操作失败"

#endif // COMMON_H
