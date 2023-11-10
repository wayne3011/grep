#ifndef GREP_GREP_OUTPUT_H
#define GREP_GREP_OUTPUT_H
#include <regex.h>
#include <stdio.h>

#include "arguments_parser.h"
int grep(Flags flags, FILE *fs, char *file_name, regex_t *reg_expressions);
void print_prefix(Flags flags, int line_number, char *filename);
void print_matches(Flags flags, int line_number, char *file_name, char *buf,
                   regex_t *reg_expressions);
void print_substr(char *str, int start, int end);
#endif  // GREP_GREP_OUTPUT_H
