#ifndef PARSE_CONFIG_H
#define PARSE_CONFIG_H

#include <stdio.h>
#include "td.h"

td_list_T *file_parse(FILE *);
td_T *line_parse(char *line, size_t index);

#endif
