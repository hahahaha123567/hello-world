#include <stdio.h>
#include <stdlib.h>

#define MaxVertices 10  /* maximum number of vertices */
typedef int Vertex;     /* vertices are numbered from 0 to MaxVertices-1 */
typedef struct VNode *PtrToVNode;
struct VNode {
    Vertex Vert;
    PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode {
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};

Graph ReadG(); /* details omitted */

void PrintV( Vertex V )
{
   printf("%d ", V);
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) );

int main()
{
    Graph G = ReadG();
    StronglyConnectedComponents( G, PrintV );
    return 0;
}

Graph ReadG()
{
	Graph G;
	int n,m;
	PtrToVNode temp,pointer;
	G=(Graph)malloc(sizeof(struct GNode));
	scanf("%d %d",&G->NumOfVertices,&G->NumOfEdges);
	G->Array=(PtrToVNode*)malloc(sizeof(PtrToVNode)*(G->NumOfVertices-1));
	for (int i=0; i<G->NumOfVertices ; ++i )
	{
		G->Array[i]=NULL;
	}
	for (int i=0; i<G->NumOfEdges; ++i )
	{
		scanf("%d %d",&n,&m);
		if (G->Array[n]==NULL)//create a dummy node if it is the first road
		{
			G->Array[n]=(PtrToVNode)malloc(sizeof(struct VNode));
			(G->Array[n])->Next=NULL;
			(G->Array[n])->Vert=m;
		}
		else		//create a node and add it after the last
		{
			temp=(PtrToVNode)malloc(sizeof(struct VNode));
			temp->Next=NULL;
			temp->Vert=m;
			pointer=G->Array[n];
			while(pointer->Next!=NULL)
			{
				pointer=pointer->Next;//find the last
			}
			pointer->Next=temp;//put it after
		}	
	}
	return G;
}

int Number = 0;
int Known[MaxVertices];
int Father[MaxVertices];
int Weight[MaxVertices];
int SearchDone[MaxVertices];

void DFS(Graph G, Vertex n)
{
	PtrToVNode TempPtr = G -> Array[n];

	if(Known[n])
		return ;
	Known[n] = 1;
	while(TempPtr){
		DFS(G, TempPtr -> Vert);
		Father[TempPtr -> Vert] = n;
		TempPtr = TempPtr -> Next;
	}
	Weight[n] = Number++;
}

Graph Reverse(Graph G)
{
	Graph Gr = malloc(sizeof(struct GNode));
	PtrToVNode TempPtr, temp, pointer;

	Gr -> NumOfVertices = G -> NumOfVertices;
	Gr -> NumOfEdges = G -> NumOfEdges;
	Gr->Array=(PtrToVNode*)malloc(sizeof(PtrToVNode)*(G->NumOfVertices-1));
	for (int i=0; i<G->NumOfVertices ; ++i )
		Gr->Array[i]=NULL;
	for(int i = 0; i < G -> NumOfVertices; i++){
		TempPtr = G -> Array[i];
		while(TempPtr){
			if (Gr->Array[TempPtr -> Vert]==NULL)//create a dummy node if it is the first road
			{
				Gr->Array[TempPtr -> Vert]=(PtrToVNode)malloc(sizeof(struct VNode));
				(Gr->Array[TempPtr -> Vert])->Next=NULL;
				(Gr->Array[TempPtr -> Vert])->Vert=i;
				//printf("Gr -> Array[%d] -> Vert = %d\n", TempPtr -> Vert, Gr -> Array[TempPtr -> Vert] -> Vert);
			}
			else		//create a node and add it after the last
			{
				temp=(PtrToVNode)malloc(sizeof(struct VNode));
				temp->Next=NULL;
				temp->Vert=i;
				pointer=Gr->Array[TempPtr -> Vert];
				while(pointer->Next!=NULL)
				{
					pointer=pointer->Next;//find the last
				}
				pointer->Next=temp;//put it after
				//printf("pointer -> Next -> Vert = %d\n", i);
			}	
			TempPtr = TempPtr -> Next;
		}
	}
	return Gr;
}

void Search(Graph G, int n)
{
	if(SearchDone[n])
		return ;

	PtrToVNode TempPtr = G -> Array[n];
	PrintV(n);
	SearchDone[n] = 1;
	while(TempPtr){
		Search(G, TempPtr -> Vert);
		TempPtr = TempPtr -> Next;
	}
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) )
{
	int i;
	//initial information
	for(i = 0; i < G -> NumOfVertices; i++){
		Known[i] = 0;
		Father[i] = -1;
		Weight[i] = -1;
		SearchDone[i] = 0;
	}
	for(i = 0; i < G -> NumOfVertices; i++)
		if(Known[i] == 0)
			DFS(G, i);
	Graph Gr = Reverse(G);
	
	for(i = G -> NumOfVertices - 1; i >= 0; i--)
		for(int Vert = 0; Vert < G -> NumOfVertices; Vert++)
			if(Weight[Vert] == i && SearchDone[Vert] == 0){
				Search(Gr, Vert);
				printf("\n");
			}
}