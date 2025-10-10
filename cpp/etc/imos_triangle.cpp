int x, y, s; // (x, y), (x+s, y), (x+s, y+s)를 정점으로 하는 삼각형
for (int i = 0; i < m; i++) {
  cin >> x >> y >> s;
  pos[x][y]++;
  pos[x][y+1]--;
  pos[x+s+1][y]--;
  pos[x+s+2][y+1]++;
  pos[x+s+1][y+s+2]++;
  pos[x+s+2][y+s+2]--;
}
for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) pos[i][j] += pos[i][j-1];
for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) pos[i][j] += pos[i-1][j];
for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) pos[i][j] += pos[i-1][j-1];
int cnt = 0;
for (int i = 1; i <= n; i++) for (int j = 1; j <= i; j++) if (pos[i][j] > 0) cnt++;
