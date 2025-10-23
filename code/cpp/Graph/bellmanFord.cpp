// require HLD-WeightedEdges, 
template <typename T = int>
vector<T> bellman_ford(int n, kENN3N::WeightedEdges<T> edges, int sv = 0, int ev = -1) {
  T MAX = numeric_limits<T>::max() / 2;
  vector<T> d(n, MAX);
  d[sv] = 0;
  for (int i = 0; i < n; i++) {
    bool upd = false;
    for (auto &e: edges) {
      if (d[e.from] == MAX) continue;
      if (d[e.to] > d[e.from] + e.cost) upd = true, d[e.to] = d[e.from] + e.cost;
    }
    if (!upd) return d;
  }
  if (ev == -1) return vector<T>();
  vector<bool> nega(n, false);
  for (int i = 0; i < n; i++) {
    for (auto &e: edges) {
      if (d[e.from] == MAX) continue;
      if (d[e.to] > d[e.from] + e.cost) nega[e.to] = true, d[e.to] = d[e.from] + e.cost;
      if (nega[e.from]) nega[e.to] = true;
    }
  }
  if (nega[ev]) return vector<T>();
  else return d;
}
/*
벨만 포드 부등식
방법은, xj - xi <= T일때, i -> j로 가는 가중치 T의 간선을 만들어주는 것이다. 
이러한 일련의 작업이 끝났다면, 임의의 정점 i에서 벨만 포드를 돌렸을 때, xj = xi + ShortestPath(i, j) 라는 값을 대입했을 때 저것을 만족함을 보장할 수 있다. 
*/
WeightedEdges<ll> g;
for (int i = 0; i < q; i++) {
  int a, b, x;
  string op;
  cin >> a >> b >> op >> x;
  // a--, b--;
  if (op == "<=") g.push_back(Edge<ll>(b+n, a, x));
  else g.push_back(Edge<ll>(a, b+n, -x));
}
for (int i = 1; i <= n+m; i++) g.push_back(Edge<ll>(0, i, 0));
auto y = bellman_ford(n+m+1, g);
cout << (y.size() ? "Possible" : "Impossible") << "\n";