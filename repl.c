/* repl.c */

#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "parse_config.h"
#include "repl.h"
#include "td.h"

#define CFG_PATH_MAX 128

static void print_td(td_list_T *);
static void repl_delete_index(td_list_T **, char *);
static void repl_add_td(td_list_T **, char *);
static void repl_change_config(td_list_T *, char *, FILE *);
static void repl_change_index(td_list_T *, char *);

static void print_td(td_list_T *head)
{
	if(!head) {
		printf("Nothing Todo!\n");
		return;
	}

	for(td_list_T *i = head; i; i = i->next)
		printf(" %ld. [%c] %s\n", i->td->index, (i->td->status == true) ? 'x' : ' ', i->td->name);
}

static void repl_delete_index(td_list_T **head, char *line)
{
	if(isspace(*++line) && isdigit(*++line) && td_list_index(*head, *line-'0'))
		td_list_delete(head, *line-'0');
	else 
		fprintf(stderr, "td: Incorrect Syntax.\n");
}

void td_help(void)
{
	printf("a [name]  [0-1] - Add todo\n" 
		"c [index] [0-1] - Change todo\n" 
		"d [index]	- Delete todo\n"
		"p 		- Prints todo list\n"
		"w		- Writes todo list\n"
		"q		- Exits Todo\n");
}

static void repl_add_td(td_list_T **head, char *line)
{
	char *to_format;

	if(isspace(*++line) && *++line)
		to_format = line;
	else {
		fprintf(stderr, "td: Incorrect Syntax.\n");
		return;
	}

	td_list_insert(head, line_parse(to_format, td_list_last_index(*head) + 1));
}

static void repl_change_config(td_list_T *head, char *cfg_path, FILE *cfg_fp)
{
	/* This removes whats already in the td.data file */

	fclose(cfg_fp);

	cfg_fp = fopen(cfg_path, "w");

	if(!cfg_fp) {
		fprintf(stderr, "td: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	for(td_list_T *i = head; i; i = i->next)
		fprintf(cfg_fp, "%s %d\n", i->td->name, i->td->status);

	fflush(cfg_fp);
}

static void repl_change_index(td_list_T *head, char *line)
{
	td_list_T *td_to_change;
	
	if(isspace(*++line) && isdigit(*++line) && (td_to_change = td_list_index(head, *line-'0')) && \
			       	isspace(*++line) && *++line)
		if(*line == '1')
			td_to_change->td->status = true;
		else if(*line == '0')
			td_to_change->td->status = false;
		else
			fprintf(stderr, "td: Incorrect Syntax.\n");
	else
		fprintf(stderr, "td: Incorrect Syntax.\n");
}

void td_repl(void)
{
	/* That should be fine right? :-) */
	
	char cfg_path[CFG_PATH_MAX + 1];
	char *prompt;
	FILE *cfg_fp;

	snprintf(cfg_path, CFG_PATH_MAX, "%s/.config/td/td.data", getenv("HOME")); 

	cfg_fp = fopen(cfg_path, "r");
	
	if(!cfg_fp) {
		fprintf(stderr, "td: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	td_list_T *td_list_head = file_parse(cfg_fp);

	printf("td: Reading from: %s\n", cfg_path);

	while((prompt = readline("td> ")) != NULL) {

		if(!prompt[0])
			continue;

		add_history(prompt);

		if(prompt[0] == 'a')
			repl_add_td(&td_list_head, prompt);
		else if(prompt[0] == 'c')
			repl_change_index(td_list_head, prompt);
		else if(prompt[0] == 'd')
			repl_delete_index(&td_list_head, prompt);
		else if(!strcmp(prompt, "h"))
			td_help();
		else if(!strcmp(prompt, "p"))
			print_td(td_list_head);
		else if(!strcmp(prompt, "w"))
			repl_change_config(td_list_head, cfg_path, cfg_fp);
		else if(!strcmp(prompt, "q")) {
			free(prompt);
			td_list_free(td_list_head);
			fclose(cfg_fp);
			exit(EXIT_SUCCESS);
		} else
			fprintf(stderr, "td: Incorrect Syntax.\n");
	}
}
