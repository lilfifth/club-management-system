#include "common.h"
#include "user.h"
#include "activity.h"
#include "finance.h"
#include "statistics.h"
#include "file_utils.h"
#include <assert.h>

// 基本功能测试
void test_user_management() {
    printf("测试用户管理模块...\n");

    // 测试用户注册
    int user_id1 = user_register("testuser1", "password123", "张三", "zhangsan@example.com");
    assert(user_id1 > 0);

    int user_id2 = user_register("testuser2", "password456", "李四", "lisi@example.com");
    assert(user_id2 > 0);

    // 测试用户登录
    assert(user_login("testuser1", "password123"));
    assert(!user_login("testuser1", "wrongpassword"));

    // 测试用户信息查询
    User* user = user_get_by_username("testuser1");
    assert(user != NULL);
    assert(strcmp(user->name, "张三") == 0);

    printf("? 用户管理模块测试通过\n");
}

void test_activity_management() {
    printf("测试活动管理模块...\n");

    // 先登录管理员用户（假设已存在）
    assert(user_login("testuser1", "password123"));

    // 测试活动创建
    time_t start_time = time(NULL) + 86400; // 明天
    time_t end_time = start_time + 7200; // 2小时后

    int activity_id = activity_create("测试活动", "这是一个测试活动",
                                    "张三", start_time, end_time,
                                    "会议室A", 50);
    assert(activity_id > 0);

    // 测试活动查询
    Activity* activity = activity_get_by_id(activity_id);
    assert(activity != NULL);
    assert(strcmp(activity->title, "测试活动") == 0);

    // 测试活动报名
    assert(activity_signup(activity_id, 1)); // 假设用户ID为1

    printf("? 活动管理模块测试通过\n");
}

void test_finance_management() {
    printf("测试财务管理模块...\n");

    // 测试财务记录添加
    int record_id1 = finance_add_record("活动经费", 1000.0, FINANCE_INCOME,
                                       "活动收入", "张三");
    assert(record_id1 > 0);

    int record_id2 = finance_add_record("活动物资", 200.0, FINANCE_EXPENSE,
                                       "办公用品", "张三");
    assert(record_id2 > 0);

    // 测试财务统计
    int count;
    FinanceRecord* records = finance_get_records(&count);
    assert(count >= 2);

    printf("? 财务管理模块测试通过\n");
}

void test_statistics() {
    printf("测试统计模块...\n");

    Statistics stats = get_system_statistics();
    assert(stats.total_users >= 2);
    assert(stats.total_activities >= 1);
    assert(stats.total_income >= 1000.0);

    printf("? 统计模块测试通过\n");
}

void test_file_operations() {
    printf("测试文件操作...\n");

    // 测试数据保存
    assert(user_save_to_file());
    assert(activity_save_to_file());
    assert(finance_save_to_file());

    // 清理内存中的数据
    // 实际测试中可能需要重新加载验证

    printf("? 文件操作测试通过\n");
}

int main() {
    printf("开始智能社团管理系统功能测试...\n\n");

    // 初始化数据
    user_load_from_file();
    activity_load_from_file();
    finance_load_from_file();

    // 运行测试
    test_user_management();
    test_activity_management();
    test_finance_management();
    test_statistics();
    test_file_operations();

    printf("\n所有测试通过！?\n");
    printf("系统基本功能正常。\n");

    return 0;
}
