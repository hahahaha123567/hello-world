#include <stdio.h>
#include <stdlib.h>

#define MaxTree 10 /* maximum number of nodes in a tree */
typedef int ElementType;

typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType Element;
    Tree  Left;
    Tree  Right;
};

Tree BuildTree(); /* details omitted */
void PrintNode( Tree NodePtr )
{
   printf(" %d", NodePtr->Element);
}

void Level_order ( Tree T, void (*visit)(Tree ThisNode) );

int main()
{
    Tree T = BuildTree();
    printf("Level-order:");
    Level_order(T, PrintNode);
    return 0;
}

Tree BuildTree()
{
	Tree root = NULL, now, haha;

	haha = (Tree)malloc(sizeof(struct TreeNode));
	haha->Element = 1;
	root = haha;
	now = haha;
	haha = (Tree)malloc(sizeof(struct TreeNode));
	haha->Element = 2;
	now->Left = haha;
	haha = (Tree)malloc(sizeof(struct TreeNode));
	haha->Element = 3;
	now->Right = haha;
	now = now->Left;
	haha = (Tree)malloc(sizeof(struct TreeNode));
	haha->Element = 4;
	haha->Left = NULL;
	haha->Right = NULL;
	now->Left = haha;
	haha = (Tree)malloc(sizeof(struct TreeNode));
	haha->Element = 5;
	haha->Left = NULL;
	haha->Right = NULL;
	now->Right = haha;
	now = root->Right;
	haha = (Tree)malloc(sizeof(struct TreeNode));
	haha->Element = 6;
	haha->Left = NULL;
	haha->Right = NULL;
	now->Left = haha;
	haha = (Tree)malloc(sizeof(struct TreeNode));
	haha->Element = 7;
	now->Right = haha;
	haha->Left = NULL;
	haha->Right = NULL;
	return root;
}

void Level_order ( Tree T, void (*visit)(Tree ThisNode) )
{
	Tree q[MaxTree+1];
	Tree haha = NULL;
	int front = 0, rear = 0;

	if(T){
		q[rear++] = T;
		while(front != rear){
			(*visit)(haha = q[front++]);
			if(haha->Left)
				q[rear++] = haha->Left;
			if(haha->Right)
				q[rear++] = haha->Right;
		}
	}
}
