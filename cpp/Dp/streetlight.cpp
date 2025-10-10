int n, m;
ll x[1002], w[1002], wsum[1002], dp[1002][1002][2];
int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> x[i] >> w[i];
    wsum[i] = wsum[i-1] + w[i];
  }
  for (int i = 0; i <= 1001; i++) for (int j = 0; j <= 1001; j++) dp[i][j][0] = dp[i][j][1] = 1'000'000'000'000'000LL;
  dp[m][m][0] = dp[m][m][1] = 0;
  for (int len = 1; len <= n; len++) {
    for (int l = max(1, m-len+1); l <= m; l++) {
      int r = l+len-1;
      if (r > n) continue;
      if (l-1 >= 1) dp[l-1][r][0] = min({dp[l-1][r][0], dp[l][r][0]+(wsum[n]-wsum[r]+wsum[l-1])*(x[l]-x[l-1]), dp[l][r][1]+(wsum[n]-wsum[r]+wsum[l-1])*(x[r]-x[l-1])});
      if (r+1 <= n) dp[l][r+1][1] = min({dp[l][r+1][1], dp[l][r][0]+(wsum[n]-wsum[r]+wsum[l-1])*(x[r+1]-x[l]), dp[l][r][1]+(wsum[n]-wsum[r]+wsum[l-1])*(x[r+1]-x[r])});
    }
  }
  cout << min(dp[1][n][0], dp[1][n][1]);
}