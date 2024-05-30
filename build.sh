#!/bin/sh

# Yes its shell not make (I don't know how to use make)

CC=cc
CFLAGS="-Wall -Wextra -lreadline -O2"
OBJ="obj/*.o"
BIN="td"

build() {
	$CC $CFLAGS -c main.c -o obj/main.o
	$CC $CFLAGS -c parse_config.c -o obj/parse_config.o
	$CC $CFLAGS -c repl.c -o obj/relp.o
	$CC $CFLAGS -c td.c -o obj/td.o

	$CC $CFLAGS $OBJ -o $BIN
}

clean() {
	rm $OBJ
	rm $BIN
}

usage() {
	echo "Usage: $0 [build clean]" 
}

case "$1" in
	build) build ;;
	clean) clean ;;
	*) usage && exit 1 ;;
esac
