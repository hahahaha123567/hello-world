#include <stdio.h>
#include <stdlib.h>
#define ERROR 1e8
typedef int ElementType;
typedef enum { push, pop, end } Operation;

typedef struct StackRecord *Stack;
struct StackRecord  {
    int Capacity;       /* maximum size of the stack array */
    int Top1;           /* top pointer for Stack 1 */
    int Top2;           /* top pointer for Stack 2 */
    ElementType *Array; /* space for the two stacks */
};

Stack CreateStack( int MaxElements );
int IsEmpty( Stack S, int Stacknum );
int IsFull( Stack S );
int Push( ElementType X, Stack S, int Stacknum );
ElementType Top_Pop( Stack S, int Stacknum );

Operation GetOp();  /* details omitted */
void PrintStack( Stack S, int Stacknum ); /* details omitted */

int main()
{
    int N, Sn, X;
    Stack S;
    int done = 0;

    scanf("%d", &N);
    S = CreateStack(N);
    while ( !done ) {
        switch( GetOp() ) {
        case push: 
            scanf("%d %d", &Sn, &X);
            if (!Push(X, S, Sn)) printf("Stack %d is Full!\n", Sn);
            break;
        case pop:
            scanf("%d", &Sn);
            X = Top_Pop(S, Sn);
            if ( X==ERROR ) printf("Stack %d is Empty!\n", Sn);
            break;
        case end:
            PrintStack(S, 1);
            PrintStack(S, 2);
            done = 1;
            break;
        }
    }
    return 0;
}
#include <string.h>
int Push( ElementType X, Stack S, int Stacknum )
{
	if(IsFull(S))
		return 0;
	switch (Stacknum){
		case 1: S->Array[++S->Top1] = X;
				break;
		case 2: S->Array[--S->Top2] = X;
	}
	return 1;
}
ElementType Top_Pop( Stack S, int Stacknum )
{
	ElementType temp;
	if(IsEmpty(S, Stacknum))
		return ERROR;
	switch (Stacknum){
		case 1: temp = S->Array[S->Top1--];
				break;
		case 2: temp = S->Array[S->Top2++];
	}
	return temp;
}

Stack CreateStack( int MaxElements )
{
	Stack s;
	s = (Stack)malloc(sizeof(struct StackRecord));
	s->Capacity = MaxElements;
	s->Array = (ElementType *)malloc(sizeof(ElementType) * MaxElements);
	s->Top1 = -1;
	s->Top2 = MaxElements;
	return s;
}

int IsEmpty( Stack S, int Stacknum )
{
	switch (Stacknum){
		case 1: return(S->Top1 == -1);
		case 2: return(S->Top2 == S->Capacity);
	}
}

int IsFull( Stack S )
{
	return S->Top1 + 1 == S->Top2;
}

Operation GetOp()
{
	char p[5];
	scanf("%s", p);
	if(!strcmp(p, "Push"))
		return push;
	else if(!strcmp(p, "Pop"))
		return pop;
	else if(!strcmp(p, "End"))
		return end;
}

void PrintStack( Stack S, int Stacknum )
{
	int p1 = S->Top1, p2 = S->Top2;
	if(Stacknum == 1){
		printf("Pop from Stack 1:");
		while(p1 != -1)
		printf(" %d", S->Array[p1--]);
	printf("\n");
	}
	else if(Stacknum == 2){
		printf("Pop from Stack 2:");
		while(p2 != S->Capacity)
			printf(" %d", S->Array[p2++]);
	}
}
