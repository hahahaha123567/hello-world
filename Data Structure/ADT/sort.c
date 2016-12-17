#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER 10
#define MAX 99

void InsertSort(int *a, int n);
void ShellSort(int *a, int n);
void HeapSort(int *a, int n);
void MergeSort(int *a, int n);
void QuickSort(int *a, int n);

int main(void)
{
	int a[NUMBER], b[NUMBER], c[NUMBER], d[NUMBER], e[NUMBER];

	srand( (unsigned int)time(0) );
	printf("Array before sorted:\n");
	for(int i = 0; i < NUMBER; i++){
		a[i] = rand() % 100;
		b[i] = a[i];
		c[i] = a[i];
		d[i] = a[i];
		e[i] = a[i];
		printf("%d ", a[i]);
	}
	printf("\n");

	InsertSort(a, NUMBER);
	printf("Array after InsertSort:\n");
	for(int i = 0; i < NUMBER; i++)
		printf("%d ", a[i]);
	printf("\n");

	ShellSort(b, NUMBER);
	printf("Array after ShellSort:\n");
	for(int i = 0; i < NUMBER; i++)
		printf("%d ", b[i]);
	printf("\n");

	HeapSort(e, NUMBER);
	printf("Array after HeapSort:\n");
	for(int i = 0; i < NUMBER; i++)
		printf("%d ", e[i]);
	printf("\n");

	MergeSort(c, NUMBER);
	printf("Array after MergeSort:\n");
	for(int i = 0; i < NUMBER; i++)
		printf("%d ", c[i]);
	printf("\n");

	QuickSort(d, NUMBER);
	printf("Array after QuickSort:\n");
	for(int i = 0; i < NUMBER; i++)
		printf("%d ", d[i]);
	printf("\n");

	return 0;
}

void InsertSort(int *a, int n)
{
	int compared, inserted, temp;

	for(inserted = 1; inserted < n; inserted++){
		temp = a[inserted];
		for(compared = inserted - 1; compared >= 0; compared--){
			if(a[compared] > temp)
				a[compared + 1] = a[compared];
			else
				break;
		}
		a[compared + 1] = temp;
	}
}

void ShellSort(int *a, int n)
{
	int compared, inserted, temp;
	int increment;

	for(increment = n / 2; increment > 0; increment /= 2){
		//insert sort, and an increment is a unit length
		for(inserted = increment; inserted < n; inserted += increment){
			temp = a[inserted];
			for(compared = inserted - increment; compared >= 0; compared -= increment){
				if(a[compared] > temp)
					a[compared + increment] = a[compared];
				else
					break;
			}
			a[compared + increment] = temp;
		}
	}
}

typedef struct HeapRecord* heap;
struct HeapRecord
{
	int *element;
	int capacity;
	int size;
};

heap Initialize(int max);
void Insert(int n, heap H);
int Delete(heap H);

void HeapSort(int *a, int n)
{
	heap H;

	H = Initialize(n);
	for(int i = 0; i < n; i++)
		Insert(a[i], H);
	for(int i = 0; i < n; i++)
		a[i] = Delete(H);
}

heap Initialize(int max)
{
	heap H;

	H = (heap)malloc(sizeof(struct HeapRecord));
	H -> element = (int *)malloc(sizeof(int) * (max + 1));
	H -> capacity = max;
	H -> size = 0;
	H -> element[0] = -1e5;
	return H;
}

void Insert(int n, heap H)
{
	int i;
	for(i = ++(H -> size); n < H -> element[i / 2]; i /= 2)
		H -> element[i] = H -> element[i / 2];
	H -> element[i] = n;
}

int Delete(heap H)
{
	int parent, child;
	int last, temp;

	temp = H -> element[1];
	last = H -> element[H -> size --];
	//parent = child; not parent *= 2; !!!!!!!!!
	for(parent = 1; parent * 2 <= H -> size; parent = child){
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

/*
I learned this version of MergeSort from BlackWhite, but it malloc too much memory
void MergeSort(int *a, int n)
{
	int num_left, num_right, *p_left, *p_right;
	int index_left = 0, index_right = 0, index_sum = 0;
	
	//divide
	if(n <= 1)
		return ; 
	num_left = n / 2;
	num_right = n - num_left;
	p_left = (int *)malloc(sizeof(a[0]) * num_left);
	memcpy(p_left, a, sizeof(a[0]) * num_left);
	p_right = (int *)malloc(sizeof(a[0]) * num_right);
	memcpy(p_right, a + num_left, sizeof(a[0]) * num_right);
	MergeSort(p_left, num_left);
	MergeSort(p_right, num_right);
	//merge
	while(index_sum < n){
		if(index_left == num_left)
			a[index_sum++] = p_right[index_right++];
		else if(index_right == num_right)
			a[index_sum++] = p_left[index_left++];
		else if(p_left[index_left] < p_right[index_right])
			a[index_sum++] = p_left[index_left++];
		else
			a[index_sum++] = p_right[index_right++];
	}
	free(p_left);
	free(p_right);
}
*/

//this version of MergeSort declare an shell function, new a temparray in the shell, so saved a lot of space
void Divide(int* a, int* TempArray, int left, int right);
void Merge(int* a, int* TempArray, int left, int left_end, int right_end);

void MergeSort(int *a, int n)
{
	int* TempArray;

	TempArray = (int *)malloc(sizeof(int) * n);
	Divide(a, TempArray, 0, n - 1);
}

void Divide(int* a, int* TempArray, int left, int right)
{
	int mid = (left + right) / 2;

	if(left >= right)
		return ;
	Divide(a, TempArray, left, mid);
	Divide(a, TempArray, mid + 1, right);
	Merge(a, TempArray, left, mid, right);
}

void Merge(int* a, int* TempArray, int left, int left_end, int right_end)
{
	int start = left, index = left, right = left_end + 1;

	while(left <= left_end && right <= right_end){
		if(a[left] < a[right])
			TempArray[index++] = a[left++];
		else
			TempArray[index++] = a[right++];
	}
	while(left <= left_end)
		TempArray[index++] = a[left++];
	while(right <= right_end)
		TempArray[index++] = a[right++];
	//here we may not copy the array, but return the temparray
	for(int i = start; i <= right_end; i++)
		a[i] = TempArray[i];
}

void QuickSort(int *a, int n)
{
	int left = 0, right = n-1, pivot = a[0];
	
	if(n <= 1)
		return ;
	while(left < right)
	{
		while(a[right] >= pivot && left < right)
			right--;
		if(left < right)
			a[left] = a[right];
		while(a[left] <= pivot && left < right)
			left++;
		if(left < right)
			a[right] = a[left];
	}
	a[left] = pivot;
	QuickSort(a, left);
	QuickSort((a+left+1), n-left-1);
}