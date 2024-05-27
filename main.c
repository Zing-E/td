/* main.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "td.h"
#include "parse_config.h"
#include "repl.h"

int main(int argc, char *argv[])
{
	td_repl();

	return 0;
}
