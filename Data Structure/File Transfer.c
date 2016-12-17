/*
We have a network of computers and a list of bi-directional connections. 
Each of these connections allows a file transfer from one computer to another. 
Is it possible to send a file from any computer on the network to any other?

Input Specification:
Each input file contains one test case. 
For each test case, the first line contains N(2≤N≤10^4), the total number of computers in a network. 
Each computer in the network is then represented by a positive integer between 1 and N. 
Then in the following lines, the input is given in the format:
I c1 c2
where I stands for inputting a connection between c1 and c2; or
C c1 c2
where C stands for checking if it is possible to transfer files between c1 and c2; or
S
where S stands for stopping this case.

Output Specification:
For each C case, print in one line the word "yes" or "no" if it is possible or impossible to transfer files between c1 and c2, respectively. 
At the end of each case, print in one line "The network is connected." 
if there is a path between any pair of computers; or "There are k components." where k is the number of connected components in this network.

**It is an equivalance class question, and solve it by disjoint set**
**Warning**
**in the disjoint set ADT, the parameter of Union is two root**

Sample Input 1:
5
C 3 2
I 3 2
C 1 5
I 4 5
I 2 4
C 3 5
S
Sample Output 1:
no
no
yes
There are 2 components.
Sample Input 2:
5
C 3 2
I 3 2
C 1 5
I 4 5
I 2 4
C 3 5
I 1 3
C 1 5
S
Sample Output 2:
no
no
yes
yes
The network is connected.
*/
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