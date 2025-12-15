# 默认目标：显示帮助信息
.DEFAULT_GOAL := help

# 定义变量：Verilator编译选项、源文件目录
VERILATOR := verilator
# 生成文件统一放入 build 下 (先定义目录再组装 FLAGS 避免空路径)
BUILD_DIR := ./build
OBJ_DIR := $(BUILD_DIR)/obj_dir
LOG_DIR := $(BUILD_DIR)/logs
VSRC_DIR := ./vsrc
CSRC_DIR := ./csrc
WAVE_FILE := $(LOG_DIR)/wave.fst
VERILATOR_FLAGS := -Wall -I$(VSRC_DIR) --cc --trace-fst --exe --build --Mdir $(OBJ_DIR)

# 帮助信息
help:
	@echo "用法："
	@echo "  make XXX        - 编译vsrc/XXX.v和csrc/XXX_main.cpp（XXX为模块名）"
	@echo "  make wave       - 运行仿真生成wave.fst波形文件"
	@echo "  make clean      - 清理编译产物和波形文件"

# 动态目标规则：匹配所有未定义的目标（即XXX模块）
%:
	@if [ -z "$@" ]; then \
		echo "错误：请指定模块名！例如：make your_module"; \
		exit 1; \
	fi
	@# 检查Verilog源文件是否存在
	@if [ ! -f "$(VSRC_DIR)/$@.v" ]; then \
		echo "错误：Verilog文件 $(VSRC_DIR)/$@.v 不存在！"; \
		exit 1; \
	fi
	@# 检查C++主文件是否存在
	@if [ ! -f "$(CSRC_DIR)/$@_main.cpp" ]; then \
		echo "错误：C++主文件 $(CSRC_DIR)/$@_main.cpp 不存在！"; \
		exit 1; \
	fi
	@echo "正在编译模块：$@"
	@mkdir -p $(OBJ_DIR) $(LOG_DIR)
	WAVE_PATH=$(abspath $(LOG_DIR)/$@_wave.fst); \
	SRC_V=$(abspath $(VSRC_DIR)/$@.v); \
	SRC_CPP=$(abspath $(CSRC_DIR)/$@_main.cpp); \
	SRC_DPI=$(abspath $(CSRC_DIR)/dpi_trap.cpp); \
	$(VERILATOR) $(VERILATOR_FLAGS) -CFLAGS "-DTRACE_FST_PATH=$$WAVE_PATH" $$SRC_V $$SRC_CPP $$SRC_DPI || { echo "Verilator 构建失败"; exit 1; }
	@echo "编译完成！可执行文件：$(OBJ_DIR)/V$@"
	@echo "正在运行：$(OBJ_DIR)/V$@"
	@$(OBJ_DIR)/V$@ || { echo "可执行运行失败"; exit 1; }
	@echo "若启用了跟踪，波形应在：$(LOG_DIR)/$@_wave.fst"

# wave目标：运行仿真（依赖于已编译的可执行文件）
wave:
	@# 只查找obj_dir中以V开头的可执行文件（排除中间编译文件）
	EXE_FILE := $(shell find $(OBJ_DIR) -maxdepth 1 -type f -executable -name "V*")
	@if [ -z "$(EXE_FILE)" ]; then \
		echo "错误：未找到编译产物！请先执行 make XXX 编译模块"; \
		exit 1; \
	fi
	@# 统计可执行文件数量，确保只有一个
	EXE_COUNT := $(shell echo "$(EXE_FILE)" | wc -w)
	@if [ "$(EXE_COUNT)" -ne 1 ]; then \
		echo "错误：找到多个可执行文件，请先清理旧产物（make clean）后重新编译单个模块"; \
		echo "找到的可执行文件：$(EXE_FILE)"; \
		exit 1; \
	fi
	@echo "正在运行仿真：$(EXE_FILE)"
	$(EXE_FILE)
	@if ls $(LOG_DIR)/*_wave.fst 1>/dev/null 2>&1; then \
		echo "波形文件生成成功："; ls -l $(LOG_DIR)/*_wave.fst; \
	else \
		echo "警告：未生成波形文件，请检查仿真代码是否启用了FST跟踪"; \
	fi

# clean目标：清理编译产物和波形文件
clean:
	@echo "正在清理..."
	rm -rf $(OBJ_DIR)
	rm -rf $(LOG_DIR)
	@echo "清理完成！"

# 伪目标声明（避免与同名文件冲突）
.PHONY: help wave clean