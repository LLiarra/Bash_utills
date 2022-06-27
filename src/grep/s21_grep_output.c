//  copyright 2022 HARMONIC

#include "s21_grep.h"

void s21_check_grep_arg(char* argv, t_grep* grep, t_common* common) {
  if (*argv == '-') {
    s21_parse_grep_flags(argv + 1, grep);
  } else if (*argv != '-' && grep->is_template && !grep->flags.f) {
    s21_work_tempale(argv, grep);
    grep->is_template = 0;
  } else if (*argv != '-' && grep->pattern.is_f) {
    s21_save_file_patterns(argv, grep);
    grep->pattern.is_f = 0;
  } else {
    s21_save_path(argv, common);
  }
}

void s21_parse_grep_flags(char* argv, t_grep* grep) {
  while (*argv) {
    switch (*argv) {
    case 'e':
      grep->flags.e = 1;
      grep->is_template = 1;
      break;
    case 'i':
      grep->flags.i = 1;
      break;
    case 'v':
      grep->flags.v = 1;
      break;
    case 'c':
      grep->flags.c = 1;
      break;
    case 'l':
      grep->flags.l = 1;
      break;
    case 'n':
      grep->flags.n = 1;
      break;
    case 'h':
      grep->flags.h = 1;
      break;
    case 's':
      grep->flags.s = 1;
      break;
    case 'f':
      grep->flags.f = 1;
      grep->pattern.is_f = 1;
      break;
    case 'o':
      grep->flags.o = 1;
      break;
    default:
      fprintf(stderr, "s21_grep: invalid option -- '%c'\n", *argv);
      exit(2);
    }
    argv++;
  }
}

void s21_grep_read_file(char* path, t_grep* grep, t_common* common) {
  char* result = NULL;
  size_t len = 0;
  grep->path = path;
  grep->count_path = common->file_count;

  s21_check_combination(grep);

  if (s21_check_file(path)) {
    FILE* file;
    int first_read = 1;
    file = fopen(path, "r");
    while (getline(&result, &len, file) != -1) {
      grep->number_line++;
      int i = 0;

      while (i < grep->count_templates) {
       s21_find_cmp(result, &grep->pattern.reg[i], grep);

        if (grep->process.is_compare) {
          grep->count_matches++;
          grep->flags.l && first_read ? s21_print_l(grep->path) : 0;
          first_read = 0;
          !grep->flags.o ? s21_print_with_flags(result, common, grep) : 0;
          if (grep->flags.o) {
            s21_several_cmp(result, &grep->pattern.reg[i], grep);
          }
          if (!grep->flags.o) {
            break;
          }
        }
        i++;
      }
      if (!grep->process.is_compare) {
       s21_print_with_flags(result, common, grep);
      }
      free(result);
      result = NULL;
    }
    grep->flags.c && !grep->flags.l ? s21_print_c(grep) : 0;
    fclose(file);
  } else {
    grep->flags.s ? 0 : fprintf(stderr, "s21_grep: %s: No such file or directory\n", path);
  }
  free(result);
  grep->count_matches = 0;
  grep->number_line = 0;
}

void s21_grep_files_output(t_common* common, t_grep* grep) {
  if (grep->flags.f) {
    s21_open_template_file(grep);
    s21_compile_regex(grep);
  }
  for (int i = 0; i < common->file_count; i++) {
    s21_grep_read_file(common->path[i], grep, common);
  }
}

void s21_check_combination(t_grep* grep) {
  if (grep->flags.o && grep->flags.l) {
    grep->flags.o = 0;
  }
  if (grep->flags.o && grep->flags.v) {
    #ifdef __linux__
      exit(-1);
    #elif __APPLE__
    grep->flags.o = 0;
    #else
    exit(-1);
    #endif
  }
  if (grep->flags.c && (grep->flags.n || grep->flags.o)) {
    grep->flags.n = 0;
    grep->flags.o = 0;
  }
}

void s21_save_file_patterns(char* argv, t_grep* grep) {
  grep->pattern.file_with_patterns[grep->pattern.count_files_with_patterns++] = s21_strdup(argv);
}

void s21_open_template_file(t_grep* grep) {
  for (int i = 0; i < grep->pattern.count_files_with_patterns; i++) {
    s21_read_template_file(grep->pattern.file_with_patterns[i], grep);
  }
}

void s21_read_template_file(char* path, t_grep* grep) {
  FILE* file;
  size_t len = 0;
  char* result = NULL;
  if (s21_check_file(path)) {
    file = fopen(path, "r");
    while (getline(&result, &len, file) != -1) {
      grep->templates[grep->count_templates++] = s21_strdup(result);
       free(result);
      result = NULL;
    }
    fclose(file);
  } else {
    grep->flags.s ? 0 : fprintf(stderr, "s21_grep: %s: No such file or directory\n", path);
  }
  free(result);
}

void s21_compile_regex(t_grep* grep) {
  regex_t* reg = calloc(grep->count_templates, sizeof(regex_t));
  int flag = 0;
  if (grep->flags.i) {
    flag = REG_ICASE;
  } else {
    flag = REG_EXTENDED;
  }
    for (int i = 0; i < grep->count_templates; i++) {
      regcomp(&reg[i], grep->templates[i], flag);
    }
  grep->pattern.reg = reg;
}
