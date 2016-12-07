#include<stdio.h>
void quick_sort(int *a, int n)
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
	quick_sort(a, left);
	quick_sort((a+left+1), n-left-1);
}
int main(void)
{
	int a[5];
	int i;
	
	for(i = 0; i < 5; i++)
		scanf("%d", &a[i]);
	quick_sort(a, 5);
	for(i = 0; i < 5; i++)
		printf("%d ", a[i]);
	return 0;
}

