// $Id: list.c,v 1.102 2012-11-25 12:52:30-08 - - $

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "debugf.h"
#include "list.h"

static char *list_tag = "struct list";
static char *listnode_tag = "struct listnode";

typedef struct listnode *listnode_ref;

struct list {
   //
   // INVARIANT:  Both head and last are NULL or neither are NULL.
   // If neither are null, then following listnode next links from
   // head will get to last, and prev links from last gets to head.
   //
   char *tag;
   listnode_ref head;
   listnode_ref curr;
   listnode_ref last;
};

struct listnode {
   char *tag;
   char *line;
   listnode_ref prev;
   listnode_ref next;
};

void debugdump_list (list_ref list) {
   listnode_ref itor = NULL;
   assert (is_list (list));
   fflush (NULL);
   fprintf (stderr,
            "\n[%p]->struct list {tag=[%p]->[%s];"
            " head=[%p]; curr=[%p]; last=[%p]; }\n",
            list, list->tag, list->tag,
            list->head, list->curr, list->last);
   printf("%c", '\n');
   for (itor = list->head; itor != NULL; itor = itor->next) {
      fprintf (stderr,
               "[%p]->struct listnode {tag=[%p]->[%s];"
               " line=[%p]=[%s]; prev=[%p]; next=[%p]; }\n",
               itor, itor->tag, itor->tag, itor->line, itor->line,
               itor->prev, itor->next);
      printf("%c", '\n');
   }
   fflush (NULL);
}


list_ref new_list (void) {
   //
   // Creates a new struct list.
   //
   list_ref list = malloc (sizeof (struct list));
   assert (list != NULL);
   list->tag = list_tag;
   list->head = NULL;
   list->curr = NULL;
   list->last = NULL;
   return list;
}

void free_list (list_ref list) {
   assert (is_list (list));
  // assert (empty_list (list));
   list -> curr = list -> head;
}

bool movehead(list_ref list){
   assert(list -> head != NULL); 
   list -> curr = list -> head;
   return true; 
}

bool moveprev(list_ref list){    
   if(list -> curr == list -> head)  
      return false;                     
   list -> curr = list -> curr -> prev;
   return true;
}

bool movenext(list_ref list){
   if(list -> curr == list -> last)
      return false;
   list ->curr = list -> curr -> next;
   return true;
}

bool movelast(list_ref list){
   assert(list -> last != NULL);
   list -> curr = list -> last;
   return true;
}

char* set_last(list_ref list){
   list -> curr = list -> last;
   return list -> last -> line;
}

int get_size(list_ref list){
   int count = 0;
   listnode_ref temp = list -> head;
   while(temp != NULL){
      temp = temp -> next;
      count++;
   }
return count;
}

bool setmove_list (list_ref list, list_move move) {
   assert (is_list (list));
   switch (move) {
      case MOVE_HEAD:
           movehead(list);
           break;
      case MOVE_PREV:
           moveprev(list);
           break;
      case MOVE_NEXT:
           movenext(list);
           break;
      case MOVE_LAST:
           movelast(list);
           break;
      default: ;
   }
   return false;
}

char *viewcurr_list (list_ref list) {
   assert (is_list (list));
   if(list -> curr == NULL)
      return NULL;
   return list -> curr -> line;
}

void insert_list_before(list_ref list, char* line){
   assert(is_list(list));
   listnode_ref new = malloc(sizeof(struct listnode));
   assert(new!=NULL);
   new -> line = line;
   new -> tag = listnode_tag;
   if(list -> head == NULL){
      list -> head = new;
      list -> last = new;
      list -> head -> next = NULL;
      list -> head -> prev = NULL; 
   }
   else if(list -> curr -> prev == NULL){
      new -> next = list -> head;
      new -> prev = NULL;
      list -> head = new;
   }
  // else if(list -> curr -> next == NULL){        //error
  //    new -> next = list -> curr;
  //    new -> prev = list -> last -> prev;
  //    list -> curr -> prev = new;
     // new -> next = list -> last;
  // }
   else{                                          //works
      listnode_ref a = list -> curr -> prev;
      listnode_ref b = new;
      listnode_ref c = list -> curr;
      b -> next = a -> next;
      b -> prev = a;
      a -> next = b;
      c -> prev = b;
   }
   if(list -> head == new)
      new -> prev = NULL;
   if(list -> last == new)
      new -> next = NULL;
   list -> curr = new;
}

void insert_list (list_ref list, char *line) {
   assert (is_list (list));
   listnode_ref new = malloc(sizeof(struct listnode));
   assert(new != NULL);
   new -> line = line;
   new -> tag = listnode_tag;
   new -> next = NULL;
   new -> prev = NULL;
   if(list ->head == NULL){
      list -> head = new;
      list -> last = new;
      }
   else if(list -> curr -> prev == NULL){  
      new -> next = list -> curr -> next;
      new -> prev = list -> head;
      list -> head -> next = new;
    }
   else if(list -> curr -> next ==NULL){
      list -> curr -> next = new;
      new -> prev = list -> last;
      new -> next = NULL;
      list -> last = new;
    }
   else{
      listnode_ref a = list -> curr;
      listnode_ref b = new;
      listnode_ref c = list -> curr -> next;
      b -> next = a -> next;
      b -> prev = a;
      a -> next = b;
      c -> prev = b;    
   }
   if(new -> next == NULL)
      list -> last = new;
   if(new -> prev == NULL)
      list -> head = new;
   list -> curr = new;
}

void delete_list (list_ref list) {
   assert (is_list (list));
  // assert (! empty_list (list));
   if(empty_list(list) || list -> head == NULL )
      return;
   listnode_ref a = list -> curr -> prev;
   listnode_ref b = list -> curr;
   listnode_ref c = list -> curr -> next;
   if(list -> head == list -> curr){
      listnode_ref temp = list -> head;
      list -> head = list -> head -> next;
      free(temp -> line);
      free(temp);
      list -> curr = list -> head;
   }
   else if(list -> last == list -> curr){
      listnode_ref temp = list -> last;
      list -> last = list -> last -> prev;
      free(temp->line);
      free(temp);
      list -> curr = list -> last;
      list -> last -> next = NULL;
   }
   else{
      a -> next = b -> next;
      c -> prev = b -> prev;
      list -> curr = c;
      free(b -> line);
      free(b);
   }
}

bool empty_list (list_ref list) {
   assert (is_list (list));
   return list->head == NULL;
}

bool is_list (list_ref list) {
   return list != NULL && list->tag == list_tag;
}

