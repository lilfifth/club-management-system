# 🚀 GitHub项目设置指南

本指南将帮助您将智能社团活动与财务管理系统推送到GitHub。

## 📋 前置要求

- 已安装Git
- 有GitHub账户
- 项目已按规范组织

## 🔧 本地Git设置

### 1. 初始化Git仓库

```bash
# 如果还没有初始化
git init

# 添加所有文件
git add .

# 提交初始版本
git commit -m "Initial commit: 智能社团活动与财务管理系统

- 完整的用户、活动、财务管理功能
- 模块化C语言架构
- 跨平台兼容性
- 完善的文档和测试"
```

### 2. 配置Git用户信息

**重要**: 设置您自定义的Git用户信息（这将显示在GitHub提交记录中）

#### 方法1: 使用自动配置脚本 (推荐)

项目提供了自动配置脚本，让设置变得简单：

**Windows批处理脚本**:
```cmd
# 双击运行 setup_git_config.bat 文件
# 或者在命令行中运行:
setup_git_config.bat
```

**PowerShell脚本**:
```powershell
# 在PowerShell中运行:
.\setup_git_config.ps1
```

脚本会自动提示您输入自定义用户名和邮箱，然后完成配置。

#### 方法2: 手动配置

```bash
# 设置自定义用户名（可以是中文、英文或其他您喜欢的名称）
git config --global user.name "您的自定义用户名"

# 设置邮箱（建议使用真实邮箱，方便接收通知）
git config --global user.email "your-email@example.com"

# 或者只为当前项目设置（不影响其他项目）
cd "C:\aaaaaaaaaaaa\智能社团活动与财务管理系统c语言"
git config user.name "您的项目用户名"
git config user.email "your-project-email@example.com"
```

#### 自定义用户名的好处

1. **保护隐私**: 不使用真实姓名
2. **品牌化**: 使用您喜欢的昵称或品牌名
3. **国际化**: 支持中文、emoji等特殊字符
4. **灵活性**: 可以为不同项目使用不同身份

#### 查看当前配置

```bash
# 查看全局配置
git config --global --list

# 查看当前项目配置
git config --list

# 查看用户名
git config user.name
git config user.email
```

#### 修改已有的提交信息

如果已经提交但想要修改作者信息：

```bash
# 修改最后一次提交的作者信息
git commit --amend --author="您的自定义用户名 <your-email@example.com>" --no-edit

# 修改多个提交的作者信息（需要交互式rebase）
git rebase -i HEAD~n  # n是提交数量
# 然后将pick改为edit，保存退出，再执行上面的amend命令

# 强制推送修改后的提交
git push origin main --force
```

### 高级配置选项

#### 1. 为不同项目使用不同身份

```bash
# 在项目目录中设置特定配置
cd "C:\aaaaaaaaaaaa\智能社团活动与财务管理系统c语言"
git config user.name "社团管理系统开发者"
git config user.email "club-system-dev@example.com"
```

#### 2. 使用Git配置文件

创建 `.gitconfig` 文件在项目根目录：

```ini
[user]
    name = 您的自定义用户名
    email = your-email@example.com
```

#### 3. 提交时临时指定作者

```bash
# 单次提交使用指定作者
git commit --author="临时用户名 <temp-email@example.com>" -m "提交信息"

# 或者在rebase时修改
git rebase -i HEAD~1
# 将pick改为edit，然后：
GIT_AUTHOR_NAME="新用户名" GIT_AUTHOR_EMAIL="new-email@example.com" git commit --amend --no-edit
```

#### 4. 使用别名简化操作

在全局Git配置中添加别名：

```bash
git config --global alias.amend-author 'commit --amend --author'
```

然后使用：
```bash
git amend-author "您的用户名 <your-email@example.com>" --no-edit
```

### GitHub显示设置

推送到GitHub后，您还可以在GitHub上进一步自定义显示：

1. **GitHub用户名**: 在GitHub设置中可以设置显示名称
2. **头像**: 上传自定义头像
3. **个人资料**: 添加自我介绍
4. **邮箱隐私**: 设置提交邮箱的显示方式

### 注意事项

- ⚠️ **提交历史**: 一旦推送到GitHub，更改作者信息需要强制推送
- 🔒 **邮箱验证**: 建议使用真实邮箱以接收GitHub通知
- 🌍 **字符编码**: GitHub支持Unicode字符，可以使用中文用户名
- 🔄 **同步更新**: 如果更改了用户信息，记得更新所有相关配置

### 常见问题解决

#### Q: 推送时显示错误的用户名？
A: 检查本地Git配置：`git config user.name`

#### Q: GitHub上显示的不是我设置的用户名？
A: 可能是邮箱没有验证，或者GitHub缓存了旧信息

#### Q: 如何在不同电脑上保持相同配置？
A: 使用相同的Git配置命令，或导入配置文件

#### Q: 可以使用emoji作为用户名吗？
A: GitHub支持emoji，但建议在专业项目中使用合适的名称

## 🌐 GitHub仓库创建

### 方法1: GitHub网页创建

1. 访问 [GitHub.com](https://github.com)
2. 点击右上角 "+" → "New repository"
3. 填写信息：
   - **Repository name**: `club-management-system` 或 `智能社团管理系统`
   - **Description**: `基于C语言的智能社团活动与财务管理系统，提供完整的社团管理功能`
   - **Visibility**: 选择 `Public` (公开) 或 `Private` (私有)
4. **不要**勾选 "Add a README file" 等选项
5. 点击 "Create repository"

### 方法2: GitHub CLI (推荐)

```bash
# 安装GitHub CLI (如果还没有)
# Windows: winget install --id GitHub.cli
# macOS: brew install gh
# Ubuntu: curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg | sudo dd of=/usr/share/keyrings/githubcli-archive-keyring.gpg
#         echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | sudo tee /etc/apt/sources.list.d/github-cli.list > /dev/null
#         sudo apt update && sudo apt install gh

# 登录GitHub
gh auth login

# 创建仓库
gh repo create club-management-system --public --description "基于C语言的智能社团活动与财务管理系统"
```

## 📤 推送代码到GitHub

### 1. 添加远程仓库

```bash
# 使用HTTPS (推荐新手)
git remote add origin https://github.com/您的用户名/club-management-system.git

# 或者使用SSH (需要配置SSH密钥)
git remote add origin git@github.com:您的用户名/club-management-system.git
```

### 2. 推送代码

```bash
# 推送主分支
git branch -M main
git push -u origin main
```

## 🎨 项目展示优化

### 1. 添加GitHub徽章

在README.md顶部添加：

```markdown
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C](https://img.shields.io/badge/C-99-blue.svg)](https://en.wikipedia.org/wiki/C99)
[![Build Status](https://img.shields.io/github/actions/workflow/status/your-username/club-management-system/ci.yml)](https://github.com/your-username/club-management-system/actions)
```

### 2. 设置项目主题

在仓库设置中：
- **About**: 添加项目描述和主题标签
- **Topics**: 添加 `c`, `management-system`, `club-management`, `finance`, `console-application`

### 3. 创建发布版本

```bash
# 创建标签
git tag -a v1.0 -m "Release version 1.0 - 功能完善版"

# 推送标签
git push origin v1.0

# 使用GitHub CLI创建发布
gh release create v1.0 --title "Release v1.0" --notes "功能完善版发布

## 新功能
- 完整的用户管理功能
- 活动发布与报名系统
- 财务收支管理
- 统计分析报告
- 跨平台兼容性"
```

## 🔄 后续维护

### 1. 定期更新

```bash
# 拉取最新更改
git pull origin main

# 创建新功能分支
git checkout -b feature/new-feature

# 提交更改
git add .
git commit -m "feat: 添加新功能"
git push origin feature/new-feature

# 创建Pull Request
gh pr create --title "添加新功能" --body "详细描述新功能"
```

### 2. 问题管理

- 使用GitHub Issues跟踪bug和功能请求
- 使用Projects管理开发进度
- 使用Discussions进行社区讨论

### 3. CI/CD监控

- 查看Actions标签页监控自动构建
- 设置分支保护规则
- 配置自动发布

## 📊 项目统计

推送成功后，您可以查看：

- **Traffic**: 访问统计
- **Commits**: 提交历史
- **Contributors**: 贡献者统计
- **Languages**: 代码语言占比 (主要为C)
- **Stars/Forks**: 项目受欢迎程度

## 🎯 最佳实践

### 项目命名
- 使用英文仓库名: `club-management-system`
- 中文描述可以放在README中

### 分支策略
- `main`: 稳定版本
- `develop`: 开发版本
- `feature/*`: 功能分支
- `hotfix/*`: 紧急修复

### 提交规范
```
feat: 新功能
fix: 修复bug
docs: 文档更新
style: 代码格式
refactor: 代码重构
test: 测试相关
chore: 构建工具
```

### 版本号
使用语义化版本: `MAJOR.MINOR.PATCH`
- `1.0.0`: 初始版本
- `1.1.0`: 新功能
- `1.0.1`: 修复bug

## 🆘 常见问题

### 推送失败
```bash
# 检查远程仓库
git remote -v

# 重新设置远程仓库
git remote set-url origin https://github.com/您的用户名/club-management-system.git

# 强制推送 (谨慎使用)
git push -u origin main --force
```

### 权限问题
```bash
# 检查GitHub权限
gh auth status

# 重新登录
gh auth login
```

### 分支同步
```bash
# 从远程同步分支
git fetch origin
git checkout main
git merge origin/main
```

## 📞 获取帮助

- **GitHub Docs**: https://docs.github.com/
- **GitHub CLI**: https://cli.github.com/
- **Git文档**: https://git-scm.com/doc

---

🎉 恭喜！您的项目现在已经成功推送到GitHub！

记得：
1. ⭐ 给自己项目点个星
2. 📖 完善README文档
3. 🐛 使用Issues管理问题
4. 🤝 欢迎其他开发者贡献
