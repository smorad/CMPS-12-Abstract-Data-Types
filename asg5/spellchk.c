// $Id: spellchk.c,v 1.91 2012-12-05 18:56:05-08 - - $

#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

#include "debugf.h"
#include "hashset.h"
#include "yyextern.h"

#define STDIN_NAME       "-"
//#define DEFAULT_DICTNAME "/usr/share/dict/words"
#define DEFAULT_DICTNAME "/afs/cats.ucsc.edu/courses/cmps012b-wm/usr/dict/words";
#define DEFAULT_DICT_POS 0
#define EXTRA_DICT_POS   1
#define NUMBER_DICTS     2

bool debugmode = false;
bool extradebug = false;
int SUPER_FAILURE = 2;
char * errors[1024] = {NULL};
void print_error (char *object, char *message) {
   fflush (NULL);
   fprintf (stderr, "%s: %s: %s\n", Exec_Name, object, message);
   fflush (NULL);
   Exit_Status = SUPER_FAILURE;
   exit(Exit_Status);
}

FILE *open_infile (char *filename) {
   FILE *file = fopen (filename, "r");
   if (file == NULL) print_error (filename, strerror (errno));
   DEBUGF ('m', "filename = \"%s\", file = 0x%p\n", filename, file);
   return file;
}

void spellcheck (hashset_ref hashset) { //unitialized
   yylineno = 1;
   int misspelled = 0;
  // DEBUGF ('m', "filename = \"%s\", hashset = 0x%p\n",
  //              filename, hashset);
   int arrayindex = 0;
   //char* errors[1024] = {NULL};
   for (;;) {
      int token = yylex ();
      if (token == 0) break;
      if(!has_hashset(hashset, yytext)){
         char* buff;
        // for(int i=0; yytext[i]!= NULL; i++){
           // buff[i] = tolower(yytext[i]);
       //  }
         buff = strdup(yytext);
         buff[0] = tolower(buff[0]);
         if(!has_hashset(hashset, buff)){  //segfault
            misspelled++;
            char *string = strdup(yytext);
            assert(string != NULL);
            errors[arrayindex] = string;
            arrayindex++;
         }
      free(buff);
      }
             
      DEBUGF ('m', "line %d, yytext = \"%s\"\n", yylineno, yytext);
      //STUBPRINTF ("%s: %d: %s\n", filename, yylineno, yytext);

   }
   int i = 0;
   if(errors[i]!=NULL){
      printf("%d Misspelled words:\n", misspelled);
      Exit_Status = EXIT_FAILURE;
   }
   for(i = 0; errors[i]; i++)
      printf("%s\n", errors[i]);
}

void load_dictionary (char *dictionary_name, hashset_ref hashset) {
   if (dictionary_name == NULL) return;
   DEBUGF ('m', "dictionary_name = \"%s\", hashset = %p\n",
           dictionary_name, hashset);
  // STUBPRINTF ("Open dictionary, load it, close it\n");
   FILE *fp = fopen(dictionary_name, "r");
   if(fp==NULL) print_error("File error", "File not found");
   char buff[1024];
   int count=0;
   while(fgets(buff, sizeof buff, fp) != NULL){
      if(buff[strlen(buff)-1] == '\n')
         buff[strlen(buff)-1] = '\0';
      char* in = strdup(buff);
      assert(in!=NULL);
      put_hashset(hashset, in);
      count++;
   }
      DEBUGF('m', "attempted to add %d words to hashset\n", count);
      fclose(fp);
}



void free_errors(){
   for(int i=0; errors[i]; i++)
      free(errors[i]);
}




int main (int argc, char **argv) {
   Exec_Name = basename (argv[0]);
   char *default_dictionary = DEFAULT_DICTNAME;
   char *user_dictionary = NULL;
   hashset_ref hashset = new_hashset ();
   yy_flex_debug = false;

   // Scan the arguments and set flags.
   opterr = false;
   for (;;) {
      int option = getopt (argc, argv, "nxyd:@:");
      if (option == EOF) break;
      switch (option) {
         char optopt_string[16]; // used in default:
         case 'd': user_dictionary = optarg;
                   break;
         case 'n': default_dictionary = NULL;
                   break;
         case 'x': if(debugmode) extradebug = true; debugmode = true;
                   break;
         case 'y': yy_flex_debug = true;
                   break;
         case '@': set_debugflags (optarg);
                   if (strpbrk (optarg, "@y")) yy_flex_debug = true;
                   break;
         default : sprintf (optopt_string, "-%c", optopt);
                   print_error (optopt_string, "invalid option");
                   break;
      }
   }

   // Load the dictionaries into the hash table.
   load_dictionary (default_dictionary, hashset);
   load_dictionary (user_dictionary, hashset);

   // Read and do spell checking on each of the files.
   if (optind >= argc) {
      yyin = stdin;
     // spellcheck (STDIN_NAME, hashset);
      spellcheck(hashset);
   }else {
      int fileix = optind;
      for (; fileix < argc; ++fileix) {
         DEBUGF ('m', "argv[%d] = \"%s\"\n", fileix, argv[fileix]);
         char *filename = argv[fileix];
         if (strcmp (filename, STDIN_NAME) == 0) {
            yyin = stdin;
           // spellcheck (STDIN_NAME, hashset);
            spellcheck(hashset);
         }else {
            yyin = open_infile (filename);
            if (yyin == NULL) continue;
            //spellcheck (filename, hashset);
            spellcheck(hashset);
            fclose (yyin);
         }
      }

   }
   
      if(debugmode) debug_hash(hashset);
      if(extradebug) superdebug(hashset);
   yycleanup ();
   free_hashset(hashset);
   free_errors();
   return Exit_Status;
}

