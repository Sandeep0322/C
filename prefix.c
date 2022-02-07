
//This program converts the expression infix to postfix and prefix.
//Preprocessing directive ctype is used for check the numeric alphabet is there or not.

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>                                          
#define MAX 20

/* **************************************
 *  		Functions		*
 * *************************************/

int postfix ();

/**

 * @brief convert infix to postfix.

 * @param expression is read to char pointer.
 * @param char pointer will read one by one operand/operator.
 * @param if any operator exsits it push to stack and by checking some conditions it will pop.

 * This will not return any value or expression
 * it will check the condition and it will print in the function itself.

 **/

char *prifix( char infix[20], char prefix[20] );

/**

 * @brief convert infix to prefix.

 * The infix expression will reverse first 
 * @param it checks the conditions,push and pop operations are done to the stack by the conditions .
 * @param In this pop operators and operands are read to a string (prefix).
 
 * @return string(prefix) expression is return to main function.
 
 * return expression is not prefix expression.
 * reverse the return expression then we will get the prefix expression.

 **/

char *reverse ( char array[30] );

/**

 * @brief reverse the string(expression) and return.

 * @param reverse is done by looping function.
 * @param the reverse string is copy to original string.

 * @return string(expression) is return.

 **/

char pop();

/**

 * @brief stack operator it will return.

 * @param stack operator is read to a char varaible
 * @return the operator

 **/

void push( char symbol );

/**

 * @breif The operator is pushing to stack.

 **/

int prcd( char symbol );

/**

 * @breif precedance of operators.
 * @param it will check and return the operator.
 * @return it return the value. 

 **/

/* **************************************
 *  	     global declaration		*
 * *************************************/

//Stack is used to temp store operator
int top = -1 ;
char stack[MAX];

void main() {

	char infix[20],prefix[20],temp;

	printf("Enter infix operation: ");
	scanf("%s",infix);

	printf("\n");

	printf("infix expression : %s \n",infix);
	postfix(infix);

	printf("\n");

	prifix(infix,prefix);

        //In prefix we reverse the exprission twice
	reverse(prefix); 
                               
	puts((prefix));
	printf("\n");
   
}

char *prifix(char infix[20],char prefix[20]) {
	int i,j = 0;
	char symbol;
	
        //First we will store # in stack in prefix
	stack[++top] = '#';
	
	//reverse the expression and do the postfix operation
	reverse(infix);      
                           
	printf("prefix expression : ");
	for (i = 0;i<strlen(infix);i++) {

		//One to one characters will read to symbol variable
		symbol = infix[i];   
                         
		if (isalnum(symbol)) {

			prefix[j] = symbol;
			j++;

		}
		else {
			if (symbol == ')' ) {

				//If closed braket exists it pushes to stack			
				push(symbol);   
                    
			} 
			else if(symbol == '('){

				//If open bracket exists untill closed bracket comes stack symbols will print
				while (stack[top] != ')' ){

					prefix[j] = pop();
					j++;

				}
				pop();
			}
			else{

				//If precedance/priority checks not satisfy it will push to stack
				if (prcd(stack[top]) <= prcd(symbol)) {

					push(symbol);

				} 
				else {

					// if priority satisfy it will pop to a string
					while(prcd(stack[top]) >= prcd(symbol)){

						prefix[j] = pop();
						j++;

					}
					push(symbol);
				}
			}
		}
	}

 	//We stored # in stack first loaction until it comes it will pop to string
	while (stack[top] != '#'){

		prefix[j] = pop();
		j++;

	}
	prefix[j] = '\0';
	return prefix;
}

char *reverse(char array[30]){
	int i,j;
	char temp[100];
	
	//This reverse the original expression 
	for (i = strlen(array)-1, j = 0; i+1 != 0; --i, ++j) {

		temp[j] = array[i];

	}

	temp[j] = '\0';
	strcpy(array,temp);
	return array;
}

char pop() {
	char a;

	//Whatever the operator at stack loaction it will return
	a = stack[top--]; 
                                
	return a;
}

void push(char symbol) {
	// Whatever the operator it will store in stack by pushing
	stack[++top] = symbol;                            
}

int prcd(char symbol) {
	switch(symbol){
		case '+':
		case '-':
		return 2;
		break;

		case '*':
		case '/':
		return 4;
		break;

		case '$':                                    
		case '^':
		return 6;
		break;

		case '#':
		case '(':
		case ')':
		return 1;
		break;
	}
}

int postfix(char exp[20]){
	char *e, x;
	printf("\n");

	// expression is read to pointer of e
	e = exp;                                                     
	
	printf("postfix expression : ");
	while(*e != '\0'){
	    if(isalnum(*e)){
	        printf("%c",*e);
            }

	    //It is not taken reversed expression so we can directly do same like above
	    else if(*e == '(') {                                        
	        push(*e);
	    }

	    else if(*e == ')'){
	        while((x = pop()) != '(')
	            printf("%c", x);
	    }

	    else{
	        while(prcd(stack[top]) >= prcd(*e))
	            printf("%c",pop());
	        push(*e);
	    }
	    e++;
	}
	
	while((top != -1) && (stack[top] != '#')){

	    printf("%c",pop());

	}
	printf("\n");
	return 0;
}
