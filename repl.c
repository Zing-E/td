/* repl.c */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "td.h"
#include "parse_config.h"
#include "repl.h"

#define CFG_PATH_MAX 128

static void print_td(td_list_T *);
static void delete_index(td_list_T **, char *);
static void change_config(FILE *, td_list_T *);

static void print_td(td_list_T *head)
{
	if(!head) {
		printf("Nothing Todo!\n");
		return;
	}

	for(td_list_T *i = head; i; i = i->next)
		printf(" %ld. [%c] %s\n", i->td->index, (i->td->status == true) ? 'x' : ' ', i->td->name);
}

static void change_config(FILE *fp, td_list_T *)
{
}

static void delete_index(td_list_T **head, char *line)
{
	if(*++line) 
		if(isspace(*line) && *++line) 
			if(isdigit(*line) && td_list_index(*head, *line-'0')) {
				td_list_delete(head, *line-'0');
				return;
			} else 
				fprintf(stderr, "td: Incorrect Syntax.\n");
}


void td_repl(void)
{
	/* That should be fine right? :-) */
	
	char cfg_path[CFG_PATH_MAX + 1];
	char *prompt;
	FILE *cfg_fp;
	bool is_edited = false;
	
	snprintf(cfg_path, CFG_PATH_MAX, "/home/%s/.config/td/td.data", getlogin()); 

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

		if(!strcmp(prompt, "p"))
			print_td(td_list_head);
		else if(prompt[0] == 'd') 
			delete_index(&td_list_head, prompt);
		else if(!strcmp(prompt, "q"))
			exit(EXIT_SUCCESS);

	}

	free(prompt);
}
