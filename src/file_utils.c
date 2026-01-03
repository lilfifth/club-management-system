#include "file_utils.h"
#include <errno.h>
#ifdef _WIN32
#include <direct.h>
#endif

// 保存用户数据到文件
int file_save_users(const User* users, int count) {
    FILE* file = fopen(USER_DATA_FILE, "w");
    if (!file) {
        printf("错误：无法打开用户数据文件\n");
        return 0;
    }

    fprintf(file, "# 用户数据文件\n");
    fprintf(file, "# 格式: id,username,password,name,email,role,register_time,is_active\n");

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%s,%s,%s,%d,%ld,%d\n",
                users[i].id,
                users[i].username,
                users[i].password,
                users[i].name,
                users[i].email,
                users[i].role,
                users[i].register_time,
                users[i].is_active);
    }

    fclose(file);
    return 1;
}

// 从文件加载用户数据
int file_load_users(User* users, int max_count) {
    FILE* file = fopen(USER_DATA_FILE, "r");
    if (!file) {
        // 文件不存在是正常的（首次运行）
        return 0;
    }

    int count = 0;
    char line[1024];

    while (fgets(line, sizeof(line), file) && count < max_count) {
        // 跳过注释行和空行
        if (line[0] == '#' || line[0] == '\n' || line[0] == '\r') {
            continue;
        }

        // 解析CSV格式数据
        User user = {0};
        if (sscanf(line, "%d,%49[^,],%49[^,],%49[^,],%49[^,],%d,%ld,%d",
                   &user.id,
                   user.username,
                   user.password,
                   user.name,
                   user.email,
                   &user.role,
                   &user.register_time,
                   &user.is_active) == 8) {
            users[count++] = user;
        }
    }

    fclose(file);
    return count;
}

// 保存活动数据到文件
int file_save_activities(const Activity* activities, int count) {
    FILE* file = fopen(ACTIVITY_DATA_FILE, "w");
    if (!file) {
        printf("错误：无法打开活动数据文件\n");
        return 0;
    }

    fprintf(file, "# 活动数据文件\n");
    fprintf(file, "# 格式: id,title,description,organizer,create_time,start_time,end_time,location,max_participants,current_participants,status,is_active\n");

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%s,%s,%ld,%ld,%ld,%s,%d,%d,%d,%d\n",
                activities[i].id,
                activities[i].title,
                activities[i].description,
                activities[i].organizer,
                activities[i].create_time,
                activities[i].start_time,
                activities[i].end_time,
                activities[i].location,
                activities[i].max_participants,
                activities[i].current_participants,
                activities[i].status,
                activities[i].is_active);
    }

    fclose(file);
    return 1;
}

// 从文件加载活动数据
int file_load_activities(Activity* activities, int max_count) {
    FILE* file = fopen(ACTIVITY_DATA_FILE, "r");
    if (!file) {
        return 0;
    }

    int count = 0;
    char line[2048];

    while (fgets(line, sizeof(line), file) && count < max_count) {
        if (line[0] == '#' || line[0] == '\n' || line[0] == '\r') {
            continue;
        }

        Activity activity = {0};
        if (sscanf(line, "%d,%49[^,],%199[^,],%49[^,],%ld,%ld,%ld,%49[^,],%d,%d,%d,%d",
                   &activity.id,
                   activity.title,
                   activity.description,
                   activity.organizer,
                   &activity.create_time,
                   &activity.start_time,
                   &activity.end_time,
                   activity.location,
                   &activity.max_participants,
                   &activity.current_participants,
                   &activity.status,
                   &activity.is_active) == 12) {
            activities[count++] = activity;
        }
    }

    fclose(file);
    return count;
}

// 保存财务记录到文件
int file_save_finance_records(const FinanceRecord* records, int count) {
    FILE* file = fopen(FINANCE_DATA_FILE, "w");
    if (!file) {
        printf("错误：无法打开财务数据文件\n");
        return 0;
    }

    fprintf(file, "# 财务数据文件\n");
    fprintf(file, "# 格式: id,description,amount,type,category,operator_name,record_time,is_active\n");

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%.2f,%d,%s,%s,%ld,%d\n",
                records[i].id,
                records[i].description,
                records[i].amount,
                records[i].type,
                records[i].category,
                records[i].operator_name,
                records[i].record_time,
                records[i].is_active);
    }

    fclose(file);
    return 1;
}

// 从文件加载财务记录
int file_load_finance_records(FinanceRecord* records, int max_count) {
    FILE* file = fopen(FINANCE_DATA_FILE, "r");
    if (!file) {
        return 0;
    }

    int count = 0;
    char line[1024];

    while (fgets(line, sizeof(line), file) && count < max_count) {
        if (line[0] == '#' || line[0] == '\n' || line[0] == '\r') {
            continue;
        }

        FinanceRecord record = {0};
        if (sscanf(line, "%d,%199[^,],%lf,%d,%49[^,],%49[^,],%ld,%d",
                   &record.id,
                   record.description,
                   &record.amount,
                   &record.type,
                   record.category,
                   record.operator_name,
                   &record.record_time,
                   &record.is_active) == 8) {
            records[count++] = record;
        }
    }

    fclose(file);
    return count;
}

// 保存报名记录到文件
int file_save_signups(const int signups[][2], int count) {
    FILE* file = fopen("signups.txt", "w");
    if (!file) {
        printf("错误：无法打开报名记录文件\n");
        return 0;
    }

    fprintf(file, "# 报名记录文件\n");
    fprintf(file, "# 格式: activity_id,user_id\n");

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%d\n", signups[i][0], signups[i][1]);
    }

    fclose(file);
    return 1;
}

// 从文件加载报名记录
int file_load_signups(int signups[][2], int max_count) {
    FILE* file = fopen("signups.txt", "r");
    if (!file) {
        return 0;
    }

    int count = 0;
    char line[256];

    while (fgets(line, sizeof(line), file) && count < max_count) {
        if (line[0] == '#' || line[0] == '\n' || line[0] == '\r') {
            continue;
        }

        int activity_id, user_id;
        if (sscanf(line, "%d,%d", &activity_id, &user_id) == 2) {
            signups[count][0] = activity_id;
            signups[count][1] = user_id;
            count++;
        }
    }

    fclose(file);
    return count;
}

// 导出用户报告
int file_export_user_report(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("错误：无法创建用户报告文件\n");
        return 0;
    }

    fprintf(file, "智能社团管理系统 - 用户报告\n");
    fprintf(file, "生成时间: %s\n\n", format_time(time(NULL)));

    fprintf(file, "%-5s %-15s %-20s %-30s %-10s %-20s\n",
            "ID", "用户名", "姓名", "邮箱", "角色", "注册时间");
    fprintf(file, "--------------------------------------------------------------------------------\n");

    // 由于无法直接访问静态变量，这里暂时输出表头
    fprintf(file, "数据导出功能需要通过用户界面调用\n");

    fclose(file);
    printf("用户报告模板已创建: %s\n", filename);
    return 1;
}

// 导出活动报告
int file_export_activity_report(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("错误：无法创建活动报告文件\n");
        return 0;
    }

    fprintf(file, "智能社团管理系统 - 活动报告\n");
    fprintf(file, "生成时间: %s\n\n", format_time(time(NULL)));
    fprintf(file, "活动数据导出功能已移至主界面实现\n");

    fclose(file);
    printf("活动报告模板已创建: %s\n", filename);
    return 1;
}

// 导出财务报告
int file_export_finance_report(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("错误：无法创建财务报告文件\n");
        return 0;
    }

    fprintf(file, "智能社团管理系统 - 财务报告\n");
    fprintf(file, "生成时间: %s\n\n", format_time(time(NULL)));
    fprintf(file, "财务数据导出功能已移至主界面实现\n");

    fclose(file);
    printf("财务报告模板已创建: %s\n", filename);
    return 1;
}

// 检查文件是否存在
int file_exists(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

// 创建目录
int create_directory(const char* path) {
#ifdef _WIN32
    return _mkdir(path) == 0 || errno == EEXIST;
#else
    return mkdir(path, 0755) == 0 || errno == EEXIST;
#endif
}

// 备份所有数据
int backup_all_data() {
    char backup_dir[100];
    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);

    sprintf(backup_dir, "backup_%04d%02d%02d_%02d%02d%02d",
            tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday,
            tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);

    if (!create_directory(backup_dir)) {
        printf("错误：无法创建备份目录\n");
        return 0;
    }

    // 复制文件到备份目录
    char cmd[256];

#ifdef _WIN32
    sprintf(cmd, "copy %s %s\\", USER_DATA_FILE, backup_dir);
    system(cmd);
    sprintf(cmd, "copy %s %s\\", ACTIVITY_DATA_FILE, backup_dir);
    system(cmd);
    sprintf(cmd, "copy %s %s\\", FINANCE_DATA_FILE, backup_dir);
    system(cmd);
    sprintf(cmd, "copy signups.txt %s\\", backup_dir);
    system(cmd);
#else
    sprintf(cmd, "cp %s %s/", USER_DATA_FILE, backup_dir);
    system(cmd);
    sprintf(cmd, "cp %s %s/", ACTIVITY_DATA_FILE, backup_dir);
    system(cmd);
    sprintf(cmd, "cp %s %s/", FINANCE_DATA_FILE, backup_dir);
    system(cmd);
    sprintf(cmd, "cp signups.txt %s/", backup_dir);
    system(cmd);
#endif

    printf("数据备份完成：%s\n", backup_dir);
    return 1;
}
