#include <stdio.h>
#include <stdlib.h>

typedef struct StackRecord* stack;
struct StackRecord{
	int sp;
    char op[100];
};

stack GetInFix();
stack InToPost(stack infix);
int JudgePriority(char a1, char a2);
float Calculate(stack postfix);

int main(void)
{
	stack infix, postfix;

	printf("Please input expression (0-9):\n");
	infix = GetInFix();
	postfix = InToPost(infix);
	printf("%d\n", (int)Calculate(postfix));
	return 0;
}

stack GetInFix()
{
	stack infix;
	char temp;

	infix = (stack)malloc(sizeof(struct StackRecord));
	infix -> sp = -1;
	temp = getchar();
	while(temp != '#'){
		infix -> op[++(infix -> sp)] = temp;
		temp = getchar();
	}
	return infix;
}

stack InToPost(stack infix)
{
	stack postfix;
	char tempstack[100];
	int ptr = -1;
	char temp;
	int i = 0;

	postfix = (stack)malloc(sizeof(struct StackRecord));
	postfix -> sp = -1;
	while(i <= infix -> sp){
		temp = infix -> op[i];
		if(temp >= '0' && temp <= '9')
			postfix -> op[++(postfix -> sp)] = temp;
		else if(temp == ')'){
			while(tempstack[ptr] != '(')
				postfix -> op[++(postfix -> sp)] = tempstack[ptr--];
			ptr--;
		}
		else if(ptr != -1){
			while(JudgePriority(temp, tempstack[ptr])){
				postfix -> op[++(postfix -> sp)] = tempstack[ptr--];
				if(ptr == -1)
					break;
			}
			tempstack[++ptr] = temp;
		}
		else
			tempstack[++ptr] = temp;
		i++;
	}
	while(ptr > -1)
		postfix -> op[++(postfix -> sp)] = tempstack[ptr--];
	return postfix;
}

int JudgePriority(char a1, char a2)//a1 < a2
{
	int flag1, flag2;

	if(a1 == '+' || a1 == '-')
		flag1 = 0;
	else if(a1 == '*' || a1 == '/')
		flag1 = 1;
	else
		flag1 = 2;

	if(a2 == '+' || a2 == '-')
		flag2 = 0;
	else if(a2 == '*' || a2 == '/')
		flag2 = 1;
	else
		flag2 = -1;

	if(flag1 <= flag2)
		return 1;
	else
		return 0;
}

float Calculate(stack postfix)
{
	float tempstack[100];
	int ptr = -1;
	int i = 0;
	float temp;

	while(i <= postfix -> sp){
		if(postfix -> op[i] >= '0' && postfix -> op[i] <= '9'){
			tempstack[++ptr] = (float)(postfix -> op[i] - '0');
		}
		else if(postfix -> op[i] == '+'){
			temp = tempstack[ptr - 1] + tempstack[ptr];
			printf("%.2f + %.2f = %.2f\n", tempstack[ptr - 1], tempstack[ptr], temp);
			tempstack[--ptr] = temp;
		}
		else if(postfix -> op[i] == '-'){
			temp = tempstack[ptr - 1] - tempstack[ptr];
			printf("%.2f - %.2f = %.2f\n", tempstack[ptr - 1], tempstack[ptr], temp);
			tempstack[--ptr] = temp;
		}
		else if(postfix -> op[i] == '*'){
			temp = tempstack[ptr - 1] * tempstack[ptr];
			printf("%.2f * %.2f = %.2f\n", tempstack[ptr - 1], tempstack[ptr], temp);
			tempstack[--ptr] = temp;
		}
		else if(postfix -> op[i] == '/'){
			temp = tempstack[ptr - 1] / tempstack[ptr];
			printf("%.2f / %.2f = %.2f\n", tempstack[ptr - 1], tempstack[ptr], temp);
			tempstack[--ptr] = temp;
		}
		i++;
	}
	return tempstack[ptr];
}