using ull = unsigned long long;
// fft ll = DnC + CRT
// ================= AtCoder Convolution Library =================
namespace atcoder {
namespace internal {
  int ceil_pow2(int n) { int x = 0; while ((1U << x) < (ui)(n)) x++; return x; }
  int bsf(ui n) { return __builtin_ctz(n); }
  constexpr ll safe_mod(ll x, ll m) { x %= m; if (x < 0) x += m; return x; }
  constexpr pair<ll, ll> inv_gcd(ll a, ll b) {
    a = safe_mod(a, b);
    if (a == 0) return {b, 0};
    ll s = b, t = a;
    ll m0 = 0, m1 = 1;
    while (t) {
      ll u = s / t;
      s -= t * u;
      m0 -= m1 * u;
      auto tmp = s; s = t; t = tmp;
      tmp = m0; m0 = m1; m1 = tmp;
    }
    if (m0 < 0) m0 += b / s;
    return {s, m0};
  }
  constexpr ll pow_mod(ll x, ll n, int m) {
    if (m == 1) return 0;
    ui _m = (ui)(m);
    ull r = 1, y = safe_mod(x, m);
    while (n) { if (n & 1) r = (r * y) % _m; y = (y * y) % _m; n >>= 1; }
    return r;
  }
  constexpr bool is_prime(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 7 || n == 61) return true;
    if (n % 2 == 0) return false;
    ll d = n - 1;
    while (d % 2 == 0) d /= 2;
    constexpr ll bases[3] = {2, 7, 61};
    for (ll a : bases) {
      ll t = d, y = pow_mod(a, t, n);
      while (t != n - 1 && y != 1 && y != n - 1) { y = y * y % n; t <<= 1; }
      if (y != n - 1 && t % 2 == 0) return false;
    }
    return true;
  }
  constexpr int primitive_root(int m) {
    if (m == 998244353) return 3;
    if (m == 2) return 1;
    int divs[20] = {2}, cnt = 1;
    int x = (m - 1) / 2;
    while (x % 2 == 0) x /= 2;
    for (int i = 3; (ll)(i) * i <= x; i += 2) {
      if (x % i == 0) { divs[cnt++] = i; while (x % i == 0) x /= i; }
    }
    if (x > 1) divs[cnt++] = x;
    for (int g = 2; ; g++) {
      bool ok = true;
      for (int i = 0; i < cnt; i++) {
        if (pow_mod(g, (m - 1) / divs[i], m) == 1) { ok = false; break; }
      }
      if (ok) return g;
    }
  }
  template <class T> using is_integral = typename std::is_integral<T>;
} // namespace internal
template <int m>
struct static_modint {
  using mint = static_modint;
  static constexpr int mod() { return m; }
  int v;
  static_modint(ll x = 0) : v(x % m) { if (v < 0) v += m; }
  mint& operator+=(const mint& o) { v += o.v; if (v >= m) v -= m; return *this; }
  mint& operator-=(const mint& o) { v -= o.v; if (v < 0) v += m; return *this; }
  mint& operator*=(const mint& o) { v = (int)((ll)v * o.v % m); return *this; }
  mint& operator/=(const mint& o) { return *this = *this * o.inv(); }
  mint operator+(const mint& o) const { return mint(*this) += o; }
  mint operator-(const mint& o) const { return mint(*this) -= o; }
  mint operator*(const mint& o) const { return mint(*this) *= o; }
  mint operator/(const mint& o) const { return mint(*this) /= o; }
  mint pow(ll n) const {
    mint res = 1, x = *this;
    while (n > 0) { if (n & 1) res *= x; x *= x; n >>= 1; }
    return res;
  }
  mint inv() const {
    if (prime) { assert(v); return pow(m - 2); } 
    else { auto eg = internal::inv_gcd(v, m); assert(eg.first == 1); return eg.second; }
  }
  static constexpr bool prime = internal::is_prime(m);
};
namespace internal {
  template <class mint> void butterfly(vector<mint>& a) {
    constexpr int g = primitive_root(mint::mod());
    int n = a.size(), h = ceil_pow2(n);
    static vector<mint> sum_e;
    if (sum_e.empty()) {
      sum_e.resize(30);
      mint es[30], ies[30];
      int cnt2 = bsf(mint::mod() - 1);
      mint e = mint(g).pow((mint::mod() - 1) >> cnt2), ie = e.inv();
      for (int i = cnt2; i >= 2; i--) {
        es[i - 2] = e; ies[i - 2] = ie; e *= e; ie *= ie;
      }
      mint now = 1;
      for (int i = 0; i < cnt2 - 2; i++) {
        sum_e[i] = es[i] * now; now *= ies[i];
      }
    }
    for (int ph = 1; ph <= h; ph++) {
      int w = 1 << (ph - 1), p = 1 << (h - ph);
      mint now = 1;
      for (int s = 0; s < w; s++) {
        int offset = s << (h - ph + 1);
        for (int i = 0; i < p; i++) {
          auto l = a[i + offset], r = a[i + offset + p] * now;
          a[i + offset] = l + r; a[i + offset + p] = l - r;
        }
        now *= sum_e[bsf(~(ui)(s))];
      }
    }
  }
  template <class mint> void butterfly_inv(vector<mint>& a) {
    constexpr int g = primitive_root(mint::mod());
    int n = a.size(), h = ceil_pow2(n);
    static vector<mint> sum_ie;
    if (sum_ie.empty()) {
      sum_ie.resize(30);
      mint es[30], ies[30];
      int cnt2 = bsf(mint::mod() - 1);
      mint e = mint(g).pow((mint::mod() - 1) >> cnt2), ie = e.inv();
      for (int i = cnt2; i >= 2; i--) {
        es[i - 2] = e; ies[i - 2] = ie; e *= e; ie *= ie;
      }
      mint now = 1;
      for (int i = 0; i < cnt2 - 2; i++) {
        sum_ie[i] = ies[i] * now; now *= es[i];
      }
    }
    for (int ph = h; ph >= 1; ph--) {
      int w = 1 << (ph - 1), p = 1 << (h - ph);
      mint inow = 1;
      for (int s = 0; s < w; s++) {
        int offset = s << (h - ph + 1);
        for (int i = 0; i < p; i++) {
          auto l = a[i + offset], r = a[i + offset + p];
          a[i + offset] = l + r; a[i + offset + p] = (l - r) * inow;
        }
        inow *= sum_ie[bsf(~(ui)(s))];
      }
    }
  }
} // namespace internal
template <class mint>
vector<mint> convolution(vector<mint> a, vector<mint> b) {
  int n = a.size(), m = b.size();
  if (!n || !m) return {};
  int z = 1 << internal::ceil_pow2(n + m - 1);
  a.resize(z); b.resize(z);
  internal::butterfly(a); internal::butterfly(b);
  for (int i = 0; i < z; i++) a[i] *= b[i];
  internal::butterfly_inv(a);
  a.resize(n + m - 1);
  mint iz = mint(z).inv();
  for (int i = 0; i < n + m - 1; i++) a[i] *= iz;
  return a;
}
template <ui mod = 998244353, class T, enable_if_t<internal::is_integral<T>::value>* = nullptr>
vector<T> convolution_int(const vector<T>& a, const vector<T>& b) {
  int n = a.size(), m = b.size();
  if (!n || !m) return {};
  using mint = static_modint<mod>;
  vector<mint> a2(n), b2(m);
  for (int i = 0; i < n; i++) a2[i] = mint(a[i]);
  for (int i = 0; i < m; i++) b2[i] = mint(b[i]);
  auto c2 = convolution(move(a2), move(b2));
  vector<T> c(n + m - 1);
  for (int i = 0; i < n + m - 1; i++) c[i] = c2[i].v;
  return c;
}
vector<ll> convolution_ll(const vector<ll>& a, const vector<ll>& b) {
  int n = a.size(), m = b.size();
  if (!n || !m) return {};
  static constexpr ui MOD1 = 754974721; // 2^24 * 45 + 1
  static constexpr ui MOD2 = 167772161; // 2^25 * 5 + 1
  static constexpr ui MOD3 = 469762049; // 2^26 * 7 + 1
  auto c1 = convolution_int<MOD1>(a, b);
  auto c2 = convolution_int<MOD2>(a, b);
  auto c3 = convolution_int<MOD3>(a, b);
  ll m1_m2 = (ll)MOD1 * MOD2;
  ll m1_inv_m2 = internal::inv_gcd(MOD1, MOD2).second;
  ll m1_m2_inv_m3 = internal::inv_gcd(m1_m2, MOD3).second;
  vector<ll> c(n + m - 1);
  for (int i = 0; i < n + m - 1; i++) {
    ll v1 = c1[i], v2 = c2[i], v3 = c3[i];
    ll x = v1;
    ll y = (v2 - x) * m1_inv_m2 % MOD2;
    if (y < 0) y += MOD2;
    x += y * MOD1;
    ll z = (v3 - x % MOD3) * m1_m2_inv_m3 % MOD3;
    if (z < 0) z += MOD3;
    c[i] = x + z * m1_m2;
  }
  return c;
}} // namespace atcoder