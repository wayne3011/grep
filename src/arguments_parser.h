#ifndef C3_SIMPLEBASHUTILS_1_ARGUMENTS_PARSER_H
#define C3_SIMPLEBASHUTILS_1_ARGUMENTS_PARSER_H
#define UNKNOWN_FLAG 1
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct {
  bool flagE;
  bool flagI;
  bool flagV;
  bool flagC;
  bool flagL;
  bool flagN;
  bool flagH;
  bool flagS;
  bool flagF;
  bool flagO;
} Flags;
int parse_flags(int argc, char *argv[], Flags *flags, char ***templates,
                int *templates_count);
void parse_files(int argc, char *argv[], char **files_names);
int parse_arguments(int argc, char *argv[], Flags *flags, char ***file_args,
                    int *files_count, char ***templates, int *templates_count);
int get_templates_from_file(char *filepath, char ***templates,
                            int *templates_count);
int add_new_template(char ***templates, int *templates_count,
                     char *new_template);
int get_line(FILE *fp, char **str, size_t *buf_length);
#endif  // C3_SIMPLEBASHUTILS_1_ARGUMENTS_PARSER_H
