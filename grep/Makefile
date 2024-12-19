CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic
S21_GREP = s21_grep
S21_TEST = test_grep.sh

# Исходники
SRC = s21_grep.c
OBJ = $(SRC:.c=.o)

# Компиляция
$(S21_GREP): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(S21_GREP)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

# Очистка объектов и исполнимого файла
clean:
	rm -f $(OBJ) $(S21_GREP)

# Запуск тестов
test: $(S21_GREP)
	chmod +x $(S21_TEST)
	./$(S21_TEST)

# Для компиляции и запуска тестов
all: $(S21_GREP)

rebuild: clean $(S21_GREP)
