#include <err.h>
#include <regex.h>
#include <stdio.h>

#include "arguments_parser.h"
#include "grep_output.h"
#include "regulars.h"
#define ALLOCATION_ERROR -1
#define PARSING_ERROR -2
int read_files(char** file_paths, int file_paths_count, Flags flags,
               regex_t* reg_expressions);
void free_templates(char** templates, int templates_count);
void help();
int main(int argc, char* argv[]) {
  if (argc == 1) {
    help();
    return 0;
  }
  Flags flags = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int files_count = 0;
  char** filenames = NULL;
  int templates_count = 0;
  char** templates = NULL;
  int parsing_error =
      parse_arguments(argc, argv, &flags, &filenames, &files_count, &templates,
                      &templates_count);
  if (parsing_error < 0) {
    if (filenames) free(filenames);
    if (templates) free(templates);
    return PARSING_ERROR;
  }
  regex_t reg_expression;

  int compile_error =
      compile_reg(templates, templates_count, &reg_expression, flags);
  free_templates(templates, templates_count);
  if (compile_error == 0)
    read_files(filenames, files_count, flags, &reg_expression);
  if (templates) free(filenames);
  regfree(&reg_expression);
}

int read_files(char** file_paths, int file_paths_count, Flags flags,
               regex_t* reg_expressions) {
  for (int i = 0; i < file_paths_count; ++i) {
    FILE* fs = fopen(file_paths[i], "r+");
    if (fs == NULL) {
      if (!flags.flagS) warn("%s", file_paths[i]);
    } else {
      grep(flags, fs, file_paths[i], reg_expressions);
      fclose(fs);
    }
  }
  return 0;
}

void free_templates(char** templates, int templates_count) {
  for (int i = 0; i < templates_count; ++i) {
    if (templates[i]) free(templates[i]);
  }
  if (templates) free(templates);
}

void help() {
  fprintf(stderr,
          "Usage: grep [OPTION]... PATTERNS [FILE]...\n"
          "Try 'grep --help' for more information.\n");
}
