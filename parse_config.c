/* parse_config.c */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse_config.h"
#include "td.h"

td_T *line_parse(char *line, size_t index)
{
	td_T *td;

	char *name = calloc(1, strlen(line) + 1);
	
	if(!name) {
		fprintf(stderr, "td: Failure getting memory.\n");
		exit(EXIT_FAILURE);
	}
	
	char *word;
	int status = -1;
	size_t space_count = 0;

	while((word = strsep(&line, " "))) {

		if(word[0] == '\0')
			continue;
		else if(isdigit(word[0]) && word[1] == '\0') {
			if(word[0] == '1')
				status = true;
			else
				status = false;
			break;
		}

		if(space_count != 0)
			strcat(name, " ");
		
		strcat(name, word);
		
		space_count++;
	}

	/* If no status is given default to false */

	if(status == -1)
		status = false;

	td = new_td(name, index, status);

	return td;
}

td_list_T *file_parse(FILE *fp)
{	
	size_t buf_size = 20;
	char *buf = malloc(buf_size);
	
	if(!buf) {
		fprintf(stderr, "td: Failure getting memory.\n");
		exit(EXIT_FAILURE);
	}

	td_list_T *td_list = NULL;
	
	size_t index = 1;

	while(getline(&buf, &buf_size, fp) != -1) {
		
		buf[strlen(buf) - 1] = '\0'; /* Remove newline character */

		td_list_insert(&td_list, line_parse(buf, index));

		index++;
	}

	return td_list;
}
