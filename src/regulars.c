#include "regulars.h"

#include <stdio.h>
#include <string.h>
#define REGEX_COMPILE_ERROR -3
#define ALLOCATION_ERROR -1

int compile_reg(char **templates, int templates_count, regex_t *reg_expressions,
                Flags flags) {
  char *all_templates_str = NULL;
  int err =
      concat_all_templates(templates, templates_count, &all_templates_str);
  if (err) return err;
  int compile_error = regcomp(reg_expressions, all_templates_str,
                              REG_EXTENDED | (flags.flagI ? REG_ICASE : 0));
  if (all_templates_str != NULL) free(all_templates_str);
  if (compile_error) {
    printf("grep: Invalid regex expression");
    return REGEX_COMPILE_ERROR;
  }
  return 0;
}
int concat_all_templates(char **templates, int templates_count, char **result) {
  size_t total_length = 0;
  for (char **template = templates; template - templates < templates_count;
       template ++)
    total_length += strlen(*template);
  *result = calloc(sizeof(char), total_length + templates_count);
  if (result == NULL) {
    printf("Allocation error");
    return ALLOCATION_ERROR;
  }
  for (char **template = templates; template - templates < templates_count - 1;
       template ++) {
    *result = strcat(*result, *template);
    *result = strcat(*result, "|");
  }
  *result = strcat(*result, templates[templates_count - 1]);
  return 0;
}