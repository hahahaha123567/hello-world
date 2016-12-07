#include <stdio.h>
#include <stdlib.h>

#define NotVertex (-1)
#define MaxVertexNum (600)
#define Infinity (1e6)
typedef int Vertex;

//node in adjacent list
typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode{
    Vertex AdjV;
    int Weight;
    PtrToAdjVNode Next;
};
typedef struct Vnode{
    PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];
typedef struct GNode* Graph;
struct GNode{  
    int Capacity, VertexNum, EdgeNum, BadGuy;
    int Bikes[MaxVertexNum];
    AdjList List;
};
//table to store vertex infomation used in dijkstra
typedef struct TableEntry Table;
struct TableEntry{
	int Known, Distence;
};
//path information
typedef struct PathNode Path;
struct PathNode{
	int ParentNumber;
	Vertex Parent[MaxVertexNum];
};
typedef struct PathNode* PtrToPath;

Graph InitialGraph();
Table* InitialTable(Graph G);
Path* InitialPath(Graph G);
void Dijkstra(Graph G, Table* T, Path* P);
void Calc(Graph G, Path* P, Vertex V, int count);

int FinalSend = Infinity, FinalTake = Infinity;
Vertex TempPath[MaxVertexNum], FinalPath[MaxVertexNum];

int main(void)
{
	int i = 1;
	Graph G;
	Table* T;
	Path* P;
	//Vertex* FinalPath = (Vertex*)malloc(sizeof(Vertex) * MaxVertexNum);

	G = InitialGraph();
	T = InitialTable(G);
	P = InitialPath(G);
	Dijkstra(G, T, P);
	Calc(G, P, G -> BadGuy, 0);
	
	printf("%d ", FinalSend);
	printf("0");
	while(FinalPath[i] != G -> BadGuy)
		printf("->%d", FinalPath[i++]);
	printf("->%d", FinalPath[i + 1]);
	printf(" %d\n", FinalTake);
	
	return 0;
}

Graph InitialGraph()
{
	Graph G;
	Vertex Source, Destination, Weight;
	PtrToAdjVNode TempNode, ptr;

	G = (Graph)malloc(sizeof(struct GNode));
	scanf("%d%d%d%d", &G -> Capacity, &G -> VertexNum, &G -> BadGuy, &G -> EdgeNum);
	for(int i = 1; i <= G -> VertexNum; i++)
		scanf("%d", &G -> Bikes[i]);
    for(int i = 0; i <= G -> VertexNum; i++)
        G -> List[i].FirstEdge = NULL;

    for(int i = 0; i < G -> EdgeNum; i++){
        scanf("%d%d%d", &Source, &Destination, &Weight);

        TempNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
        TempNode -> AdjV = Destination;
        TempNode -> Weight = Weight;
        TempNode -> Next = NULL;
        ptr = G -> List[Source].FirstEdge;
        if(ptr == NULL)
            G -> List[Source].FirstEdge = TempNode;
        else{
            while(ptr -> Next)
                ptr = ptr -> Next;
            ptr -> Next = TempNode;
        }

        TempNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
        TempNode -> AdjV = Source;
        TempNode -> Weight = Weight;
        TempNode -> Next = NULL;
        ptr = G -> List[Destination].FirstEdge;
        if(ptr == NULL)
            G -> List[Destination].FirstEdge = TempNode;
        else{
            while(ptr -> Next)
                ptr = ptr -> Next;
            ptr -> Next = TempNode;
        }
    }

    return G;
}

Table* InitialTable(Graph G)
{
	Table* T;

	T = (Table *)malloc(sizeof(struct TableEntry) * (G -> VertexNum + 1));
	for(int i = 0; i <= G -> VertexNum; i++){
		T[i].Known = 0;
		T[i].Distence = Infinity;
	}
	T[0].Distence = 0;

	return T;
}

Path* InitialPath(Graph G)
{
	Path* P;

	P = (Path*)malloc(sizeof(struct PathNode) * (G -> VertexNum + 1));
	for(int i = 0; i < G -> VertexNum; i++)
		P[i].ParentNumber = 0;

	return P;
}

void Dijkstra(Graph G, Table* T, Path* P)
{
	int TempDistence;
	PtrToAdjVNode TempPtr;
	Vertex CurrentVertex;

	while(1){
		//definite the unknown nearest vertex
		CurrentVertex = NotVertex;
		TempDistence = Infinity;
		for(int i = 0; i <= G -> VertexNum; i++){
			if(T[i].Known == 0 && T[i].Distence < TempDistence){
				TempDistence = T[i].Distence;
				CurrentVertex = i;
			}
		}
		if(CurrentVertex == NotVertex)
			break;
		T[CurrentVertex].Known = 1;
		if(T[G -> BadGuy].Known)
			break;
		//change the unknown vertex adjacent to the current vertex
		TempPtr = G -> List[CurrentVertex].FirstEdge;
		while(TempPtr){
			if(T[CurrentVertex].Distence + TempPtr -> Weight < T[TempPtr -> AdjV].Distence){
				T[TempPtr -> AdjV].Distence = T[CurrentVertex].Distence + TempPtr -> Weight;
				P[TempPtr -> AdjV].ParentNumber = 1;
				P[TempPtr -> AdjV].Parent[P[TempPtr -> AdjV].ParentNumber - 1] = CurrentVertex;
			}
			else if(T[CurrentVertex].Distence + TempPtr -> Weight == T[TempPtr -> AdjV].Distence){
				P[TempPtr -> AdjV].ParentNumber++;
				P[TempPtr -> AdjV].Parent[P[TempPtr -> AdjV].ParentNumber - 1] = CurrentVertex;
			}
			TempPtr = TempPtr -> Next;
		}
	}
}

void Calc(Graph G, Path* P, Vertex V, int count)
{
	//Vertex* TempPath = malloc(sizeof(Vertex) * G -> VertexNum);
	int Send = 0, Take = 0, i, nico;

	TempPath[count] = V;
	if(V){
		for(int i = 0; i < P[V].ParentNumber; i++)
			Calc(G, P, P[V].Parent[i], count + 1);
	}
	else{
		for(int i = 0; i < count; i++){
			if(G -> Bikes[TempPath[i]] < G -> Capacity / 2)
				Send += (G -> Capacity / 2 - G -> Bikes[TempPath[i]]);
			else if(G -> Bikes[TempPath[i]] > G -> Capacity / 2){
				if(G -> Bikes[TempPath[i]] - G -> Capacity / 2 >= Send){
					Take += (G -> Bikes[TempPath[i]] - G -> Capacity / 2 - Send);
					Send = 0;
				}
				else
					Send -= (G -> Bikes[TempPath[i]] - G -> Capacity / 2);
			}
		}
		if(Send < FinalSend || (Send == FinalSend && Take < FinalTake)){
			FinalSend = Send;
			FinalTake = Take;
			
			nico = 0;
			while(TempPath[nico])
				nico++;
			for(i = 0; i <= nico; i++)
				FinalPath[i] = TempPath[nico - i];
			FinalPath[i] = G -> BadGuy;
		}
	}
}
