/*
Given the structure of a binary tree and a sequence of distinct integer keys, 
there is only one way to fill these keys into the tree so that the resulting tree satisfies the definition of a BST. 
You are supposed to output the level order traversal sequence of that tree. 

Input Specification:
Each input file contains one test case. 
For each case, the first line gives a positive integer N (≤100) which is the total number of nodes in the tree. 
The next N lines each contains the left and the right children of a node in the format left_index right_index, 
provided that the nodes are numbered from 0 to N-1, and 0 is always the root. 
If one child is missing, then -1 will represent the NULL child pointer. 
Finally N distinct integer keys are given in the last line.

Output Specification:
For each test case, print in one line the level order traversal sequence of that tree. 
All the numbers must be separated by a space, with no extra space at the end of the line.

**build a Binary Search Tree by judging -1**
**sort the input data, and put each of them in order**

Sample Input:
9
1 6
2 3
-1 -1
-1 4
5 -1
-1 -1
7 -1
-1 8
-1 -1
73 45 11 58 82 25 67 38 42

Sample Output:
58 25 82 11 38 67 45 73 42
*/

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
	Tree haha = malloc(sizeof(struct TreeNode));
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
	}
	if(T -> flag == 1){
		T -> flag = 0;
		return T;
	}
	if(T -> Right){
		temp = findleast(T -> Right);
		if(temp)
			return temp;
	}
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