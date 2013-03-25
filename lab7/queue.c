/* $Id: queue.c,v 1.34 2012-11-19 19:26:39-08 - - $ */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define STUBPRINTF(...) fprintf (stderr, __VA_ARGS__);

static char *queue_tag = "struct queue";
static char *queuenode_tag = "struct queuenode";

typedef struct queuenode *queuenode_ref;

struct queuenode {
   char *tag;
   queue_item_t item;
   queuenode_ref link;
};

struct queue {
   char *tag;
   queuenode_ref front;
   queuenode_ref rear;
};

queue_ref new_queue (void) {
   queue_ref new = malloc(sizeof(struct queue));
   assert(new!=NULL);
   new->front = NULL;
   new->rear = NULL;
   new -> tag = queue_tag;
   return new;
}

void free_queue (queue_ref queue) {
   assert (is_queue (queue));
   assert (isempty_queue (queue));
   memset (queue, 0, sizeof (struct queue));
   free (queue);
}

void insert_queue (queue_ref queue, queue_item_t item) {
   assert (is_queue (queue));
   queuenode_ref new = malloc(3*sizeof(struct queuenode));
   assert(new!=NULL);
   new -> item = item;
   new -> link = NULL;
   new -> tag = queuenode_tag;
   if(queue -> front==NULL){
     queue -> front = new;
     queue -> rear = new;
   }
   else
       queue ->  rear -> link = new;
       queue -> rear = new;
}

queue_item_t remove_queue (queue_ref queue) {
   assert (is_queue (queue));
   assert (! isempty_queue (queue));
   queue_item_t temp = queue -> front -> item;
   queuenode_ref tnode = queue -> front;
  // free(queue ->front);
   queue -> front = queue -> front -> link;
   free(tnode);
   return temp;
}

bool isempty_queue (queue_ref queue) {
   assert (is_queue (queue));
   return queue->front == NULL;
}

bool is_queue (queue_ref queue) {
   return queue != NULL && queue->tag == queue_tag;
}

