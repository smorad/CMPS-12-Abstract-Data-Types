// $Id: hashset.c,v 1.131 2012-12-05 17:23:17-08 - - $

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#include "debugf.h"
#include "hashset.h"
#include "strhash.h"

#define HASH_NEW_SIZE 15;

struct hashset {
   size_t length;
   int load;
   char **array;
};

hashset_ref new_hashset (void) {
   hashset_ref new = malloc (sizeof (struct hashset));
   assert (new != NULL);
   new->length = HASH_NEW_SIZE;
   new->load = 0;
   new->array = malloc (new->length * sizeof (char*));
   assert (new->array != NULL);
   for (size_t index = 0; index < new->length; ++index) {
      new->array[index] = NULL;
   }
   DEBUGF ('h', "%p -> struct hashset {length = %d, array=%p}\n",
                new, new->length, new->array);
   return new;
}

void free_hashset (hashset_ref hashset) {
   DEBUGF ('h', "free (%p), free (%p)\n", hashset->array, hashset);
   for(unsigned int i=0; i<hashset -> length; i++)
      if(hashset -> array[i] != NULL)
         free(hashset -> array[i]);
   memset (hashset->array, 0, hashset->length * sizeof (char*));
   free (hashset->array);
   memset (hashset, 0, sizeof (struct hashset));
   free (hashset);
}

void doublearray(hashset_ref hashset){
   bool loop = false;
   size_t nlength = 1+ 2* hashset -> length;
   char** narray = malloc(nlength * sizeof (char*)); 
   for(unsigned int i=0; i<nlength; i++)
      narray[i] = NULL;
   DEBUGF('h', "Trying to double array to size: %zu\n", nlength);
   DEBUGF('h', "Load is: %d\n", hashset -> load);
   fflush(NULL);
   for(hashcode_t count = 0; count < hashset -> length; count++){
      if(hashset -> array[count] != NULL){
         hashcode_t hash =strhash(hashset->array[count])%nlength; 
         while(true){
         if(hash == nlength && !loop){
            loop = true;
            hash = 0;
         } 
         if(narray[hash] == NULL) break;  
         else hash++;
         }
      narray[hash] = hashset -> array[count];                  
      }                                                               
   }
   char** temp = hashset -> array;
   hashset -> array = narray;
   hashset -> length = nlength;
   free(temp);  
}


void put_hashset (hashset_ref hashset, char *item) {
   hashcode_t hash = strhash(item) %hashset -> length;
   bool loop = false;
   if(hashset-> load *(unsigned int)4 > hashset -> length)
      doublearray(hashset);  
   while(true){
      if(hashset -> array[hash]== NULL) break;
      if(strcmp(hashset -> array[hash], item)==0) return;
      if(!loop && (hash == hashset -> length-1)){ 
         DEBUGF('h', "LOOP'D around array\n");
         loop = true;
         hash = 0;
      }
      hash++;
   }
   hashset -> array[hash] = item;
   hashset -> load ++;
   DEBUGF('h', "item: %s placed in slot: %zd.\n load: %d\n", 
item, hash, hashset -> load);
   DEBUGF('h', "slot: %zd is now %s\n", hash, hashset -> array[hash]);
    
}

bool has_hashset (hashset_ref hashset, char *item) {
   if(item == NULL) return false;
   hashcode_t hash = strhash(item) % hashset ->length;
   for(unsigned int x=0; x<hashset->length-hash;x++){ 
      if(hashset->array[hash+x]==NULL) return false;
      if(strcmp(hashset -> array[hash+x], item)==0) return true;
   }
   return false;
}

/*   while(hashset -> array[hash] != NULL){
     if(!loop && (hash == hashset -> length)){
         loop = true;
         hash = 0;
      } 
      if(strcmp(hashset -> array[hash], item)==0)
        return true; 
      hash++;
   }
   return false;
}*/

void superdebug(hashset_ref hashset){
for(unsigned int i = 0; i<hashset -> length; i++)
   if(hashset -> array[i] != NULL)
      printf("array[%10d] = %12zu \"%s\"\n", i, 
strhash(hashset -> array[i])% hashset -> length,
 hashset -> array[i]);
}


void debug_hash(hashset_ref hashset){
   //int clustersize = 0;
   int clusters[1024] = {0};
   int count = 0;
   int pos = 0;
   printf("%7d words in hashset\n", hashset -> load);
   printf("%7zd length of hash array\n" , hashset -> length);
   while((unsigned int)pos < hashset -> length){
      if(hashset -> array[pos] != NULL){
         count++;
      }
      else{
          ++clusters[count];
          count = 0;
      }
   pos++;
   }
   for(int i=0; (unsigned int)i<sizeof(clusters)/sizeof(int); i++)
      if(clusters[i]!=0 && i!=0)
         printf("%7d clusters of size %7d\n",clusters[i],i);
}
