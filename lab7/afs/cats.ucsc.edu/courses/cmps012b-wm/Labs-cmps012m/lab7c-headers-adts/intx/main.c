/* $Id: main.c,v 1.5 2012-11-01 19:33:32-07 - - $ */

/*
* Silly main program which just creates an intx box, puts a
* number in it, gets it back out, and deletes the box.
* Run with bcheck to verify no memory leaks.
*/

#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include "intx.h"

char *execname = NULL;

int main (int argc, char **argv) {
   argc = argc; // Avoid:16: warning: unused parameter 'argc'
   execname = basename (argv[0]);

   /* Declare the box and initialize it.  */
   intx_ref box = new_intx();
   printf ("box = %p\n", box);

   /* Perform a couple of operations on it.  */
   put_intx (box, 1024);
   printf ("box value is %d\n", get_intx (box));

   /* Free up the box and set the handle to NULL to avoid a dangle. */
   free_intx (box);
   box = NULL;

   return EXIT_SUCCESS;
}

