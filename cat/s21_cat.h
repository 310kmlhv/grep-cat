#ifndef S21_CAT_H
#define S21_CAT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct Cat {
    int b;
    int e;
    int n;
    int s;
    int t;
    int v;
};

void parse_flag(int argc, char **argv, struct Cat* one, int* file_arg);
void filter(struct Cat* one, FILE *file);
void handle_vet_flag(char ch);
void handle_ve_flag(char ch);
void handle_vt_flag(char ch);
void handle_t_flag(char ch);
void handle_E_flag(char ch);
void handle_T_flag(char ch);
void print_char_with_flags(char ch, struct Cat *one);

#endif //S21_CAT_H
