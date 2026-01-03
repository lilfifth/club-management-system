# 🏫 智能社团活动与财务管理系统

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C](https://img.shields.io/badge/C-99-blue.svg)](https://en.wikipedia.org/wiki/C99)
[![Build Status](https://img.shields.io/github/actions/workflow/status/lilfifth/club-management-system/ci.yml)](https://github.com/lilfifth/club-management-system/actions)

一个功能完整的C语言社团活动与财务管理系统，提供用户管理、活动管理、财务管理、统计分析等全方位功能。

## ✨ 功能特性

### 👥 用户管理
- 🔐 用户注册与登录
- 👤 个人信息管理
- 🔑 密码修改
- 📋 用户查询

### 📅 活动管理
- 📝 活动发布与编辑
- 🎯 活动报名系统
- 🔍 活动搜索查询
- 📊 参与统计

### 💰 财务管理
- 💸 收支记录管理
- 📈 财务报表生成
- 📊 财务统计分析
- 📤 数据导出

### 📈 统计分析
- 👥 用户参与度分析
- 🔥 活动热度排行
- 💹 财务趋势分析
- 📋 综合报告

## 🏗️ 项目结构

```
club-management-system/
├── src/                    # 源代码目录
│   ├── main.c             # 主程序入口
│   ├── user.c             # 用户管理模块
│   ├── activity.c         # 活动管理模块
│   ├── finance.c          # 财务管理模块
│   ├── statistics.c       # 统计分析模块
│   ├── file_utils.c       # 文件操作模块
│   └── utils.c            # 工具函数
├── include/               # 头文件目录
│   ├── common.h           # 公共定义和结构体
│   ├── user.h             # 用户管理接口
│   ├── activity.h         # 活动管理接口
│   ├── finance.h          # 财务管理接口
│   ├── statistics.h       # 统计分析接口
│   └── file_utils.h       # 文件操作接口
├── tests/                 # 测试目录
│   └── test_basic_functionality.c
├── docs/                  # 文档目录
│   ├── 项目总结报告.md    # 项目总结
│   └── 功能完善报告.md    # 功能完善报告
├── build/                 # 构建输出目录
├── .gitignore            # Git忽略文件
├── LICENSE               # MIT许可证
├── Makefile              # 构建脚本
└── README.md             # 项目说明
```

## 🚀 快速开始

### 环境要求

- **编译器**: GCC 6.0+ 或兼容的C99编译器
- **操作系统**: Windows / Linux / macOS
- **构建工具**: Make

### 编译安装

```bash
# 克隆项目
git clone https://github.com/lilfifth/club-management-system.git
cd club-management-system

# 编译项目
make

# 或者编译Windows版本
make windows

# 运行程序
./club_system
```

### 测试运行

```bash
# 运行单元测试
make test

# 清理构建文件
make clean
```

## 📖 使用指南

### 首次运行
1. 运行程序后选择"用户注册"创建管理员账户
2. 使用注册的账户登录系统
3. 开始管理社团活动和财务

### 主要功能
- **用户菜单**: 个人信息管理、活动参与、财务查看
- **管理员菜单**: 用户管理、活动管理、财务管理、系统统计

### 数据文件
程序运行时会在当前目录生成以下数据文件：
- `users.txt` - 用户数据
- `activities.txt` - 活动数据
- `finance.txt` - 财务数据
- `signups.txt` - 报名记录

## 🛠️ 开发与构建

### 构建选项

```bash
# 标准编译
make

# 调试版本（包含调试信息）
make debug

# Windows交叉编译
make windows

# 清理构建文件
make clean

# 重新编译
make rebuild

# 显示帮助
make help
```

### 项目架构

- **模块化设计**: 每个功能模块独立，便于维护和扩展
- **接口抽象**: 通过头文件提供清晰的API接口
- **错误处理**: 完善的输入验证和异常处理
- **数据持久化**: 文件系统存储，支持数据备份恢复

## 🤝 贡献指南

欢迎提交Issue和Pull Request！

1. Fork 本项目
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 创建 Pull Request

### 开发规范

- 遵循C99标准
- 代码要有详细注释
- 提交前请运行测试
- 保持代码风格一致

## 📋 测试

```bash
# 运行所有测试
make test

# 运行功能测试
./test_program
```

## 📄 许可证

本项目采用 MIT 许可证 - 查看 [LICENSE](LICENSE) 文件了解详情。

## 🙏 致谢

感谢所有为这个项目做出贡献的开发者！

## 📞 联系方式

- 项目维护者: 智能社团管理系统开发团队
- 项目主页: https://github.com/lilfifth/club-management-system

---

⭐ 如果这个项目对你有帮助，请给它一个星标！
