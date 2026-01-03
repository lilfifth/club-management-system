#include "common.h"
#include "user.h"
#include "activity.h"
#include "finance.h"
#include "statistics.h"
#include "file_utils.h"

// 函数声明
void display_main_menu();
void display_user_menu();
void display_activity_menu();
void display_finance_menu();
void display_admin_menu();
void handle_user_registration();
void handle_user_login();
void handle_user_management();
void handle_activity_management();
void handle_finance_management();
void handle_statistics_view();
void handle_admin_operations();
void handle_user_profile();
void handle_activity_operations();
void handle_finance_operations();

// 工具函数声明
void handle_user_operations(int choice);
void handle_data_export();

// 输入验证函数
int get_valid_choice(int min, int max);
double get_valid_amount();
void get_valid_string(char* buffer, int max_len, const char* prompt);
int get_valid_date_input(time_t* start_time, time_t* end_time);

// 全局变量
int is_logged_in = 0;

// 主函数
int main() {
    // 初始化系统
    printf("=======================================\n");
    printf("  智能社团活动与财务管理系统 v1.0\n");
    printf("=======================================\n");

    // 加载数据
    printf("正在加载系统数据...\n");
    user_load_from_file();
    activity_load_from_file();
    finance_load_from_file();

    printf("系统启动成功！\n\n");

    // 主循环
    while (1) {
        if (!is_logged_in) {
            display_main_menu();
        } else {
            if (current_user.role == ROLE_ADMIN) {
                display_admin_menu();
            } else {
                display_user_menu();
            }
        }

        int choice;
        if (!is_logged_in) {
            choice = get_valid_choice(0, 2);
            switch (choice) {
                case 1:
                    handle_user_registration();
                    break;
                case 2:
                    handle_user_login();
                    break;
                case 0:
                    printf("\n╔══════════════════════════════════════════════════════════════╗\n");
                    printf("║                      感谢使用本系统！                           ║\n");
                    printf("║                                                              ║\n");
                    printf("║                 智能社团活动与财务管理系统                    ║\n");
                    printf("╚══════════════════════════════════════════════════════════════╝\n");
                    return 0;
            }
        } else {
            if (current_user.role == ROLE_ADMIN) {
                choice = get_valid_choice(0, 6);
                handle_admin_operations(choice);
            } else {
                choice = get_valid_choice(0, 4);
                handle_user_operations(choice);
            }
        }

        pause_system();
        clear_screen();
    }

    return 0;
}

// 显示主菜单
void display_main_menu() {
    clear_screen();
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                 智能社团活动与财务管理系统                    ║\n");
    printf("║                                                              ║\n");
    printf("║                    欢迎使用本系统！                           ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║  1. 用户注册 - 创建新用户账户                               ║\n");
    printf("║  2. 用户登录 - 登录系统                                     ║\n");
    printf("║  0. 退出系统 - 安全退出程序                                 ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    printf("请选择操作 (0-2): ");
}

// 显示用户菜单
void display_user_menu() {
    clear_screen();
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                     用 户 菜 单                              ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║ 当前用户: %-25s 角色: %-12s ║\n",
           current_user.name,
           current_user.role == ROLE_ADMIN ? "管理员" : "普通成员");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║  1. 个人信息管理 - 查看和修改个人信息                       ║\n");
    printf("║  2. 活动管理     - 浏览和报名活动                           ║\n");
    printf("║  3. 财务信息查看 - 查看财务余额和报表                       ║\n");
    printf("║  4. 系统统计     - 查看系统统计信息                         ║\n");
    printf("║  0. 退出登录     - 返回主菜单                               ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    printf("请选择操作 (0-4): ");
}

// 显示管理员菜单
void display_admin_menu() {
    clear_screen();
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                   管 理 员 菜 单                            ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║ 当前用户: %-25s 角色: 管理员               ║\n", current_user.name);
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║  1. 用户管理     - 管理用户账户                             ║\n");
    printf("║  2. 活动管理     - 管理社团活动                             ║\n");
    printf("║  3. 财务管理     - 管理财务收支                             ║\n");
    printf("║  4. 系统统计     - 查看详细统计                             ║\n");
    printf("║  5. 数据导出     - 导出各类报表                             ║\n");
    printf("║  6. 数据备份     - 备份系统数据                             ║\n");
    printf("║  0. 退出登录     - 返回主菜单                               ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    printf("请选择操作 (0-6): ");
}

// 处理用户注册
void handle_user_registration() {
    char username[MAX_NAME_LEN];
    char password[MAX_NAME_LEN];
    char name[MAX_NAME_LEN];
    char email[MAX_NAME_LEN];
    char confirm_password[MAX_NAME_LEN];

    printf("\n╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                        用 户 注 册                          ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");

    get_valid_string(username, sizeof(username), "用户名 (3-20个字符): ");
    if (strlen(username) < 3 || strlen(username) > 20) {
        printf("错误：用户名长度必须在3-20个字符之间！\n");
        return;
    }

    get_valid_string(password, sizeof(password), "密码 (6-20个字符): ");
    if (strlen(password) < 6 || strlen(password) > 20) {
        printf("错误：密码长度必须在6-20个字符之间！\n");
        return;
    }

    get_valid_string(confirm_password, sizeof(confirm_password), "确认密码: ");
    if (strcmp(password, confirm_password) != 0) {
        printf("错误：两次输入的密码不一致！\n");
        return;
    }

    get_valid_string(name, sizeof(name), "真实姓名: ");
    if (strlen(name) < 2) {
        printf("错误：请输入有效的姓名！\n");
        return;
    }

    get_valid_string(email, sizeof(email), "邮箱地址: ");
    if (!validate_email(email)) {
        printf("错误：请输入有效的邮箱地址！\n");
        return;
    }

    if (user_register(username, password, name, email)) {
        printf("\n? 注册成功！请使用您的账户登录系统。\n");
    }
}

// 处理用户登录
void handle_user_login() {
    char username[MAX_NAME_LEN];
    char password[MAX_NAME_LEN];

    printf("\n╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                        用 户 登 录                          ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");

    get_valid_string(username, sizeof(username), "用户名: ");
    get_valid_string(password, sizeof(password), "密码: ");

    if (user_login(username, password)) {
        is_logged_in = 1;
        printf("\n? 登录成功！欢迎回来，%s！\n", current_user.name);
    } else {
        printf("\n? 登录失败！请检查用户名和密码。\n");
    }
}

// 处理管理员操作
void handle_admin_operations(int choice) {
    switch (choice) {
        case 1:
            handle_user_management();
            break;
        case 2:
            handle_activity_management();
            break;
        case 3:
            handle_finance_management();
            break;
        case 4:
            handle_statistics_view();
            break;
        case 5:
            handle_data_export();
            break;
        case 6:
            backup_all_data();
            break;
        case 0:
            printf("已退出登录\n");
            is_logged_in = 0;
            current_user = (User){0};
            break;
        default:
            printf("无效选择\n");
            break;
    }
}

// 处理数据导出
void handle_data_export() {
    printf("\n╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                        数 据 导 出                          ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║  1. 导出用户数据 - 生成用户列表报告                         ║\n");
    printf("║  2. 导出活动数据 - 生成活动统计报告                         ║\n");
    printf("║  3. 导出财务数据 - 生成财务明细报告                         ║\n");
    printf("║  4. 导出完整报告 - 生成所有数据综合报告                     ║\n");
    printf("║  0. 返回上级菜单                                           ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");

    int choice = get_valid_choice(0, 4);

    switch (choice) {
        case 1: {
            char filename[100];
            get_valid_string(filename, sizeof(filename), "输入导出文件名 (默认: users_report.csv): ");
            if (strlen(filename) == 0) {
                strcpy(filename, "users_report.csv");
            }

            // 直接在这里实现用户数据导出
            FILE* file = fopen(filename, "w");
            if (!file) {
                printf("? 无法创建文件！\n");
                break;
            }

            int count;
            User* users = user_get_all(&count);

            fprintf(file, "智能社团管理系统 - 用户报告\n");
            fprintf(file, "生成时间: %s\n\n", format_time(time(NULL)));
            fprintf(file, "%-5s %-15s %-20s %-30s %-10s %-20s\n",
                    "ID", "用户名", "姓名", "邮箱", "角色", "注册时间");
            fprintf(file, "--------------------------------------------------------------------------------\n");

            int active_count = 0;
            for (int i = 0; i < count; i++) {
                if (users[i].is_active) {
                    const char* role_str = users[i].role == ROLE_ADMIN ? "管理员" : "成员";
                    fprintf(file, "%-5d %-15s %-20s %-30s %-10s %-20s\n",
                           users[i].id, users[i].username, users[i].name,
                           users[i].email, role_str, format_time(users[i].register_time));
                    active_count++;
                }
            }
            fprintf(file, "\n总计: %d 个活跃用户\n", active_count);
            fclose(file);
            printf("? 用户报告已导出到: %s\n", filename);
            break;
        }
        case 2: {
            char filename[100];
            get_valid_string(filename, sizeof(filename), "输入导出文件名 (默认: activities_report.csv): ");
            if (strlen(filename) == 0) {
                strcpy(filename, "activities_report.csv");
            }

            FILE* file = fopen(filename, "w");
            if (!file) {
                printf("? 无法创建文件！\n");
                break;
            }

            int count;
            Activity* activities = activity_get_all(&count);

            fprintf(file, "智能社团管理系统 - 活动报告\n");
            fprintf(file, "生成时间: %s\n\n", format_time(time(NULL)));
            fprintf(file, "%-5s %-20s %-15s %-15s %-10s %-10s %-15s\n",
                    "ID", "标题", "组织者", "地点", "状态", "参与人数", "开始时间");
            fprintf(file, "----------------------------------------------------------------------------------------\n");

            int active_count = 0, pending_count = 0, completed_count = 0, cancelled_count = 0;
            int total_participants = 0;

            for (int i = 0; i < count; i++) {
                if (activities[i].is_active) {
                    const char* status_str;
                    switch (activities[i].status) {
                        case ACTIVITY_PENDING: status_str = "待开始"; pending_count++; break;
                        case ACTIVITY_ACTIVE: status_str = "进行中"; active_count++; break;
                        case ACTIVITY_COMPLETED: status_str = "已完成"; completed_count++; break;
                        case ACTIVITY_CANCELLED: status_str = "已取消"; cancelled_count++; break;
                        default: status_str = "未知"; break;
                    }

                    fprintf(file, "%-5d %-20s %-15s %-15s %-10s %-10d %-15s\n",
                           activities[i].id, activities[i].title, activities[i].organizer,
                           activities[i].location, status_str, activities[i].current_participants,
                           format_time(activities[i].start_time));
                    total_participants += activities[i].current_participants;
                }
            }

            fprintf(file, "\n统计信息:\n");
            fprintf(file, "总活动数: %d\n", count);
            fprintf(file, "待开始: %d\n", pending_count);
            fprintf(file, "进行中: %d\n", active_count);
            fprintf(file, "已完成: %d\n", completed_count);
            fprintf(file, "已取消: %d\n", cancelled_count);
            fprintf(file, "总参与人数: %d\n", total_participants);

            fclose(file);
            printf("? 活动报告已导出到: %s\n", filename);
            break;
        }
        case 3: {
            char filename[100];
            get_valid_string(filename, sizeof(filename), "输入导出文件名 (默认: finance_report.csv): ");
            if (strlen(filename) == 0) {
                strcpy(filename, "finance_report.csv");
            }

            FILE* file = fopen(filename, "w");
            if (!file) {
                printf("? 无法创建文件！\n");
                break;
            }

            int count;
            FinanceRecord* records = finance_get_records(&count);

            fprintf(file, "智能社团管理系统 - 财务报告\n");
            fprintf(file, "生成时间: %s\n\n", format_time(time(NULL)));
            fprintf(file, "%-5s %-30s %-10s %-15s %-20s %-15s %-20s\n",
                    "ID", "描述", "金额", "类型", "分类", "操作员", "记录时间");
            fprintf(file, "----------------------------------------------------------------------------------------------------\n");

            double total_income = 0.0, total_expense = 0.0;
            for (int i = 0; i < count; i++) {
                if (records[i].is_active) {
                    const char* type_str = records[i].type == FINANCE_INCOME ? "收入" : "支出";
                    fprintf(file, "%-5d %-30s %-10.2f %-15s %-20s %-15s %-20s\n",
                           records[i].id, records[i].description, records[i].amount,
                           type_str, records[i].category, records[i].operator_name,
                           format_time(records[i].record_time));

                    if (records[i].type == FINANCE_INCOME) {
                        total_income += records[i].amount;
                    } else {
                        total_expense += records[i].amount;
                    }
                }
            }

            fprintf(file, "----------------------------------------------------------------------------------------------------\n");
            fprintf(file, "总收入: %.2f\n", total_income);
            fprintf(file, "总支出: %.2f\n", total_expense);
            fprintf(file, "当前结余: %.2f\n", total_income - total_expense);

            fclose(file);
            printf("? 财务报告已导出到: %s\n", filename);
            break;
        }
        case 4: {
            printf("正在生成完整报告...\n");
            handle_data_export(); // 递归调用前面的选项
            export_statistics_report("statistics_report.csv");
            printf("? 完整报告生成完毕！\n");
            break;
        }
        case 0:
            break;
    }
}

// 处理普通用户操作
void handle_user_operations(int choice) {
    switch (choice) {
        case 1:
            handle_user_profile();
            break;
        case 2:
            handle_activity_operations();
            break;
        case 3:
            handle_finance_operations();
            break;
        case 4:
            handle_statistics_view();
            break;
        case 0:
            printf("已退出登录\n");
            is_logged_in = 0;
            current_user = (User){0};
            break;
        default:
            printf("无效选择\n");
            break;
    }
}

// 处理用户管理（管理员）
void handle_user_management() {
    printf("\n╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                        用 户 管 理                          ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║  1. 查看所有用户 - 显示用户列表                             ║\n");
    printf("║  2. 删除用户     - 删除指定用户                             ║\n");
    printf("║  0. 返回上级菜单                                           ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");

    int choice = get_valid_choice(0, 2);

    switch (choice) {
        case 1: {
            int count;
            User* users = user_get_all(&count);
            printf("\n╔══════════════════════════════════════════════════════════════╗\n");
            printf("║                        用 户 列 表                          ║\n");
            printf("╠══════════════════════════════════════════════════════════════╣\n");
            printf("║ %-5s %-15s %-20s %-12s %-20s ║\n", "ID", "用户名", "姓名", "角色", "注册时间");
            printf("╠══════════════════════════════════════════════════════════════╣\n");

            int active_count = 0;
            for (int i = 0; i < count; i++) {
                if (users[i].is_active) {
                    printf("║ %-5d %-15s %-20s %-12s %-20s ║\n",
                           users[i].id, users[i].username, users[i].name,
                           users[i].role == ROLE_ADMIN ? "管理员" : "成员",
                           format_time(users[i].register_time));
                    active_count++;
                }
            }
            printf("╚══════════════════════════════════════════════════════════════╝\n");
            printf("总计: %d 个活跃用户\n", active_count);
            break;
        }
        case 2: {
            printf("\n输入要删除的用户ID: ");
            int user_id = get_valid_choice(1, 9999);
            if (user_delete(user_id)) {
                printf("\n? 用户删除成功！\n");
            }
            break;
        }
        case 0:
            break;
    }
}

// 处理活动管理（管理员）
void handle_activity_management() {
    printf("\n========== 活动管理 ==========\n");
    printf("1. 发布新活动\n");
    printf("2. 查看所有活动\n");
    printf("3. 修改活动\n");
    printf("4. 删除活动\n");
    printf("5. 完成活动\n");
    printf("6. 取消活动\n");
    printf("0. 返回上级菜单\n");
    printf("==============================\n");

    int choice;
    printf("请选择: ");
    scanf("%d", &choice);
    getchar();

    switch (choice) {
        case 1: {
            char title[MAX_NAME_LEN], description[MAX_DESC_LEN], location[MAX_NAME_LEN];
            int max_participants;
            time_t start_time, end_time;

            printf("\n╔══════════════════════════════════════════════════════════════╗\n");
            printf("║                        创建新活动                            ║\n");
            printf("╚══════════════════════════════════════════════════════════════╝\n");

            get_valid_string(title, sizeof(title), "活动标题: ");
            get_valid_string(description, sizeof(description), "活动描述: ");
            get_valid_string(location, sizeof(location), "活动地点: ");

            if (!get_valid_date_input(&start_time, &end_time)) {
                printf("? 时间输入错误！\n");
                break;
            }

            printf("最大参与人数 (1-1000): ");
            max_participants = get_valid_choice(1, 1000);

            if (activity_create(title, description, current_user.name,
                              start_time, end_time, location, max_participants)) {
                printf("\n? 活动创建成功！\n");
            }
            break;
        }
        case 2: {
            int count;
            Activity* activities = activity_get_all(&count);
            activity_display_list(activities, count);
            break;
        }
        case 3: {
            int activity_id;
            printf("输入活动ID: ");
            scanf("%d", &activity_id);
            getchar();

            // 简化修改，只修改基本信息
            char title[MAX_NAME_LEN], location[MAX_NAME_LEN];
            printf("新标题 (留空保持不变): ");
            fgets(title, sizeof(title), stdin);
            title[strcspn(title, "\n")] = 0;

            printf("新地点 (留空保持不变): ");
            fgets(location, sizeof(location), stdin);
            location[strcspn(location, "\n")] = 0;

            Activity* activity = activity_get_by_id(activity_id);
            if (activity) {
                activity_update(activity_id,
                              strlen(title) > 0 ? title : NULL,
                              NULL, 0, 0,
                              strlen(location) > 0 ? location : NULL, 0);
            }
            break;
        }
        case 4: {
            int activity_id;
            printf("输入要删除的活动ID: ");
            scanf("%d", &activity_id);
            getchar();
            activity_delete(activity_id);
            break;
        }
        case 5: {
            int activity_id;
            printf("输入要完成的活动ID: ");
            scanf("%d", &activity_id);
            getchar();
            activity_complete(activity_id);
            break;
        }
        case 6: {
            int activity_id;
            printf("输入要取消的活动ID: ");
            scanf("%d", &activity_id);
            getchar();
            activity_cancel(activity_id);
            break;
        }
        case 0:
            break;
        default:
            printf("无效选择\n");
    }
}

// 占位符函数，后续实现
void handle_finance_management() {
    printf("\n========== 财务管理 ==========\n");
    printf("1. 添加收入记录\n");
    printf("2. 添加支出记录\n");
    printf("3. 查看财务报表\n");
    printf("4. 修改财务记录\n");
    printf("5. 删除财务记录\n");
    printf("6. 导出财务报表\n");
    printf("0. 返回上级菜单\n");
    printf("==============================\n");

    int choice;
    printf("请选择: ");
    scanf("%d", &choice);
    getchar();

    switch (choice) {
        case 1: {
            // 添加收入记录
            char description[MAX_DESC_LEN], category[MAX_NAME_LEN];
            double amount;

            printf("\n╔══════════════════════════════════════════════════════════════╗\n");
            printf("║                        添加收入记录                          ║\n");
            printf("╚══════════════════════════════════════════════════════════════╝\n");

            get_valid_string(description, sizeof(description), "收入描述: ");
            amount = get_valid_amount();
            get_valid_string(category, sizeof(category), "收入分类: ");

            if (finance_add_record(description, amount, FINANCE_INCOME, category, current_user.name)) {
                printf("\n? 收入记录添加成功！\n");
            }
            break;
        }
        case 2: {
            // 添加支出记录
            char description[MAX_DESC_LEN], category[MAX_NAME_LEN];
            double amount;

            printf("\n╔══════════════════════════════════════════════════════════════╗\n");
            printf("║                        添加支出记录                          ║\n");
            printf("╚══════════════════════════════════════════════════════════════╝\n");

            get_valid_string(description, sizeof(description), "支出描述: ");
            amount = get_valid_amount();
            get_valid_string(category, sizeof(category), "支出分类: ");

            if (finance_add_record(description, amount, FINANCE_EXPENSE, category, current_user.name)) {
                printf("\n? 支出记录添加成功！\n");
            }
            break;
        }
        case 3:
            finance_generate_report();
            break;
        case 4: {
            // 修改财务记录
            int record_id;
            printf("输入要修改的记录ID: ");
            scanf("%d", &record_id);
            getchar();

            char description[MAX_DESC_LEN], category[MAX_NAME_LEN];
            double amount;

            printf("新描述 (留空保持不变): ");
            fgets(description, sizeof(description), stdin);
            description[strcspn(description, "\n")] = 0;

            printf("新金额 (输入0保持不变): ");
            scanf("%lf", &amount);
            getchar();

            printf("新分类 (留空保持不变): ");
            fgets(category, sizeof(category), stdin);
            category[strcspn(category, "\n")] = 0;

            finance_update_record(record_id,
                                strlen(description) > 0 ? description : NULL,
                                amount > 0 ? amount : -1,
                                strlen(category) > 0 ? category : NULL);
            break;
        }
        case 5: {
            int record_id;
            printf("输入要删除的记录ID: ");
            scanf("%d", &record_id);
            getchar();
            finance_delete_record(record_id);
            break;
        }
        case 6: {
            char filename[100];
            printf("输入导出文件名 (如: finance_report.csv): ");
            fgets(filename, sizeof(filename), stdin);
            filename[strcspn(filename, "\n")] = 0;
            if (strlen(filename) == 0) {
                strcpy(filename, "finance_report.csv");
            }
            finance_export_report(filename);
            break;
        }
        case 0:
            break;
        default:
            printf("无效选择\n");
    }
}

void handle_statistics_view() {
    printf("\n========== 系统统计 ==========\n");
    printf("1. 查看完整统计报告\n");
    printf("2. 用户统计信息\n");
    printf("3. 活动统计信息\n");
    printf("4. 财务统计信息\n");
    printf("5. 用户参与度分析\n");
    printf("6. 活动热度分析\n");
    printf("7. 财务趋势分析\n");
    printf("8. 导出统计报告\n");
    printf("0. 返回\n");
    printf("===============================\n");

    int choice;
    printf("请选择: ");
    scanf("%d", &choice);
    getchar();

    switch (choice) {
        case 1:
            display_full_statistics_report();
            break;
        case 2:
            display_user_statistics();
            break;
        case 3:
            display_activity_statistics();
            break;
        case 4:
            display_finance_statistics();
            break;
        case 5:
            analyze_user_participation();
            break;
        case 6:
            analyze_activity_popularity();
            break;
        case 7:
            analyze_finance_trends();
            break;
        case 8: {
            char filename[100];
            printf("输入导出文件名 (如: statistics_report.csv): ");
            fgets(filename, sizeof(filename), stdin);
            filename[strcspn(filename, "\n")] = 0;
            if (strlen(filename) == 0) {
                strcpy(filename, "statistics_report.csv");
            }
            export_statistics_report(filename);
            break;
        }
        case 0:
            break;
        default:
            printf("无效选择\n");
    }
}

void handle_user_profile() {
    printf("\n========== 个人信息 ==========\n");
    user_display_info(&current_user);

    printf("\n1. 修改个人信息\n");
    printf("2. 修改密码\n");
    printf("0. 返回\n");
    printf("===============================\n");

    int choice;
    printf("请选择: ");
    scanf("%d", &choice);
    getchar();

    switch (choice) {
        case 1: {
            char name[MAX_NAME_LEN], email[MAX_NAME_LEN];
            printf("新姓名 (留空保持不变): ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0;
            trim_whitespace(name);

            printf("新邮箱 (留空保持不变): ");
            fgets(email, sizeof(email), stdin);
            email[strcspn(email, "\n")] = 0;
            trim_whitespace(email);

            user_update_info(current_user.id,
                           strlen(name) > 0 ? name : NULL,
                           strlen(email) > 0 ? email : NULL);
            break;
        }
        case 2: {
            char old_password[MAX_NAME_LEN], new_password[MAX_NAME_LEN];
            printf("原密码: ");
            fgets(old_password, sizeof(old_password), stdin);
            old_password[strcspn(old_password, "\n")] = 0;

            printf("新密码: ");
            fgets(new_password, sizeof(new_password), stdin);
            new_password[strcspn(new_password, "\n")] = 0;

            user_change_password(current_user.id, old_password, new_password);
            break;
        }
        case 0:
            break;
        default:
            printf("无效选择\n");
    }
}

void handle_activity_operations() {
    printf("\n========== 活动操作 ==========\n");
    printf("1. 查看活动列表\n");
    printf("2. 搜索活动\n");
    printf("3. 活动详情\n");
    printf("4. 报名活动\n");
    printf("5. 取消报名\n");
    printf("0. 返回\n");
    printf("===============================\n");

    int choice;
    printf("请选择: ");
    scanf("%d", &choice);
    getchar();

    switch (choice) {
        case 1: {
            int count;
            Activity* activities = activity_get_all(&count);
            activity_display_list(activities, count);
            break;
        }
        case 2: {
            char keyword[MAX_NAME_LEN];
            printf("输入搜索关键词: ");
            fgets(keyword, sizeof(keyword), stdin);
            keyword[strcspn(keyword, "\n")] = 0;

            int count;
            Activity* results = activity_search(keyword, &count);
            activity_display_list(results, count);
            break;
        }
        case 3: {
            int activity_id;
            printf("输入活动ID: ");
            scanf("%d", &activity_id);
            getchar();

            Activity* activity = activity_get_by_id(activity_id);
            if (activity) {
                activity_display_info(activity);
            } else {
                printf("活动不存在\n");
            }
            break;
        }
        case 4: {
            int activity_id;
            printf("输入要报名的活动ID: ");
            scanf("%d", &activity_id);
            getchar();
            activity_signup(activity_id, current_user.id);
            break;
        }
        case 5: {
            int activity_id;
            printf("输入要取消报名的活动ID: ");
            scanf("%d", &activity_id);
            getchar();
            activity_cancel_signup(activity_id, current_user.id);
            break;
        }
        case 0:
            break;
        default:
            printf("无效选择\n");
    }
}

void handle_finance_operations() {
    printf("\n========== 财务信息 ==========\n");
    printf("1. 查看财务余额\n");
    printf("2. 查看财务报表\n");
    printf("3. 导出财务报表\n");
    printf("0. 返回\n");
    printf("==============================\n");

    int choice;
    printf("请选择: ");
    scanf("%d", &choice);
    getchar();

    switch (choice) {
        case 1:
            finance_display_balance();
            break;
        case 2:
            finance_generate_report();
            break;
        case 3: {
            char filename[100];
            printf("输入导出文件名 (如: finance_report.csv): ");
            fgets(filename, sizeof(filename), stdin);
            filename[strcspn(filename, "\n")] = 0;
            if (strlen(filename) == 0) {
                strcpy(filename, "finance_report.csv");
            }
            finance_export_report(filename);
            break;
        }
        case 0:
            break;
        default:
            printf("无效选择\n");
    }
}

// 备份所有数据（管理员功能）- 声明在file_utils.h中

// 获取有效选择
int get_valid_choice(int min, int max) {
    int choice;
    char input[100];

    while (1) {
        printf("请选择 (%d-%d): ", min, max);
        if (fgets(input, sizeof(input), stdin) == NULL) {
            return min - 1; // 错误值
        }

        // 移除换行符
        input[strcspn(input, "\n")] = 0;

        // 检查是否为数字
        if (sscanf(input, "%d", &choice) != 1) {
            printf("错误：请输入有效的数字！\n");
            continue;
        }

        if (choice >= min && choice <= max) {
            return choice;
        } else {
            printf("错误：选择必须在 %d-%d 之间！\n", min, max);
        }
    }
}

// 获取有效金额
double get_valid_amount() {
    double amount;
    char input[100];

    while (1) {
        printf("请输入金额: ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            return -1.0;
        }

        input[strcspn(input, "\n")] = 0;

        if (sscanf(input, "%lf", &amount) != 1) {
            printf("错误：请输入有效的金额！\n");
            continue;
        }

        if (amount <= 0) {
            printf("错误：金额必须大于0！\n");
            continue;
        }

        if (amount > 999999.99) {
            printf("错误：金额不能超过999999.99！\n");
            continue;
        }

        return amount;
    }
}

// 获取有效字符串
void get_valid_string(char* buffer, int max_len, const char* prompt) {
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, max_len, stdin) == NULL) {
            buffer[0] = '\0';
            return;
        }

        // 移除换行符
        buffer[strcspn(buffer, "\n")] = 0;

        // 去除前后空格
        trim_whitespace(buffer);

        if (strlen(buffer) == 0) {
            printf("错误：输入不能为空！\n");
            continue;
        }

        if ((int)strlen(buffer) >= max_len - 1) {
            printf("错误：输入过长，请重新输入！\n");
            continue;
        }

        break;
    }
}

// 获取有效日期输入
int get_valid_date_input(time_t* start_time, time_t* end_time) {
    char date_str[50];

    while (1) {
        get_valid_string(date_str, sizeof(date_str), "开始时间 (YYYY-MM-DD HH:MM:SS): ");
        if (!validate_date(date_str, start_time)) {
            printf("错误：日期格式无效！请使用 YYYY-MM-DD HH:MM:SS 格式\n");
            continue;
        }

        get_valid_string(date_str, sizeof(date_str), "结束时间 (YYYY-MM-DD HH:MM:SS): ");
        if (!validate_date(date_str, end_time)) {
            printf("错误：日期格式无效！请使用 YYYY-MM-DD HH:MM:SS 格式\n");
            continue;
        }

        if (*start_time >= *end_time) {
            printf("错误：开始时间不能晚于结束时间！\n");
            continue;
        }

        // 检查时间是否合理（不能太久远或太遥远）
        time_t now = time(NULL);
        if (*start_time < now - 86400 * 365) { // 一年前
            printf("警告：开始时间太久远了！\n");
        }

        if (*end_time > now + 86400 * 365 * 2) { // 两年后
            printf("警告：结束时间太遥远了！\n");
        }

        return 1;
    }
}
