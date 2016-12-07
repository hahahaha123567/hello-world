#include <stdio.h>
#include <stdlib.h>

#define ElementType int
#define ERROR 1e5
typedef enum { push, pop, inject, eject, end } Operation;

typedef struct Node *PtrToNode;
struct Node {
    ElementType Element;
    PtrToNode Next, Last;
};
typedef struct DequeRecord *Deque;
struct DequeRecord {
    PtrToNode Front, Rear;
};
Deque CreateDeque();
int Push( ElementType X, Deque D );
ElementType Pop( Deque D );
int Inject( ElementType X, Deque D );
ElementType Eject( Deque D );

Operation GetOp();          /* details omitted */
void PrintDeque( Deque D ); /* details omitted */

int main()
{
    ElementType X;
    Deque D;
    int done = 0;

    D = CreateDeque();
    while (!done) {
        switch(GetOp()) {
        case push: 
            scanf("%d", &X);
            if (!Push(X, D)) printf("Memory is Full!\n");
            break;
        case pop:
            X = Pop(D);
            if ( X==ERROR ) printf("Deque is Empty!\n");
            break;
        case inject: 
            scanf("%d", &X);
            if (!Inject(X, D)) printf("Memory is Full!\n");
            break;
        case eject:
            X = Eject(D);
            if ( X==ERROR ) printf("Deque is Empty!\n");
            break;
        case end:
            PrintDeque(D);
            done = 1;
            break;
        }
    }
    return 0;
}

#include <string.h>

Deque CreateDeque()
{
	Deque d;
	PtrToNode head = NULL, tail =NULL, p = NULL;
	int i;
	d = (Deque)malloc(sizeof(struct DequeRecord));
	for(i = 0; i < 100; i++){
		p = (PtrToNode)malloc(sizeof(struct Node));
		if(head == NULL)
			head = p;
		else{
			tail->Next = p;
			p->Last = tail;
		}
		tail = p;
	}
	tail->Next = head;
	head->Last = tail;
	d->Rear = head;
	d->Front = head;
	return d;
}

int Inject( ElementType X, Deque D )
{
	if(D->Rear->Next == D->Front)
		return 0;
	D->Rear = D->Rear->Next;
	D->Rear->Element = X;
	return 1;
}
ElementType Pop( Deque D )
{
	if(D->Front == D->Rear)
		return ERROR;
	else if(D->Front->Next == D->Rear){
		D->Rear = D->Front;
		return D->Front->Next->Element;
	}
	ElementType tempnum = D->Front->Next->Element;
	PtrToNode temp = D->Front->Next;
	D->Front->Next = D->Front->Next->Next;
	free(temp); 
	return tempnum;
}
int Push( ElementType X, Deque D )
{
	PtrToNode p = (PtrToNode)malloc(sizeof(struct Node));
	p->Next = D->Front->Next;
	D->Front->Next->Last = p;
	D->Front->Next = p;
	p->Last = D->Front;
	p->Element = X;
	if(D->Front == D->Rear)
		D->Rear = D->Rear->Next;
	return 1;
}
ElementType Eject( Deque D )
{
	if(D->Rear == D->Front)
		return ERROR;
	D->Rear = D->Rear->Last;
	return D->Rear->Next->Element;
}

Operation GetOp()
{
	char op[7];
	scanf("%s", op);
	if(!strcmp(op, "Pop"))
		return pop;
	else if(!strcmp(op, "Push"))
		return push;
	else if(!strcmp(op, "Eject"))
		return eject;
	else if(!strcmp(op, "Inject"))
		return inject;
	else if(!strcmp(op, "End"))
		return end;
}
void PrintDeque( Deque D )
{
	printf("Inside Deque:");
	while(D->Rear != D->Front){
		printf(" %d", D->Front->Next->Element);
		D->Front = D->Front->Next;
	}
}

