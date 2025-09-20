// ACL(Atcoder Library) Template - Disjoint set
struct dsu {
  public:
    dsu() : _n(0) {}
    explicit dsu(int n) : _n(n), psz(n, -1) {}
    int merge(int a, int b) {
      int x = leader(a), y = leader(b);
      if (x == y) return x;
      if (-psz[x] < -psz[y]) swap(x, y);
      psz[x] += psz[y];
      psz[y] = x;
      return x;
    }
    bool same(int a, int b) { return leader(a) == leader(b); }
    int leader(int a) { return (psz[a] < 0 ? a : psz[a] = leader(psz[a])); }
    int size(int a) { return -psz[leader(a)]; }
    vector<vector<int>> groups() {
      vector<int> buf(_n), gsz(_n);
      for (int i = 0; i < _n; i++) {
        buf[i] = leader(i);
        gsz[buf[i]]++;
      }
      vector<vector<int>> result(_n);
      for (int i = 0; i < _n; i++) result[i].reserve(gsz[i]);
      for (int i = 0; i < _n; i++) result[buf[i]].push_back(i);
      result.erase(remove_if(result.begin(), result.end(), [&](const vector<int>& v) { return v.empty(); }), result.end());
      return result;
    }
  private:
    int _n;
    vector<int> psz;
};