// dynamic programing
// repeatable Longest Common Subsequence

#include <stdio.h>

int main()
{
	// input
	int wcnmsbchutiren;
	int loveNum;
	scanf("%d", &wcnmsbchutiren);
	scanf("%d", &loveNum);
	int loveColor[loveNum];
	for (int i = 0; i < loveNum; ++i) {
		scanf("%d", &loveColor[i]);
	}
	int colorNum;
	scanf("%d", &colorNum);
	int color[colorNum];
	for (int i = 0; i < colorNum; ++i) {
		scanf("%d", &color[i]);
	}
	// traversal, initial the length
	// bottom up
	int dp[loveNum+1][colorNum+1];
	for (int i = 0; i <= loveNum; ++i) {
		for (int j = 0; j <= colorNum; ++j) {
			if (i == 0 || j == 0) {
				dp[i][j] = 0;
			}
			else if (loveColor[i-1] == color[j-1]) { 
				// dp[i][j] = dp[i][j-1] + 1;
				dp[i][j] = dp[i-1][j] > dp[i][j-1] ? dp[i-1][j] : dp[i][j-1];
				dp[i][j]++;
			}
			else {
				dp[i][j] = dp[i-1][j] > dp[i][j-1] ? dp[i-1][j] : dp[i][j-1];
			}
		}
	}

	printf("%d\n", dp[loveNum][colorNum]);

	return 0;
}

