#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include "common.h"

// 文件操作函数声明

// 用户数据文件操作
int file_save_users(const User* users, int count);
int file_load_users(User* users, int max_count);

// 活动数据文件操作
int file_save_activities(const Activity* activities, int count);
int file_load_activities(Activity* activities, int max_count);

// 财务数据文件操作
int file_save_finance_records(const FinanceRecord* records, int count);
int file_load_finance_records(FinanceRecord* records, int max_count);

// 报名记录文件操作
int file_save_signups(const int signups[][2], int count);
int file_load_signups(int signups[][2], int max_count);

// 数据导出功能
int file_export_user_report(const char* filename);
int file_export_activity_report(const char* filename);
int file_export_finance_report(const char* filename);

// 文件存在性检查
int file_exists(const char* filename);

// 创建目录（如果需要）
int create_directory(const char* path);

// 备份数据
int backup_all_data();

#endif // FILE_UTILS_H
