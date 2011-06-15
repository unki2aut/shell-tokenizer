/******************************************************************************/
/* FILENAME: tokenize.c                                                       */
/* PURPOSE:  tokenize a source by delimiter                                   */
/* AUTHOR:   (c) Martin Fillafer (unki2aut@gmail.com)                         */
/* DATE:     2011-06-15                                                       */
/* VERSION:  v0.2                                                             */
/******************************************************************************/

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#define MAXLINE 1024

/* globals */
const char* szCommand = "<not yet set>";

void usage(void) {
  (void) fprintf(stderr, "Usage: %s -d <delim> [- | filename]\n", szCommand);
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
  FILE *fp;
  char buffer[MAXLINE];
  char *delim = NULL, *file = NULL;
  int ibuf = 0, idelim = 0, i = 0;

  szCommand = argv[0];

#ifdef DEBUG
  fprintf(stdout, "DEBUG argc: %i\n", argc);
#endif

  if (argc < 3 || argc > 4) {
    usage();
  }

  if (strcmp(argv[1], "-d") != 0) {
    usage();
  }

  delim = argv[2];

  if(argc == 4) {
    file = argv[3];
  }

#ifdef DEBUG
  fprintf(stdout, "DEBUG delim: '%s'\n", delim);
#endif

  if (file == NULL) {
    fp = stdin;
#ifdef DEBUG
    printf("DEBUG file == NULL\n");
#endif
  } else if (strcmp(file, "-") == 0) {
    fp = stdin;
#ifdef DEBUG
    printf("DEBUG file == '-'\n");
#endif
  } else if ((fp = fopen(file, "r")) == 0) {
    fp = stdin;
    usage();
  }

  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    ibuf = 0;
    idelim = 0;

    while (ibuf < sizeof(buffer) && buffer[ibuf] != '\0') {
      if (delim[idelim] == buffer[ibuf] && idelim != strlen(delim)) {
#ifdef DEBUG
        printf("\nDEBUG buf[%i]: %c, delim[%i]: %c\n",
          ibuf, buffer[ibuf], idelim, delim[idelim]);
#endif

        idelim++;
        ibuf++;
      } else {
        /* if characters are not the same */
        if (idelim == 0) {
          (void) fprintf(stdout, "%c", buffer[ibuf]);
          ibuf++;
        } else {
#ifdef DEBUG
          printf("DEBUG idelim: %i, strlen(delim): %i",
            idelim, strlen(delim));
#endif

          if (idelim == strlen(delim)) { /* if delimiter was found */
            (void) fprintf(stdout, "\n");

          } else { /* if parts of delim are the same */
            for (i = ibuf - idelim; i < ibuf; i++)
              (void) fprintf(stdout, "%c", buffer[i]);
          }
        }

        idelim = 0;
      }
    }
  }

  fclose(fp);
  exit(EXIT_SUCCESS);
}
