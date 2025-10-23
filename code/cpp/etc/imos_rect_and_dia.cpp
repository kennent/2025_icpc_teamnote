const int FIX = 5, DIV = 1e9;
int ty, px, py, qx, qy, r;
for (int i = 0; i < k; i++) {
  cin >> ty;
  if (ty == 1) {
    cin >> px >> py >> qx >> qy;
    px += FIX;
    py += FIX;
    qx += FIX;
    qy += FIX;
    rect[py][px] += 1;
    rect[qy+1][px] -= 1;
    rect[py][qx+1] -= 1;
    rect[qy+1][qx+1] += 1;
  } else {
    cin >> px >> py >> r;
    px += FIX;
    py += FIX;
    dia[py-r][px] += 1;
    dia[py-r+1][px] += 1;
    dia[py+1][px-r-1] -= 1;
    dia[py+1][px-r] -= 1;
    dia[py+1][px+r+1] -= 1;
    dia[py+1][px+r] -= 1;
    dia[py+r+1][px] += 1;
    dia[py+r+2][px] -= 1;
  }
}
for (int i = 0; i < h+FIX; i++) for (int j = 1; j < w+FIX; j++) rect[i][j] += rect[i][j-1];
for (int i = 0; i < w+FIX; i++) for (int j = 1; j < h+FIX; j++) rect[j][i] += rect[j-1][i];
for (int i = 1; i < h+FIX; i++) for (int j = 1; j < w+FIX; j++) dia[i][j] += dia[i-1][j-1];
for (int i = 1; i < h+FIX; i++) for (int j = 0; j < w-1+FIX; j++) dia[i][j] += dia[i-1][j+1];
for (int i = 0+FIX; i < h+FIX; i++) {
  for (int j = 0+FIX; j < w+FIX; j++) {
    if ((rect[i][j] + dia[i][j]) % 2) cout << "#";
    else cout << ".";
  }
  cout << "\n";
}