/* main.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "td.h"
#include "parse_config.h"

void print_td(td_list_T *);

void print_td(td_list_T *head)
{
	for(td_list_T *i = head; i; i = i->next)
		printf(" %ld. [%c] %s\n", i->td->index, (i->td->status == true) ? 'x' : ' ', i->td->name);
}

int main(int argc, char *argv[])
{
	td_list_T *head = file_parse(fopen("./td.cfg", "r"));

	print_td(head);
	
	return 0;
}
