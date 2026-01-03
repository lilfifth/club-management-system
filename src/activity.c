#include "activity.h"
#include "file_utils.h"

// 全局活动数组和计数器
static Activity activities[MAX_ACTIVITIES];
static int activity_count = 0;
static int next_activity_id = 1;

// 报名记录（简化实现，实际项目中应该用数据库）
static int signup_records[MAX_ACTIVITIES * MAX_USERS][2]; // [activity_id, user_id]
static int signup_count = 0;

// 创建活动
int activity_create(const char* title, const char* description,
                   const char* organizer, time_t start_time, time_t end_time,
                   const char* location, int max_participants) {
    // 输入验证
    if (!title || !description || !organizer || !location) {
        printf("错误：所有字段都必须填写\n");
        return 0;
    }

    if (strlen(title) == 0 || strlen(description) == 0 ||
        strlen(organizer) == 0 || strlen(location) == 0) {
        printf("错误：字段不能为空\n");
        return 0;
    }

    if (start_time >= end_time) {
        printf("错误：开始时间不能晚于结束时间\n");
        return 0;
    }

    if (max_participants <= 0) {
        printf("错误：最大参与人数必须大于0\n");
        return 0;
    }

    // 检查活动数组是否已满
    if (activity_count >= MAX_ACTIVITIES) {
        printf("错误：活动数量已达上限\n");
        return 0;
    }

    // 创建新活动
    Activity new_activity;
    new_activity.id = next_activity_id++;
    strcpy(new_activity.title, title);
    strcpy(new_activity.description, description);
    strcpy(new_activity.organizer, organizer);
    new_activity.create_time = time(NULL);
    new_activity.start_time = start_time;
    new_activity.end_time = end_time;
    strcpy(new_activity.location, location);
    new_activity.max_participants = max_participants;
    new_activity.current_participants = 0;
    new_activity.status = ACTIVITY_PENDING;
    new_activity.is_active = 1;

    activities[activity_count++] = new_activity;

    // 保存到文件
    if (!activity_save_to_file()) {
        printf("警告：活动创建成功，但保存到文件失败\n");
    }

    printf("活动创建成功！\n");
    return new_activity.id;
}

// 活动报名
int activity_signup(int activity_id, int user_id) {
    Activity* activity = activity_get_by_id(activity_id);
    if (!activity) {
        printf("错误：活动不存在\n");
        return 0;
    }

    if (activity->status != ACTIVITY_PENDING && activity->status != ACTIVITY_ACTIVE) {
        printf("错误：活动无法报名\n");
        return 0;
    }

    if (activity->current_participants >= activity->max_participants) {
        printf("错误：活动已满员\n");
        return 0;
    }

    if (activity_is_user_signed_up(activity_id, user_id)) {
        printf("错误：您已报名此活动\n");
        return 0;
    }

    // 检查报名记录数组是否已满
    if (signup_count >= MAX_ACTIVITIES * MAX_USERS) {
        printf("错误：报名记录已满\n");
        return 0;
    }

    // 添加报名记录
    signup_records[signup_count][0] = activity_id;
    signup_records[signup_count][1] = user_id;
    signup_count++;

    activity->current_participants++;

    // 保存到文件
    if (!activity_save_to_file()) {
        printf("警告：报名成功，但保存到文件失败\n");
    }

    printf("报名成功！\n");
    return 1;
}

// 取消报名
int activity_cancel_signup(int activity_id, int user_id) {
    Activity* activity = activity_get_by_id(activity_id);
    if (!activity) {
        printf("错误：活动不存在\n");
        return 0;
    }

    if (!activity_is_user_signed_up(activity_id, user_id)) {
        printf("错误：您未报名此活动\n");
        return 0;
    }

    // 移除报名记录
    for (int i = 0; i < signup_count; i++) {
        if (signup_records[i][0] == activity_id && signup_records[i][1] == user_id) {
            // 移动数组元素
            for (int j = i; j < signup_count - 1; j++) {
                signup_records[j][0] = signup_records[j + 1][0];
                signup_records[j][1] = signup_records[j + 1][1];
            }
            signup_count--;
            break;
        }
    }

    activity->current_participants--;

    // 保存到文件
    if (!activity_save_to_file()) {
        printf("警告：取消报名成功，但保存到文件失败\n");
    }

    printf("取消报名成功！\n");
    return 1;
}

// 根据ID获取活动
Activity* activity_get_by_id(int activity_id) {
    for (int i = 0; i < activity_count; i++) {
        if (activities[i].id == activity_id && activities[i].is_active) {
            return &activities[i];
        }
    }
    return NULL;
}

// 获取所有活动
Activity* activity_get_all(int* count) {
    *count = activity_count;
    return activities;
}

// 按状态获取活动
Activity* activity_get_by_status(int status, int* count) {
    static Activity filtered_activities[MAX_ACTIVITIES];
    int filtered_count = 0;

    for (int i = 0; i < activity_count; i++) {
        if (activities[i].is_active && activities[i].status == status) {
            filtered_activities[filtered_count++] = activities[i];
        }
    }

    *count = filtered_count;
    return filtered_activities;
}

// 搜索活动
Activity* activity_search(const char* keyword, int* count) {
    static Activity search_results[MAX_ACTIVITIES];
    int result_count = 0;

    if (!keyword || strlen(keyword) == 0) {
        return activity_get_all(count);
    }

    for (int i = 0; i < activity_count; i++) {
        if (activities[i].is_active &&
            (strstr(activities[i].title, keyword) ||
             strstr(activities[i].description, keyword))) {
            search_results[result_count++] = activities[i];
        }
    }

    *count = result_count;
    return search_results;
}

// 显示活动信息
void activity_display_info(const Activity* activity) {
    if (!activity) {
        printf("活动信息不存在\n");
        return;
    }

    printf("\n=== 活动详情 ===\n");
    printf("ID: %d\n", activity->id);
    printf("标题: %s\n", activity->title);
    printf("描述: %s\n", activity->description);
    printf("组织者: %s\n", activity->organizer);
    printf("地点: %s\n", activity->location);
    printf("开始时间: %s\n", format_time(activity->start_time));
    printf("结束时间: %s\n", format_time(activity->end_time));
    printf("参与人数: %d/%d\n", activity->current_participants, activity->max_participants);

    const char* status_str;
    switch (activity->status) {
        case ACTIVITY_PENDING: status_str = "待开始"; break;
        case ACTIVITY_ACTIVE: status_str = "进行中"; break;
        case ACTIVITY_COMPLETED: status_str = "已完成"; break;
        case ACTIVITY_CANCELLED: status_str = "已取消"; break;
        default: status_str = "未知"; break;
    }
    printf("状态: %s\n", status_str);
    printf("================\n");
}

// 显示活动列表
void activity_display_list(Activity* activities, int count) {
    if (count == 0) {
        printf("暂无活动\n");
        return;
    }

    printf("\n%-5s %-20s %-15s %-10s %-8s\n", "ID", "标题", "组织者", "状态", "参与人数");
    print_separator();

    for (int i = 0; i < count; i++) {
        const char* status_str;
        switch (activities[i].status) {
            case ACTIVITY_PENDING: status_str = "待开始"; break;
            case ACTIVITY_ACTIVE: status_str = "进行中"; break;
            case ACTIVITY_COMPLETED: status_str = "已完成"; break;
            case ACTIVITY_CANCELLED: status_str = "已取消"; break;
            default: status_str = "未知"; break;
        }

        printf("%-5d %-20s %-15s %-10s %-8d\n",
               activities[i].id,
               activities[i].title,
               activities[i].organizer,
               status_str,
               activities[i].current_participants);
    }
}

// 删除活动
int activity_delete(int activity_id) {
    for (int i = 0; i < activity_count; i++) {
        if (activities[i].id == activity_id && activities[i].is_active) {
            activities[i].is_active = 0;

            // 清理相关的报名记录
            for (int j = 0; j < signup_count; j++) {
                if (signup_records[j][0] == activity_id) {
                    // 移除报名记录
                    for (int k = j; k < signup_count - 1; k++) {
                        signup_records[k][0] = signup_records[k + 1][0];
                        signup_records[k][1] = signup_records[k + 1][1];
                    }
                    signup_count--;
                    j--; // 调整索引
                }
            }

            // 保存到文件
            if (!activity_save_to_file()) {
                printf("警告：活动删除成功，但保存到文件失败\n");
            }

            printf("活动删除成功！\n");
            return 1;
        }
    }

    printf("错误：活动不存在\n");
    return 0;
}

// 更新活动信息
int activity_update(int activity_id, const char* title, const char* description,
                   time_t start_time, time_t end_time, const char* location,
                   int max_participants) {
    Activity* activity = activity_get_by_id(activity_id);
    if (!activity) {
        printf("错误：活动不存在\n");
        return 0;
    }

    if (activity->status != ACTIVITY_PENDING) {
        printf("错误：只能修改待开始的活动\n");
        return 0;
    }

    // 更新信息
    if (title && strlen(title) > 0) strcpy(activity->title, title);
    if (description && strlen(description) > 0) strcpy(activity->description, description);
    if (start_time > 0) activity->start_time = start_time;
    if (end_time > 0) activity->end_time = end_time;
    if (location && strlen(location) > 0) strcpy(activity->location, location);
    if (max_participants > 0) activity->max_participants = max_participants;

    // 保存到文件
    if (!activity_save_to_file()) {
        printf("警告：活动更新成功，但保存到文件失败\n");
    }

    printf("活动更新成功！\n");
    return 1;
}

// 完成活动
int activity_complete(int activity_id) {
    Activity* activity = activity_get_by_id(activity_id);
    if (!activity) {
        printf("错误：活动不存在\n");
        return 0;
    }

    if (activity->status != ACTIVITY_ACTIVE) {
        printf("错误：只有进行中的活动才能完成\n");
        return 0;
    }

    activity->status = ACTIVITY_COMPLETED;

    // 保存到文件
    if (!activity_save_to_file()) {
        printf("警告：活动完成成功，但保存到文件失败\n");
    }

    printf("活动已完成！\n");
    return 1;
}

// 取消活动
int activity_cancel(int activity_id) {
    Activity* activity = activity_get_by_id(activity_id);
    if (!activity) {
        printf("错误：活动不存在\n");
        return 0;
    }

    if (activity->status == ACTIVITY_COMPLETED || activity->status == ACTIVITY_CANCELLED) {
        printf("错误：活动已完成或已取消\n");
        return 0;
    }

    activity->status = ACTIVITY_CANCELLED;

    // 保存到文件
    if (!activity_save_to_file()) {
        printf("警告：活动取消成功，但保存到文件失败\n");
    }

    printf("活动已取消！\n");
    return 1;
}

// 检查用户是否已报名
int activity_is_user_signed_up(int activity_id, int user_id) {
    for (int i = 0; i < signup_count; i++) {
        if (signup_records[i][0] == activity_id && signup_records[i][1] == user_id) {
            return 1;
        }
    }
    return 0;
}

// 获取活动参与者列表
int* activity_get_participants(int activity_id, int* count) {
    static int participants[MAX_USERS];
    int participant_count = 0;

    for (int i = 0; i < signup_count; i++) {
        if (signup_records[i][0] == activity_id) {
            participants[participant_count++] = signup_records[i][1];
        }
    }

    *count = participant_count;
    return participants;
}

// 保存活动数据到文件
int activity_save_to_file() {
    return file_save_activities(activities, activity_count) &&
           file_save_signups(signup_records, signup_count);
}

// 从文件加载活动数据
int activity_load_from_file() {
    activity_count = file_load_activities(activities, MAX_ACTIVITIES);
    if (activity_count < 0) {
        activity_count = 0;
        return 0;
    }

    signup_count = file_load_signups(signup_records, MAX_ACTIVITIES * MAX_USERS);
    if (signup_count < 0) {
        signup_count = 0;
        return 0;
    }

    // 更新下一个活动ID
    for (int i = 0; i < activity_count; i++) {
        if (activities[i].id >= next_activity_id) {
            next_activity_id = activities[i].id + 1;
        }
    }

    return 1;
}
