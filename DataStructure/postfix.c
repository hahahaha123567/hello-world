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
	//printf("push: %f\n", m);
}

ElementType pop(stack s)
{
	if(s->top == -1){
		//printf("pop: infinity\n");
		return Infinity;
	}
	else{
		//printf("pop: %f\n", s->array[s->top]);
		return s->array[(s->top)--];
	}
}
