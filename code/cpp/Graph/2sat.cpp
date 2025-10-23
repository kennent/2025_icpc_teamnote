struct csr {
  vector<int> s, el;
  csr(int n, vector<pii>& edges): s(n + 1), el(edges.size()) {
    for (auto e: edges) s[e.first+1]++;
    for (int i = 1; i <= n; i++) s[i] += s[i-1];
    auto cnt = s;
    for (auto e : edges) el[cnt[e.first]++] = e.second;
  }
};

struct scc_graph {
  scc_graph(int n) : _n(n) {}
  void add(int from, int to) { edges.push_back({from, to}); }
  pair<int, vector<int>> scc_ids() {
    auto g = csr(_n, edges);
    int cord = 0, gnum = 0;
    vector<int> vis, low(_n), ord(_n, -1), ids(_n);
    vis.reserve(_n);
    auto dfs = [&](auto self, int v) -> void {
      low[v] = ord[v] = cord++;
      vis.push_back(v);
      for (int i = g.s[v]; i < g.s[v + 1]; i++) {
        auto to = g.el[i];
        if (ord[to] == -1) {
          self(self, to);
          low[v] = min(low[v], low[to]);
        } else low[v] = min(low[v], ord[to]);
      }
      if (low[v] == ord[v]) {
        while (true) {
          int u = vis.back();
          vis.pop_back();
          ord[u] = _n, ids[u] = gnum;
          if (u == v) break;
        }
        gnum++;
      }
    };
    for (int i = 0; i < _n; i++) if (ord[i] == -1) dfs(dfs, i);
    for (auto& x : ids) x = gnum - 1 - x;
    return {gnum, ids};
  }

  vector<vector<int>> scc() {
    auto ids = scc_ids();
    int gnum = ids.first;
    vector<int> cnt(gnum);
    for (auto x : ids.second) cnt[x]++;
    vector<vector<int>> g(ids.first);
    for (int i = 0; i < gnum; i++) g[i].reserve(cnt[i]);
    for (int i = 0; i < _n; i++) g[ids.second[i]].push_back(i);
    return g;
  }

  int _n;
  vector<pii> edges;
};

struct two_sat {
  int n;
  vector<bool> ans;
  scc_graph scc;
  
  explicit two_sat(int _n): n(_n), ans(_n), scc(2*_n) {}
  void add(int i, bool f, int j, bool g) {
    scc.add(2 * i + (f ? 0 : 1), 2 * j + (g ? 1 : 0));
    scc.add(2 * j + (g ? 0 : 1), 2 * i + (f ? 1 : 0));
  }

  bool satisfiable() {
    auto id = scc.scc_ids().second;
    for (int i = 0; i < n; i++) {
      if (id[2 * i] == id[2 * i + 1]) return false;
      ans[i] = id[2 * i] < id[2 * i + 1];
    }
    return true;
  }
  vector<bool> answer() { return ans; }
};