//It is an equivalance class question, and solve it by disjoint set
#include <stdio.h>
#include <stdlib.h>

int Find(int* DisJointSet, int n);
void Union(int* DisJointSet, int root1, int root2);
int isConnect(int* DisJointSet, int size);

int main(void)
{
	int size;
	int *DisJointSet;
	int operand1, operand2;
	char opcode;
	int NumOfComponent;

	scanf("%d", &size);
	DisJointSet = (int *)malloc(sizeof(int) * (size + 1));

	for(int i = 1; i <= size; i++)
		DisJointSet[i] = -1;

	getchar();
	scanf("%c", &opcode);
	while(opcode != 'S'){
		if(opcode == 'C'){
			scanf("%d%d", &operand1, &operand2);
			if(Find(DisJointSet, operand1) == Find(DisJointSet, operand2))
				printf("yes\n");
			else
				printf("no\n");
		}
		else{
			scanf("%d%d", &operand1, &operand2);
			Union(DisJointSet, Find(DisJointSet, operand1), Find(DisJointSet, operand2));
		}
		getchar();
		scanf("%c", &opcode);
	}

	NumOfComponent = isConnect(DisJointSet, size);
	if(NumOfComponent == 1)
		printf("The network is connected.");
	else
		printf("There are %d components.", NumOfComponent);
}

int Find(int* DisJointSet, int n)
{
	if(DisJointSet[n] < 0)
		return n;
	else
		return DisJointSet[n] = Find(DisJointSet, DisJointSet[n]);
}

void Union(int* DisJointSet, int root1, int root2)
{
	if(DisJointSet[root1] < DisJointSet[root2])
		DisJointSet[root2] = root1;
	else if(DisJointSet[root1] == DisJointSet[root2])
		DisJointSet[root1] = root2--;
	else
		DisJointSet[root1] = root2;
}

int isConnect(int* DisJointSet, int size)
{
	int sum = 0;

	for(int i = 1; i <= size; i++){
		if(DisJointSet[i] <= 0)
			sum++;
	}
	return sum;
}