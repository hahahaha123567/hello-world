#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass( ElementType list[], ElementType sorted[], int N, int length );

void output( ElementType list[], int N )
{
    int i;
    for (i=0; i<N; i++) printf("%d ", list[i]);
    printf("\n");
}

void  merge_sort( ElementType list[],  int N )
{
    ElementType extra[MAXN];  /* the extra space required */
    int  length = 1;  /* current length of sublist being merged */
    while( length < N ) { 
        merge_pass( list, extra, N, length ); /* merge list into extra */
        output( extra, N );
        length *= 2;
        merge_pass( extra, list, N, length ); /* merge extra back to list */
        output( list, N );
        length *= 2;
    }
} 


int main()
{
    int N, i;
    ElementType A[MAXN];

    scanf("%d", &N);
    for (i=0; i<N; i++) scanf("%d", &A[i]);
    merge_sort(A, N);
    output(A, N);

    return 0;
}

void merge_pass( ElementType list[], ElementType sorted[], int N, int length )
{
    int i = 0;
    int left, left_end, right, right_end;

    left = 0;
    while (1){
        left_end = left + length - 1;
        if(left_end >= N - 1)
            break;
        right = left_end + 1;
        right_end = right + length - 1;
        if (right_end > N - 1)
            right_end = N - 1;
        for (i = left; i <= right_end; i++){
            if (left > left_end){
                sorted[i] = list[right++];
                //printf("sorted[%d] = %d\n", i, list[right - 1]);
            }
            else if (right > right_end){
                sorted[i] = list[left++];
                //printf("sorted[%d] = %d\n", i, list[left - 1]);
            }
            else if (list[left] < list[right]){
                sorted[i] = list[left++];
                //printf("sorted[%d] = %d\n", i, list[left - 1]);
            }
            else{
                sorted[i] = list[right++];
                //printf("sorted[%d] = %d\n", i, list[right - 1]);
            }
        }
        left = right_end + 1;
    }
    for( ; i < N; i++)
        sorted[i] = list[i];
}