#include <stdio.h>
#include <stdlib.h>

int main()
{
	// input
	int n;
	scanf("%d", &n);
	// a[n] stores the n inputs
	int a[n];
	for (int i = 0; i < n; ++i) {
		scanf("%d", a+i);
	}

	// the Longest Increasing Subsequence on the left of i
	// upLen[i] means the length of LIS ended with i
	int upLen[n];
	for (int i = 0; i < n; ++i) {
		// initial as 1
		upLen[i] = 1;
		// traverse the nodes on the left of i
		for (int j = 0; j < i; ++j) {
			// suppose that j1, j2, ... are nodes on the left of i and a[j] < a[i]
			// upLen[i] = max(upLen[j1], upLen[j2], ...)
			if (upLen[j] >= upLen[i] && a[j] < a[i]) {
				upLen[i] = upLen[j] + 1;
			}
		}
	}

	// the Longest Decreasing Subsequence on the right of i
	// downLen[i] means the length of LDS ended with i
	int downLen[n];
	for (int i = n-1; i >= 0; --i) {
		// initial as 1
		downLen[i] = 1;
		// traverse the nodes on the left of i
		for (int j = n-1; j > i; --j) {
			// suppose that j1, j2, ... are nodes on the right of i and a[j] < a[i]
			// downLen[i] = max(downLen[j1], downLen[j2], ...)
			if (downLen[j] >= downLen[i] && a[j] < a[i]) {
				downLen[i] = downLen[j] + 1;
			}
		}
	}

	// calculate done, look for the peak
	int maxLength = 0, peak;
	for (int i = 0; i < n; ++i) {
		// if there isn't a increasing sequence or decreasing sequence, ignore the node
		if (upLen[i] == 1 || downLen[i] == 1) {
			continue;
		}
		// renew the peak node
		if (upLen[i] + downLen[i] > maxLength) {
			peak = i;
			maxLength = upLen[i] + downLen[i];
		}
		// if length is equal, compare the symmetric
		else if (upLen[i] + downLen[i] == maxLength) {
			if (abs(upLen[i] - downLen[i]) < abs(upLen[peak] - downLen[peak])) {
				peak = i;
				maxLength = upLen[i] + downLen[i];
			}
		}
	}

	// output
	if (maxLength == 0) {
		printf("No peak shape\n");
	}
	else {
		printf("%d %d %d\n", maxLength-1, peak+1, a[peak]);
	}

	return 0;
}
