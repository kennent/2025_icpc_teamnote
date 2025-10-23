template <class Cap> struct mf_graph {
  mf_graph(int n = 0) : _n(n), g(n) {}
  void add_edge(int from, int to, Cap cap) {
    int from_id = g[from].size();
    int to_id = g[to].size();
    g[from].push_back({to, to_id, cap});
    g[to].push_back({from, from_id, 0});
  }
  Cap flow(int s, int t, Cap limit = numeric_limits<Cap>::max()) {
    Cap flow = 0;
    vector<int> level(_n), iter(_n);
    auto bfs = [&]() {
      fill(level.begin(), level.end(), -1);
      level[s] = 0;
      queue<int> q;
      q.push(s);
      while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto& e : g[v]) {
          if (e.cap > 0 && level[e.to] < 0) {
            level[e.to] = level[v] + 1;
            q.push(e.to);
          }
        }
      }
      return level[t] != -1;
    };
    auto dfs = [&](auto self, int v, Cap up) -> Cap {
      if (v == t) return up;
      Cap res = 0;
      for (int& i = iter[v]; i < g[v].size(); i++) {
        _edge &e = g[v][i], &re = g[e.to][e.rev];
        if (e.cap > 0 && level[v] < level[e.to]) {
          Cap d = self(self, e.to, min(up - res, e.cap));
          if (d > 0) {
            e.cap -= d;
            re.cap += d;
            res += d;
            if (res == up) break;
          }
        }
      }
      return res;
    };
    while (flow < limit && bfs()) {
      fill(iter.begin(), iter.end(), 0);
      Cap f = dfs(dfs, s, limit - flow);
      if (!f) break;
      flow += f;
    }
    return flow;
  }

private:
  struct _edge { int to, rev; Cap cap; };
  int _n;
  vector<vector<_edge>> g;
};
mf_graph<int> mf;