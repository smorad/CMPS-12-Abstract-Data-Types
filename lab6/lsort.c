#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>


typedef struct node *node_ref;
typedef char *cstring;
struct node{
    cstring value;
    node_ref link;
};

int EXIT_STATUS = 0;
node_ref head = NULL;

int opt = 0;
bool debug = false;


void sort(node_ref node){
node_ref prev = NULL;
node_ref curr = head;
while(curr!= NULL){
    if((strcmp(curr->value,  node->value)) >0)
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
        printf("%s\n",curr->value);
    else
        printf("%p-> {%s, %p]\n", curr, curr->value, curr->link);
    temp = curr;
    curr = curr -> link;
    free(temp->value); 
    free(temp);     
    }
}

void readstdin(void){
char buffer[72];
    while(true){
        char *input = fgets(buffer, sizeof buffer, stdin);
        if(input==NULL)
            break;
        char *nl = strchr(buffer, '\n');
        if(nl!=NULL)
            *nl='\0';
        else{
            fprintf(stderr, "%s\n", "Unterminated line detected");
            EXIT_STATUS = EXIT_FAILURE;
        }   
        node_ref node = malloc(sizeof(struct node));
        assert(node!=NULL);
        node -> value = strdup(buffer);
        assert(node->value!=NULL);
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
