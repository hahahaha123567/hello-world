#include <stdio.h>
#include <stdlib.h>

#define NUMBER 15

int* Copy(int *a, int n);
void Print(int *a, int n);
void InsertionSort(int *a, int n);
void ShellSort(int *a, int n);
void HeapSort(int *a, int n);
void MergeSort(int *a, int n);
void QuickSort(int *a, int n);

int main(void)
{
	int *a = malloc(sizeof(int) * NUMBER);
	int *b, *c, *d, *e;

	srand( (unsigned int)time(0) );
	for(int i = 0; i < NUMBER; i++)
		a[i] = rand() % 100;
	b = Copy(a, NUMBER);
	c = Copy(a, NUMBER);
	d = Copy(a, NUMBER);
	e = Copy(a, NUMBER);

	printf("Array before sorted:\n");
	Print(a, NUMBER);

	InsertionSort(a, NUMBER);
	printf("Array after InsertionSort:\n");
	Print(a, NUMBER);

	ShellSort(b, NUMBER);
	printf("Array after ShellSort:\n");
	Print(b, NUMBER);

	HeapSort(c, NUMBER);
	printf("Array after HeapSort:\n");
	Print(c, NUMBER);

	MergeSort(d, NUMBER);
	printf("Array after MergeSort:\n");
	Print(d, NUMBER);

	QuickSort(e, NUMBER);
	printf("Array after QuickSort:\n");
	Print(e, NUMBER);

	return 0;
}

void InsertionSort(int *a, int n)
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

/*
this version of heapsort: build a new heap by inserting for n times, and delete elements for n times
it cost double space

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
*/

//this version of heapsort divide the original array to two parts: unsorted and sorted
# define LeftChild(i) (2 * (i) + 1)
void PercolateDown(int *a, int data, int size);

void HeapSort(int *a, int n)
{
	for (int i = n / 2; i >= 0; i--)
		PercolateDown(a, i, n);
	for (int i = n - 1; i > 0 ; i--){
		int temp = a[0];
		a[0] = a[i];
		a[i] = temp;
		PercolateDown(a, 0, i);
	}
}

void PercolateDown(int *a, int data, int size)
{
	int parent = data, child = LeftChild(parent);

    for( ; child < size; parent = child, child = LeftChild(parent)){
        if(child + 1 < size && a[child] < a[child + 1])
            child++;
        if(a[parent] < a[child]){
            int temp = a[parent];
            a[parent] = a[child];
            a[child] = temp;
        }
        else
            break;
    }
}

/*
I learned this version of MergeSort from BlackWhite, but it cost too much memory

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

//this version of MergeSort declare an shell function, new a temp array in the shell, so saved a lot of space
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

/*
I learned this version of quick sort from BlackWhite too, 

void QuickSort(int *a, int n)
{
	int left = 0, right = n-1, pivot = a[0];
	
	if(n <= 1)
		return ;
	while(left < right)
	{
		while(a[right] > pivot && left < right)
			right--;
		if(left < right)
			a[left] = a[right];
		while(a[left] < pivot && left < right)
			left++;
		if(left < right)
			a[right] = a[left];
	}
	a[left] = pivot;
	QuickSort(a, left);
	QuickSort((a+left+1), n-left-1);
}
*/

//a better way of select the pivot and divide the array
# define CUTOFF 10	//when the number of elements is small enough, choose InsertionSort instead of QuickSort
void Qsort(int *a, int left, int right);
int Median3(int *a, int left, int right);
void Swap(int *a, int *b);

//drive function
void QuickSort(int *a, int n)
{
	Qsort(a, 0, n - 1);
}

void Qsort(int *a, int left, int right)
{
	int pivot, index_left, index_right;
	//QuickSort
	if(left + CUTOFF <= right){
		pivot = Median3(a, left, right);
		index_left = left;
		index_right = right - 1;
		while(1){
			//**Warning**
			//the ++ opration must happen whether the value is bog or small
			//'<' not '<=', unnecessary exchange is better than produce unbalanced subarray if all elements are equal
			while(a[++index_left] < pivot) ;
			while(a[--index_right] > pivot) ;
			if(index_left < index_right)
				Swap(&a[index_left], &a[index_right]);
			else
				break;
		}
		Qsort(a, left, index_left - 1);
		Qsort(a, index_right + 1, right);
	}
	//InsertionSort
	else
		InsertionSort(a + left, right - left + 1);
}

//first: a[left] < a[mid] < a[right]
//then:	 take a[mid] as pivot, put it in the position [right - 1]
int Median3(int *a, int left, int right)
{
	int mid = (left + right) / 2;

	if(a[left] > a[mid])
		Swap(&a[left], &a[mid]);
	if(a[left] > a[right])
		Swap(&a[left], &a[right]);
	if(a[mid] > a[right])
		Swap(&a[mid], &a[right]);
	Swap(&a[mid], &a[right - 1]);
	return a[right - 1];
}

void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int* Copy(int *a, int n)
{
	int *b = malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
		b[i] = a[i];
	return b;
}

void Print(int *a, int n)
{
	for (int i = 0; i < n; ++i)
		printf("%d ", a[i]);
	printf("\n");
}