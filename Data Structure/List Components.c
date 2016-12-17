# include <stdio.h>
# include <stdlib.h>

# define MAXVERTEXNUM 10

typedef struct GraphNode* Graph;
struct GraphNode{
	int VertexNum;
	int EdgeNum;
	int Edge[MAXVERTEXNUM][MAXVERTEXNUM];
};

typedef struct QueueNode* Queue;
struct QueueNode
{
	int Front;
	int Rear;
	int Element[MAXVERTEXNUM];
};

Graph ReadGraph();
Queue InitialQueue(Graph G);
void DFS(Graph G, int* DFSvisited, int Vertex);
void BFS(Graph G, int* BFSvisited, Queue Q);

int main(void)
{
	Graph G;
	Queue Q = malloc(sizeof(struct QueueNode));
	int DFSvisited[MAXVERTEXNUM] = {0};
	int BFSvisited[MAXVERTEXNUM] = {0};

	G = ReadGraph();
	Q -> Front = 0;
	Q -> Rear = 0;
	for (int i = 0; i < G -> VertexNum; ++i){
		if (DFSvisited[i] == 0){
			printf("{ ");
			DFS(G, DFSvisited, i);
			printf("}\n");
		}
	}
	for (int i = 0; i < G -> VertexNum; ++i){
		if (BFSvisited[i] == 0){
			BFSvisited[i] = 1;
			Q -> Element[Q -> Rear++] = i;
			printf("{ ");
			BFS(G, BFSvisited, Q);
			printf("}\n");
		}
	}
	return 0;
}

Graph ReadGraph()
{
	int Vertex1, Vertex2;
	Graph G = malloc(sizeof(struct GraphNode));

	scanf("%d%d", &G -> VertexNum, &G -> EdgeNum);
	for (int i = 0; i < G -> VertexNum; ++i)
		for (int j = 0; j < G -> VertexNum; ++j)
			G -> Edge[i][j] = 0;
	for (int i = 0; i < G -> EdgeNum; ++i){
		scanf("%d%d", &Vertex1, &Vertex2);
		G -> Edge[Vertex1][Vertex2]++;
		G -> Edge[Vertex2][Vertex1]++;
	}

	return G;
}

void DFS(Graph G, int* DFSvisited, int Vertex)
{
	DFSvisited[Vertex] = 1;
	printf("%d ", Vertex);
	for (int i = 0; i < G -> VertexNum; ++i){
		if (G -> Edge[Vertex][i] && DFSvisited[i] == 0)
			DFS(G, DFSvisited, i);
	}
}

void BFS(Graph G, int* BFSvisited, Queue Q)
{
	int Vertex = Q -> Element[Q -> Front++];

	printf("%d ", Vertex);
	for (int i = 0; i < G -> VertexNum; ++i){
		if (G -> Edge[Vertex][i] && BFSvisited[i] == 0){
			BFSvisited[i] = 1;
			Q -> Element[Q -> Rear++] = i;
		}
	}
	if(Q -> Front < Q -> Rear)
		BFS(G, BFSvisited, Q);
}