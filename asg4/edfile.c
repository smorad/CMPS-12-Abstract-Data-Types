// $Id: edfile.c,v 1.201 2012-11-25 13:37:57-08 - - $

#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "debugf.h"
#include "list.h"

bool want_echo = false;
int EXIT_STATUS = EXIT_SUCCESS;
char *fname = NULL;
FILE *file;

char *remove_first(char *string){
   return string+1;
}

void badline (int stdincount, char *stdinline) {
   fflush (NULL);
   fprintf (stderr, "Bad input line %d: %s\n", stdincount, stdinline);
   fflush (NULL);
}

void printall(list_ref list){
   if(!empty_list(list)){
      setmove_list(list, MOVE_HEAD);
      for(int i = 0; i<get_size(list); i++){
         printf("%s\n", viewcurr_list(list));
         setmove_list(list, MOVE_NEXT);
      }
   }
   else{
      fprintf(stderr, "list is empty\n");
      EXIT_STATUS = EXIT_FAILURE;
   }
}


void writefile(list_ref list, char* filename){
   if(empty_list(list)) return;
   if(filename != NULL)
   fname = filename;
   file = fopen(filename,"w+");
   int i = 0;
   for(; i< get_size(list); i++){ 
      fputs(viewcurr_list(list), file);
      fputs("\n", file);
      setmove_list(list, MOVE_NEXT);
      fflush(NULL);
   }
   printf("%d %s%s\n", i, "lines written to ", filename);
}

void save(list_ref list, char *str){
   setmove_list(list, MOVE_HEAD);
   if(strlen(str)>1){
      char *input = strdup(str+1);
     // char *input =  malloc(1024);
    //  strcpy(input, str);
     // input = remove_first(input);
      fname = input;
   }
   writefile(list, fname);
}


void insert(list_ref list, char* line){
   if(strlen(line)<2){
      fprintf (stderr, "%s: cannot insert empty string\n", Exec_Name);
      printf("%s\n", "Cannot insert nothing!");
      EXIT_STATUS = EXIT_FAILURE;
      return;
   }
   char *input = strdup(line+1);
   //char *input =  malloc(2048);   //memleak
   //strcpy(input, line);                           //memleak
   //input = remove_first(input);
   insert_list(list, input);
   printf("%s\n", viewcurr_list(list));
   
}

bool move(list_ref list, list_move move){
   bool temp = setmove_list(list, move);
   printf("%s\n", viewcurr_list(list));
   return temp;
}
void initread(list_ref list, char* filename){
   char *input = strdup(filename);
   FILE *fp = fopen(input, "r");
      if(fp == NULL)
         return;
   char buff[1024];
   int i = 0;
   while(true){
      if((fgets(buff, sizeof buff, fp))==NULL)
         break;
     char * filein =strdup(buff);
     filein[strlen(filein)-1] = '\0';
     insert_list(list, filein);
     i++;  
   }
   printf("%d %s%s\n", i, "lines read from ", filename);
   fclose(fp);
   free(input);
}



void readin(list_ref list, char* filename){
   if(strlen(filename)<2){
      fprintf (stderr, "%s: Filename cannot be empty\n", Exec_Name);
      printf("%s\n", "Cannot insert nothing!");
      EXIT_STATUS = EXIT_FAILURE;
      return;
   }
   char *input = strdup(filename+1);
   //char *input =  malloc(2048);
   //strcpy(input, filename);
   //input = remove_first(input);
   FILE *fp = fopen(input, "r");
   if(fp == NULL){
      fprintf(stderr, "%s: %s not found.", Exec_Name, input);
      EXIT_STATUS = EXIT_FAILURE;
      return;
   }
   char buff[1024];
   int i = 0;
   while(true){
      if((fgets(buff, sizeof buff, fp))==NULL)
         break;
     char * filein =strdup(buff);    
     filein[strlen(filein)-1] = '\0';
     insert_list(list, filein);
     i++;  
   }
   printf("%d %s%s\n", i, "lines read from ", filename);
   fclose(fp);
   free(input);
}

void cleanup(list_ref list){
   if(empty_list(list)) return;
  // setmove_list(list, MOVE_LAST);
  // delete_list(list);
   setmove_list(list, MOVE_HEAD);
  // delete_list(list);
   for(int i = 0; i<get_size(list)+1; i++){
      delete_list(list);
      setmove_list(list, MOVE_NEXT);
   //   delete_list(list);
   }
   //free(fname);
}

void insert_before(list_ref list, char* line){
   if(strlen(line)<2){
      fprintf (stderr, "%s: cannot insert empty string\n", Exec_Name);
      printf("%s\n", "Cannot insert nothing!");
      EXIT_STATUS = EXIT_FAILURE;
      return;
   }
   char *input = strdup(line+1);
   //strcpy(input, line);
   //input = remove_first(input);
   insert_list_before(list, input);
   printf("%s\n", viewcurr_list(list));
}

void delete(list_ref list){
   if(!empty_list(list))
      delete_list(list);
   else{
      fprintf(stderr, "%s: list is empty\n", Exec_Name);
      EXIT_STATUS = EXIT_FAILURE;
   }
}

void viewcurr(list_ref list){
   if(empty_list(list)){
      fprintf(stderr, "%s: list is empty\n", Exec_Name);
      EXIT_STATUS = EXIT_FAILURE;
   }
   else
      printf("%s\n", viewcurr_list(list));
}

void editfile (list_ref list) {
   char stdinline[1024];
   int stdincount = 0;
   bool blank = true;
   for(;; ++stdincount) {
      printf ("%s: ", Exec_Name);
      char *linepos = fgets (stdinline, sizeof stdinline, stdin);
      if (linepos == NULL){
         save(list, fname-1);
         cleanup(list);
         printf("%s", "^D\n");
         return;
      }
      if(!isblank(stdinline[0]))
         blank = false;
      if (want_echo) printf ("%s", stdinline);
      linepos = strchr (stdinline, '\n');
      if (linepos == NULL || stdinline[0] == '\0') {
         badline (stdincount, stdinline);
      }else {
         *linepos = '\0';
         switch (stdinline[0]) {
            case '#': break;
            case ' ': break;
            case '\t': break;
            case '*': printall(list); break;
            case '.': viewcurr(list); break; 
            case '$': move(list, MOVE_LAST);    break;
            case '0': move(list, MOVE_HEAD);    break;
            case '<': move(list, MOVE_PREV);    break;
            case '>': move(list, MOVE_NEXT);    break;
            case '@': debugdump_list (list);    break;
            case 'a': insert(list, stdinline);  break;
            case 'd': delete(list);        break;
            case 'i': insert_before(list, stdinline); break;
            case 'r': readin(list, stdinline);  break;
            case 'w': save(list, stdinline);    break;
            default : badline (stdincount, stdinline); break;
         }
      }
   }
}


void usage_exit() {
   fflush (NULL);
   fprintf (stderr, "Usage: %s filename\n", Exec_Name);
   fflush (NULL);
   exit (EXIT_FAILURE);
}

int main (int argc, char **argv) {
   Exec_Name = basename (argv[0]);
   if (argc != 2) usage_exit();
   want_echo = ! (isatty (fileno (stdin)) && isatty (fileno (stdout)));
  // file = fopen(argv[1],"w");
 //  assert(file != NULL);
   fname = argv[1];
   list_ref list = new_list(); 
   initread(list, fname);
   editfile (list);
   free_list (list); list = NULL;
   //free(fname);
   return EXIT_STATUS;
}
