template <class S, auto op, auto e, class F, auto mapping, auto composition, auto id>
struct lazy_segtree {
  public:
    lazy_segtree(int n = 0) : lazy_segtree(vector<S>(n, e())) {}
    lazy_segtree(const vector<S>& v) : _n(v.size()) {
      sz = 1;
      while (sz < _n) sz <<= 1;
      lg = __builtin_ctz(sz);
      d.assign(2 * sz, e());
      lz.assign(sz, id());
      for (int i = 0; i < _n; i++) d[sz + i] = v[i];
      for (int i = sz - 1; i >= 1; i--) update(i);
    }
    void set(int p, S x) {
      p += sz;
      for (int i = lg; i >= 1; i--) push(p >> i);
      d[p] = x;
      for (int i = 1; i <= lg; i++) update(p >> i);
    }
    S get(int p) {
      p += sz;
      for (int i = lg; i >= 1; i--) push(p >> i);
      return d[p];
    }
    S prod(int l, int r) {
      if (l == r) return e();
      l += sz, r += sz;
      for (int i = lg; i >= 1; i--) {
        if (((l >> i) << i) != l) push(l >> i);
        if (((r >> i) << i) != r) push((r - 1) >> i);
      }
      S sml = e(), smr = e();
      while (l < r) {
        if (l & 1) sml = op(sml, d[l++]);
        if (r & 1) smr = op(d[--r], smr);
        l >>= 1, r >>= 1;
      }
      return op(sml, smr);
    }
    S all_prod() { return d[1]; }
    void apply(int p, F f) {
      p += sz;
      for (int i = lg; i >= 1; i--) push(p >> i);
      d[p] = mapping(f, d[p]);
      for (int i = 1; i <= lg; i++) update(p >> i);
    }
    void apply(int l, int r, F f) {
      if (l == r) return;
      l += sz, r += sz;
      for (int i = lg; i >= 1; i--) {
        if (((l >> i) << i) != l) push(l >> i);
        if (((r >> i) << i) != r) push((r - 1) >> i);
      }
      int l2 = l, r2 = r;
      while (l < r) {
        if (l & 1) all_apply(l++, f);
        if (r & 1) all_apply(--r, f);
        l >>= 1, r >>= 1;
      }
      l = l2, r = r2;
      for (int i = 1; i <= lg; i++) {
        if (((l >> i) << i) != l) update(l >> i);
        if (((r >> i) << i) != r) update((r - 1) >> i);
      }
    }
  private:
    int _n, sz, lg;
    vector<S> d;
    vector<F> lz;
    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
      d[k] = mapping(f, d[k]);
      if (k < sz) lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
      all_apply(2 * k, lz[k]);
      all_apply(2 * k + 1, lz[k]);
      lz[k] = id();
    }
};