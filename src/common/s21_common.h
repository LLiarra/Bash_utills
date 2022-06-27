//  copyright 2022 HARMONIC

#ifndef SRC_COMMON_S21_COMMON_H_
#define SRC_COMMON_S21_COMMON_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned int s21_size_t;
#define s21_NULL ((void*) NULL)
typedef int wchar_t;

typedef struct s_common {
  int file_count;
  char **path;
} t_common;

char* s21_strdup(const char* src);
int s21_check_file(char* path);
void s21_init_common_struct(t_common *common);
void s21_save_path(char* argv, t_common* common);
void s21_free_common_memory(t_common* common);

#endif  //  SRC_COMMON_S21_COMMON_H_
