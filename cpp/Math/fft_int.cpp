using pll = pair<ll, ll>;
using ull = unsigned long long;
// X.v 와 같이 접근해야함. int 범위 내 NTT 전용
namespace NTT {
  constexpr int MOD = 998244353;
  constexpr int G = 3; // Primitive root for MOD
  struct mint {
    int v;
    mint(ll x = 0) : v(x % MOD) { if (v < 0) v += MOD; }
    mint& operator+=(const mint& o) { v += o.v; if (v >= MOD) v -= MOD; return *this; }
    mint& operator-=(const mint& o) { v -= o.v; if (v < 0) v += MOD; return *this; }
    mint& operator*=(const mint& o) { v = (int)((ll)v * o.v % MOD); return *this; }
    mint operator+(const mint& o) const { return mint(*this) += o; }
    mint operator-(const mint& o) const { return mint(*this) -= o; }
    mint operator*(const mint& o) const { return mint(*this) *= o; }
    mint pow(ll n) const {
      mint res = 1, x = *this;
      while (n > 0) {
        if (n & 1) res *= x;
        x *= x;
        n >>= 1;
      }
      return res;
    }
    mint inv() const { return pow(MOD - 2); }
  };
  int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
  }
  int bsf(unsigned int n) { return __builtin_ctz(n); }
  void butterfly(vector<mint>& a) {
    int n = a.size();
    int h = ceil_pow2(n);
    static bool first = true;
    static vector<mint> sum_e;
    if (first) {
      first = false;
      sum_e.resize(30);
      mint es[30], ies[30];
      int cnt2 = bsf(MOD - 1);
      mint e = mint(G).pow((MOD - 1) >> cnt2), ie = e.inv();
      for (int i = cnt2; i >= 2; i--) {
        es[i - 2] = e;
        ies[i - 2] = ie;
        e *= e;
        ie *= ie;
      }
      mint now = 1;
      for (int i = 0; i < cnt2 - 2; i++) {
        sum_e[i] = es[i] * now;
        now *= ies[i];
      }
    }
    for (int ph = 1; ph <= h; ph++) {
      int w = 1 << (ph - 1), p = 1 << (h - ph);
      mint now = 1;
      for (int s = 0; s < w; s++) {
        int offset = s << (h - ph + 1);
        for (int i = 0; i < p; i++) {
          auto l = a[i + offset];
          auto r = a[i + offset + p] * now;
          a[i + offset] = l + r;
          a[i + offset + p] = l - r;
        }
        now *= sum_e[bsf(~(unsigned int)(s))];
      }
    }
  }
  void butterfly_inv(vector<mint>& a) {
    int n = a.size();
    int h = ceil_pow2(n);
    static bool first = true;
    static vector<mint> sum_ie;
    if (first) {
      first = false;
      sum_ie.resize(30);
      mint es[30], ies[30];
      int cnt2 = bsf(MOD - 1);
      mint e = mint(G).pow((MOD - 1) >> cnt2), ie = e.inv();
      for (int i = cnt2; i >= 2; i--) {
        es[i - 2] = e; ies[i - 2] = ie;
        e *= e; ie *= ie;
      }
      mint now = 1;
      for (int i = 0; i < cnt2 - 2; i++) { sum_ie[i] = ies[i] * now; now *= es[i]; }
    }
    for (int ph = h; ph >= 1; ph--) {
      int w = 1 << (ph - 1), p = 1 << (h - ph);
      mint inow = 1;
      for (int s = 0; s < w; s++) {
        int offset = s << (h - ph + 1);
        for (int i = 0; i < p; i++) {
          auto l = a[i + offset];
          auto r = a[i + offset + p];
          a[i + offset] = l + r;
          a[i + offset + p] = (l - r) * inow;
        }
        inow *= sum_ie[bsf(~(unsigned int)(s))];
      }
    }
  }
  vector<mint> convolution(vector<mint> a, vector<mint> b) {
    int n = a.size(), m = b.size();
    if (!n || !m) return {};
    if (min(n, m) <= 60) {
      if (n < m) { swap(n, m); swap(a, b); }
      vector<mint> ans(n + m - 1);
      for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) ans[i + j] += a[i] * b[j];
      return ans;
    }
    int z = 1 << ceil_pow2(n + m - 1);
    a.resize(z); b.resize(z);
    butterfly(a); butterfly(b);
    for (int i = 0; i < z; i++) a[i] *= b[i];
    butterfly_inv(a);
    a.resize(n + m - 1);
    mint iz = mint(z).inv();
    for (int i = 0; i < n + m - 1; i++) a[i] *= iz;
    return a;
  }
} // namespace NTT
vector<NTT::mint> a;