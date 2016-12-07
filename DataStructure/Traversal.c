#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NodeRecord* Tree;
struct NodeRecord{
	int Element;
	Tree Left;
	Tree Right;
};

Tree BuildTree(int n);
void PostPrint(Tree T, int n);

static int count = 0;

int main(void)
{
	int n;
	scanf("%d", &n);
	Tree T = BuildTree(n);
	PostPrint(T, n);
	return 0;
}

Tree BuildTree(int n)
{
	int sp = -1, size = sizeof(struct NodeRecord);
	Tree stack[40], flag = NULL;
	char op[5];
	Tree haha, root;

	for(int i = 1; i <= 2 * n; i++){
		scanf("%s", op);
		if(strcmp(op, "Push") == 0){
			haha = (Tree)malloc(size);
			haha -> Left = NULL;
			haha -> Right = NULL;
			scanf("%d", &(haha -> Element));

			if(flag == NULL){
				root = haha;
				flag = root;
			}
			else if(flag -> Left == NULL)
				flag -> Left = haha;
			else
				flag -> Right = haha;
			stack[++sp] = haha;
			flag = haha;
		}
		else{
			flag = stack[sp--];
		}
	}
	return root;
}

void PostPrint(Tree T, int n)
{
	if(T){
		PostPrint(T -> Left, n);
		PostPrint(T -> Right, n);
		if(count < (n-1)){
			printf("%d ", T -> Element);
			count++;
		}
		else
			printf("%d", T -> Element);
	}
}