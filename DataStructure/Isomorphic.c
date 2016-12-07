#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType Element;
    Tree  Left;
    Tree  Right;
};

Tree BuildTree(); /* details omitted */

int Isomorphic( Tree T1, Tree T2 );

int main()
{
    Tree T1, T2;
    T1 = BuildTree();
    printf("haha\n");
    T2 = BuildTree();
    printf("haha\n");
    printf("%d\n", Isomorphic(T1, T2));
    return 0;
}

Tree BuildTree()
{
	Tree haha = NULL;
	char temp;
	int size = sizeof(struct TreeNode);

	scanf("%c", &temp);
	if(temp != '#'){
		haha = (Tree)malloc(size);
		haha -> Element = temp;
		haha -> Left = BuildTree();
		haha -> Right = BuildTree();
	}
	return haha;
}
int Isomorphic( Tree T1, Tree T2 )
{
	if((!T1 && T2) || (T1 && !T2))
		return 0;
	else if(!T1 && !T2)
		return 1;
	else if((T1->Element != T2->Element))
		return 0;
	else
		return ((Isomorphic(T1->Left, T2->Right) && Isomorphic(T1->Right, T2->Left)) || (Isomorphic(T1->Right, T2->Right) && Isomorphic(T1->Left, T2->Left)));
}