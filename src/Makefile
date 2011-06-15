#########################################################################
# FILENAME:  Makefile                                                   #
# PURPOSE:   Makefile for cut2                                          #
# AUTHOR:    Fillafer Martin (unki2aut@gmail.com)                       #
# DATE:      07.06.2009                                                 #
#########################################################################


#########################################################################
CC=gcc
CFLAGS=-ansi -pedantic -Wall -g -D_XOPEN_SOURCE=500

all: cut2

cut2: cut2.o
	$(CC) -o cut2 cut2.o

cut2.o: cut2.c
	$(CC) $(CFLAGS) -c cut2.c

	
.PHONY: clean

clean:
	rm cut2 cut2.o
