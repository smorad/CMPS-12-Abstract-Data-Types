#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "inssort.h"

char* array[10] = {NULL};
char buffer[1024];
int stringcomp(const void* x, const void* y){
   return strcmp(*((const char**)x), *((const char**)(y)));
}

int main(int argc, char** argv){
   //argc = argc;
   //argv = argv;
   int count = 0;
   while(fgets(buffer, 1024, stdin)!= NULL){
      strcat(buffer, "\0");
      array[count] = strdup(buffer);
      count++;
      printf("%d", count);
    }
   inssort(&array[0], count, sizeof(char*), stringcomp);
   int i;
   for( i = 0; i< count; i++){
      printf("%s\n", array[i]);
      free(array[i]);
   }
   return EXIT_SUCCESS;
}
