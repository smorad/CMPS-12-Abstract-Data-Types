// $Id: list4.c,v 1.15 2012-11-05 18:14:43-08 - - $

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node *node_ref;
struct node {
   char *word;
   node_ref link;
};

int main (int argc, char **argv) {
   node_ref head=NULL;
   for (int argi = 0 ; argi < argc; argi++) {
      node_ref node = malloc (2*sizeof (node_ref));
      assert (node != NULL);
      node->word = argv[argi];
      node->link = head;
      head = node;
   }
   for (node_ref curr = head; curr->link != NULL; curr = curr->link) {
      printf ("%p->node {word=%p->[%s], link=%p}\n",
              curr, curr->word, curr->word, curr->link);
   }
   node_ref node = head;
   while(node!=NULL){
     node_ref temp = node;
     node=node->link;
     free(temp); 
   }
      return EXIT_SUCCESS ;
}
