#ifndef USER_H
#define USER_H

#include "common.h"

// 用户管理函数声明

// 用户注册
int user_register(const char* username, const char* password,
                  const char* name, const char* email);

// 用户登录
int user_login(const char* username, const char* password);

// 修改用户信息
int user_update_info(int user_id, const char* name, const char* email);

// 查询用户信息
User* user_get_by_id(int user_id);
User* user_get_by_username(const char* username);
void user_display_info(const User* user);

// 获取所有用户列表
User* user_get_all(int* count);

// 删除用户（软删除）
int user_delete(int user_id);

// 密码修改
int user_change_password(int user_id, const char* old_password,
                        const char* new_password);

// 用户数据文件操作
int user_save_to_file();
int user_load_from_file();

#endif // USER_H
