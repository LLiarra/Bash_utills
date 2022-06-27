//  copyright 2022 HARMONIC

#include "s21_cat.h"

static void s21_check_char(char symb, t_cat* cat) {
  switch (symb) {
  case '\n':
  case '\r':
    break;
  default:
    cat->is_empty = 0;
    cat->one_enter = 0;
    break;
  }
}

static int s21_escape_char(wchar_t symb) {
  if (symb >= 0 && symb < 32) {
    symb += 64;
  } else if (symb >= 127) {
    symb -= 64;
  }
  return symb;
}

static void s21_wrapper_putchar(wchar_t symb, t_cat* cat) {
  if (cat->t || cat->e) {
    if ((symb >= 0 && symb < 32) || symb == 127) {
      if (cat->t && (symb != 13 && symb != 10)) {
        printf("^%c", s21_escape_char(cat->symb));
      } else if (cat->e && symb != 9 && symb != 10) {
        printf("^%c", s21_escape_char(cat->symb));
      } else if (cat->e && symb == '\t') {
        putchar(symb);
      } else if (cat->e && symb == '\n') {
        putchar('$');
      }
      if (symb == '\n' || symb == '\r') {
        putchar(symb);
      }
    } else if (symb >= 128 && symb <= 159) {
      printf("M-%c", s21_escape_char(cat->symb));
    } else {
      putchar(symb);
    }
  } else {
    putchar(symb);
  }
}

static void s21_begin_read(t_cat* cat) {
  if (cat->n) {
    printf("%6d\t", cat->str_count++);
    cat->begin = 0;
  }
}

static int s21_squeeze(t_cat* cat, char symb) {
  int result = 0;
  if (cat->is_empty && cat->s) {
    if (cat->one_enter) {
      result = 1;
    } else if (symb != '\r') {
      cat->one_enter = 1;
    }
  }
  return result;
}
static void s21_output_process(t_cat* cat, char symbol) {
  if (cat->b) {
    if ((symbol == '\r' || symbol == '\n') && cat->is_new_line) {
      s21_wrapper_putchar(symbol, cat);
    } else if (symbol != STR_END && cat->is_new_line) {
      cat->begin = 0;
      cat->is_new_line = 0;
      printf("%6d\t", cat->str_count++);
      s21_wrapper_putchar(symbol, cat);
    } else {
      s21_wrapper_putchar(symbol, cat);
    }
  } else {
    s21_wrapper_putchar(symbol, cat);
  }
}

static void s21_read_file(char* path, t_cat* cat) {
  if (s21_check_file(path)) {
    FILE* file;
    file = fopen(path, "r");
    cat->begin = 1;
    cat->is_new_line = 1;
    wchar_t read_char;
    int is_n = 0;

    while ((read_char = fgetc(file)) != EOF) {
      cat->symb = read_char;
      if (is_n) {
        is_n = 0;
        if (cat->n) {
          printf("%6d\t", cat->str_count++);
        }
      }
      if (cat->begin) {
        s21_begin_read(cat);
      }
      s21_check_char(read_char, cat);
      if (s21_squeeze(cat, read_char)) {
        continue;
      }
      s21_output_process(cat, read_char);
      if (read_char == '\n') {
        is_n = 1;
        cat->is_empty = 1;
        cat->is_new_line = 1;
      }
    }
    fclose(file);
  } else {
     cat->s? 0 : fprintf(stderr, "s21_cat: %s: No such file or directory\n", path);
  }
}

void s21_cat_files_output(t_common* common, t_cat* cat) {
  if (cat->b && cat->t) {
    cat->b = 0;
    cat->n = 1;
  }
  if (cat->n && cat->b) {
    cat->n = 0;
  }
  for (int i = 0; i < common->file_count; i++) {
    s21_read_file(common->path[i], cat);
  }
}
