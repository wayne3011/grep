#include "arguments_parser.h"

#include <err.h>
#include <stdio.h>
#include <string.h>

int parse_arguments(int argc, char *argv[], Flags *flags, char ***file_args,
                    int *files_count, char ***templates, int *templates_count) {
  int err = parse_flags(argc, argv, flags, templates, templates_count);
  if (err < 0) return -1;
  if (*templates_count == 0 && !flags->flagE) {
    err = add_new_template(templates, templates_count, argv[optind]);
    if (err < 0) return -1;
    optind++;
  }
  *files_count = argc - optind;
  //*file_args = (char**)malloc(sizeof(char*) * (*files_count));
  *file_args = malloc(sizeof(char *) * *files_count);
  parse_files(argc, argv, *file_args);
  return 0;
}

int parse_flags(int argc, char *argv[], Flags *flags, char ***templates,
                int *templates_count) {
  int c;
  while (1) {
    c = getopt(argc, argv, "e:ivclnhsf:o");
    if (c == -1) break;
    switch (c) {
      case 'e':
        flags->flagE = true;
        if (add_new_template(templates, templates_count, optarg) < 0) return -1;
        break;
      case 'i':
        flags->flagI = true;
        break;
      case 'v':
        flags->flagV = true;
        break;
      case 'c':
        flags->flagC = true;
        break;
      case 'l':
        flags->flagL = true;
        break;
      case 'n':
        flags->flagN = true;
        break;
      case 'h':
        flags->flagH = true;
        break;
      case 's':
        flags->flagS = true;
        break;
      case 'f':
        flags->flagF = true;
        if (get_templates_from_file(optarg, templates, templates_count) < 0)
          return -1;
        break;
      case 'o':
        flags->flagO = true;
        break;
      default:
        printf("Unknown flag!");
        return UNKNOWN_FLAG;
    }
  }
  if (((argc - optind < 2 && flags->flagE) ||
       (argc - optind < 3 && !flags->flagE)) &&
      !flags->flagH)
    flags->flagH = true;
  return 0;
}
void parse_files(int argc, char *argv[], char **files_names) {
  int i = 0;
  while (optind < argc) {
    files_names[i++] = argv[optind++];
  }
}

int get_templates_from_file(char *filepath, char ***templates,
                            int *templates_count) {
  FILE *fp = fopen(filepath, "r");
  if (fp == NULL) {
    warn("%s", filepath);
    return 0;
  }

  char *buf = NULL;
  size_t buf_size = 0;
  int err = 0;
  while (get_line(fp, &buf, &buf_size) != EOF && err != -1) {
    if (add_new_template(templates, templates_count, buf) < 0) err = -1;
  }
  if (buf) {
    free(buf);
    buf = NULL;
  }
  fclose(fp);
  return err;
}

int add_new_template(char ***templates, int *templates_count,
                     char *new_template) {
  (*templates_count)++;
  *templates = (char **)realloc(*templates, sizeof(char *) * *templates_count);
  char *new_element = (char *)calloc(sizeof(char), strlen(new_template) + 1);
  if (*templates == NULL || new_element == NULL) {
    printf("grep: Allocation error");
    return -1;
  }
  strcpy(new_element, new_template);
  (*templates)[(*templates_count) - 1] = new_element;

  return 0;
}

int get_line(FILE *fp, char **str, size_t *buf_length) {
  int str_len = 0;
  str_len = getline(str, buf_length, fp);
  if (str_len > 0) {
    (*str)[str_len - 1] =
        (*str)[str_len - 1] == '\n' ? '\0' : (*str)[str_len - 1];
    return 0;
  } else
    return -1;
}
