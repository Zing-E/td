/* main.c */

#include <string.h>

#include "repl.h"

int main(int argc, char *argv[])
{
	if(*++argv && !strcmp(*argv, "-h")) 
		td_help();
	else
		td_repl();

	return 0;
}
