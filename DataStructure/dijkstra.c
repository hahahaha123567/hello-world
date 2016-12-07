#include "stdio.h"
#include "stdlib.h"

#define NotVertex (-1)
#define MaxVertexNum (10)
#define Infinity (1e4)
#define niconiconi (1)
typedef int Vertex;
typedef int DistenceType;

//node in adjacent list
typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode{
    Vertex AdjV;
    DistenceType Distence;
    PtrToAdjVNode Next;
};
//array of adjacent list
typedef struct Vnode{
    PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];
//graph information
typedef struct GNode* Graph;
struct GNode{  
    int VertexNum;
    int EdgeNum;
    AdjList List;
};
//table to store vertex infomation used in dijkstra
typedef struct TableEntry Table;
struct TableEntry{
	int Known;
	DistenceType Distence;
	Vertex Path;
};

Graph ReadGraph();
void Dijkstra(Vertex Start, Graph G, Table T[]);
void print(Graph G, Table T[]);

int main(void)
{
	Graph G;
	Vertex Start;
	Table T[MaxVertexNum];

	G = ReadGraph();
	scanf("%d", &Start);
	Dijkstra(Start, G, T);
	print(G, T);
	return 0;
}

Graph ReadGraph()
{
    Graph G;
    Vertex Source, Destination, Length;
    PtrToAdjVNode ptr, Temp;

    G = (Graph)malloc(sizeof(struct GNode));
    scanf("%d%d", &G -> VertexNum, &G -> EdgeNum);
    for(int i = 0; i < G -> VertexNum; i++)
        G -> List[i].FirstEdge = NULL;
    for(int i = 0; i < G -> EdgeNum; i++){
        scanf("%d%d%d", &Source, &Destination, &Length);
        Temp = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
        Temp -> AdjV = Destination;
        Temp -> Distence = Length;
        Temp -> Next = NULL;
        ptr = G -> List[Source].FirstEdge;
        if(ptr == NULL)
            G -> List[Source].FirstEdge = Temp;
        else{
            while(ptr -> Next != NULL)
                ptr = ptr -> Next;
            ptr -> Next = Temp;
        }
    }
    return G;
}

void Dijkstra(Vertex Start, Graph G, Table T[])
{
	Vertex CurrentVertex, AdjacentVertex;
	DistenceType ShortestDistence, TempDistence;
	PtrToAdjVNode TempPtr;
	//initial the table
	for(int i = 0; i < G -> VertexNum; i++){
		T[i].Known = 0;
		T[i].Distence = Infinity;
		T[i].Path = NotVertex;
	}
	T[Start].Distence = 0;
	while(niconiconi){
		//CurrentVertex is the shortest unknown vertex
		ShortestDistence = Infinity;
		for(int i = 0; i < G -> VertexNum; i++){
			if(!T[i].Known && T[i].Distence < ShortestDistence){
				ShortestDistence = T[i].Distence;
				CurrentVertex = i;
			}
		}
		if(ShortestDistence == Infinity)
			break;

		T[CurrentVertex].Known = 1;
		TempPtr = G -> List[CurrentVertex].FirstEdge;
		while(TempPtr){
			TempDistence = TempPtr -> Distence + T[CurrentVertex].Distence;
			if(TempDistence < T[TempPtr -> AdjV].Distence){
				T[TempPtr -> AdjV].Distence = TempDistence;
				T[TempPtr -> AdjV].Path = CurrentVertex;
			}
			TempPtr = TempPtr -> Next;
		}
	}
}

void print(Graph G, Table T[])
{
	for(int i = 0; i < G -> VertexNum; i++)
		printf("the distence to %d is %d\n", i, T[i].Distence);
}