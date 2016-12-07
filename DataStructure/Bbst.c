#include <stdio.h>
#include <stdlib.h>
#define MAX 10000

typedef struct TreeNode* Tree;
struct TreeNode{
	int key;
	int flag;
	Tree Left;
	Tree Right;
};

Tree build();
void fill(Tree T, int N);
Tree findleast(T);
void leveltra(Tree T);

int main(void)
{
	int N;
	Tree T;

	scanf("%d", &N);
	T = build();
	fill(T, N);
	leveltra(T);
	return 0;
}

Tree build()
{
	int left, right;
	Tree haha = NULL;

	haha = (Tree)malloc(sizeof(struct TreeNode));
	haha -> flag = 1;
	haha -> Left = NULL;
	haha -> Right = NULL;
	scanf("%d%d", &left, &right);
	if(left != -1)
		haha -> Left = build();
	if(right != -1)
		haha -> Right = build();
	return haha;
}

void fill(Tree T, int N)
{
	int keys[MAX], temp;
	Tree haha;

	for(int i = 0; i < N; i++)
		scanf("%d", keys + i);
	for(int i = 0; i < N; i++)
		for(int j = 1; j < N; j++)
			if(keys[j - 1] > keys[j]){
				temp = keys[j - 1];
				keys[j - 1] = keys[j];
				keys[j] = temp;
			}
	for(int i = 0; i < N; i++){
		haha = findleast(T);
		haha -> key = keys[i];
	}
}

Tree findleast(Tree T)
{
	Tree temp;

	if(T -> Left){
		temp = findleast(T -> Left);
		if(temp)
			return temp;
		else if(T -> flag == 1){
			T -> flag = 0;
			return T;
		}
		else if(T -> Right){
			temp = findleast(T -> Right);
			if(temp)
				return temp;
			else 
				return NULL;
		}
		else
			return NULL;
	}
	else if(T -> flag == 1){
		T -> flag = 0;
		return T;
	}
	else if(T -> Right){
		temp = findleast(T -> Right);
		if(temp)
			return temp;
		else 
			return NULL;
	}
	else
		return NULL;
}

void leveltra(Tree T)
{
	Tree queue[MAX], temp;
	int Front, Rear;

	temp = T;
	Front = Rear = 0;
	queue[Rear++] = T;
	printf("%d", T -> key);
	while(Front != Rear){
		T = queue[Front++];
		if(T != temp)
			printf(" %d", T -> key);
		if(T -> Left)
			queue[Rear++] = T -> Left;
		if(T -> Right)
			queue[Rear++] = T -> Right;
	}
}