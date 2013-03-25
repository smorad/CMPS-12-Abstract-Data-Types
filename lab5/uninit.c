// $Id: uninit.c,v 1.1 2012-11-05 16:01:28-08 - - $

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
   int foo;
   printf ("%d\n", foo);
   int *pointer;
   printf ("%d\n", *pointer);
}
