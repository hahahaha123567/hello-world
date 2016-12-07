#include <stdio.h>
#include <stdlib.h>
typedef struct Node *PtrToNode;
struct Node  {
    int Coefficient;
    int Exponent;
    PtrToNode Next;
};
typedef PtrToNode Polynomial;

Polynomial Read(); /* details omitted */
void Print( Polynomial p ); /* details omitted */
Polynomial Add( Polynomial a, Polynomial b );

int main()
{
    Polynomial a, b, s;
    a = Read();
    b = Read();
    s = Add(a, b);
    Print(s);
    return 0;
}

Polynomial Add( Polynomial a, Polynomial b )
{
	Polynomial p1 = a, p2 = b, head = NULL, tail = NULL, ans = NULL;
	
	if(p1 == NULL && p2 == NULL){
    /*	head = (Polynomial)malloc(sizeof(struct Node));
    	head->Coefficient = 0;
    	head->Exponent = 0;
    	head->Next = NULL;*/
	}
    else if(p1 == NULL)
        return p2;
    else if(p2 == NULL)
        return p1;
	while(p1 || p2){
        ans = (Polynomial)malloc(sizeof(struct Node));
        if(!p1){
            ans->Exponent = p2->Exponent;
            ans->Coefficient = p2->Coefficient;
            p2 = p2->Next;
        }
        else if(!p2){
            ans->Exponent = p1->Exponent;
            ans->Coefficient = p1->Coefficient;
            p1 = p1->Next;
        }
		else if(p1->Exponent > p2->Exponent){
            ans->Exponent = p1->Exponent;
            ans->Coefficient = p1->Coefficient;
            p1 = p1->Next;
        }
        else if(p2->Exponent > p1->Exponent){
            ans->Exponent = p2->Exponent;
            ans->Coefficient = p2->Coefficient;
            p2 = p2->Next;
        }
        else if(p2->Exponent == p1->Exponent){
            ans->Exponent = p2->Exponent;
            ans->Coefficient = p1->Coefficient + p2->Coefficient;
            if(ans->Coefficient == 0 && head != NULL){
            	free(ans);
            	p1 = p1->Next;
            	p2 = p2->Next;
            	continue;
			}
            p1 = p1->Next;
            p2 = p2->Next;
        }
        if(head == NULL)
            head = ans;
        else
    	    tail->Next = ans;
        tail = ans;
	}
    tail->Next = NULL;
    /*if(head == NULL){
    	head = (Polynomial)malloc(sizeof(struct Node));
    	head->Coefficient = 0;
    	head->Exponent = 0;
    	head->Next = NULL;
	}*/
    return head;
}

Polynomial Read()
{
    int i, n;
    Polynomial head = NULL, tail = NULL, p = NULL;

    scanf("%d", &n);
    for(i = 1; i <= n; i++){
        p = (Polynomial)malloc(sizeof(struct Node));
        scanf("%d%d", &(p->Coefficient), &(p->Exponent));
        if(head == NULL)
            head = p;
        else
    	    tail->Next = p;
        tail = p;
    }
    tail->Next = NULL; 
    return head;
}

void Print( Polynomial p )
{
    while(p){
        printf("%d %d ", p->Coefficient, p->Exponent);
        p = p->Next;
    }
}
