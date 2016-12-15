#include <stdio.h>
#include "stack.h"

//will not compile until you provide a decleration for stack
int main(int argc, char * argv[]) {

	//will not compile till you provide a decleration for stack 
	Stack* stack = stack_init();

	if (stack == NULL) {
		fprintf(stderr, STR_ERR_MEM);
		return EXIT_FAILURE;
	}

	printf(STR_STACK_WELCOME);
	printf(STR_PROMPT);

	//to store strings from stdin
	char readin[BUFSIZ];
	char* popped;
	char* peeked;
	
	int choice = STACK_EMPTY;
	
	//Loop until user wants to exit
	while (choice!=EXIT) {

		scanf("%d",&choice);
		if(choice==EXIT) {
			break;
		}
		
		switch(choice) {
			
			case PUSH: 
					printf(STR_PUSH_PROMPT);
					scanf("%s",readin);
					push(stack,readin);
					printf(STR_PUSH_SUCCESS, readin);
					break;
					
			case POP: 
					popped = pop(stack);
					if(popped!=NULL) {
						printf(STR_POP_SUCCESS, popped);
					} else {
						printf(STR_POP_FAILURE);
					}
					break;
					
			case PEEK: 
					peeked = peek(stack);
					if(peeked!=NULL) {
						printf(STR_PEEK_SUCCESS, peeked);
					} else {
						printf(STR_PEEK_FAILURE);
					}
					break;
					
			case PRINT: 
					print(stack);
					break;
					
			case ISEMPTY:
					if(isEmpty(stack)) {
						printf(STR_PRINT_NO_ITEMS);
					} else {
						printf(STR_PRINT_NOT_EMPTY);
					}
					break;
					
			default: printf(STR_ERR_UNKNOWN);
					
		}
		printf("\n");

		printf(STR_PROMPT);
	}

	//destroy stack
	stack_delete(stack);
	free(stack);
	printf(STR_GOODBYE);
	return EXIT_SUCCESS;
}
