template <class Cap, class Cost> struct mcf_graph {
  public:
    mcf_graph(int n = 0) : _n(n), g(n) {}
    void add_edge(int from, int to, Cap cap, Cost cost) {
      g[from].push_back({to, (int)g[to].size(), cap, cost});
      g[to].push_back({from, (int)g[from].size() - 1, 0, -cost});
    }
    pair<Cap, Cost> flow(int s, int t, Cap flow_limit = numeric_limits<Cap>::max()) {
      Cap flow = 0;
      Cost cost = 0;
      vector<Cost> h(_n, 0);
      vector<int> prev_v(_n), prev_e(_n);
  
      while (flow < flow_limit) {
        vector<Cost> dist(_n, numeric_limits<Cost>::max());
        dist[s] = 0;
        priority_queue<pair<Cost, int>, vector<pair<Cost, int>>, greater<pair<Cost, int>>> que;
        que.push({0, s});
  
        while (!que.empty()) {
          auto [d, v] = que.top();
          que.pop();
          if (dist[v] < d) continue;
          for (int i = 0; i < g[v].size(); i++) {
            _edge& e = g[v][i];
            if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
              dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
              prev_v[e.to] = v;
              prev_e[e.to] = i;
              que.push({dist[e.to], e.to});
            }
          }
        }
  
        if (dist[t] == numeric_limits<Cost>::max()) break;
        for (int i = 0; i < _n; i++) h[i] += dist[i];
  
        Cap d = flow_limit - flow;
        for (int v = t; v != s; v = prev_v[v]) d = min(d, g[prev_v[v]][prev_e[v]].cap);
        flow += d;
        cost += d * h[t];
        for (int v = t; v != s; v = prev_v[v]) {
          _edge& e = g[prev_v[v]][prev_e[v]];
          e.cap -= d;
          g[v][e.rev].cap += d;
        }
      }
      return {flow, cost};
    }
  private:
    struct _edge { int to, rev; Cap cap; Cost cost; };
    int _n;
    vector<vector<_edge>> g;
};