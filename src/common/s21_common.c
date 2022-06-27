//  copyright 2022 HARMONIC

#include "s21_common.h"

int s21_check_file(char* path) {
  int valid = 0;

  FILE* file = fopen(path, "r");
  if (file != s21_NULL) {
    valid = 1;
    fclose(file);
  }

  return valid;
}

char* s21_strdup(const char* src) {
  s21_size_t size = strlen(src);
  char* result = (char*)calloc(size + 1, sizeof(char));
  memcpy(result, src, size);
  result[size] = '\0';
  return result;
}

void s21_save_path(char* argv, t_common* common) {
  common->path[common->file_count++] = s21_strdup(argv);
}

void s21_init_common_struct(t_common* common) {
  common->file_count = 0;
  common->path = (char**)calloc(40, sizeof(char*));
}

void s21_free_common_memory(t_common* common) {
  for (int i = 0; i < common->file_count; i++) {
    free(common->path[i]);
  }
  free(common->path);
}
