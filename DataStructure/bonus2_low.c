#include "stdio.h"
#include "stdlib.h"

#define MAXVERTEXNUMBER 600
#define INFINITE 100000
typedef int* DisjointSet;

typedef struct GraghNode* Graph;
struct GraghNode{
	int VertexNum;
	int EdgeNum;
	int Cost[MAXVERTEXNUMBER + 1][MAXVERTEXNUMBER + 1];
	int Status[MAXVERTEXNUMBER + 1][MAXVERTEXNUMBER + 1];
};

Graph InitialGragh();
Graph CopyGraph(Graph);
void CalcCost(Graph G);
int CalcVertex(Graph G, int Conquered);
int isConnected(Graph G, DisjointSet D);
void Union(DisjointSet D, int root1, int root2);
int Find(DisjointSet D, int n);

int main(void)
{
	Graph G, Temp;

	G = InitialGragh();
	CalcCost(G);

	return 0;
}

Graph InitialGragh()
{
	Graph G = malloc(sizeof(struct GraghNode));
	int Source, Destination;

	scanf("%d%d", &G -> VertexNum, &G -> EdgeNum);
	for(int i = 1; i <= G -> VertexNum; i++)
		for(int j = 1; j <= G -> VertexNum; j++)
			G -> Status[i][j] = -1;
	for(int i = 1; i <= G -> EdgeNum; i++){
		scanf("%d%d", &Source, &Destination);
		scanf("%d", &G -> Cost[Source][Destination]);
		G -> Cost[Destination][Source] = G -> Cost[Source][Destination];
		scanf("%d", &G -> Status[Source][Destination]);
		G -> Status[Destination][Source] = G -> Status[Source][Destination];
	}

	return G;
}

Graph CopyGraph(Graph G)
{
	Graph Temp = malloc(sizeof(struct GraghNode));

	Temp -> VertexNum = G -> VertexNum;
	Temp -> EdgeNum = G -> EdgeNum;
	for(int i = 1; i <= G -> VertexNum; i++)
		for(int j = 1; j <= G -> VertexNum; j++){
			Temp -> Cost[i][j] = G -> Cost[i][j];
			Temp -> Status[i][j] = G -> Status[i][j];
		}

	return Temp;
}

void CalcCost(Graph G)
{
	Graph Temp;
	int CostMost = 0, index = 1;
	int* VertexCost = (int*)malloc(sizeof(int) * (G -> VertexNum + 1)); 

	for(int i = 1; i <= G -> VertexNum; i++){
		Temp = CopyGraph(G);
		VertexCost[i] = CalcVertex(Temp, i);
		free(Temp);
	}
	for(int i = 1; i <= G -> VertexNum; i++){
		if(VertexCost[i] > CostMost)
			CostMost = VertexCost[i];
	}
	if(CostMost == 0)
		printf("0");
	else{
		for(int i = 1; i <= G -> VertexNum; i++)
			if(VertexCost[i] == CostMost){
				if(index++ == 1)
					printf("%d", i);
				else
					printf(" %d", i);
			}
	}
	
}

int CalcVertex(Graph G, int Conquered)
{
	int Shortest, fuck1, fuck2, SumCost = 0;
	DisjointSet D;

	//delete the edges adjacent to the Conquered vertex
	for(int i = 1; i <= G -> VertexNum; i++){
		G -> Status[i][Conquered] = -1;
		G -> Status[Conquered][i] = -1;
	}
	//initial the disjointset
	D = (int*)malloc(sizeof(int) * (G -> VertexNum + 1));
	for(int i = 1; i <= G -> VertexNum; i++)
		D[i] = -1;
	for(int i = 1; i <= G -> VertexNum; i++)
		for(int j = i; j <= G -> VertexNum; j++)
			if(G -> Status[i][j] == 1)
				Union(D, Find(D, i), Find(D, j));
	/*
	printf("%d is Conquered\n", Conquered);
	printf("present disjointset:\n");
	for(int i = 1; i <= G -> VertexNum; i++)
		printf("%d ", D[i]);
	printf("\n");
	*/
	if(isConnected(G, D)){
		//printf("%d cost 0\n", Conquered);
		return 0;
	}

	while(1){
		Shortest = INFINITE;
		for(int i = 1; i <= G -> VertexNum; i++)
			for(int j = i; j <= G -> VertexNum; j++){
				if(G -> Status[i][j] == 0){
					if(Find(D, i) == Find(D, j)){
						G -> Status[i][j] = -1;
						G -> Status[j][i] = -1;
					}
					else if(G -> Cost[i][j] < Shortest){
						Shortest = G -> Cost[i][j];
						fuck1 = i;
						fuck2 = j;
					}
				}
			}
		if(Shortest == INFINITE){
			return INFINITE;
		}
		G -> Status[fuck1][fuck2] = 1;
		G -> Status[fuck2][fuck1] = 1;
		Union(D, Find(D, fuck1), Find(D, fuck2));
		//printf("%d to %d is connected\n", fuck1, fuck2);
		/*
		printf("present disjointset:\n");
		for(int i = 1; i <= G -> VertexNum; i++)
			printf("%d ", D[i]);
		printf("\n");
		*/
		SumCost += G -> Cost[fuck1][fuck2];
		if(isConnected(G, D)){
			//printf("%d cost %d\n", Conquered, SumCost);
			return SumCost;
		}
	}
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