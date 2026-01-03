#include "user.h"
#include "file_utils.h"

// 全局用户数组和计数器
static User users[MAX_USERS];
static int user_count = 0;
static int next_user_id = 1;

// 当前登录用户
User current_user = {0};

// 用户注册
int user_register(const char* username, const char* password,
                  const char* name, const char* email) {
    // 输入验证
    if (!username || !password || !name || !email) {
        printf("错误：所有字段都必须填写\n");
        return 0;
    }

    if (strlen(username) == 0 || strlen(password) == 0 ||
        strlen(name) == 0 || strlen(email) == 0) {
        printf("错误：字段不能为空\n");
        return 0;
    }

    if (!validate_email(email)) {
        printf("错误：邮箱格式无效\n");
        return 0;
    }

    // 检查用户名是否已存在
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && users[i].is_active) {
            printf("错误：用户名已存在\n");
            return 0;
        }
    }

    // 检查用户数组是否已满
    if (user_count >= MAX_USERS) {
        printf("错误：用户数量已达上限\n");
        return 0;
    }

    // 创建新用户
    User new_user;
    new_user.id = next_user_id++;
    strcpy(new_user.username, username);
    strcpy(new_user.password, password);
    strcpy(new_user.name, name);
    strcpy(new_user.email, email);
    new_user.role = ROLE_MEMBER;
    new_user.register_time = time(NULL);
    new_user.is_active = 1;

    users[user_count++] = new_user;

    // 保存到文件
    if (!user_save_to_file()) {
        printf("警告：用户注册成功，但保存到文件失败\n");
    }

    printf("用户注册成功！\n");
    return new_user.id;
}

// 用户登录
int user_login(const char* username, const char* password) {
    if (!username || !password) {
        printf("错误：用户名和密码不能为空\n");
        return 0;
    }

    for (int i = 0; i < user_count; i++) {
        if (users[i].is_active &&
            strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            current_user = users[i];
            printf("登录成功！欢迎 %s\n", current_user.name);
            return 1;
        }
    }

    printf("错误：用户名或密码错误\n");
    return 0;
}

// 修改用户信息
int user_update_info(int user_id, const char* name, const char* email) {
    if (!name || !email) {
        printf("错误：姓名和邮箱不能为空\n");
        return 0;
    }

    if (!validate_email(email)) {
        printf("错误：邮箱格式无效\n");
        return 0;
    }

    for (int i = 0; i < user_count; i++) {
        if (users[i].id == user_id && users[i].is_active) {
            strcpy(users[i].name, name);
            strcpy(users[i].email, email);

            // 保存到文件
            if (!user_save_to_file()) {
                printf("警告：信息更新成功，但保存到文件失败\n");
            }

            printf("用户信息更新成功！\n");
            return 1;
        }
    }

    printf("错误：用户不存在\n");
    return 0;
}

// 根据ID获取用户
User* user_get_by_id(int user_id) {
    for (int i = 0; i < user_count; i++) {
        if (users[i].id == user_id && users[i].is_active) {
            return &users[i];
        }
    }
    return NULL;
}

// 根据用户名获取用户
User* user_get_by_username(const char* username) {
    for (int i = 0; i < user_count; i++) {
        if (users[i].is_active && strcmp(users[i].username, username) == 0) {
            return &users[i];
        }
    }
    return NULL;
}

// 显示用户信息
void user_display_info(const User* user) {
    if (!user) {
        printf("用户信息不存在\n");
        return;
    }

    printf("\n=== 用户信息 ===\n");
    printf("ID: %d\n", user->id);
    printf("用户名: %s\n", user->username);
    printf("姓名: %s\n", user->name);
    printf("邮箱: %s\n", user->email);
    printf("角色: %s\n", user->role == ROLE_ADMIN ? "管理员" : "普通成员");
    printf("注册时间: %s\n", format_time(user->register_time));
    printf("================\n");
}

// 获取所有用户
User* user_get_all(int* count) {
    *count = user_count;
    return users;
}

// 删除用户（软删除）
int user_delete(int user_id) {
    for (int i = 0; i < user_count; i++) {
        if (users[i].id == user_id && users[i].is_active) {
            users[i].is_active = 0;

            // 保存到文件
            if (!user_save_to_file()) {
                printf("警告：用户删除成功，但保存到文件失败\n");
            }

            printf("用户删除成功！\n");
            return 1;
        }
    }

    printf("错误：用户不存在\n");
    return 0;
}

// 修改密码
int user_change_password(int user_id, const char* old_password,
                        const char* new_password) {
    if (!old_password || !new_password) {
        printf("错误：密码不能为空\n");
        return 0;
    }

    if (strlen(new_password) == 0) {
        printf("错误：新密码不能为空\n");
        return 0;
    }

    for (int i = 0; i < user_count; i++) {
        if (users[i].id == user_id && users[i].is_active) {
            if (strcmp(users[i].password, old_password) != 0) {
                printf("错误：原密码错误\n");
                return 0;
            }

            strcpy(users[i].password, new_password);

            // 保存到文件
            if (!user_save_to_file()) {
                printf("警告：密码修改成功，但保存到文件失败\n");
            }

            printf("密码修改成功！\n");
            return 1;
        }
    }

    printf("错误：用户不存在\n");
    return 0;
}

// 保存用户数据到文件
int user_save_to_file() {
    return file_save_users(users, user_count);
}

// 从文件加载用户数据
int user_load_from_file() {
    user_count = file_load_users(users, MAX_USERS);
    if (user_count < 0) {
        user_count = 0;
        return 0;
    }

    // 更新下一个用户ID
    for (int i = 0; i < user_count; i++) {
        if (users[i].id >= next_user_id) {
            next_user_id = users[i].id + 1;
        }
    }

    return 1;
}
