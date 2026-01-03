#ifndef FINANCE_H
#define FINANCE_H

#include "common.h"

// 财务管理函数声明

// 记录财务收支
int finance_add_record(const char* description, double amount, int type,
                      const char* category, const char* operator_name);

// 查看财务记录
FinanceRecord* finance_get_records(int* count);
FinanceRecord* finance_get_by_type(int type, int* count);
FinanceRecord* finance_get_by_category(const char* category, int* count);

// 生成财务报表
void finance_generate_report();
void finance_display_balance();

// 删除财务记录
int finance_delete_record(int record_id);

// 修改财务记录
int finance_update_record(int record_id, const char* description,
                         double amount, const char* category);

// 导出财务数据
int finance_export_report(const char* filename);

// 财务数据文件操作
int finance_save_to_file();
int finance_load_from_file();

#endif // FINANCE_H
