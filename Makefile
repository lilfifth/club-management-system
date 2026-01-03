# 智能社团活动与财务管理系统 - Makefile

# 编译器设置
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Isrc -Iinclude
LDFLAGS =

# 可执行文件名
TARGET = club_system

# 源文件目录
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# 源文件
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/user.c $(SRC_DIR)/activity.c $(SRC_DIR)/utils.c $(SRC_DIR)/file_utils.c $(SRC_DIR)/finance.c $(SRC_DIR)/statistics.c

# 目标文件
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# 头文件
HEADERS = $(INC_DIR)/common.h $(INC_DIR)/user.h $(INC_DIR)/activity.h $(INC_DIR)/finance.h $(INC_DIR)/statistics.h $(INC_DIR)/file_utils.h

# 默认目标
all: $(BUILD_DIR) $(TARGET)

# 创建构建目录
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# 生成可执行文件
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(TARGET)
	@echo "编译完成！可执行文件: $(TARGET)"

# 编译源文件为目标文件
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# 清理编译文件
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
	@echo "清理完成"

# 重新编译
rebuild: clean all

# 运行程序
run: $(TARGET)
	./$(TARGET)

# 调试编译（包含调试信息）
debug: CFLAGS += -g -DDEBUG
debug: clean all

# Windows 兼容性
.PHONY: windows
windows: CC = x86_64-w64-mingw32-gcc
windows: TARGET = club_system.exe
windows: all

# 安装（复制可执行文件到系统路径）
.PHONY: install
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/
	@echo "安装完成"

# 卸载
.PHONY: uninstall
uninstall:
	rm -f /usr/local/bin/$(TARGET)
	@echo "卸载完成"

# 帮助信息
.PHONY: help
help:
	@echo "智能社团管理系统 - 编译选项"
	@echo "  all       - 编译所有文件"
	@echo "  clean     - 清理编译文件"
	@echo "  rebuild   - 重新编译"
	@echo "  run       - 编译并运行程序"
	@echo "  debug     - 调试模式编译"
	@echo "  windows   - 交叉编译 Windows 版本"
	@echo "  install   - 安装到系统"
	@echo "  uninstall - 从系统卸载"
	@echo "  help      - 显示此帮助信息"

# 显示项目信息
.PHONY: info
info:
	@echo "项目名称: 智能社团活动与财务管理系统"
	@echo "版本: v1.0"
	@echo "作者: 开发团队"
	@echo "编译器: $(CC)"
	@echo "源文件: $(SRCS)"
	@echo "头文件: $(HEADERS)"
