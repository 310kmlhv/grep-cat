#include "s21_grep.h"


int main(int argc, char **argv) {
    struct Grep one = {0};
    char template[MAX_LENGTH];
    int file_arg;
    int count_files;
    parse_flag(argc, argv, &one, &file_arg);

    strcpy(template, argv[file_arg]);
    one.template = template;
    file_arg++;
    int err_fl = 0;

    count_files = argc - file_arg;
    
    
    for (;file_arg < argc; file_arg++){
        FILE *file = fopen(argv[file_arg], "r");
        if (file == NULL) {
            err_fl = 1;
            if (!one.s){
                printf("Ошибка открытия файла: %s\n", argv[file_arg]);
            }
            
        }
        if (err_fl == 0) {

            filter(&one, file, argc, argv, argv[file_arg], count_files, file_arg);
            fclose(file);
            print_results(&one, argv[file_arg], count_files);
        }
        if (file_arg != argc){
            if (one.c == 1){
                printf("\n");
            }
            clear_results(&one);
        }
        if (one.l == 1){
            break;
        }
                
            
    }   

    for (int i = 0; i < one.result_count; i++) {
        free(one.results[i]);
    }
    free(one.results);

    return 0;
}



void clear_results(struct Grep *one) {
    // Освободить все строки в массиве
    for (int i = 0; i < one->result_count; i++) {
        free(one->results[i]);
    }
    // Освободить сам массив
    free(one->results);
    
    // Вернуть указатель на массив и счетчик в исходное состояние
    one->results = NULL;
    one->result_count = 0;
}


void parse_flag(int argc, char **argv, struct Grep *one, int *file_arg) {
    int empty_fl = 1;
    for (int i = 1; i < argc && argv[i][0] == '-'; i++) {
        
        // Проходим по каждому символу флага, начиная с второго
        for (int j = 1; argv[i][j] != '\0'; j++) {
            switch (argv[i][j]) {
                case 'e':
                    one->e = 1;
                    break;
                case 'i':
                    one->i = 1;
                    break;
                case 'v':
                    one->v = 1;
                    break;
                case 'c':
                    one->c = 1;
                    break;
                case 'l':
                    one->l = 1;
                    break;
                case 'n':
                    one->n = 1;
                    break;
                case 'h':
                    one->h = 1;
                    break;
                case 's':
                    one->s = 1;
                    break;  
                case 'o':
                    one->o = 1;
                    break;
                default:
                    printf("Ошибка, флаг: -%c не поддерживается.\n", argv[i][j]);
                    break;
            }
        }

        *file_arg = i + 1;
        empty_fl = 0;
    }

    // Если флаги не были указаны, устанавливаем e по умолчанию
    if (empty_fl) {
        one->e = 1;
        *file_arg = 1;
    }

}

void filter(struct Grep *one, FILE *file, int argc, char **argv, char* filename, int count_files, int file_arg) {
    char line[MAX_LENGTH];

    int line_fl = 0;
    int match_found = 0;
    int found_in_any_file = 0;
    int line_number = 0;
    int c_fl = 0;
    int o_fl = 0;

    while (fgets(line, MAX_LENGTH, file)) {
        line_number++;
        if ((one->e || one->h || one->o) && !one->v && !one->c && !one->l && !one->n) {
            handle_e_flag(line, one, &line_fl);
            if (one->o && line_fl == 1){
                line_fl = 0;
                o_fl = 1;
            }
        }
        if (one->i && !one->c && !one->l && !one->n) {
            handle_i_flag(line, one, &line_fl);
            if (one->v){
                line_fl = 0;
            }
        }
        if (one->v && !one->n) {
            
            handle_v_flag(line, one, &line_fl);
        }
        if (line_fl && !one->c && !one->l) {
            one->results = realloc(one->results, (one->result_count + 1) * sizeof(char *));
            one->results[one->result_count] = malloc(strlen(line) + 1);
            strcpy(one->results[one->result_count], line);
            one->result_count++;
        }
        if (one->c) {
            if (count_files > 1 && c_fl == 0){
                printf("%s:", filename);
                c_fl = 1;
            }
            handle_c_flag(line, one, &match_found);
        }
        if (one->n && !one->c && !one->l) {
            handle_n_flag(line, one, &line_number);
        }
        line_fl = 0;
        if (one->o && o_fl == 1){
            printf("%s\n", one->template);
        }
        o_fl = 0;
    }
    if (one->c) {
        printf("%d", match_found);
    }
    if (one->l) {
        if (one->c){
            printf("\n");
        }
        handle_l_flag(one, &found_in_any_file, argc, argv, file_arg); 
    }
    
}

void handle_e_flag(char line[MAX_LENGTH], struct Grep *one, int *line_fl) {
    regex_t regex;
    if (regcomp(&regex, one->template, 0) != 0) {
        printf("Ошибка компиляции регулярного выражения\n");
        return;
    }

    if (regexec(&regex, line, 0, NULL, 0) == 0) {
        *line_fl = 1;
    }

    regfree(&regex);
}

void handle_i_flag(char line[MAX_LENGTH], struct Grep *one, int* line_fl) {
    regex_t regex;
    if (one->i) {
        
        if (regcomp(&regex, one->template, REG_ICASE) != 0) {
            printf("Ошибка компиляции регулярного выражения\n");
            return;
        }
    } else {
        if (regcomp(&regex, one->template, 0) != 0) {
            printf("Ошибка компиляции регулярного выражения\n");
            return;
        }
    }

    if (regexec(&regex, line, 0, NULL, 0) == 0) {
        *line_fl = 1;
        
    
    }

    regfree(&regex);
}

void handle_v_flag(char line[MAX_LENGTH], struct Grep *one, int* line_fl) {
    regex_t regex;
    if (one->i) {
        
        if (regcomp(&regex, one->template, REG_ICASE) != 0) {
            printf("Ошибка компиляции регулярного выражения\n");
            return;
        }
    } else {
        if (regcomp(&regex, one->template, 0) != 0) {
            printf("Ошибка компиляции регулярного выражения\n");
            return;
        }
    }

    if (regexec(&regex, line, 0, NULL, 0) != 0) {
        *line_fl = 1;
       
        
    }

    regfree(&regex);
}

void handle_c_flag(char line[MAX_LENGTH], struct Grep *one, int *match_found) {
    regex_t regex;
    if (one->i) {
        
        if (regcomp(&regex, one->template, REG_ICASE) != 0) {
            printf("Ошибка компиляции регулярного выражения\n");
            return;
        }
    } else {
        if (regcomp(&regex, one->template, 0) != 0) {
            printf("Ошибка компиляции регулярного выражения\n");
            return;
        }
    }
    
    if (regexec(&regex, line, 0, NULL, 0) == 0 && !one->v) {
        (*match_found)++;
    }
    if (regexec(&regex, line, 0, NULL, 0) != 0 && one->v){
        (*match_found)++;
    }

    regfree(&regex);
}

void handle_l_flag(struct Grep *one, int *found_in_any_file, int argc, char **argv, int file_arg) {
    int error_flag = 0;

    for (int i = file_arg; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL && !one->s) {
            printf("Ошибка открытия файла");
            error_flag = 1;
        }

        if (!error_flag) {
            if (find_pattern_in_file(file, one->template)) {
                printf("%s\n", argv[i]);
                *found_in_any_file = 1;
            }

            if (!*found_in_any_file) {
                printf("Шаблон \"%s\" не найден в указанных файлах.\n", one->template);
            }
        }
        fclose(file);
    }
}

int find_pattern_in_file(FILE *file, const char *pattern) {
    char buffer[MAX_LENGTH];
    regex_t regex;

    if (regcomp(&regex, pattern, 0) != 0) {
        return 0;
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        if (regexec(&regex, buffer, 0, NULL, 0) == 0) {
            regfree(&regex);
            return 1;
        }
    }

    regfree(&regex);
    return 0;
}

void handle_n_flag(char line[MAX_LENGTH], struct Grep *one, int *line_number) {
    regex_t regex;
    if (one->i) {
        
        if (regcomp(&regex, one->template, REG_ICASE) != 0) {
            printf("Ошибка компиляции регулярного выражения\n");
            return;
        }
    } else {
        if (regcomp(&regex, one->template, 0) != 0) {
            return;
        }
    }

    if (regexec(&regex, line, 0, NULL, 0) == 0 && !one->v) {
        // Динамически выделяем память для новой строки и добавляем в массив
        one->results = realloc(one->results, (one->result_count + 1) * sizeof(char *));
        
        // Выделяем память для строки с номером строки
        one->results[one->result_count] = (char *)malloc(MAX_LENGTH);
        if (one->results[one->result_count] != NULL) {
            snprintf(one->results[one->result_count], MAX_LENGTH, "%d:%s", *line_number, line);
            one->result_count++;
        }
    }
    if (regexec(&regex, line, 0, NULL, 0) != 0 && one->v) {
        // Динамически выделяем память для новой строки и добавляем в массив
        one->results = realloc(one->results, (one->result_count + 1) * sizeof(char *));
        
        // Выделяем память для строки с номером строки
        one->results[one->result_count] = (char *)malloc(MAX_LENGTH);
        if (one->results[one->result_count] != NULL) {
            snprintf(one->results[one->result_count], MAX_LENGTH, "%d:%s", *line_number, line);
            one->result_count++;
        }
    }

    regfree(&regex);
}

void print_results(struct Grep *one, char* filename, int count_files) {
    
    for (int i = 0; i < one->result_count; i++) {
        if (count_files > 1 && !one->h){
            printf("%s:", filename);
        }
        
        printf("%s", one->results[i]);
    }
}
