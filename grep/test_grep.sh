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

create_test_file_2() {
    cat << EOF > test2_file.txt
Another test file.
This file contains some different lines.
test is here too.
test should be tested in both files.
EOF
}

# Функция для удаления тестового файла
cleanup_test_file() {
    rm -f test_file.txt test2_file.txt
}

# Функция для запуска теста
run_test() {
    local description="$1"
    local test_cmd="$2"
    local expected_cmd="$3"
    
    total_tests=$((total_tests + 1))

    # Создаем тестовые файлы
    create_test_file
    create_test_file_2

    # Запуск оригинального grep
    echo "Тест: $description"
    echo "Команда: $test_cmd"
    
    # Получаем результаты от оригинального grep и тестируемой программы
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

    # Удаляем тестовые файлы
    cleanup_test_file
}

# Тестирование с флагами (один файл)
run_test "Тест с флагом -e" \
    "./s21_grep -e 'test' test_file.txt" \
    "grep -e 'test' test_file.txt"

run_test "Тест с флагом -i" \
    "./s21_grep -i 'Test' test_file.txt" \
    "grep -i 'Test' test_file.txt"

run_test "Тест с флагом -v" \
    "./s21_grep -v 'test' test_file.txt" \
    "grep -v 'test' test_file.txt"

run_test "Тест с флагом -c" \
    "./s21_grep -c 'test' test_file.txt" \
    "grep -c 'test' test_file.txt"

run_test "Тест с флагом -l" \
    "./s21_grep -l 'test' test_file.txt" \
    "grep -l 'test' test_file.txt"

run_test "Тест с флагом -n" \
    "./s21_grep -n 'test' test_file.txt" \
    "grep -n 'test' test_file.txt"

run_test "Тест с флагом -h" \
    "./s21_grep -h 'test' test_file.txt" \
    "grep -h 'test' test_file.txt"

run_test "Тест с флагом -s" \
    "./s21_grep -s 'test' testfile.txt" \
    "grep -s 'test' testfile.txt"

run_test "Тест с флагом -o" \
    "./s21_grep -o 'test' test_file.txt" \
    "grep -o 'test' test_file.txt"


# Тесты с несколькими файлами
run_test "Тест с флагом -e для нескольких файлов" \
    "./s21_grep -e 'test' test_file.txt test2_file.txt" \
    "grep -e 'test' test_file.txt test2_file.txt"

run_test "Тест с флагом -i для нескольких файлов" \
    "./s21_grep -i 'Test' test_file.txt test2_file.txt" \
    "grep -i 'Test' test_file.txt test2_file.txt"

run_test "Тест с флагом -v для нескольких файлов" \
    "./s21_grep -v 'test' test_file.txt test2_file.txt" \
    "grep -v 'test' test_file.txt test2_file.txt"

run_test "Тест с флагом -c для нескольких файлов" \
    "./s21_grep -c 'test' test_file.txt test2_file.txt" \
    "grep -c 'test' test_file.txt test2_file.txt"

run_test "Тест с флагом -l для нескольких файлов" \
    "./s21_grep -l 'test' test_file.txt test2_file.txt" \
    "grep -l 'test' test_file.txt test2_file.txt"

run_test "Тест с флагом -n для нескольких файлов" \
    "./s21_grep -n 'test' test_file.txt test2_file.txt" \
    "grep -n 'test' test_file.txt test2_file.txt"

run_test "Тест с флагом -h для нескольких файлов" \
    "./s21_grep -h 'test' test_file.txt test2_file.txt" \
    "grep -h 'test' test_file.txt test2_file.txt"

# Тесты с комбинациями флагов (по 2 флага)
run_test "Тест с комбинацией флагов -ie" \
    "./s21_grep -ie 'Test' test_file.txt" \
    "grep -ie 'Test' test_file.txt"

run_test "Тест с комбинацией флагов -ve" \
    "./s21_grep -ve 'Test' test_file.txt" \
    "grep -ve 'Test' test_file.txt"

run_test "Тест с комбинацией флагов -ce" \
    "./s21_grep -ce 'Test' test_file.txt" \
    "grep -ce 'Test' test_file.txt"

run_test "Тест с комбинацией флагов -le" \
    "./s21_grep -le 'Test' test_file.txt" \
    "grep -le 'Test' test_file.txt"

run_test "Тест с комбинацией флагов -ne" \
    "./s21_grep -ne 'Test' test_file.txt" \
    "grep -ne 'Test' test_file.txt"

run_test "Тест с комбинацией флагов -iv" \
    "./s21_grep -iv 'Test' test_file.txt" \
    "grep -iv 'Test' test_file.txt"

run_test "Тест с комбинацией флагов -ic" \
    "./s21_grep -ic 'Test' test_file.txt" \
    "grep -ic 'Test' test_file.txt"

run_test "Тест с комбинацией флагов -il" \
    "./s21_grep -il 'Test' test_file.txt" \
    "grep -il 'Test' test_file.txt"

run_test "Тест с комбинацией флагов -in" \
    "./s21_grep -in 'Test' test_file.txt" \
    "grep -in 'Test' test_file.txt"

run_test "Тест с комбинацией флагов -vc" \
    "./s21_grep -vc 'Test' test_file.txt" \
    "grep -vc 'Test' test_file.txt"

run_test "Тест с комбинацией флагов -vl" \
    "./s21_grep -vl 'Test' test_file.txt" \
    "grep -vl 'Test' test_file.txt"

run_test "Тест с комбинацией флагов -vn" \
    "./s21_grep -vn 'Test' test_file.txt" \
    "grep -vn 'Test' test_file.txt"

run_test "Тест с комбинацией флагов -cn" \
    "./s21_grep -cn 'Test' test_file.txt" \
    "grep -cn 'Test' test_file.txt"

run_test "Тест с комбинацией флагов -ln" \
    "./s21_grep -ln 'Test' test_file.txt" \
    "grep -ln 'Test' test_file.txt"

run_test "Тест с комбинацией флагов -he" \
    "./s21_grep -he 'Test' test_file.txt" \
    "grep -he 'Test' test_file.txt"

run_test "Тест с комбинацией флагов -hv" \
    "./s21_grep -hv 'Test' test_file.txt" \
    "grep -hv 'Test' test_file.txt"

run_test "Тест с комбинацией флагов -hc" \
    "./s21_grep -hc 'Test' test_file.txt" \
    "grep -hc 'Test' test_file.txt"

run_test "Тест с комбинацией флагов -hl" \
    "./s21_grep -hl 'Test' test_file.txt" \
    "grep -hl 'Test' test_file.txt"

run_test "Тест с комбинацией флагов -hn" \
    "./s21_grep -hn 'Test' test_file.txt" \
    "grep -hn 'Test' test_file.txt"

run_test "Тест с комбинацией флагов -oe" \
    "./s21_grep -oe 'Test' test_file.txt" \
    "grep -oe 'Test' test_file.txt"

run_test "Тест с комбинацией флагов -ov" \
    "./s21_grep -ov 'Test' test_file.txt" \
    "grep -ov 'Test' test_file.txt"

run_test "Тест с комбинацией флагов -oc" \
    "./s21_grep -oc 'Test' test_file.txt" \
    "grep -oc 'Test' test_file.txt"

run_test "Тест с комбинацией флагов -ol" \
    "./s21_grep -ol 'Test' test_file.txt" \
    "grep -ol 'Test' test_file.txt"


# Тесты с комбинациями флагов (по 3 флага)
run_test "Тест с комбинацией флагов -i -v -e" \
    "./s21_grep -i -v -e 'Test' test_file.txt" \
    "grep -i -v -e 'Test' test_file.txt"

run_test "Тест с комбинацией флагов -c -n -e" \
    "./s21_grep -c -n -e 'test' test_file.txt" \
    "grep -c -n -e 'test' test_file.txt"

# Тесты с комбинациями флагов (по 4 флага)
run_test "Тест с комбинацией флагов -i -v -c -e" \
    "./s21_grep -i -v -c -e 'Test' test_file.txt" \
    "grep -i -v -c -e 'Test' test_file.txt"

run_test "Тест с комбинацией флагов -n -l -v -c" \
    "./s21_grep -n -l -v -c 'test' test_file.txt" \
    "grep -n -l -v -c 'test' test_file.txt"

# Тестировка пустого grep без флагов
run_test "Тест с пустым grep без флагов" \
    "./s21_grep 'test' test_file.txt" \
    "grep 'test' test_file.txt"

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
