//  copyright 2022 HARMONIC

#include "s21_grep.h"

int s21_grep(int argc, char** argv) {
  t_grep grep;
  t_common common;
  int is_error = 0;

  if (argc >= 3) {
    s21_init_grep_struct(&grep);
    s21_init_common_struct(&common);
    for (int i = 1; i < argc; i++) {
      s21_check_grep_arg(argv[i], &grep, &common);
    }
    if (!grep.flags.f) {
      s21_compile_regex(&grep);
    }
    s21_grep_files_output(&common, &grep);
    s21_free_grep_memory(&grep);
    s21_free_common_memory(&common);
  } else {
    fprintf(stderr, "Usage: grep [OPTION]... PATTERNS [FILE]...");
    is_error = 1;
  }
  return is_error ? EXIT_FAILURE : EXIT_SUCCESS;
}

int main(int argc, char** argv) {
  s21_grep(argc, argv);
  return 0;
}
