#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>

int EXIT_STATUS = EXIT_SUCCESS;
int seconds = 15552000;

void getinfo(char* name){
   struct stat stat;
   char timebuff[1024];
   char symlink_buff[1024];
   int readlink_status = readlink(name, symlink_buff, sizeof(symlink_buff));
   time_t now = time(NULL);
   int status = lstat(name, &stat);  //put lsat struct stat into buf
   if(status != 0){
      EXIT_STATUS = EXIT_FAILURE;
      fprintf(stderr, strerror(errno), "%s\n");
      fflush(NULL);
      return;
   }
   if(readlink_status == -1)
      printf("%06o %8ld %8ld %s\n", stat.st_mode, stat.st_size, stat.st_mtime, name);
   else
      printf("%06o %8ld %8ld %s -> %s\n", stat.st_mode, stat.st_size, stat.st_mtime, name, symlink_buff);
   struct tm *tm = localtime(&stat.st_mtime);   //localtime of file 
   time_t filetime = stat.st_mtime;
   if(now - filetime > seconds || filetime - now > seconds)
      strftime(timebuff, 1024, "%b %e  %Y", tm);
   else
      strftime(timebuff, 1024, "%b %e %R", tm);
   printf("%s\n", timebuff);
}

int main(int argc, char** argv){
   argc = argc;
   if(argc>1)
      for(int count = 1; count < argc; count ++){
         getinfo(argv[count]);
      }
   else
      getinfo(".");

   return EXIT_STATUS;
}
