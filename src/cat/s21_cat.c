//  copyright 2022 HARMONIC

#include "s21_cat.h"

int s21_cat(int argc, char* argv[]) {
  t_cat cat;
  t_common common;
  int is_error = 0;
  s21_init_cat_struct(&cat);
  if (argc > 1) {
    s21_init_common_struct(&common);
    for (int i = 1; i < argc; i++) {
      s21_check_cat_arg(argv[i], &cat, &common);
     }
    s21_cat_files_output(&common, &cat);
    s21_free_common_memory(&common);
    } else {
    fprintf(stderr, "Usage: cat PATTERNS [FILE]...");
    is_error = 1;
    }
  return is_error ? EXIT_FAILURE : EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
  s21_cat(argc, argv);
  return 0;
}
