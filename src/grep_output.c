#include "grep_output.h"
int grep(Flags flags, FILE *fs, char *file_name, regex_t *reg_expressions) {
  bool match_found = false;
  char *buf = NULL;
  int match_count = 0;
  int line_number = 0;
  size_t buf_length = 0;
  while (get_line(fs, &buf, &buf_length) != EOF && !match_found) {
    line_number++;
    int match_result = regexec(reg_expressions, buf, 0, 0, 0);
    if ((!match_result && !flags.flagV) || (flags.flagV && match_result)) {
      if (flags.flagL) {
        match_found = true;
      } else {
        match_count++;
        print_matches(flags, line_number, file_name, buf, reg_expressions);
      }
    }
  }

  if (buf) {
    free(buf);
    buf = NULL;
  }

  if (flags.flagC && !flags.flagL) {
    print_prefix(flags, 0, file_name);
    printf("%d\n", match_count);
  }
  if (match_found && flags.flagL) {
    printf("%s\n", file_name);
  }
  return 0;
}
void print_prefix(Flags flags, int line_number, char *filename) {
  if (!flags.flagH) printf("%s:", filename);
  if (flags.flagN && !flags.flagC) printf("%d:", line_number);
}

void print_matches(Flags flags, int line_number, char *file_name, char *buf,
                   regex_t *reg_expressions) {
  regmatch_t match;
  if (!flags.flagC) {
    if (!flags.flagO) {
      print_prefix(flags, line_number, file_name);
      printf("%s\n", buf);
    } else {
      while (regexec(reg_expressions, buf, 1, &match, 0) == 0) {
        print_prefix(flags, line_number, file_name);
        print_substr(buf, match.rm_so, match.rm_eo);
        buf += match.rm_eo;
      }
    }
  }
}

void print_substr(char *str, int start, int end) {
  for (int i = start; i < end; ++i) {
    putchar(str[i]);
  }
  printf("\n");
}