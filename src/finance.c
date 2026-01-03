#include "finance.h"
#include "file_utils.h"

// 全局财务记录数组和计数器
static FinanceRecord finance_records[MAX_FINANCE_RECORDS];
static int finance_record_count = 0;
static int next_finance_id = 1;

// 添加财务记录
int finance_add_record(const char* description, double amount, int type,
                      const char* category, const char* operator_name) {
    // 输入验证
    if (!description || !category || !operator_name) {
        printf("错误：所有字段都必须填写\n");
        return 0;
    }

    if (strlen(description) == 0 || strlen(category) == 0 || strlen(operator_name) == 0) {
        printf("错误：字段不能为空\n");
        return 0;
    }

    if (amount <= 0) {
        printf("错误：金额必须大于0\n");
        return 0;
    }

    if (type != FINANCE_INCOME && type != FINANCE_EXPENSE) {
        printf("错误：无效的财务类型\n");
        return 0;
    }

    // 检查数组是否已满
    if (finance_record_count >= MAX_FINANCE_RECORDS) {
        printf("错误：财务记录数量已达上限\n");
        return 0;
    }

    // 创建新记录
    FinanceRecord new_record;
    new_record.id = next_finance_id++;
    strcpy(new_record.description, description);
    new_record.amount = amount;
    new_record.type = type;
    strcpy(new_record.category, category);
    strcpy(new_record.operator_name, operator_name);
    new_record.record_time = time(NULL);
    new_record.is_active = 1;

    finance_records[finance_record_count++] = new_record;

    // 保存到文件
    if (!finance_save_to_file()) {
        printf("警告：财务记录添加成功，但保存到文件失败\n");
    }

    printf("财务记录添加成功！\n");
    return new_record.id;
}

// 获取所有财务记录
FinanceRecord* finance_get_records(int* count) {
    *count = finance_record_count;
    return finance_records;
}

// 根据类型获取记录
FinanceRecord* finance_get_by_type(int type, int* count) {
    static FinanceRecord filtered_records[MAX_FINANCE_RECORDS];
    int filtered_count = 0;

    for (int i = 0; i < finance_record_count; i++) {
        if (finance_records[i].is_active && finance_records[i].type == type) {
            filtered_records[filtered_count++] = finance_records[i];
        }
    }

    *count = filtered_count;
    return filtered_records;
}

// 根据分类获取记录
FinanceRecord* finance_get_by_category(const char* category, int* count) {
    static FinanceRecord filtered_records[MAX_FINANCE_RECORDS];
    int filtered_count = 0;

    for (int i = 0; i < finance_record_count; i++) {
        if (finance_records[i].is_active &&
            strcmp(finance_records[i].category, category) == 0) {
            filtered_records[filtered_count++] = finance_records[i];
        }
    }

    *count = filtered_count;
    return filtered_records;
}

// 生成财务报表
void finance_generate_report() {
    double total_income = 0.0, total_expense = 0.0;
    int income_count = 0, expense_count = 0;

    printf("\n========== 财务报表 ==========\n");
    printf("%-5s %-30s %-10s %-15s %-20s %-15s %-20s\n",
           "ID", "描述", "金额", "类型", "分类", "操作员", "记录时间");
    printf("----------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < finance_record_count; i++) {
        if (finance_records[i].is_active) {
            const char* type_str = finance_records[i].type == FINANCE_INCOME ? "收入" : "支出";

            printf("%-5d %-30s %-10.2f %-15s %-20s %-15s %-20s\n",
                   finance_records[i].id,
                   finance_records[i].description,
                   finance_records[i].amount,
                   type_str,
                   finance_records[i].category,
                   finance_records[i].operator_name,
                   format_time(finance_records[i].record_time));

            if (finance_records[i].type == FINANCE_INCOME) {
                total_income += finance_records[i].amount;
                income_count++;
            } else {
                total_expense += finance_records[i].amount;
                expense_count++;
            }
        }
    }

    printf("----------------------------------------------------------------------------------------------------\n");
    printf("收入笔数: %d  总收入: %.2f\n", income_count, total_income);
    printf("支出笔数: %d  总支出: %.2f\n", expense_count, total_expense);
    printf("结余: %.2f\n", total_income - total_expense);
    printf("===============================\n");
}

// 显示余额
void finance_display_balance() {
    double total_income = 0.0, total_expense = 0.0;

    for (int i = 0; i < finance_record_count; i++) {
        if (finance_records[i].is_active) {
            if (finance_records[i].type == FINANCE_INCOME) {
                total_income += finance_records[i].amount;
            } else {
                total_expense += finance_records[i].amount;
            }
        }
    }

    printf("\n========== 财务余额 ==========\n");
    printf("总收入: %.2f\n", total_income);
    printf("总支出: %.2f\n", total_expense);
    printf("当前结余: %.2f\n", total_income - total_expense);
    printf("==============================\n");
}

// 删除财务记录
int finance_delete_record(int record_id) {
    for (int i = 0; i < finance_record_count; i++) {
        if (finance_records[i].id == record_id && finance_records[i].is_active) {
            finance_records[i].is_active = 0;

            // 保存到文件
            if (!finance_save_to_file()) {
                printf("警告：财务记录删除成功，但保存到文件失败\n");
            }

            printf("财务记录删除成功！\n");
            return 1;
        }
    }

    printf("错误：财务记录不存在\n");
    return 0;
}

// 修改财务记录
int finance_update_record(int record_id, const char* description,
                         double amount, const char* category) {
    for (int i = 0; i < finance_record_count; i++) {
        if (finance_records[i].id == record_id && finance_records[i].is_active) {
            if (description && strlen(description) > 0) {
                strcpy(finance_records[i].description, description);
            }
            if (amount > 0) {
                finance_records[i].amount = amount;
            }
            if (category && strlen(category) > 0) {
                strcpy(finance_records[i].category, category);
            }

            // 保存到文件
            if (!finance_save_to_file()) {
                printf("警告：财务记录修改成功，但保存到文件失败\n");
            }

            printf("财务记录修改成功！\n");
            return 1;
        }
    }

    printf("错误：财务记录不存在\n");
    return 0;
}

// 导出财务报告
int finance_export_report(const char* filename) {
    return file_export_finance_report(filename);
}

// 保存财务数据到文件
int finance_save_to_file() {
    return file_save_finance_records(finance_records, finance_record_count);
}

// 从文件加载财务数据
int finance_load_from_file() {
    finance_record_count = file_load_finance_records(finance_records, MAX_FINANCE_RECORDS);
    if (finance_record_count < 0) {
        finance_record_count = 0;
        return 0;
    }

    // 更新下一个财务记录ID
    for (int i = 0; i < finance_record_count; i++) {
        if (finance_records[i].id >= next_finance_id) {
            next_finance_id = finance_records[i].id + 1;
        }
    }

    return 1;
}
