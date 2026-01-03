# 智能社团管理系统 - Git配置设置脚本
# 使用PowerShell设置自定义的Git用户名和邮箱

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "   智能社团管理系统 - Git配置设置" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "这个脚本将帮助您设置自定义的Git用户名和邮箱" -ForegroundColor Yellow
Write-Host "用于推送到GitHub的项目提交信息" -ForegroundColor Yellow
Write-Host ""

# 获取用户输入
$gitName = Read-Host "请输入您的自定义用户名 (例如: 社团管理系统开发者)"
$gitEmail = Read-Host "请输入您的邮箱地址"

Write-Host ""
Write-Host "正在设置Git配置..." -ForegroundColor Green
Write-Host ""

try {
    # 设置Git配置
    git config --global user.name "$gitName"
    git config --global user.email "$gitEmail"

    Write-Host "Git全局配置已设置完成！" -ForegroundColor Green
    Write-Host ""
    Write-Host "用户名: $gitName" -ForegroundColor White
    Write-Host "邮箱: $gitEmail" -ForegroundColor White
    Write-Host ""

    # 验证配置
    Write-Host "验证配置..." -ForegroundColor Yellow
    git config --global user.name
    git config --global user.email

    Write-Host ""
    Write-Host "========================================" -ForegroundColor Cyan
    Write-Host "配置完成！现在您可以推送代码到GitHub了" -ForegroundColor Green
    Write-Host "========================================" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "下一步操作:" -ForegroundColor Yellow
    Write-Host "1. 运行: git add ." -ForegroundColor White
    Write-Host "2. 运行: git commit -m 'Initial commit'" -ForegroundColor White
    Write-Host "3. 运行: git remote add origin https://github.com/您的用户名/club-management-system.git" -ForegroundColor White
    Write-Host "4. 运行: git push -u origin main" -ForegroundColor White
    Write-Host ""
    Write-Host "按任意键继续..." -ForegroundColor Gray
    $null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
}
catch {
    Write-Host "设置过程中出现错误: $($_.Exception.Message)" -ForegroundColor Red
    Write-Host "请手动运行以下命令:" -ForegroundColor Yellow
    Write-Host "git config --global user.name '$gitName'" -ForegroundColor White
    Write-Host "git config --global user.email '$gitEmail'" -ForegroundColor White
    Write-Host ""
    Write-Host "按任意键退出..." -ForegroundColor Gray
    $null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
}
