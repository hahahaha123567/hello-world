/*
An inorder binary tree traversal can be implemented in a non-recursive way with a stack. 
For example, suppose that when a 6-node binary tree (with the keys numbered from 1 to 6) is traversed, 
the stack operations are: push(1); push(2); push(3); pop(); pop(); push(4); pop(); pop(); push(5); push(6); pop(); pop(). 
Then a unique binary tree (shown in Figure 1) can be generated from this sequence of operations. 
Your task is to give the postorder traversal sequence of this tree.

Input Specification:
Each input file contains one test case. 
For each case, the first line contains a positive integer N (≤30) which is the total number of nodes in a tree (and hence the nodes are numbered from 1 to N). 
Then 2N lines follow, each describes a stack operation in the format: 
"Push X" where X is the index of the node being pushed onto the stack; or "Pop" meaning to pop one node from the stack.

Output Specification:
For each test case, print the postorder traversal sequence of the corresponding tree in one line. 
A solution is guaranteed to exist. 
All the numbers must be separated by exactly one space, and there must be no extra space at the end of the line.

**the node to insert is 'flag', the last node accessed by stack**

Sample Input:
6
Push 1
Push 2
Push 3
Pop
Pop
Push 4
Pop
Pop
Push 5
Push 6
Pop
Pop
Sample Output:
3 4 2 6 5 1
*/

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
	int sp = -1;
	Tree stack[40], flag = NULL;
	char op[5];
	Tree haha, root;

	for(int i = 1; i <= 2 * n; i++){
		scanf("%s", op);
		if(strcmp(op, "Push") == 0){
			haha = (Tree)malloc(sizeof(struct NodeRecord));
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
		else
			flag = stack[sp--];
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