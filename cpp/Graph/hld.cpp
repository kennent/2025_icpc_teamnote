// require ACL seg
template <typename T = int>
struct Edge {
  int from, to;
  T cost;
  Edge(int _to, T _cost = 1): from(-1), to(_to), cost(_cost) {} // from is array index
  Edge(int _from, int _to, T _cost): from(_from), to(_to), cost(_cost) {} // only edge save, ex) use in prim
  Edge &operator= (const int &x) {
    to = x;
    return *this;
  }
  operator int() const { return to; }
};
// weighted graph
template <typename T>
using WeightedEdges = vector<Edge<T>>;
template <typename T>
using WeightedFIDXEdges = vector<vector<pair<int, T>>>;
using UnweightedEdges = vector<vector<int>>;
template <typename T>
pair<WeightedEdges<T>, WeightedFIDXEdges<T>> w_fidx_graph(int n, int m = -1, bool is_directed = false, bool is_1idx = true) {
  WeightedEdges<T> wg;
  WeightedFIDXEdges<T> g(n), c(n);
  if (m == -1) m = n-1;
  int ui = 1;
  while (m--) {
    int u, v;
    T w;
    cin >> u >> v;
    // cin >> v;
    // u = ++ui;
    w=0;
    if (is_1idx) u--, v--;
    wg.emplace_back(u, v, w);
    g[u].push_back({v, w});
    if (!is_directed) g[v].push_back({u, w});
  }
  queue<pair<int,int>> q;
  q.push({0, -1});
  while (q.size()) {
    auto [v, pv] = q.front();
    q.pop();
    for (auto &[e, w]: g[v]) {
      if (e != pv) {
        c[v].emplace_back(e, w);
        q.push({e, v});
      }
    }
  }
  return {wg, c};
}
// basic HLD
template <typename T, class S, auto Sop, auto Se>
struct HeavyLightDecomposition {
  // private:
  public:
    int root, eid, fid;
    vector<int> sz, d, p, top, in, out, vis, id;
    vector<T> x;
    WeightedFIDXEdges<T> c;
    atcoder::segtree<S, Sop, Se> seg;
    void dfs1(int v, int pv = -1, int cid = -1) {
      vis[v] = 1;
      sz[v] = 1;
      id[v] = cid;
      for (auto &e: c[v]) {
        if (e.first == pv) continue;
        d[e.first] = d[v]+1;
        p[e.first] = v;
        dfs1(e.first, v, cid);
        sz[v] += sz[e.first];
        if (sz[e.first] > sz[c[v][0].first]) swap(e, c[v][0]);
      }
    }
    void dfs2(int v, int pv = -1) {
      vis[v] = 2;
      in[v] = eid++;
      for (auto &[e, w]: c[v]) {
        if (e == pv) continue;
        top[e] = e == c[v][0].first ? top[v] : e;
        dfs2(e, v);
        x[e] = w;
      }
      out[v] = eid;
    }
  // public:
    HeavyLightDecomposition(WeightedFIDXEdges<T> g, int _root = 0)
      : c(g),
        root(_root),
        eid(0),
        fid(0),
        sz(g.size(), 0),
        d(g.size(), 0),
        x(g.size(), 0),
        in(g.size(), -1),
        out(g.size(), -1),
        vis(g.size(), 0),
        id(g.size(), 0),
        seg(atcoder::segtree<S, Sop, Se>(g.size()+1)),
        top(g.size(), root),
        p(g.size(), root) {
      for (int i = 0; i < g.size(); i++) if (vis[i] != 1) dfs1(i, -1, fid++);
      for (int i = 0; i < g.size(); i++) if (vis[i] != 2) dfs2(i);
      // init_seg();
    }

    void init_seg(vector<T> v) {
      assert(x.size() == v.size());
      for (int i = 0; i < x.size(); i++) seg.set(in[i], x[i] = v[i]);
    }

    int lca(int u, int v) {
      while (top[u] != top[v]) {
        if (d[top[u]] < d[top[v]]) swap(u, v);
        int st = top[u];
        u = p[st];
      }
      if (d[u] > d[v]) swap(u, v);
      return u;
    }

    S query(int u, int v, int inc_start = 0) {
      S r = Se();
      while (top[u] != top[v]) {
        if (d[top[u]] < d[top[v]]) swap(u, v);
        int st = top[u];
        r = Sop(r, seg.prod(in[st], in[u]+1));
        u = p[st];
      }
      if (d[u] > d[v]) swap(u, v);
      r = Sop(r, seg.prod(in[u]+inc_start, in[v]+1));
      return r;
    }
};
// lazy hld
template <typename T, class S, auto Sop, auto Se, class F, auto mapping, auto composition, auto id>
struct LazyHeavyLightDecomposition {
  // private:
  public:
    int root, eid;
    vector<int> sz, d, p, top, in, out, vis;
    vector<T> x;
    WeightedFIDXEdges<T> c;
    atcoder::lazy_segtree<S, Sop, Se, F, mapping, composition, id> seg;
    void dfs1(int v, int pv = -1) {
      vis[v] = 1;
      sz[v] = 1;
      for (auto &e: c[v]) {
        if (e.first == pv) continue;
        d[e.first] = d[v]+1;
        p[e.first] = v;
        dfs1(e.first, v);
        sz[v] += sz[e.first];
        if (sz[e.first] > sz[c[v][0].first]) swap(e, c[v][0]);
      }
    }
    void dfs2(int v, int pv = -1) {
      vis[v] = 2;
      in[v] = eid++;
      for (auto &[e, w]: c[v]) {
        if (e == pv) continue;
        top[e] = e == c[v][0].first ? top[v] : e;
        dfs2(e, v);
        x[e] = w;
      }
      out[v] = eid;
    }
  // public:
    LazyHeavyLightDecomposition(WeightedFIDXEdges<T> g, int _root = 0)
      : c(g),
        root(_root),
        eid(0),
        sz(g.size(), 0),
        d(g.size(), 0),
        x(g.size(), 0),
        in(g.size(), -1),
        out(g.size(), -1),
        vis(g.size(), 0),
        seg(atcoder::lazy_segtree<S, Sop, Se, F, mapping, composition, id>(g.size()+1)),
        top(g.size(), root),
        p(g.size(), root) {
      for (int i = 0; i < g.size(); i++) if (vis[i] != 1) dfs1(i);
      for (int i = 0; i < g.size(); i++) if (vis[i] != 2) dfs2(i);
      // init_seg();
    }

    void init_seg(vector<S> v) {
      assert(x.size() == v.size());
      for (int i = 0; i < x.size(); i++) seg.set(in[i], v[i]);
    }

    int lca(int u, int v) {
      while (top[u] != top[v]) {
        if (d[top[u]] < d[top[v]]) swap(u, v);
        int st = top[u];
        u = p[st];
      }
      if (d[u] > d[v]) swap(u, v);
      return u;
    }

    S query(int u, int v, int inc_start = 0) {
      S l = Se();
      S r = Se();
      while (top[u] != top[v]) {
        // if (d[top[u]] < d[top[v]]) swap(u, v);
        if (d[top[u]] > d[top[v]]) {
          int st = top[u];
          l = Sop(seg.prod(in[st], in[u]+1), l);
          u = p[st];
        } else {
          int st = top[v];
          r = Sop(seg.prod(in[st], in[v]+1), r);
          v = p[st];
        }
      }
      if (d[u] < d[v]) r = Sop(seg.prod(in[u]+inc_start, in[v]+1), r);
      else l = Sop(seg.prod(in[v]+inc_start, in[u]+1), l);
      swap(l.l, l.r);
      return Sop(l, r);
    }

    void apply(int u, int v, F x, int inc_start = 0) {
      while (top[u] != top[v]) {
        if (d[top[u]] < d[top[v]]) swap(u, v);
        int st = top[u];
        seg.apply(in[st], in[u]+1, x);
        u = p[st];
      }
      if (d[u] > d[v]) swap(u, v);
      seg.apply(in[u]+inc_start, in[v]+1, x);
    }
};