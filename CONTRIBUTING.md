# 🤝 贡献指南

感谢您对智能社团活动与财务管理系统项目的兴趣！我们欢迎各种形式的贡献。

## 📋 贡献前准备

### 开发环境设置

1. **克隆项目**
   ```bash
   git clone https://github.com/your-username/club-management-system.git
   cd club-management-system
   ```

2. **安装依赖**
   - **Windows**: 安装MinGW GCC
   - **Linux**: `sudo apt-get install build-essential gcc`
   - **macOS**: `brew install gcc make`

3. **验证安装**
   ```bash
   make          # 编译项目
   ./club_system # 运行程序
   ```

### 分支管理

- `main`: 主分支，稳定版本
- `develop`: 开发分支，新功能在此合并
- `feature/*`: 功能分支
- `bugfix/*`: 修复分支
- `hotfix/*`: 紧急修复分支

## 🚀 贡献流程

### 1. 选择或创建Issue

- 查看 [Issues](../../issues) 页面
- 选择一个待解决的问题，或创建一个新的Issue
- 如果是新功能，请详细描述需求

### 2. 创建分支

```bash
# 从develop分支创建功能分支
git checkout develop
git pull origin develop
git checkout -b feature/your-feature-name

# 或者修复分支
git checkout -b bugfix/issue-number-description
```

### 3. 编写代码

#### 编码规范

- **语言标准**: 遵循C99标准
- **命名规范**:
  - 函数: `snake_case` (如: `user_register`)
  - 变量: `snake_case` (如: `user_count`)
  - 常量: `UPPER_SNAKE_CASE` (如: `MAX_NAME_LEN`)
  - 结构体: `PascalCase` (如: `User`, `Activity`)

- **代码风格**:
  ```c
  // 函数注释
  /**
   * @brief 函数功能描述
   * @param param1 参数1描述
   * @return 返回值描述
   */
  int function_name(int param1) {
      // 函数实现
      if (condition) {
          // 处理逻辑
      }

      return result;
  }
  ```

- **错误处理**:
  ```c
  if (!validate_input(input)) {
      printf("错误：输入无效！\n");
      return ERROR_CODE;
  }
  ```

### 4. 编写测试

- 在 `tests/` 目录下添加相应的测试文件
- 测试文件名格式: `test_功能名称.c`
- 确保测试覆盖主要功能路径

```c
// tests/test_user_management.c
void test_user_registration() {
    // 测试用户注册功能
    int result = user_register("testuser", "password", "测试用户", "test@example.com");
    assert(result > 0);
}
```

### 5. 提交更改

```bash
# 添加文件
git add .

# 提交更改 (请使用有意义的提交信息)
git commit -m "feat: 添加用户注册功能

- 实现用户注册逻辑
- 添加邮箱格式验证
- 更新用户界面提示

Closes #123"

# 推送到远程分支
git push origin feature/your-feature-name
```

#### 提交信息规范

- `feat:` 新功能
- `fix:` 修复bug
- `docs:` 文档更新
- `style:` 代码格式调整
- `refactor:` 代码重构
- `test:` 测试相关
- `chore:` 构建过程或工具配置

### 6. 创建Pull Request

1. 访问项目 [Pull Requests](../../pulls) 页面
2. 点击 "New pull request"
3. 选择你的分支作为 compare 分支
4. 填写PR描述：
   - 简要说明更改内容
   - 关联相关Issue
   - 说明测试情况
   - 添加截图或演示（如果适用）

### 7. 代码审查

- 等待维护者审查
- 根据反馈修改代码
- 讨论和解决任何问题
- 一旦批准，PR将被合并

## 🧪 测试要求

### 编译测试
```bash
make clean
make
make test
```

### 功能测试
- 所有现有功能正常工作
- 新功能按预期工作
- 边界情况得到正确处理

### 代码质量
- 无编译警告
- 通过静态分析检查
- 代码覆盖率合理

## 📝 文档要求

### 代码注释
- 所有公共函数需要详细注释
- 复杂逻辑需要解释性注释
- 使用Doxygen格式的注释

### README更新
- 如果添加新功能，请更新README.md
- 添加使用示例和截图
- 更新构建和安装说明

## 🐛 报告Bug

### Bug报告模板
```
## Bug描述
简要描述问题

## 复现步骤
1. 执行 '...'
2. 点击 '...'
3. 出现错误

## 预期行为
描述应该发生什么

## 实际行为
描述实际发生了什么

## 环境信息
- OS: [e.g. Windows 10]
- Compiler: [e.g. GCC 9.3.0]
- Version: [e.g. v1.0]

## 附加信息
任何其他相关信息
```

## 💡 功能请求

### 功能请求模板
```
## 功能描述
简要描述新功能

## 需求背景
为什么需要这个功能？

## 实现建议
如何实现这个功能？

## 替代方案
其他可能的解决方案
```

## 📞 联系方式

- **Issues**: [GitHub Issues](../../issues)
- **Discussions**: [GitHub Discussions](../../discussions)
- **Email**: 维护者邮箱

## 🙏 行为准则

- 保持友善和尊重
- 提供建设性的反馈
- 遵循开源社区规范
- 尊重他人的时间和贡献

感谢您的贡献！🎉
