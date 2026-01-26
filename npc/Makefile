TOPNAME = top
VERILATOR = verilator
VERILATOR_CFLAGS += -MMD --build -cc  \
				-O3 --x-assign fast --x-initial fast --noassert --trace

BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)
VSRCS = $(shell find ./vsrc -name "*.v")
CSRCS = $(shell find ./csrc -name "*.cpp")

default: $(BIN)

$(BIN): vsrc/top.v csrc/main.cpp
	@mkdir -p $(BUILD_DIR)
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		--top-module $(TOPNAME) \
		--exe \
		-o $(abspath $(BIN)) \
		$(VSRCS) $(CSRCS)

run: $(BIN)
	$(BIN)

clean:
	rm -rf $(BUILD_DIR)

include ../Makefile
