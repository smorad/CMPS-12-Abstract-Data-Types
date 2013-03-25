#include<stdlib.h>
#include <stdio.h>
extern char **environ;
int main(int argc, char **argv){
for(int argi=0; environ[argi]!=NULL; argi++)
   printf("%s\n", environ[argi]);
return 0;
}
