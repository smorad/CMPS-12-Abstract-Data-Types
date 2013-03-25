#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

typedef struct node *node_ref;

struct node{
    double value;
    node_ref link;
};


node_ref head = NULL;
int EXIT_STATUS = 0;
int opt = 0;
bool debug = false;


void sort(node_ref node){
node_ref prev = NULL;
node_ref curr = head;
while(curr!= NULL){
    if((curr->value - node->value) >0)
        break;
    prev=curr;
    curr=curr->link;
}
node -> link = curr;
if(prev == NULL)
    head = node;
else
    prev->link = node;



}


void printlist(void){
node_ref curr = head;
node_ref temp = NULL;
while(curr!=NULL){
    if(!debug)
        printf("%24.15g\n",curr->value);
    else
        printf("%p-> {%lg, %p]\n", curr, curr->value, curr->link);
    temp = curr;
    curr = curr -> link;
    free(temp);     
    }
}

void readstdin(void){
double num = 0;
int input = 0;  
    while(true){
        input = scanf("%lg", &num);
        if(input==EOF)
            break;
        if(input==0)
            EXIT_STATUS = EXIT_FAILURE;  
        node_ref node = malloc(sizeof(struct node));
        assert(node!=NULL);
        node -> value = num;
        node -> link = NULL;
        sort(node);
        }
printlist();    
}






int main(int argc, char **argv){
while((opt = getopt(argc, argv, "d"))!= -1){
    if((opt = 'd')){
        debug = true;
} 
    else
        debug = false;  
}
    readstdin();
return EXIT_STATUS;
}
