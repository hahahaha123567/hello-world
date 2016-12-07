#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void merge_sort(int *a, int n)
{
	int num_left, num_right, *p_left, *p_right;
	int i = 0, j = 0, k = 0, m;
	
	if(n <= 1)
		return ; 
	num_left = n / 2;
	num_right = n - num_left;
	p_left = (int *)malloc(sizeof(a[0]) * num_left);
	memcpy(p_left, a, sizeof(a[0]) * num_left);
	p_right = (int *)malloc(sizeof(a[0]) * num_right);
	memcpy(p_right, a+num_left, sizeof(a[0]) * num_right);
	merge_sort(p_left, num_left);
	merge_sort(p_right, num_right);
	while(k < n){
		if(i == num_left)
			a[k++] = p_right[j++];
		else if(j == num_right)
			a[k++] = p_left[i++];
		else if(p_left[i] < p_right[j])
			a[k++] = p_left[i++];
		else
			a[k++] = p_right[j++];
	}
	free(p_left);
	free(p_right);
}
int main(void)
{
	int i, a[5];
	
	for(i = 0; i < 5; i++)
		scanf("%d", &a[i]);
	merge_sort(a, 5);
	for(i = 0; i < 5; i++)
		printf("%d ", a[i]);
	return 0;
}
