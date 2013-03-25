/* $Id: main.c,v 1.19 2012-11-19 19:10:15-08 - - $ */

#include <assert.h>
#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

char *execname = NULL;
int exit_status = EXIT_SUCCESS;

void putinqueue (queue_ref queue, FILE *input, char *filename) {
   char buffer[1024];
   char *linepos;
   for (int linenr = 1; ; ++linenr) {
      linepos = fgets (buffer, sizeof buffer, input);
      if (linepos == NULL) break;
      linepos = strchr (buffer, '\n');
      if (linepos == NULL) {
         fflush (NULL);
         fprintf (stderr, "%s: %s[%d]: unterminated line\n",
                  execname, filename, linenr);
         fflush (NULL);
         exit_status = EXIT_FAILURE;
      }else {
         *linepos = '\0';
      }
      linepos = strdup (buffer);
      assert (linepos != NULL);
      insert_queue (queue, linepos);
     // free(linepos);
   }
}

void putfileinqueue (queue_ref queue, char *filename) {
   FILE *input = fopen (filename, "r");
   if (input == NULL) {
      fflush (NULL);
      fprintf (stderr, "%s: %s: %s\n",
               execname, filename, strerror (errno));
      fflush (NULL);
      exit_status = EXIT_FAILURE;
   }else {
      putinqueue (queue, input, filename);
      fclose (input);
   }
}


int main (int argc, char **argv) {
   execname = basename (argv[0]);
   queue_ref queue = new_queue();

   if (argc < 2) {
      putinqueue (queue, stdin, "-");
   }else {
      for (int argi = 1; argi < argc; ++argi) {
         if (strcmp (argv[argi], "-") == 0) {
            putinqueue (queue, stdin, "-");
         }else {
            putfileinqueue (queue, argv[argi]);
         }
      }
   }

   while (! isempty_queue (queue)) {
      char *temp = remove_queue(queue);
      printf ("%s\n", temp);
      free(temp);
   }
   free(queue);
   return exit_status;
}

