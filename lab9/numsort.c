#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "inssort.h"

double data[1000] = {'\0'};

int dubcomp(const void* x, const void* y){
   const double *xx = (const double *)x;
   const double *yy = (const double *)y;
   return *xx-*yy;
}

int main(int argc, char** argv){
   int status = 0;
   int count = 0;
   while(true){    
      if(status==EOF)
         break;
      if(data[1000]!= '\0')   
         break;
      status = scanf("%lf", &data[count]); 
      count++;
   } 
   inssort(&data[0], count-1, sizeof(double*), dubcomp);
   int i;
   for(i = 0; i< count-1; i++)
      printf("%20.15g\n", data[i]);
   return EXIT_SUCCESS;
}
