int citys[101][101];
int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= 100; i++)
    for (int j = 1; j <= 100; j++)
      citys[i][j] = 1e6 * 100;
  int a, b, c;
  for (int i = 0; i < m; i++) {
    cin >> a >> b >> c;
    citys[a][b] = min(citys[a][b], c);
  }
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (i != j)
          citys[i][j] = min(citys[i][j], citys[i][k]+citys[k][j]);
      }
    }
  }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      cout << (citys[i][j] != 1e6 * 100 ? citys[i][j] : 0) << (j != n ? ' ' : '\n');
}