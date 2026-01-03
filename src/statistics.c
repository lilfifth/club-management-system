#include "statistics.h"
#include "user.h"
#include "activity.h"
#include "finance.h"

// 获取系统统计信息
Statistics get_system_statistics() {
    Statistics stats = {0};

    // 用户统计
    int user_count_temp;
    User* users_temp = user_get_all(&user_count_temp);
    for (int i = 0; i < user_count_temp; i++) {
        if (users_temp[i].is_active) {
            stats.total_users++;
            if (users_temp[i].role == ROLE_MEMBER) {
                stats.active_users++;
            }
        }
    }

    // 活动统计
    int activity_count_temp;
    Activity* activities_temp = activity_get_all(&activity_count_temp);
    for (int i = 0; i < activity_count_temp; i++) {
        if (activities_temp[i].is_active) {
            stats.total_activities++;
            if (activities_temp[i].status == ACTIVITY_ACTIVE ||
                activities_temp[i].status == ACTIVITY_PENDING) {
                stats.active_activities++;
            }
        }
    }

    // 财务统计
    int finance_count_temp;
    FinanceRecord* finance_temp = finance_get_records(&finance_count_temp);
    for (int i = 0; i < finance_count_temp; i++) {
        if (finance_temp[i].is_active) {
            if (finance_temp[i].type == FINANCE_INCOME) {
                stats.total_income += finance_temp[i].amount;
            } else {
                stats.total_expense += finance_temp[i].amount;
            }
        }
    }

    stats.balance = stats.total_income - stats.total_expense;

    return stats;
}

// 显示用户统计
void display_user_statistics() {
    Statistics stats = get_system_statistics();

    printf("\n========== 用户统计 ==========\n");
    printf("总用户数: %d\n", stats.total_users);
    printf("活跃成员数: %d\n", stats.active_users);
    printf("管理员数: %d\n", stats.total_users - stats.active_users);

    // 用户注册时间分布（简化版）
    printf("\n用户注册统计:\n");
    // 这里可以添加更详细的注册时间分析

    printf("==============================\n");
}

// 显示活动统计
void display_activity_statistics() {
    Statistics stats = get_system_statistics();
    int pending_count = 0, active_count = 0, completed_count = 0, cancelled_count = 0;

    printf("\n========== 活动统计 ==========\n");
    printf("总活动数: %d\n", stats.total_activities);
    printf("活跃活动数: %d\n", stats.active_activities);

    // 活动状态统计
    int activity_count_temp;
    Activity* activities_temp = activity_get_all(&activity_count_temp);
    for (int i = 0; i < activity_count_temp; i++) {
        if (activities_temp[i].is_active) {
            switch (activities_temp[i].status) {
                case ACTIVITY_PENDING: pending_count++; break;
                case ACTIVITY_ACTIVE: active_count++; break;
                case ACTIVITY_COMPLETED: completed_count++; break;
                case ACTIVITY_CANCELLED: cancelled_count++; break;
            }
        }
    }

    printf("待开始活动: %d\n", pending_count);
    printf("进行中活动: %d\n", active_count);
    printf("已完成活动: %d\n", completed_count);
    printf("已取消活动: %d\n", cancelled_count);

    // 报名统计
    int total_signups = 0;
    for (int i = 0; i < activity_count_temp; i++) {
        if (activities_temp[i].is_active) {
            total_signups += activities_temp[i].current_participants;
        }
    }
    printf("总报名人数: %d\n", total_signups);

    printf("==============================\n");
}

// 显示财务统计
void display_finance_statistics() {
    Statistics stats = get_system_statistics();

    printf("\n========== 财务统计 ==========\n");
    printf("总收入: %.2f\n", stats.total_income);
    printf("总支出: %.2f\n", stats.total_expense);
    printf("当前结余: %.2f\n", stats.balance);

    // 财务分类统计
    printf("\n财务分类统计:\n");
    // 这里可以添加按分类的统计

    printf("==============================\n");
}

// 显示完整统计报告
void display_full_statistics_report() {
    printf("\n===================================\n");
    printf("      智能社团管理系统统计报告\n");
    printf("===================================\n");
    printf("生成时间: %s\n", format_time(time(NULL)));

    display_user_statistics();
    display_activity_statistics();
    display_finance_statistics();

    printf("\n===================================\n");
}

// 导出统计报告
int export_statistics_report(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("错误：无法创建统计报告文件\n");
        return 0;
    }

    Statistics stats = get_system_statistics();

    fprintf(file, "智能社团管理系统统计报告\n");
    fprintf(file, "生成时间: %s\n\n", format_time(time(NULL)));

    fprintf(file, "=== 用户统计 ===\n");
    fprintf(file, "总用户数: %d\n", stats.total_users);
    fprintf(file, "活跃成员数: %d\n", stats.active_users);
    fprintf(file, "管理员数: %d\n\n", stats.total_users - stats.active_users);

    fprintf(file, "=== 活动统计 ===\n");
    fprintf(file, "总活动数: %d\n", stats.total_activities);
    fprintf(file, "活跃活动数: %d\n\n", stats.active_activities);

    fprintf(file, "=== 财务统计 ===\n");
    fprintf(file, "总收入: %.2f\n", stats.total_income);
    fprintf(file, "总支出: %.2f\n", stats.total_expense);
    fprintf(file, "当前结余: %.2f\n\n", stats.balance);

    fclose(file);
    printf("统计报告已导出到: %s\n", filename);
    return 1;
}

// 用户参与度分析
void analyze_user_participation() {
    printf("\n========== 用户参与度分析 ==========\n");

    int user_count_temp;
    User* users_temp = user_get_all(&user_count_temp);

    // 统计每个用户的活动参与情况
    for (int i = 0; i < user_count_temp; i++) {
        if (users_temp[i].is_active && users_temp[i].role == ROLE_MEMBER) {
            int participation_count = 0;

            // 统计该用户参与的活动数量
            int activity_count_temp;
            Activity* activities_temp = activity_get_all(&activity_count_temp);

            for (int j = 0; j < activity_count_temp; j++) {
                if (activities_temp[j].is_active) {
                    int* participants;
                    int participant_count;
                    participants = activity_get_participants(activities_temp[j].id, &participant_count);

                    for (int k = 0; k < participant_count; k++) {
                        if (participants[k] == users_temp[i].id) {
                            participation_count++;
                            break;
                        }
                    }
                }
            }

            printf("用户 %s (%s): 参与 %d 个活动\n",
                   users_temp[i].name, users_temp[i].username, participation_count);
        }
    }

    printf("=====================================\n");
}

// 活动热度分析
void analyze_activity_popularity() {
    printf("\n========== 活动热度分析 ==========\n");

    // 按参与人数排序显示活动
    printf("%-30s %-15s %-10s\n", "活动名称", "组织者", "参与人数");
    printf("--------------------------------------------------\n");

    int activity_count_temp;
    Activity* activities_temp = activity_get_all(&activity_count_temp);

    // 创建副本用于排序（不修改原数组）
    Activity sorted_activities[MAX_ACTIVITIES];
    int sorted_count = 0;

    for (int i = 0; i < activity_count_temp; i++) {
        if (activities_temp[i].is_active) {
            sorted_activities[sorted_count++] = activities_temp[i];
        }
    }

    // 简单冒泡排序（实际项目中可以使用更高效的排序）
    for (int i = 0; i < sorted_count - 1; i++) {
        for (int j = 0; j < sorted_count - i - 1; j++) {
            if (sorted_activities[j].current_participants < sorted_activities[j + 1].current_participants) {
                Activity temp = sorted_activities[j];
                sorted_activities[j] = sorted_activities[j + 1];
                sorted_activities[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < sorted_count; i++) {
        printf("%-30s %-15s %-10d\n",
               sorted_activities[i].title,
               sorted_activities[i].organizer,
               sorted_activities[i].current_participants);
    }

    printf("==============================================\n");
}

// 财务趋势分析
void analyze_finance_trends() {
    printf("\n========== 财务趋势分析 ==========\n");

    int finance_count_temp;
    FinanceRecord* finance_temp = finance_get_records(&finance_count_temp);

    // 按时间排序的财务记录分析
    printf("最近10条财务记录:\n");
    printf("%-20s %-10s %-15s %-30s\n", "时间", "类型", "金额", "描述");
    printf("------------------------------------------------------------------\n");

    int display_count = 0;
    for (int i = finance_count_temp - 1; i >= 0 && display_count < 10; i--) {
        if (finance_temp[i].is_active) {
            const char* type_str = finance_temp[i].type == FINANCE_INCOME ? "收入" : "支出";
            printf("%-20s %-10s %-15.2f %-30s\n",
                   format_time(finance_temp[i].record_time),
                   type_str,
                   finance_temp[i].amount,
                   finance_temp[i].description);
            display_count++;
        }
    }

    printf("===================================\n");
}
