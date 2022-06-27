//  copyright 2022 HARMONIC

#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <regex.h>
#include "../common/s21_common.h"
#define BUFF_SIZE 256

typedef struct s_grep_flags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} t_grep_flags;

typedef struct s_pattern {
  char** file_with_patterns;
  int is_f;
  int count_files_with_patterns;
  char** patterns;
  int count_pattern;
  regex_t* reg;
} t_pattern;

typedef struct s_process {
  int is_compare;
} t_process;


typedef struct s_grep {
  int line_count;
  int count_path;
  int is_template;
  char** templates;
  int count_templates;
  int count_matches;
  int number_line;
  int is_templates_file;
  char* path;
  t_grep_flags flags;
  t_pattern pattern;
  t_process process;
} t_grep;

int s21_grep(int argc, char **argv);

//  util
void s21_init_grep_struct(t_grep *grep);
void s21_work_tempale(char* argv, t_grep* grep);
void s21_find_cmp(char* result, regex_t* needle, t_grep* grep);
void s21_several_cmp(char* haystack, regex_t* needle, t_grep* grep);
void s21_print_c(t_grep* grep);
void s21_print_l(char* path);
void s21_print_with_flags(char* result, t_common* common, t_grep* grep);
void s21_print(char* line);
void s21_several_cmp2(char* haystack, regex_t* needle, t_grep* grep);
void s21_free_grep_memory(t_grep* grep);

//  grep_output
void s21_check_grep_arg(char* argv, t_grep* grep, t_common *common);
void s21_parse_grep_flags(char* argv, t_grep* grep);
void s21_grep_read_file(char* path, t_grep* grep, t_common* common);
void s21_grep_files_output(t_common* common, t_grep* grep);
void s21_check_combination(t_grep* grep);
void s21_save_file_patterns(char* argv, t_grep* grep);
void s21_open_template_file(t_grep* grep);
void s21_read_template_file(char* path, t_grep* grep);
void s21_compile_regex(t_grep* grep);

#endif  //  SRC_GREP_S21_GREP_H_
