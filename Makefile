V = 1
SOURCE_DIR=src
BUILD_DIR=build
FILESYSTEM_DIR=filesystem

all: hello.z64
.PHONY: all

include $(N64_INST)/include/n64.mk

OBJS = $(BUILD_DIR)/main.o

hello.z64: N64_ROM_TITLE = "Hello"
hello.z64: $(BUILD_DIR)/hello.dfs

$(BUILD_DIR)/hello.elf: $(OBJS)
$(BUILD_DIR)/hello.dfs: $(wildcard filesystem/*)

clean:
	rm -f $(BUILD_DIR)/* *.z64
.PHONY: clean

-include $(wildcard $(BUILD_DIR)/*.d)