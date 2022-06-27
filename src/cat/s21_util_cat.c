//  copyright 2022 HARMONIC

#include "s21_cat.h"

void s21_parse_cat_flags(char* argv, t_cat* cat) {
  while (*argv) {
    switch (*argv) {
      case 'b':
        cat->b = 1;
        break;
      case 'e':
        cat->e = 1;
        break;
      case 'n':
        cat->n = 1;
        break;
      case 's':
        cat->s = 1;
        break;
      case 't':
        cat->t = 1;
        break;
      default:
        fprintf(stderr, "s21_cat: invalid option -- %c\n", *argv);
        exit(2);
      }
    argv++;
    }
  }

void s21_check_cat_arg(char* argv, t_cat* cat, t_common* common) {
  if (*argv != '-') {
    s21_save_path(argv, common);
    } else {
    s21_parse_cat_flags(argv + 1, cat);
    }
  }

void s21_init_cat_struct(t_cat* cat) {
  cat->b = 0;
  cat->e = 0;
  cat->s = 0;
  cat->t = 0;
  cat->n = 0;
  cat->one_enter = 0;
  cat->begin = 0;
  cat->is_new_line = 0;
  cat->str_count = 1;
  cat->is_empty = 1;
  }
