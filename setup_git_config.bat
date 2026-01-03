@echo off
chcp 65001 >nul
title 智能社团管理系统 - Git配置设置

echo ========================================
echo    智能社团管理系统 - Git配置设置
echo ========================================
echo.
echo 这个脚本将帮助您设置自定义的Git用户名和邮箱
echo 用于推送到GitHub的项目提交信息
echo.

set /p git_name="请输入您的自定义用户名 (例如: 社团管理系统开发者): "
set /p git_email="请输入您的邮箱地址: "

echo.
echo 正在设置Git配置...
echo.

REM 设置全局Git配置
git config --global user.name "%git_name%"
git config --global user.email "%git_email%"

echo Git全局配置已设置完成！
echo.
echo 用户名: %git_name%
echo 邮箱: %git_email%
echo.

REM 验证配置
echo 验证配置...
git config --global user.name
git config --global user.email

echo.
echo ========================================
echo 配置完成！现在您可以推送代码到GitHub了
echo ========================================
echo.
echo 下一步操作:
echo 1. 运行: git add .
echo 2. 运行: git commit -m "Initial commit"
echo 3. 运行: git remote add origin https://github.com/您的用户名/club-management-system.git
echo 4. 运行: git push -u origin main
echo.
pause
