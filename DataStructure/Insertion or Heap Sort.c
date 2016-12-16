# include <stdio.h>
# include <stdlib.h>

# define MAX 100

void InsertSort(int* a, int n, int* Unfinished);
void HeapSort(int *a, int n, int* Unfinished);
# define LeftChild(i) (2 * (i) + 1)
void PercolateDown(int *a, int data, int size);
int isSame(int* a, int* b, int n);
void print(int* a, int n);

int main(void)
{
    int n;
    int Unsorted1[MAX], Unsorted2[MAX], Unfinished[MAX];

    scanf("%d", &n);
    for (int i = 0; i < n; ++i){
        scanf("%d", &Unsorted1[i]);
        Unsorted2[i] = Unsorted1[i];
    }
    for (int i = 0; i < n; ++i)
        scanf("%d", &Unfinished[i]);
    HeapSort(Unsorted1, n, Unfinished);
    InsertSort(Unsorted2, n, Unfinished);
    return 0;
}

void InsertSort(int *a, int n, int* Unfinished)
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
        if(isSame(a, Unfinished, n)){
            printf("Insertion Sort\n");
            inserted++;
            temp = a[inserted];
            for(compared = inserted - 1; compared >= 0; compared--){
                if(a[compared] > temp)
                    a[compared + 1] = a[compared];
                else
                    break;
            }
            a[compared + 1] = temp;
            print(a, n);
            exit(0);
        }
    }
}

void HeapSort(int *a, int n, int* Unfinished)
{
	for (int i = n / 2; i >= 0; i--){
		PercolateDown(a, i, n);
        /*
        if(isSame(a, Unfinished, n)){
            printf("Heap Sort\n");
            if(i >= 1){ 
                i--;
                PercolateDown(a, i, n);
                print(a, n);
                exit(0);
            }
            else{
                i = n - 1;
                int temp = a[0];
                a[0] = a[i];
                a[i] = temp;
                PercolateDown(a, 0, i);
            }
        }
        */
    }
	for (int i = n - 1; i > 0 ; i--){
		int temp = a[0];
		a[0] = a[i];
		a[i] = temp;
		PercolateDown(a, 0, i);
        if(isSame(a, Unfinished, n)){
            printf("Heap Sort\n");
            i--;
            int temp = a[0];
            a[0] = a[i];
            a[i] = temp;
            PercolateDown(a, 0, i);
            print(a, n);
        }
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

int isSame(int* a, int* b, int n)
{
    for (int i = 0; i < n; ++i)
    {
        if(a[i] != b[i])
            return 0;
    }
    return 1;
}

void print(int* a, int n)
{
    for (int i = 0; i < n; ++i)
    {
        if(i == 0)
            printf("%d", a[i]);
        else
            printf(" %d", a[i]);
    }
}