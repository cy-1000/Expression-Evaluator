/*
NAME: <Cy Hynes>
LOGIN: <cs12fcf>
PID: <A14179344>
*/


#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include <string.h>

//Type conversions starts here//

char* charToString(char c) {
	char *str = (char*)malloc(sizeof(char)*TWO);
	str[ZERO] = c;
	str[ONE] = '\0';
	return str;
}
char stringToChar(char* str) {
	return str[ZERO];
}

char* intToString(int res) {
	char *str = (char*)malloc(BUFSIZ);
	sprintf(str,"%d",res);
	return str;
}

int stringToInt(char* str) {
	return atoi(str);
}
//Type conversions end here

// --------------------------------------------------------------------------

//Helper function to return precedence of operator
int precedence(char x) {
	if(x == '+' || x == '-'){
		return ONE;
	}
	if (x == '*' || x == '/' || x == '%'){
		return TWO;
	}
	return -1;
}

//converts an infix expression into postfix. 
char* convertToPostFix(char* str) {

	Stack *operatorStack = stack_init();
	int idxpostfix = 0;
	int strlength = strlen(str);
	char* postfix = malloc(sizeof(char) * strlength+1); //+1 for terminaing char
	int i;

	for(i=0; i<strlength; i++){
		//printf("iteration %d , current postfix string %s \n" , i, postfix);
		// Left Parentheses case
		if (str[i] == '('){
			push(operatorStack, charToString(str[i]));
			continue;
		}

		//Right Parentheses case
		if (str[i] == ')'){

			while (stringToChar(peek(operatorStack)) != '('){
				postfix[idxpostfix] = stringToChar(pop(operatorStack));
				idxpostfix++;
			}
			if(stringToChar(peek(operatorStack)) == '('){
				pop(operatorStack);
			}
			continue;
		}

		//Operator case
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || 
			str[i] == '%'){
				while(!isEmpty(operatorStack) &&
				 precedence(stringToChar(peek(operatorStack))) >= precedence(str[i])){
					postfix[idxpostfix] = stringToChar(pop(operatorStack));
					idxpostfix++;
				}
			push(operatorStack, charToString(str[i]));
			continue;
		}

		//Operand case
		else{ 
			postfix[idxpostfix] = str[i];
			idxpostfix++;
			continue;
		}

	}
	//Put rest of operators to the postfix expression
	while(!isEmpty(operatorStack)){
		if (precedence(stringToChar(peek(operatorStack))) == -1){
			pop(operatorStack);
			continue;
		}
		
		postfix[idxpostfix] = stringToChar(pop(operatorStack));
		idxpostfix++;
	}

	//terminate the postfix string with a \0 and return 
	postfix[idxpostfix] = '\0';
	return postfix;
}


// calculates the answer of a postfix expression.
int calculateExpression(char* str) {
	Stack *storage = stack_init();
	int len = strlen(str);
	int *answer = malloc (sizeof(int) *1 ); 
	int i;
	int num1;
	int num2;
	for (i=0; i<len; i++){
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' 
			|| str[i] == '%'){
			//retrieve the last two numbers pushed onto 
			//the stack as that is what the operator will work on
			num1 = stringToInt(pop(storage));
			num2 = stringToInt(pop(storage));

			int temp;
			char* tempstring;

			if (str[i] == '+'){
				temp = num2 + num1; 
				tempstring = intToString(temp);
				//push result back onto the stack
				push(storage, tempstring); 
			}
			if (str[i] == '-'){
				temp = num2 - num1;
				tempstring = intToString(temp);
				push(storage, tempstring);
			}
			if (str[i] == '*'){
				temp = num2 * num1;
				tempstring = intToString(temp);
				push(storage, tempstring);
			}
			if (str[i] == '/'){
				temp = num2 / num1;
				tempstring = intToString(temp);
				push(storage, tempstring);
			}
			if (str[i] == '%'){
				temp = num2 % num1;
				tempstring = intToString(temp);
				push(storage, tempstring);
			}
		}
		else{
			//if it is an operand push to stack.
			push(storage, charToString(str[i]));  
		}
}
	//the stack will have only one element in it which is the answer. 
	answer[0] = stringToInt(pop(storage)); 
	//free(answer); not sure if this is needed here.
	return *answer; 
}

//main method
int main(int argc, char **argv) {
	
	if(argc<TWO) {
		printf(STR_INCORRECT_ARGUMENT);
	} else {
		
		char* input = argv[1];  

		char* postfix = malloc (sizeof(char*) *ONE);
		strcpy(postfix, convertToPostFix(input));

		int answer = calculateExpression(postfix);
		
		printf("Input: %s", input);
		printf("\nOutput:");
		printf(STR_POSTFIX_EXPRESSION,postfix);
		printf(STR_RESULT,answer);
		printf("\n");

		//free(input);
		free(postfix);
	}
	return EXIT_SUCCESS;
}
