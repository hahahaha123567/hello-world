#include <stdio.h>
#include <stdlib.h>

typedef struct HeapRecord* heap;
struct HeapRecord
{
	int *element;
	int capacity;
	int size;
};

heap initialize(int max);
void insert(int n, heap H);
int delete(heap H);

int main(void)
{
	int temp, num;
	heap H = initialize(100);
	scanf("%d", &num);
	for(int i = 0; i < num; i++){
		scanf("%d", &temp);
		insert(temp, H);
	}
	for(int i = 0; i <= num; i++)
		printf("%d ", H -> element[i]);
	printf("\n");
	delete(H);
	for(int i = 0; i <= num - 1; i++)
		printf("%d ", H -> element[i]);
}

heap initialize(int max)
{
	heap H;

	H = (heap)malloc(sizeof(struct HeapRecord));
	H -> element = (int *)malloc(sizeof(int) * (max + 1));
	H -> capacity = max;
	H -> size = 0;
	H -> element[0] = -1e5;
	return H;
}

void insert(int n, heap H)
{
	int i;
	for(i = ++(H -> size); n < H -> element[i/2]; i /= 2)
		H -> element[i] = H -> element[i/2];
	H -> element[i] = n;
}

int delete(heap H)
{
	int parent, child;
	int last, temp;

	temp = H -> element[1];
	last = H -> element[H -> size];
	for(parent = 1; parent * 2 <= H -> size; parent *= 2){
		child = parent * 2;
		if(child < H -> size && H -> element[child] > H -> element[child + 1])
			child++;
		if(last >  H -> element[child])
			H -> element[parent] = H -> element[child];
		else
			break;
	}
	H -> element[parent] = last;
	return temp;
}