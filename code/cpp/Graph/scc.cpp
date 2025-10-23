// 1-index, initialize: scc_graph(int size), necessary make_graph
struct scc_graph {
  int n, id = 0;
  vector<int> ids, finished;
  vector<vector<int>> path, scc;
  stack<int> stk;

  scc_graph(int _n) {
    n = _n;
    ids = finished = vector<int>(n+1);
    path = vector<vector<int>>(n+1);
  }

  void make_graph() { for (int i = 1; i <= n; i++) if (!ids[i]) dfs(i); }
  void add_edge(int u, int v) { path[u].push_back(v); }

  int dfs(int s) {
    ids[s] = ++id;
    stk.push(s);

    int parent = ids[s];
    for (auto &i: path[s]) {
      if (!ids[i]) parent = min(parent, dfs(i));
      else if (!finished[i]) parent = min(parent, ids[i]);
    }

    if (parent == ids[s]) {
      vector<int> findset;
      while (true) {
        auto x = stk.top();
        stk.pop();

        findset.push_back(x);
        finished[x] = 1;
        if (s == x) break;
      }
      sort(findset.begin(), findset.end());
      scc.push_back(findset);
    }

    return parent;
  }
};