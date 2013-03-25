//Lauren Crowther lcrowthe
//Steven Morad smorad

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 16
#define EMPTY (-1)
double stack[STACK_SIZE];
int top = EMPTY;
int pos = 0;




double pop(void){
double temp = stack[top];
	top--;
	return temp;
}

void push(double d){
	if(top<14){
		top++;
		stack[top] = d;
	}
	else{
		printf("%s", "Stack overflow, input discarded");
	}
}

void clearStack(void){
	top = EMPTY;
}

void printStack(void){
	for(int i = top; i>-1; i--){
		printf("%22.15g\n",stack[i]);
	}
}




int main (int argc, char **argv) {

   while(1) {
      char buffer[4096];

      // Read in a word and stop at EOF.
      int scanct = scanf ("%4095s", buffer);
      if (scanct == EOF) {
         printf ("EOF\n");
         break;
      }
      size_t length = strlen (buffer);

      // Skip to end of line if a comment.
      if (buffer[0] == '#') {
         scanf ("%4095[^\n]", buffer);
         continue;
      }

      // Tell whether or not it is a number.
      // If yes, print it and the string.
      // If not, print the endptr data.
      char *endptr = NULL;
      double number = strtod (buffer, &endptr);
      if (*endptr == '\0') {
		push(number);
      }else {
			char operator = buffer[pos];
			switch(operator){
				case '+':
					push(pop()+pop());
					break;
				case '-':
					push(-pop()+pop());
					break;
				case '*':
					push(pop()*pop());
					break;
				case '/':
					push(1/pop()*pop());
					break;
				case '~':
					clearStack();
					break;
				case ';':
					printStack();
					break;

				default:
					printf("Invalid operator");

			}
		
      }

   }
   return EXIT_SUCCESS;
}

