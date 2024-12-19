#ifndef S21_GREP_H
#define S21_GREP_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include <stdlib.h>

#define MAX_LENGTH 1000

struct Grep {
    char **results;       // Массив строк
    int result_count;     // Количество найденных строк
    char *template;
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int o;
};

void clear_results(struct Grep *one);
void parse_flag(int argc, char **argv, struct Grep *one, int *file_arg);
void filter(struct Grep *one, FILE *file, int argc, char **argv, char* filename, int count_files, int file_arg);
void handle_e_flag(char line[MAX_LENGTH], struct Grep *one, int* line_fl);
void handle_i_flag(char line[MAX_LENGTH], struct Grep *one, int* line_fl);
void handle_v_flag(char line[MAX_LENGTH], struct Grep *one, int* line_fl);
void handle_c_flag(char line[MAX_LENGTH], struct Grep *one, int* match_found);
void handle_l_flag(struct Grep *one, int* found_in_any_file, int argc, char **argv, int file_arg);
int find_pattern_in_file(FILE *file, const char *pattern);
void handle_n_flag(char line[MAX_LENGTH], struct Grep *one, int* line_number);
void print_results(struct Grep *one, char* filename, int count_files);

#endif
