// Dynamic Programming
// Longest Common Subsequence

#include <stdio.h>

int LCS1(int * str1, int str1Len, int * str2, int str2Len); // basic dp, O(N^2)
// improve: O(NlogN), if one of the sequence is of a limited scope
// 1. sort B
// 2. map A to B: calculate the corresponding value in B
// 3. A: Longest Increasing Subsequence
// 4. get the answer

int main()
{
	// input
	int str1Len, str2Len;
	scanf("%d", &str1Len);
	int str1[str1Len];
	for (int i = 0; i < str1Len; ++i) {
		scanf("%d", &str1[i]);
	}
	scanf("%d", &str2Len);
	int str2[str2Len];
	for (int i = 0; i < str2Len; ++i) {
		scanf("%d", &str2[i]);
	}

	printf("%d\n", LCS1(str1, str1Len, str2, str2Len));
	printf("%d\n", LCS2(str1, str1Len, str2, str2Len));

	return 0;
}

int LCS1(int * str1, int str1Len, int * str2, int str2Len)
{
	int dp[str1Len][str2Len]; // dp[i][j] = str1 of length i, str2 of length j

	for (int i = 0; i < str1Len; ++i) {
		for (int j = 0; j < str2Len; ++j) {
			if (str1[i] == str2[j]) {
				if (i == 0 || j == 0) {
					dp[i][j] = 1;
				}
				else {
					dp[i][j] = dp[i-1][j-1] + 1;
				}
			}
			else {
				if (i == 0 || j == 0) {
					dp[i][j] = 0;
				}
				else {
					dp[i][j] = dp[i-1][j] > dp[i][j-1] ? dp[i-1][j] : dp[i][j-1];
				}
			}
		}
	}

	return dp[str1Len-1][str2Len-1];
}
