/*
Write the routines to do a "percolate up" and a "percolate down" in a binary min-heap.

**Warning**
**in the function PercolateDown, after each iteration, parent = child, NOT parent *= 2**
**I didn't find this bug, and it troubled me later in another program**

Sample Input:
9
1 10
1 5
1 2
0
1 9
1 1
1 4
0
0
Sample Output:
2 1 4 
Inside H: 5 10 9
*/


#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
#define MinData -1

typedef struct HeapStruct *PriorityQueue;
struct HeapStruct {
    ElementType  *Elements;
    int Capacity;
    int Size;
};

PriorityQueue Initialize( int MaxElements ); /* details omitted */

void PercolateUp( int p, PriorityQueue H );
void PercolateDown( int p, PriorityQueue H );

void Insert( ElementType X, PriorityQueue H ) 
{
    int p = ++H->Size;
    H->Elements[p] = X;
    PercolateUp( p, H );
}

ElementType DeleteMin( PriorityQueue H ) 
{ 
    ElementType MinElement; 
    MinElement = H->Elements[1];
    H->Elements[1] = H->Elements[H->Size--];
    PercolateDown( 1, H );
    return MinElement; 
}

int main()
{
    int n, i, op, X;
    PriorityQueue H;

    scanf("%d", &n);
    H = Initialize(n);
    for ( i=0; i<n; i++ ) {
        scanf("%d", &op);
        switch( op ) {
        case 1:
            scanf("%d", &X);
            Insert(X, H);
            break;
        case 0:
            printf("%d ", DeleteMin(H));
            break;
        }
    }
    printf("\nInside H:");
    for ( i=1; i<=H->Size; i++ )
        printf(" %d", H->Elements[i]);
    return 0;
}

void PercolateUp( int p, PriorityQueue H )
{
    int child;
    ElementType temp;

    for(child = p; H -> Elements[child] < H -> Elements[child / 2]; child /= 2){
        temp = H -> Elements[child];
        H -> Elements[child] = H -> Elements[child / 2];
        H -> Elements[child / 2] = temp;
    }
}

void PercolateDown( int p, PriorityQueue H )
{
    int parent, child;
    ElementType temp;

    for(parent = p; parent * 2 <= H ->Size; parent = child){
        if(parent * 2 + 1 <= H -> Size && H -> Elements[parent * 2 + 1] < H ->Elements[parent * 2])
            child = parent * 2 + 1;
        else
            child = parent * 2;
        if(H -> Elements[parent] > H -> Elements[child]){
            temp = H -> Elements[parent];
            H -> Elements[parent] = H ->Elements[child];
            H -> Elements[child] = temp;
        }
        else
            break;
    }
}

PriorityQueue Initialize( int MaxElements )
{
    PriorityQueue H;

    H = (PriorityQueue)malloc(sizeof(struct HeapStruct));
    H -> Elements = (ElementType *)malloc(sizeof(ElementType) * (MaxElements + 1));
    H -> Capacity = MaxElements;
    H -> Size = 0;
    H -> Elements[0] = -1e5;
    return H;
}