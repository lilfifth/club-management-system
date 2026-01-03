#ifndef STATISTICS_H
#define STATISTICS_H

#include "common.h"

// 统计信息函数声明

// 获取系统统计信息
Statistics get_system_statistics();

// 显示用户统计
void display_user_statistics();

// 显示活动统计
void display_activity_statistics();

// 显示财务统计
void display_finance_statistics();

// 显示完整统计报告
void display_full_statistics_report();

// 导出统计报告
int export_statistics_report(const char* filename);

// 用户参与度分析
void analyze_user_participation();

// 活动热度分析
void analyze_activity_popularity();

// 财务趋势分析
void analyze_finance_trends();

#endif // STATISTICS_H
