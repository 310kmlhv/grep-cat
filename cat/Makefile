# Переменные
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
EXE = s21_cat
TEST_SCRIPT = test_cat.sh

# Исходные файлы
SRC = s21_cat.c  # Укажите все необходимые исходные файлы

# Цели

# Главная цель: компиляция программы
all: $(EXE)

$(EXE): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(EXE)

# Запуск тестов
test: $(EXE)
	@chmod +x $(TEST_SCRIPT)
	@./$(TEST_SCRIPT)

# Очистка скомпилированных файлов
clean:
	rm -f $(EXE)

# Удаление тестов (опционально, если у вас есть другие временные файлы)
clean_tests:
	rm -f test_file.txt

# Перекомпиляция проекта
rebuild: clean all

# Флаг по умолчанию
.PHONY: all clean test clean_tests rebuild
