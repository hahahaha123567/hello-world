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
    Vertex ThisGuy, Temp = -1;
    int index = 0, fuck;

    InDegree = (Vertex *)malloc(sizeof(Vertex) * Graph -> Nv);
    for(int i = 0; i < Graph -> Nv; i++)
        InDegree[i] = 0;
    for(int i = 0; i < Graph -> Nv; i++)
        for(ptr = Graph -> G[i].FirstEdge; ptr != NULL; ptr = ptr -> Next)
            InDegree[ptr -> AdjV]++;
    for(int i = 0; i < Graph -> Nv; i++){
        if(Temp != -1){
            fuck = Temp;
            Temp = -1;
        }
        else{
            for(fuck = 0; fuck < Graph -> Nv; fuck++){
                if(InDegree[fuck] == 0){
                    InDegree[fuck] = 1000;
                    break;
                }
            }
            if(fuck == Graph -> Nv)
                return false;
        }
        TopOrder[index++] = fuck;
        InDegree[fuck] = -1;
        for(ptr = Graph -> G[fuck].FirstEdge; ptr != NULL; ptr = ptr -> Next){
            InDegree[ptr -> AdjV]--;
            if(InDegree[ptr -> AdjV] == 0)
                Temp = ptr -> AdjV;
        }
    }
    return true;
}
