/*
Write a program to evaluate a postfix expression. 
You only have to handle four kinds of operators: +, -, x, and /.
where expr points to a string that stores the postfix expression. 
It is guaranteed that there is exactly one space between any two operators or operands. 
The function EvalPostfix is supposed to return the value of the expression. 
If it is not a legal postfix expression, EvalPostfix must return a special value Infinity which is defined by the judge program.

**it is just a practice of stack**
**'-' can be either a unary operator or a binocular operator**

Sample Input 1:
11 -2 5.5 * + 23 7 / -

Sample Output 1:
-3.285714

Sample Input 2:
11 -2 5.5 * + 23 0 / -

Sample Output 2:
ERROR
*/



#include <stdio.h>
#include <stdlib.h>

typedef double ElementType;
#define Infinity 1e8
#define Max_Expr 30   /* max size of expression */

ElementType EvalPostfix( char *expr );

int main()
{
    ElementType v;
    char expr[Max_Expr];
    gets(expr);
    v = EvalPostfix( expr );
    if ( v < Infinity )
        printf("%f\n", v);
    else
        printf("ERROR\n");
    return 0;
}

typedef struct stackrecord *stack; 
typedef struct stackrecord{
	int top;
	ElementType *array;
};

void push(ElementType m, stack s);
ElementType pop(stack s);

ElementType EvalPostfix( char *expr )
{
	ElementType op1, op2, ans;
	stack s = (stack)malloc(sizeof(struct stackrecord));
	s->array = (ElementType *)malloc(sizeof(ElementType) * 30);
	s->top = -1;
	int i = 0;
	while(expr[i] != '\0'){
		if(expr[i] == ' ')
			i++;
		if(expr[i] == '+'){
			op1 = pop(s);
			if(op1 == Infinity)
				return Infinity;
			op2 = pop(s);
			if(op2 == Infinity)
				return Infinity;
			push(op1 + op2, s);
			i++;
		}
		else if(expr[i] == '-' && (expr[i+1] == ' ' || expr[i+1] == '\0')){
			op1 = pop(s);
			if(op1 == Infinity)
				return Infinity;
			op2 = pop(s);
			if(op2 == Infinity)
				push(-op1, s);
			else
				push(op2 - op1, s);
			i++;
		}
		else if(expr[i] == '*'){
			op1 = pop(s);
			if(op1 == Infinity)
				return Infinity;
			op2 = pop(s);
			if(op2 == Infinity)
				return Infinity;
			push(op1 * op2, s);
			i++;	
		}
		else if(expr[i] == '/'){
			op1 = pop(s);
			if(op1 == Infinity || op1 == 0)
				return Infinity;
			op2 = pop(s);
			if(op2 == Infinity)
				return Infinity;
			push(op2 / op1, s);
			i++;
		}
		else{
			push(atof(expr+i), s);
			while(expr[i] != ' '){
				if(expr[i] == '\0')
					break;
				else
					i++;
			}
			if(i == ' ')
				i++;
		}
	}
	if(s->top == 0)
		return s->array[s->top];
	else
		return Infinity;
}

void push(ElementType m, stack s)
{
	s->array[++(s->top)] = m;
}

ElementType pop(stack s)
{
	if(s->top == -1)
		return Infinity;
	else
		return s->array[(s->top)--];
}
