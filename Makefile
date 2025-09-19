# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c17 -DDEBUG -I$(INCLUDE_DIR)

# Цвета для вывода
GREEN := \033[0;32m
YELLOW := \033[1;33m
BLUE := \033[1;34m
RED := \033[0;31m
RESET := \033[0m

# Директории
INCLUDE_DIR = ./include
SRC_DIR = ./src
TEST_DIR = ./tests
BUILD_DIR = ./build
DIST_DIR = ./dist
BUILD_SRC_DIR = $(BUILD_DIR)/src
BUILD_TEST_DIR = $(BUILD_DIR)/tests
DIST_LIB_DIR = $(DIST_DIR)/lib
DIST_INCLUDE_DIR = $(DIST_DIR)/matrix

# Файлы
LIB_SRC := $(shell find $(SRC_DIR) -name "*.c")
TEST_SRC := $(shell find $(TEST_DIR) -name "*.c" ! -name "*_runner*")
TEST_RUNNER_SRC :=  $(TEST_DIR)/test_runner.c

LIB_OBJ := $(patsubst $(SRC_DIR)/%.c,$(BUILD_SRC_DIR)/%.o,$(LIB_SRC))
TEST_OBJ := $(patsubst $(TEST_DIR)/%.c,$(BUILD_TEST_DIR)/%.o,$(TEST_SRC))
TEST_RUNNER_OBJ := $(patsubst $(TEST_DIR)/%.c,$(BUILD_TEST_DIR)/%.o,$(TEST_RUNNER_SRC))

LIB_NAME = matrix
STATIC_LIB = $(DIST_LIB_DIR)/lib$(LIB_NAME).a
TEST_TARGET = $(BUILD_DIR)/MatrixLibTest

# Основные цели
all: create-dirs $(STATIC_LIB) install-headers
	@printf "$(GREEN)✅ Библиотека собрана успешно!$(RESET)\n"

install: create-dirs $(STATIC_LIB) install-headers
	@printf "$(GREEN)📦 Установка завершена!$(RESET)\n"

rebuild: clean all

create-dirs: $(BUILD_DIR) $(DIST_LIB_DIR) $(DIST_INCLUDE_DIR)

$(BUILD_DIR):
	@printf "$(BLUE)📂 Создание директории $@$(RESET)\n"
	@mkdir -p $@

$(DIST_LIB_DIR):
	@printf "$(BLUE)📂 Создание директории $@$(RESET)\n"
	@mkdir -p $@

$(DIST_INCLUDE_DIR):
	@printf "$(BLUE)📂 Создание директории $@$(RESET)\n"
	@mkdir -p $@

$(BUILD_SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@printf "$(YELLOW)⚙️  Компиляция: $<$(RESET)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_TEST_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(@D)
	@printf "$(YELLOW)⚙️  Компиляция теста: $<$(RESET)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

$(STATIC_LIB): $(LIB_OBJ) | create-dirs
	@printf "$(BLUE)📦 Архивация библиотеки: $@$(RESET)\n"
	@ar rcs $@ $^

install-headers: | $(DIST_INCLUDE_DIR)
	@printf "$(BLUE)📑 Копирование заголовков$(RESET)\n"
	@cp -r $(INCLUDE_DIR)/* $(DIST_INCLUDE_DIR)/

test: $(TEST_TARGET)
	@printf "$(BLUE)🚀 Запуск тестов...$(RESET)\n"
	@./$(TEST_TARGET)

$(TEST_TARGET): $(STATIC_LIB) $(TEST_OBJ) $(TEST_RUNNER_OBJ)
	@printf "$(BLUE)🔗 Компоновка тестов$(RESET)\n"
	@$(CC) $(CFLAGS) $(TEST_OBJ) $(TEST_RUNNER_OBJ) -L$(DIST_LIB_DIR) -l$(LIB_NAME) -lcunit -o $@
	@printf "$(GREEN)✅ Тесты собраны: $(TEST_TARGET)$(RESET)\n"

clean:
	@printf "$(RED)🧹 Очистка сборки...$(RESET)\n"
	@rm -rf $(BUILD_DIR) $(DIST_DIR)

clang-check:
	@printf "$(BLUE)🔍 Проверка стиля кода...$(RESET)\n"
	@find "./" -name '*.c' -o -name '*.h' | \
	xargs clang-format --style=file --dry-run -Werror

clang-format:
	@printf "$(BLUE)✍️  Переформатирование кода...$(RESET)\n"
	@find "./" -name '*.c' -o -name '*.h' | \
	xargs clan
 
