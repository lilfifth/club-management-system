#ifndef ACTIVITY_H
#define ACTIVITY_H

#include "common.h"

// 活动管理函数声明

// 发布活动
int activity_create(const char* title, const char* description,
                   const char* organizer, time_t start_time, time_t end_time,
                   const char* location, int max_participants);

// 活动报名
int activity_signup(int activity_id, int user_id);

// 取消报名
int activity_cancel_signup(int activity_id, int user_id);

// 查询活动
Activity* activity_get_by_id(int activity_id);
Activity* activity_get_all(int* count);

// 按状态查询活动
Activity* activity_get_by_status(int status, int* count);

// 搜索活动（按标题或描述）
Activity* activity_search(const char* keyword, int* count);

// 显示活动信息
void activity_display_info(const Activity* activity);
void activity_display_list(Activity* activities, int count);

// 删除活动
int activity_delete(int activity_id);

// 更新活动信息
int activity_update(int activity_id, const char* title, const char* description,
                   time_t start_time, time_t end_time, const char* location,
                   int max_participants);

// 完成活动
int activity_complete(int activity_id);

// 取消活动
int activity_cancel(int activity_id);

// 检查用户是否已报名
int activity_is_user_signed_up(int activity_id, int user_id);

// 获取活动参与者列表
int* activity_get_participants(int activity_id, int* count);

// 活动数据文件操作
int activity_save_to_file();
int activity_load_from_file();

#endif // ACTIVITY_H
