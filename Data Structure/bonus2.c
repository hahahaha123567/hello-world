#include "stdio.h"
#include "stdlib.h"

#define MAXVERTEXNUMBER 600
#define INFINITE 100000
typedef int* DisjointSet;

typedef struct GraghNode* Graph;
struct GraghNode{
	int VertexNum;
	int EdgeNum;
};

typedef struct EdgeNode* Edge;
struct EdgeNode
{
	int Source;
	int Destination;
	int Cost;
	int Status;
};

Graph InitialGragh();
Edge InitialEdge(Graph G);
void Sort(Edge E, int n);

void CalcCost(Graph G, Edge E);
int CalcVertex(Graph G, Edge E, int Conquered);

int isConnected(Graph G, DisjointSet D);
int Find(DisjointSet D, int n);
void Union(DisjointSet D, int root1, int root2);

int main(void)
{
	Graph G;
	Edge E;

	G = InitialGragh();
	E = InitialEdge(G);
	Sort(E + 1, G -> EdgeNum);
	CalcCost(G, E);

	return 0;
}

Graph InitialGragh()
{
	Graph G = malloc(sizeof(struct GraghNode));

	scanf("%d%d", &G -> VertexNum, &G -> EdgeNum);
	
	return G;
}

Edge InitialEdge(Graph G)
{
	Edge E = malloc(sizeof(struct EdgeNode) * (G -> EdgeNum + 1));

	for(int i = 1; i <= G -> EdgeNum; i++)
		scanf("%d%d%d%d", &E[i].Source, &E[i].Destination, &E[i].Cost, &E[i].Status);

	return E;
}

void Sort(Edge E, int n)
{
	int compared, inserted;
	struct EdgeNode temp;

	for(inserted = 1; inserted < n; inserted++){
		temp = E[inserted];
		for(compared = inserted - 1; compared >= 0; compared--){
			if(E[compared].Cost > temp.Cost)
				E[compared + 1] = E[compared];
			else
				break;
		}
		E[compared + 1] = temp;
	}
}

void CalcCost(Graph G, Edge E)
{
	Graph Temp;
	int CostMost = 0, index = 1;
	int* VertexCost = (int*)malloc(sizeof(int) * (G -> VertexNum + 1)); 

	for(int i = 1; i <= G -> VertexNum; i++){
		VertexCost[i] = CalcVertex(G, E, i);
		if(VertexCost[i] > CostMost)
			CostMost = VertexCost[i];
	}
	if(CostMost == 0)
		printf("0");
	else
		for(int i = 1; i <= G -> VertexNum; i++)
			if(VertexCost[i] == CostMost)
				if(index++ == 1)
					printf("%d", i);
				else
					printf(" %d", i);
}

int CalcVertex(Graph G, Edge E, int Conquered)
{
	int Shortest, root1, root2, SumCost = 0;
	DisjointSet D = malloc(sizeof(int) * (G -> VertexNum + 1));
	int count = 0;

	//initial the DisjointSet
	for(int i = 1; i <= G -> VertexNum; i++)
		D[i] = -1;
	for(int i = 1; i <= G -> EdgeNum; i++){
		if(E[i].Status && Conquered != E[i].Source && Conquered != E[i].Destination){
			root1 = Find(D, E[i].Source);
			root2 = Find(D, E[i].Destination);
			Union(D, root1, root2);
			count++;
			if (count == G -> VertexNum - 2)
				break;
		}
	}
	if(isConnected(G, D))
		return 0;
	
	for(int i = 1; i <= G -> EdgeNum; i++){
		if(E[i].Status == 0 && Conquered != E[i].Source && Conquered != E[i].Destination){
			root1 = Find(D, E[i].Source);
			root2 = Find(D, E[i].Destination);
			if(root1 != root2){
				Union(D, root1, root2);
				SumCost += E[i].Cost;
			}
			if(isConnected(G, D))
				return SumCost;
		}
	}
	return INFINITE;
}

int isConnected(Graph G, DisjointSet D)
{
	int count = 0;

	for(int i = 1; i <= G -> VertexNum; i++){
		if(D[i] <= 0)
			count++;
		if(count >= 3)
			return 0;
	}

	return 1;
}

void Union(DisjointSet D, int root1, int root2)
{
	if(root1 == root2)
		return ;
	if(D[root1] < D[root2])
		D[root2] = root1;
	else if(D[root1] == D[root2])
		D[root1] = root2--;
	else
		D[root1] = root2;
}

int Find(DisjointSet D, int n)
{
	if(D[n] < 0)
		return n;
	else
		return D[n] = Find(D, D[n]);
}