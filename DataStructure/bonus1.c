#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NodeRecord* Node;
struct NodeRecord{
	int Weight;
	int NumOfSon;
	int Sons[100];
};

typedef struct PathRecord* Road;
struct PathRecord{
	int path[100];
	int ptr;
};

Node Build(int Nodes, int Noneleaf);
void Find(Node T, int Num, int length, Road now, int target, Road R[], int* RNum);
void Add(Road now, Road R[], int* RNum);
void Sort(Road R[], int RNum);
int Cmp(Road a, Road b);
void Print(Road R[], int RNum);

int main(void)
{
	Node T;
	int Nodes, Noneleaf, target;

	Road now;
	now = (Road)malloc(sizeof(struct PathRecord));
	now -> ptr = -1;

	Road R[100];
	int RNum = 0;
	for(int i = 0; i < 100; i++){
		R[i] = (Road)malloc(sizeof(struct PathRecord));
		R[i] -> ptr = -1;
	}

	scanf("%d%d%d", &Nodes, &Noneleaf, &target);
	T = Build(Nodes, Noneleaf);
	Find(T, 0, 0, now, target, R, &RNum);
	Sort(R, RNum);
	Print(R, RNum);
	return 0;
}

Node Build(int Nodes, int Noneleaf)
{
	Node T;
	int Num;

	T = (Node)malloc(sizeof(struct NodeRecord) * Nodes);
	for(int i = 0; i < Nodes; i++)
		T[i].NumOfSon = 0;
	for(int i = 0; i < Nodes; i++)
		scanf("%d", &T[i].Weight);
	for(int i = 0; i < Noneleaf; i++){
		scanf("%d", &Num);
		scanf("%d", &T[Num].NumOfSon);
		for(int j = 0; j < T[Num].NumOfSon; j++)
			scanf("%d", &T[Num].Sons[j]);
	}
	return T;
}

void Find(Node T, int Num, int length, Road now, int target, Road R[], int* RNum)
{
	now -> path[++(now -> ptr)] = T[Num].Weight;
	length += T[Num].Weight;
	if(T[Num].NumOfSon == 0){
		if(length == target){
			Add(now, R, RNum);
		}
		else{
			(now -> ptr)--;
			length -= T[Num].Weight;
			return;
		}
	}
	else
		for(int i = 0; i < T[Num].NumOfSon; i++){
			Find(T, T[Num].Sons[i], length, now, target, R, RNum);
		}
	length -= T[Num].Weight;
	(now -> ptr)--;
}

void Add(Road now, Road R[], int* RNum)
{
	for(int i = 0; i <= now -> ptr; i++){
		R[*RNum] -> path[i] = now -> path[i];
		(R[*RNum] -> ptr)++;
	}
	(*RNum)++;
}

void Sort(Road R[], int RNum)
{
	for(int i = 0; i < RNum; i++)
		for(int j = 1; j < RNum; j++){
			if(Cmp(R[j - 1], R[j])){
				Road temp = R[j - 1];
				R[j - 1] = R[j];
				R[j] = temp;
			}
		}
}

int Cmp(Road a, Road b)
{
	int i;
	for(i = 0; i <= a -> ptr && i <= b -> ptr; i++){
		if(a -> path[i] < b -> path[i])
			return 1;
		else if(a -> path[i] > b -> path[i])
			return 0;
	}
	if(i == b -> ptr + 1 || a -> ptr == b -> ptr)
		return 0;
	else
		return 1;
}

void Print(Road R[], int RNum)
{
	printf("%d", R[0] -> path[0]);
	for(int j = 1; j <= R[0] -> ptr; j++)
		printf(" %d", R[0] -> path[j]);
	for(int i = 1; i < RNum; i++){
		printf("\n");
		printf("%d", R[i] -> path[0]);
		for(int j = 1; j <= R[i] -> ptr; j++)
			printf(" %d", R[i] -> path[j]);
	}
}