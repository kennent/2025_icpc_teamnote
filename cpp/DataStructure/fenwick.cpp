ll fenwick[N+1];
void update(int i, ll diff) {
  while (i <= N) {
    a[i] += diff;
    i += (i & -i);
  }
}
// ex. sum
ll query(int i) {
  ll r = 0;
  while (i) {
    r += a[i];
    i -= (i & -i);
  }
  return r;
}