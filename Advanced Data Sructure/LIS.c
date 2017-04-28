// Dynamic Programming
// Longest Incresing Subsequence

#include <stdio.h>

int LIS1(int * str, int strLen); // basic dp, O(N^2)
int LIS2(int * str, int strLen); // O(NlogN)

int main()
{
	// input
	int strLen;
	scanf("%d", &strLen);
	int str[strLen];
	for (int i = 0; i < strLen; ++i) {
		scanf("%d", &str[i]);
	}

	printf("%d\n", LIS1(str, strLen));
	printf("%d\n", LIS2(str, strLen));

	return 0;
}

int LIS1(int * str, int strLen)
{
	int length[strLen]; // LIS length till each node

	// build the dp
	for (int i = 0; i < strLen; ++i) {
		// initialize
		length[i] = 1;
		// traverse
		for (int j = 0; j < i; ++j) {
			if (length[j] >= length[i] && str[j] < str[i]) {
				length[i] = length[j] + 1;
			}
		}
	}
	// search the longest
	int max = 0;
	for (int i = 0; i < strLen; ++i) {
		if (length[i] > max) {
			max = length[i];
		}
	}
	return max;
}

int search(int * str, int left, int right, int n); // search function used in LIS2

int LIS2(int * str, int strLen)
{
	int lastValue[strLen]; // [i] = the last value of the sequence of length i+1
	int index = -1; // current sequence length

	for (int i = 0; i < strLen; ++i) {
		// insert into lastValue
		if (index < 0 || str[i] > lastValue[index]) {
			lastValue[++index] = str[i];
			continue;
		}
		// update lastValue
		lastValue[search(lastValue, 0, index, str[i])] = str[i];
	}

	return index + 1;
}

int search(int * str, int left, int right, int n)
{
	if (left == right) {
		return left;
	}
	int mid = (left + right) / 2 + 1;
	if (str[mid] <= n) {
		return search(str, mid, right, n);
	}
	else {
		return search(str, left, mid - 1, n);
	}
}