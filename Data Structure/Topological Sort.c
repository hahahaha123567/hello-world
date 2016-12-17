/*
Write a program to find the topological order in a digraph.
The topological order is supposed to be stored in TopOrder[] where TopOrder[i] is the i-th vertex in the resulting sequence. 
The topological sort cannot be successful if there is a cycle in the graph -- in that case TopSort must return false; otherwise return true.
Notice that the topological order might not be unique, but the judge's input guarantees the uniqueness of the result.

**since input guarantees the uniqueness of the result, the question is simplified a lot**

Sample Input 1
5 7
1 0
4 3
2 1
2 0
3 2
4 1
4 2
Sample Output 1:
4 3 2 1 0
Sample Input 2
5 8
0 3
1 0
4 3
2 1
2 0
3 2
4 1
4 2
Sample Output 2:
ERROR
*/


#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;
#define MaxVertexNum 10  /* maximum number of vertices */
typedef int Vertex;      /* vertices are numbered from 0 to MaxVertexNum-1 */

typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode{
    Vertex AdjV;
    PtrToAdjVNode Next;
};

typedef struct Vnode{
    PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode;
struct GNode{  
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;

LGraph ReadG(); /* details omitted */

bool TopSort( LGraph Graph, Vertex TopOrder[] );

int main()
{
    int i;
    Vertex TopOrder[MaxVertexNum];
    LGraph G = ReadG();

    if ( TopSort(G, TopOrder)==true )
        for ( i=0; i<G->Nv; i++ )
            printf("%d ", TopOrder[i]);
    else
        printf("ERROR");
    printf("\n");

    return 0;
}

LGraph ReadG()
{
    LGraph Graph;
    Vertex Source, Destination;
    PtrToAdjVNode ptr, Temp;

    Graph = (LGraph)malloc(sizeof(struct GNode));
    scanf("%d%d", &Graph -> Nv, &Graph -> Ne);
    for(int i = 0; i < Graph -> Nv; i++)
        Graph -> G[i].FirstEdge = NULL;
    for(int i = 0; i < Graph -> Ne; i++){
        scanf("%d%d", &Source, &Destination);
        Temp = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
        Temp -> AdjV = Destination;
        Temp -> Next = NULL;
        ptr = Graph -> G[Source].FirstEdge;
        if(ptr == NULL)
            Graph -> G[Source].FirstEdge = Temp;
        else{
            while(ptr -> Next != NULL)
                ptr = ptr -> Next;
            ptr -> Next = Temp;
        }
    }
    return Graph;
}

bool TopSort(LGraph Graph, Vertex TopOrder[])
{
    Vertex *InDegree;
    PtrToAdjVNode ptr;
    Vertex ThisGuy, Flag = 0;
    int index = 0;

    //initial the array InDegree[]
    InDegree = (Vertex *)malloc(sizeof(Vertex) * Graph -> Nv);
    for(int i = 0; i < Graph -> Nv; i++)
        InDegree[i] = 0;
    for(int i = 0; i < Graph -> Nv; i++)
        for(ptr = Graph -> G[i].FirstEdge; ptr != NULL; ptr = ptr -> Next)
            InDegree[ptr -> AdjV]++;
    //find the first vertex
    for(ThisGuy = 0; ThisGuy < Graph -> Nv; ThisGuy++){
        if(InDegree[ThisGuy] == 0)
            break;
    }
    //if the first vertex is not found
    if(ThisGuy == Graph -> Nv)
        return false;
    for(int i = 0; i < Graph -> Nv; i++){
        InDegree[ThisGuy] = -1;         //mark the visited vertex
        TopOrder[index++] = ThisGuy;    //record the path
        //every vertex adjacent to ThisGuy, InDegree subtract 1
        for(ptr = Graph -> G[ThisGuy].FirstEdge; ptr; ptr = ptr -> Next){
            InDegree[ptr -> AdjV]--;
            //find the next vertex
            if(InDegree[ptr -> AdjV] == 0)
                ThisGuy = ptr -> AdjV;
        }
        //if(the next vertex isn't found && this function has not finished)
        if(InDegree[ThisGuy] == -1 && index != Graph -> Nv)
            return false;
    }
    return true;
}
