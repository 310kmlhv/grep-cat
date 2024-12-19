#!/bin/bash

# Устанавливаем счетчики для успешных и неуспешных тестов
success_count=0
fail_count=0
total_tests=0

# Функция для создания тестового файла
create_test_file() {
    cat << EOF > test_file.txt
This is a test file.
It contains multiple lines.
Some lines contain the word test.
Test is used for testing purposes.
The word test is present in different cases, like Test, TEST, etc.
EOF
}

# Функция для удаления тестового файла
cleanup_test_file() {
    rm -f test_file.txt
}

# Функция для запуска теста
run_test() {
    local description="$1"
    local test_cmd="$2"
    local expected_cmd="$3"
    
    total_tests=$((total_tests + 1))

    # Создаем тестовый файл
    create_test_file

    # Запуск оригинального cat
    echo "Тест: $description"
    echo "Команда: $test_cmd"
    
    # Получаем результаты от оригинального cat и тестируемой программы
    original_output=$(eval "$expected_cmd")
    test_output=$(eval "$test_cmd")
    
    # Сравнение результатов
    if [ "$original_output" == "$test_output" ]; then
        echo "РЕЗУЛЬТАТ: УСПЕШНО"
        success_count=$((success_count + 1))
    else
        echo "РЕЗУЛЬТАТ: НЕ УСПЕШНО"
        fail_count=$((fail_count + 1))
        echo "Ожидаемый результат:"
        echo "$original_output"
        echo "Ваш вывод:"
        echo "$test_output"
    fi
    echo ""

    # Удаляем тестовый файл
    cleanup_test_file
}

# Тестирование с флагами
run_test "Тест с флагом -b" \
    "./s21_cat -b test_file.txt" \
    "cat -b test_file.txt"

run_test "Тест с флагом -e" \
    "./s21_cat -e test_file.txt" \
    "cat -e test_file.txt"

run_test "Тест с флагом -n" \
    "./s21_cat -n test_file.txt" \
    "cat -n test_file.txt"

run_test "Тест с флагом -s" \
    "./s21_cat -s test_file.txt" \
    "cat -s test_file.txt"

run_test "Тест с флагом -t" \
    "./s21_cat -t test_file.txt" \
    "cat -t test_file.txt"

run_test "Тест с флагом -b -e" \
    "./s21_cat -b -e test_file.txt" \
    "cat -b -e test_file.txt"

run_test "Тест с флагом -b -n" \
    "./s21_cat -b -n test_file.txt" \
    "cat -b -n test_file.txt"

run_test "Тест с флагом -b -s" \
    "./s21_cat -b -s test_file.txt" \
    "cat -b -s test_file.txt"

run_test "Тест с флагом -b -t" \
    "./s21_cat -b -t test_file.txt" \
    "cat -b -t test_file.txt"

run_test "Тест с флагом -e -n" \
    "./s21_cat -e -n test_file.txt" \
    "cat -e -n test_file.txt"

run_test "Тест с флагом -e -s" \
    "./s21_cat -e -s test_file.txt" \
    "cat -e -s test_file.txt"

run_test "Тест с флагом -e -t" \
    "./s21_cat -e -t test_file.txt" \
    "cat -e -t test_file.txt"

run_test "Тест с флагом -n -s" \
    "./s21_cat -n -s test_file.txt" \
    "cat -n -s test_file.txt"

run_test "Тест с флагом -n -t" \
    "./s21_cat -n -t test_file.txt" \
    "cat -n -t test_file.txt"

run_test "Тест с флагом -s -t" \
    "./s21_cat -s -t test_file.txt" \
    "cat -s -t test_file.txt"

# Итоги
echo "Итоги:"
echo "Успешных тестов: $success_count"
echo "Неуспешных тестов: $fail_count"
echo "Общее количество тестов: $total_tests"

if [ "$fail_count" -eq 0 ]; then
    echo "Все тесты прошли успешно!"
else
    echo "Некоторые тесты не прошли!"
fi
