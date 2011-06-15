/***************************************************************/
/* FILENAME: cut2.c                                            */
/* PURPOSE:  splitting a source by delimiter                   */
/* AUTHOR:   Fillafer Martin (unki2aut@gmail.com)              */
/* DATE:     07.06.2009                                        */
/* VERSION:  v0.1                                              */
/***************************************************************/

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#define MAXLINE 1024
#define DEBUG 0

/* globals */
const char* szCommand = "<not yet set>";

void usage(void) {
	(void) fprintf(stderr, "Usage: %s -d DELIM [- | filename]\n", szCommand);
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
	FILE *fp;
	char buffer[MAXLINE];
	char *delim, *file;
	int ibuf = 0, idelim = 0, i = 0;

	szCommand = argv[0];

	if (argc < 2 && argc > 3) {
		usage();
	}

	if (strcmp(argv[1], "-d") != 0) {
		usage();
	}

	delim = argv[2];
	file = argv[3];

	if (DEBUG) {
		fprintf(stdout, "delim: %s\n\n", delim);
	}

	if (file == NULL) {
		fp = stdin;
	} else if (strcmp(file, "-") == 0) {
		fp = stdin;
	} else if ((fp = fopen(file, "r")) == 0) {
		fp = stdin;
	}

	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		ibuf = 0;
		idelim = 0;

		while (ibuf < sizeof(buffer) && buffer[ibuf] != '\0') {
			if (delim[idelim] == buffer[ibuf] && idelim != strlen(delim)) {
				if (DEBUG)
					fprintf(stdout, "\nbuf[%i]: %c, delim[%i]: %c\n", ibuf,
							buffer[ibuf], idelim, delim[idelim]);

				idelim++;
				ibuf++;
			} else {
				/* if characters are not the same */
				if (idelim == 0) {
					fprintf(stdout, "%c", buffer[ibuf]);
					ibuf++;
				} else {
					if (DEBUG)
						fprintf(stdout, "\nidelim: %i, strlen(delim): %i\n",
								idelim, strlen(delim));

					if (idelim == strlen(delim)) { /* if delimiter was found */
						fprintf(stdout, "\n");

					} else { /* if parts of delim are the same */
						for (i = ibuf - idelim; i < ibuf; i++)
							fprintf(stdout, "%c", buffer[i]);
					}
				}

				idelim = 0;
			}
		}
	}

	fclose(fp);
	exit(EXIT_SUCCESS);
}
