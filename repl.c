/* repl.c */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "td.h"
#include "parse_config.h"
#include "repl.h"

static void fprint_td(FILE *, td_list_T *);

static void fprint_td(FILE *fp, td_list_T *head)
{	
	for(td_list_T *i = head; i; i = i->next)
		fprintf(fp, "%ld. [%c] %s\n", i->td->index, (i->td->status == true) ? 'x' : ' ', i->td->name);
}

void td_repl(void)
{
	
}
