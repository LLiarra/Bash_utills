#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

//  copyright 2022 HARMONIC

#include "../common/s21_common.h"

#ifdef __linux__
#define STR_END '\r'
#elif __APPLE__
#define STR_END '\n'
#else
#define STR_END '\n'

#endif


typedef struct s_cat {
  int b;
  int e;
  int n;
  int s;
  int t;
  wchar_t symb;
  int str_count;
  int is_empty;
  int one_enter;
  int is_new_line;
  int begin;
} t_cat;

int s21_cat(int argc, char **argv);
void s21_check_cat_arg(char* argv, t_cat* cat, t_common* common);
void s21_parse_cat_flags(char* argv, t_cat* cat);
void s21_init_cat_struct(t_cat* cat);
void s21_cat_files_output(t_common *common, t_cat* cat);


#endif  //  SRC_CAT_S21_CAT_H_
