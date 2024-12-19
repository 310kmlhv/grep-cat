#include "s21_cat.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 1000

int main(int argc, char **argv) {
    struct Cat one = {0};
    int file_arg;
    parse_flag(argc, argv, &one, &file_arg);

    for (int i = file_arg; i < argc; i++) {
        int err_fl = 0;
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            err_fl = 1;
            printf("Ошибка открытия файла: %s\n", argv[i]);
        }
        if (err_fl == 0) {
            filter(&one, file);
            fclose(file);
        }
    }
    

    return 0;
}

void parse_flag(int argc, char **argv, struct Cat *one, int *file_arg) {
    for (int i = 1; i < argc && argv[i][0] == '-'; i++) {
        if (!strcmp(argv[i], "-b") || !strcmp(argv[i], "--number-nonblank")) {
            one->b = 1;
            one->n = 0;
        } else if (!strcmp(argv[i], "-s") || !strcmp(argv[i], "--squeeze-blank")) {
            one->s = 1;
        } else if (!strcmp(argv[i], "-n") || !strcmp(argv[i], "--number")) {
            if (one->b == 0) {
                one->n = 1;
            }
        } else if (!strcmp(argv[i], "-T")) {
            one->t = 1;
        // } else if (!strcmp(argv[i], "-v")) {
        //     one->v = 1;
        } else if (!strcmp(argv[i], "-t")) {
            one->t = 1;
            one->v = 1;
        } else if (!strcmp(argv[i], "-e")) {
            one->e = 1;
            one->v = 1;  // Включаем флаг -v при -e
        } else if (!strcmp(argv[i], "-E")) {
            one->e = 1;
        } else {
            printf("Ошибка, введите корректные данные для флага: %s\n", argv[i]);
        }
        *file_arg = i + 1;  // Обновление на последний аргумент файла
    }
}

void filter(struct Cat *one, FILE *file) {
    char line[MAX_LENGTH];
    int line_number = 1;
    int prev_empty = 0; // предыдущее пустое ли было

    while (fgets(line, MAX_LENGTH, file)) {
        int stop_fl = 0;
        int is_empty = 0;
        
        if (line[0] == '\n') {
            is_empty = 1;
        }
        if (one->s && is_empty && prev_empty) {
            stop_fl = 1;
        }
        prev_empty = is_empty;

        if (stop_fl == 0) {
            // Обработка номеров строк
            if (one->n && !one->b) {
                printf("%6d\t", line_number++);
            } else if (one->b && !is_empty) {
                printf("%6d\t", line_number++);
            } else if (one->b && one->e && is_empty) {
                printf("%6c\t", ' ');
            }

            for (int i = 0; line[i] != '\0'; i++) {
                char ch = line[i];
                print_char_with_flags(ch, one);
            }
        }
    }
}


void handle_vet_flag(char ch) {
    if (ch < 32 && ch != 9 && ch != 10) {
        putchar('^');
        putchar(ch + 64);  // Преобразуем управляющий символ в вид ^X
    } else if (ch == 127) {
        putchar('^');
        putchar('?');
    } else if (ch == '\n') {
        putchar('$');
        putchar(ch); // Только конец строки как $
    }else if (ch == '\t') {
        putchar('^');
        putchar('I');
    } else {
        putchar(ch);
    }
}


void handle_ve_flag(char ch) {
    if (ch < 32 && ch != 9 && ch != 10) {
        putchar('^');
        putchar(ch + 64);  // Преобразуем управляющий символ в вид ^X
    } else if (ch == 127) {
        putchar('^');
        putchar('?');
    } else if (ch == '\n') {
        putchar('$');
        putchar(ch); // Только конец строки как $
    } else {
        putchar(ch);
    }
}

void handle_vt_flag(char ch) {
    if (ch < 32 && ch != 9 && ch != 10) {
        putchar('^');
        putchar(ch + 64);  // Преобразуем управляющий символ в вид ^X
    } else if (ch == 127) {
        putchar('^');
        putchar('?');
    } else if (ch == '\t') {
        putchar('^');
        putchar('I');
    } else {
        putchar(ch);
    }
}


void handle_t_flag(char ch) {
    if (ch == '\t') {
        putchar('^');
        putchar('I');
    } else {
        putchar(ch);
    }
}


void handle_E_flag(char ch) {
    if (ch == '\n') {
        putchar('$');
        putchar(ch); // Только конец строки как $
    } else {
        putchar(ch);
    }
}

void handle_T_flag(char ch) {
    if (ch == '\t') {
        putchar('^');
        putchar('I');
    } else {
        putchar(ch);
    }
}

void print_char_with_flags(char ch, struct Cat *one) {
    // Обработка флагов
    if (one->e && one->t) {
        // Если оба флага активны, обрабатываем поочередно
        handle_vet_flag(ch);  // Преобразуем управляющие символы с -e
        
    } else if (one->v && one->t) {
        handle_vt_flag(ch);  // Преобразуем символы с -v и -t
    } else if (one->v && one->e) {
        handle_ve_flag(ch);  // Преобразуем управляющие символы с -e
    } else if (one->t) {
        handle_T_flag(ch);  // Преобразуем только табуляцию с -t
    } else if (one->e) {
        handle_E_flag(ch);  // Преобразуем конец строки с -e
    } else {
        putchar(ch);  // Просто печатаем символ
    }
}