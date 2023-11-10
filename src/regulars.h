#ifndef GREP_REGULARS_H
#define GREP_REGULARS_H
#include <regex.h>

#include "arguments_parser.h"
int compile_reg(char** templates, int templates_count, regex_t* reg_expressions,
                Flags flags);
int concat_all_templates(char** templates, int templates_count, char** result);
#endif  // GREP_REGULARS_H
