// Tree 형태에서, 어떤 값의 조상...
int n, f[200000], dp[32][200000];
void doubling() {
  for (int j = 0; j < n; j++) dp[0][j] = f[j];
  for (int i = 1; i < 31; i++) {
    for (int j = 0; j < n; j++) {
      dp[i][j] = dp[i-1][dp[i-1][j]];
    }
  }
}