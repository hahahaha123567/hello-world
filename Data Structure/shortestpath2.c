#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;
#define INFINITY 1000000
#define MaxVertexNum 10  /* maximum number of vertices */
typedef int Vertex;      /* vertices are numbered from 0 to MaxVertexNum-1 */
typedef int WeightType;

typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;
    int Ne;
    WeightType G[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph;

MGraph ReadG(); /* details omitted */

void ShortestDist( MGraph Graph, int dist[], int path[], Vertex S );

int main()
{
    int dist[MaxVertexNum], path[MaxVertexNum];
    Vertex S, V;
    MGraph G = ReadG();

    scanf("%d", &S);
    ShortestDist( G, dist, path, S );

    for ( V=0; V<G->Nv; V++ )
        printf("%d ", dist[V]);
    printf("\n");
    for ( V=0; V<G->Nv; V++ )
        printf("%d ", path[V]);
    printf("\n");

    return 0;
}

MGraph ReadG()
{
    MGraph Graph;
    Vertex Source, Destination;
    WeightType Weight;

    Graph = (MGraph)malloc(sizeof(struct GNode));
    scanf("%d%d", &Graph -> Nv, &Graph -> Ne);
    for(int i = 0; i < Graph -> Nv; i++)
        for(int j = 0; j < Graph -> Nv; j++)
            Graph -> G[i][j] = INFINITY;
    for(int i = 0; i < Graph -> Ne; i++){
        scanf("%d%d%d", &Source, &Destination, &Weight);
        Graph -> G[Source][Destination] = Weight;
    }
    return Graph;
}

#define niconiconi (1)

void ShortestDist( MGraph Graph, int dist[], int path[], Vertex S )
{
    int known[MaxVertexNum] = {0};
    int step[MaxVertexNum] = {0};
    WeightType Mindist;
    Vertex CurrentVertex = S;
    for(int i = 0; i < Graph -> Nv; i++){
        dist[i] = INFINITY;
        path[i] = -1;
    }
    step[S] = 0;

    dist[S] = 0;
    while(niconiconi){
        Mindist = INFINITY;
        for(int i = 0; i < Graph -> Nv; i++)
            if(known[i] == 0 && dist[i] < Mindist){
                Mindist = dist[i];
                CurrentVertex = i;
            }
        if(Mindist == INFINITY)
            break;
        known[CurrentVertex] = 1;
        //printf("%d is definite\n", CurrentVertex);
        for(int i = 0; i < Graph -> Nv; i++){
            if(Graph -> G[CurrentVertex][i] < INFINITY){
                if(Graph -> G[CurrentVertex][i] + dist[CurrentVertex] < dist[i]){
                    path[i] = CurrentVertex;
                    dist[i] = Graph -> G[CurrentVertex][i] + dist[CurrentVertex];
                    step[i] = step[CurrentVertex] + 1;
                }
                else if(Graph -> G[CurrentVertex][i] + dist[CurrentVertex] == dist[i]){
                    if(step[CurrentVertex] + 1 < step[i]){
                        path[i] = CurrentVertex;
                        step[i] = step[CurrentVertex] + 1;
                    }
                }
            }
        } 
    }
    for(int i = 0; i < Graph -> Nv; i++)
        if(dist[i] == INFINITY)
            dist[i] = -1;
}