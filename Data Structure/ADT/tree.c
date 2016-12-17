#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

typedef struct TreeNode* Tree;
struct TreeNode{
	char Element;
	Tree Left;
	Tree Right;
}; 

Tree PreBuild();		//input the data in preorder, '#' means NULL
void PrePrint(Tree T);
void InPrint(Tree T);
void InPrint_Iterative(Tree T);
void PostPrint(Tree T);
void LevelPrint(Tree T);
void ListDirectory(Tree T);

int main(void)
{
	Tree T = PreBuild();

	printf("PrePrint:\t");
	PrePrint(T);
	printf("\n");

	printf("InPrint:\t");
	InPrint(T);
	printf("\n");

	printf("InPrint_Iter:\t");
	InPrint_Iterative(T);
	printf("\n");

	printf("PostPrint:\t");
	PostPrint(T);
	printf("\n");

	printf("LevelPrint:\t");
	LevelPrint(T);
	printf("\n");

	ListDirectory(T);

	return 0;
}

Tree PreBuild()
{
	Tree haha = NULL;
	char temp;
	int size = sizeof(struct TreeNode);

	scanf("%c", &temp);
	if(temp != '#'){
		haha = (Tree)malloc(size);
		haha -> Element = temp;
		haha -> Left = PreBuild();
		haha -> Right = PreBuild();
	}
	return haha;
}

void PrePrint(Tree T)
{
	if(T){
		printf("%c ", T->Element);
		PrePrint(T->Left);
		PrePrint(T->Right);
	}
}

void InPrint(Tree T)
{
	if(T){
		InPrint(T -> Left);
		printf("%c ", T -> Element);
		InPrint(T -> Right);
	}
}

void InPrint_Iterative(Tree T)
{
	Tree Stack[MAX];
	Stack[0] = NULL;
	int sp = 0;

	while(1){
		for( ; T; T = T -> Left)
			Stack[++sp] = T;
		T = Stack[sp--];
		if(T == NULL)
			break;
		printf("%c ", T -> Element);
		T = T -> Right;
	}
}

void PostPrint(Tree T)
{
	if(T){
		PostPrint(T -> Left);
		PostPrint(T -> Right);
		printf("%c ", T -> Element);
	}
}

void LevelPrint(Tree T)
{
	Tree queue[MAX];
	int Front, Rear;

	Front = Rear = 0;
	queue[Rear++] = T;
	while(Front != Rear){
		T = queue[Front++];
		printf("%c ", T -> Element);
		if(T -> Left)
			queue[Rear++] = T -> Left;
		if(T -> Right)
			queue[Rear++] = T -> Right;
	}
}

void ListDir(Tree T, int Depth)
{
	if(T){
		for(int i = 1; i <= Depth; i++)
			printf(" ");
		printf("%c\n", T -> Element);
		if(T -> Left)
			ListDir(T -> Left, Depth + 1);
		if(T -> Right)
			ListDir(T -> Right, Depth + 1);
	}
}
void ListDirectory(Tree T)
{
	ListDir(T, 0);
}