template <class S, auto op, auto e> struct segtree {
  public:
    segtree(int n = 0) : segtree(vector<S>(n, e())) {}
    segtree(const vector<S>& v) : _n(v.size()) {
      sz = 1;
      while (sz < _n) sz <<= 1;
      d.assign(2 * sz, e());
      for (int i = 0; i < _n; i++) d[sz + i] = v[i];
      for (int i = sz - 1; i >= 1; i--) update(i);
    }
    void set(int p, S x) {
      p += sz;
      d[p] = x;
      for (int i = 1; i <= __builtin_ctz(sz); i++) update(p >> i);
    }
    S get(int p) { return d[p + sz]; }
    S prod(int l, int r) {
      S sml = e(), smr = e();
      l += sz;
      r += sz;
      while (l < r) {
        if (l & 1) sml = op(sml, d[l++]);
        if (r & 1) smr = op(d[--r], smr);
        l >>= 1;
        r >>= 1;
      }
      return op(sml, smr);
    }
    S all_prod() { return d[1]; }
  private:
    int _n, sz;
    vector<S> d;
    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};