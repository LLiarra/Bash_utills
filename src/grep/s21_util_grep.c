//  copyright 2022 HARMONIC

#include "s21_grep.h"

void s21_init_grep_struct(t_grep* grep) {
  grep->flags.e = 0;
  grep->flags.i = 0;
  grep->flags.v = 0;
  grep->flags.c = 0;
  grep->flags.l = 0;
  grep->flags.n = 0;
  grep->flags.h = 0;
  grep->flags.s = 0;
  grep->flags.f = 0;
  grep->flags.o = 0;
  grep->count_path = 0;
  grep->line_count = 0;
  grep->is_template = 1;
  grep->count_matches = 0;
  grep->count_templates = 0;
  grep->number_line = 0;
  grep->process.is_compare = 0;
  grep->pattern.count_files_with_patterns = 0;
  grep->pattern.count_pattern = 0;
  grep->pattern.is_f = 0;
  grep->templates = (char**)calloc(40, sizeof(char*));
  grep->pattern.patterns = (char**)calloc(50, sizeof(char*));
  grep->pattern.file_with_patterns = (char**)calloc(50, sizeof(char*));
}

void s21_work_tempale(char* argv, t_grep* grep) {
  if (*argv == '\"' || *argv == '\'') {
    char* istr;
    istr = strtok(argv, "\"\'");
    while (istr != NULL) {
      istr = strtok(NULL, argv);
    }
    grep->templates[grep->count_templates++] = s21_strdup(istr);
  } else {
    grep->templates[grep->count_templates++] = s21_strdup(argv);
  }
}

static void s21_process_line_afer_cmp(char* haystack, regmatch_t* match, t_grep* grep) {
  if (grep->count_path > 1 && !grep->flags.h && !grep->flags.l) {
    grep->flags.c ? 0 : printf("%s:", grep->path);
  }
  if (grep->flags.n && !grep->flags.l) {
    printf("%d:", grep->number_line);
  }
  if (!grep->flags.l && !grep->flags.v) {
    for (int i = 0; i + match->rm_so < match->rm_eo; i++) {
      putchar(haystack[match->rm_so + i]);
    }
  }
  printf("\n");
}

void s21_several_cmp(char* haystack, regex_t* needle, t_grep* grep) {
  regmatch_t match;
  int shift = 0;

  while (regexec(needle, haystack + shift, 1, &match, 0) == 0) {
     s21_process_line_afer_cmp(haystack + shift, &match, grep);
    shift += match.rm_eo;
  }
}

void s21_print_c(t_grep* grep) {
  if (!grep->flags.h && grep->count_path > 1 && !grep->flags.l) {
    printf("%s:", grep->path);
  } else if (grep->flags.n) {
    printf("%d:", grep->number_line);
  }
  if (grep->flags.v) {
    int differense = grep->number_line - grep->count_matches;
    printf("%d\n", differense);
  } else {
    printf("%d\n", grep->count_matches);
  }
}

void s21_print_l(char* path) {
  printf("%s\n", path);
}

void s21_find_cmp(char* result, regex_t* needle, t_grep* grep) {
  grep->process.is_compare = 0;
  regmatch_t match;

  grep->process.is_compare = regexec(needle, result, 0, &match, 0) ? 0 : 1;
}

void s21_print_with_flags(char* result, t_common* common, t_grep* grep) {
  int is_need_path = common->file_count > 1 && !grep->flags.h && !grep->flags.l && !grep->flags.c;
  int is_need_num_line = grep->flags.n && !grep->flags.l;
  int is_need_line = !grep->flags.c && !grep->flags.o && !grep->flags.l;

  if ((!grep->process.is_compare && grep->flags.v) || (grep->process.is_compare && !grep->flags.v)) {
    if (is_need_path) {
      printf("%s:", grep->path);
    }
    if (is_need_num_line) {
      printf("%d:", grep->number_line);
    }

    if (is_need_line) {
      s21_print(result);
    }
  }
}

void s21_print(char* line) {
  size_t size = strlen(line);
  for (size_t i = 0; i < size && line[i] != '\n'; i++) {
    putchar(line[i]);
  }
  putchar('\n');
}

void s21_free_grep_memory(t_grep* grep) {
  for (int i = 0; i < grep->count_templates; i++) {
    regfree(&grep->pattern.reg[i]);
    free(grep->templates[i]);
  }
  for (int i = 0; i < grep->pattern.count_pattern; i++) {
    free(grep->pattern.patterns[i]);
  }
  free(grep->pattern.patterns);

  for (int i = 0; i < grep->pattern.count_files_with_patterns; i++) {
    free(grep->pattern.file_with_patterns[i]);
  }
  free(grep->pattern.file_with_patterns);

  free(grep->pattern.reg);
  free(grep->templates);
}
