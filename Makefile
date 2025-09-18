CC = gcc
CFLAGS = -Wall -Wextra -g -std=c17 -DDEBUG -I$(INCLUDE_DIR)

INCLUDE_DIR = ./include
SRC_DIR = ./src
TEST_DIR = ./tests
BUILD_DIR = ./build
DIST_DIR = ./dist
BUILD_SRC_DIR = $(BUILD_DIR)/src
BUILD_TEST_DIR = $(BUILD_DIR)/tests
DIST_LIB_DIR = $(DIST_DIR)/lib
DIST_INCLUDE_DIR = $(DIST_DIR)/matrix

LIB_SRC := $(shell find $(SRC_DIR) -name "*.c")
TEST_SRC := $(shell find $(TEST_DIR) -name "*.c" ! -name "*_runner*")
TEST_RUNNER_SRC :=  $(TEST_DIR)/test_runner.c

LIB_OBJ := $(patsubst $(SRC_DIR)/%.c,$(BUILD_SRC_DIR)/%.o,$(LIB_SRC))
TEST_OBJ := $(patsubst $(TEST_DIR)/%.c,$(BUILD_TEST_DIR)/%.o,$(TEST_SRC))
TEST_RUNNER_OBJ := $(patsubst $(TEST_DIR)/%.c,$(BUILD_TEST_DIR)/%.o,$(TEST_RUNNER_SRC))

LIB_NAME = matrix
STATIC_LIB = $(DIST_LIB_DIR)/lib$(LIB_NAME).a
TEST_TARGET = $(BUILD_DIR)/MatrixLibTest

all: create-dirs $(STATIC_LIB) install-headers

install: create-dirs $(STATIC_LIB) install-headers

rebuild: clean all

create-dirs: $(BUILD_DIR) $(DIST_LIB_DIR) $(DIST_INCLUDE_DIR)

$(BUILD_DIR):
	mkdir -p $@

$(DIST_LIB_DIR):
	mkdir -p $@

$(DIST_INCLUDE_DIR):
	mkdir -p $@

$(BUILD_SRC_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_TEST_DIR)/%.o: $(TEST_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(STATIC_LIB): $(LIB_OBJ) | create-dirs
	ar rcs $@ $^

install-headers: | $(DIST_INCLUDE_DIR)
	cp -r $(INCLUDE_DIR)/* $(DIST_INCLUDE_DIR)/

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(STATIC_LIB) $(TEST_OBJ) $(TEST_RUNNER_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) $(TEST_RUNNER_OBJ) -L$(DIST_LIB_DIR) -l$(LIB_NAME) -lcunit -o $@

clean:
	rm -rf $(BUILD_DIR) $(DIST_DIR)

clang-check:
	@echo "Checking code style..."
	@find "./" -name '*.c' -o -name '*.h' | \
	xargs clang-format --style=file --dry-run -Werror

clang-format:
	@echo "Reformatting code..."
	@find "./" -name '*.c' -o -name '*.h' | \
	xargs clang-format --style=file -i -Werror

.PHONY: all rebuild test clean clang-check clang-format install install-headers
