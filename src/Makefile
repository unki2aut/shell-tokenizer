################################################################################
# FILENAME:  Makefile                                                          #
# PURPOSE:   Makefile for tokenize                                             #
# AUTHOR:    (c) Martin Fillafer (unki2aut@gmail.com)                          #
# DATE:      2011-06-15                                                        #
################################################################################

CC=gcc
CFLAGS=-ansi -pedantic -Wall -g -D_XOPEN_SOURCE=500# -DDEBUG

all: tokenize Makefile

tokenize: tokenize.o
	$(CC) -o tokenize tokenize.o

tokenize.o: tokenize.c
	$(CC) $(CFLAGS) -c tokenize.c
	
.PHONY: clean

clean:
	rm tokenize tokenize.o
