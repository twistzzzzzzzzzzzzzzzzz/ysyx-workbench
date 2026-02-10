TOPNAME = top
NPC_HOME = $(abspath .)
NEMU_HOME = $(abspath ../nemu)
AM_HOME = $(abspath ../abstract-machine)

-include $(NPC_HOME)/include/config/auto.conf
-include $(NPC_HOME)/include/config/auto.conf.cmd



#TEST_NAME ?= dummy


IMG ?= $(AM_HOME)/tests/cpu-tests/build/$(NAME)-riscv32e-npc.bin
ELF ?= $(NAME).elf
DIFF_REF_SO = $(NEMU_HOME)/build/riscv32-nemu-interpreter-so


VERILATOR = verilator
VERILATOR_CFLAGS += -MMD --build -cc\
				-O3 --x-assign fast --x-initial fast --noassert \
				-I$(NPC_HOME)/build/config

ifeq ($(CONFIG_WAVE),y)
$(info DEBUG: CONFIG_WAVE is [$(CONFIG_WAVE)])
VERILATOR_CFLAGS +=   --trace
endif

BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)


VSRCS = $(shell find ./vsrc -name "*.v")
CSRCS = $(shell find ./csrc -name "*.cpp")
LDFLAGS += -lreadline -ldl -lSDL2

default: $(BIN)

$(BIN): $(VSRCS) $(CSRCS) $(NPC_HOME)/include/config/auto.conf
	@mkdir -p $(BUILD_DIR)
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		--top-module $(TOPNAME) \
		--exe \
		-o $(abspath $@) \
		-LDFLAGS "$(LDFLAGS)" \
		$(VSRCS) $(CSRCS)


run: $(BIN)
	$(BIN) $(IMG) $(DIFF_REF_SO) $(ELF)
clean:
	rm -rf $(BUILD_DIR)

include script/config.mk
