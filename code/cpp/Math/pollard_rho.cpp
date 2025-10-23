// time: O(n^(1/4))
using i64 = __int128_t;
i64 my_abs(i64 x) { return (x < 0 ? -1*x : x); }
i64 primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41 };
// i64 primes[] = { 2, 7, 61 }; // int only
i64 f(i64 x, i64 p, i64 mod) {
  i64 r = 1;
  x %= mod;
  while (p) {
    if (p%2) r *= x, r %= mod;
    p /= 2, x *= x, x %= mod;
  }
  return r;
}
// a is test number, a^d = 1 (MOD N), a^(d*2^r) = -1 (MOD N), d is odd
bool miller_rabin(i64 n, i64 a) {
  if (n == a) return true;
  if (a % n == 0) return false;
  i64 k = n-1;
  while (true) {
    i64 t = f(a, k, n);
    if (t == n-1) return true;
    if (k%2) return (t == 1 || t == n-1);
    k /= 2;
  }
}
bool isp(i64 x) {
  bool p = true;
  for (auto &e: primes) {
    p &= miller_rabin(x, e);
    if (!p) return false;
  }
  return true;
}
void g(i64 x, vector<i64> &v) {
  if (x == 1) return;
  if (x%2 == 0) { v.push_back(2); g(x/2, v); return; }
  if (isp(x)) { v.push_back(x); return; }
  i64 a, b, c, w = x;
  auto h = [&](i64 y) { return (c + y*y%x) % x; };
  do {
    if (w == x) a = b = rand()%(x-2) + 2, c = rand() % 20 + 1;
    a = h(a), b = h(h(b)), w = __gcd(my_abs(a-b), x);
  } while (w == 1);
  g(w, v);
  g(x/w, v);
}
// source: jinhan, factorize code
vector<pair<i64, int>> pollard_rho(i64 x) {
  vector<i64> v;
  vector<pair<i64, int>> r;
  g(x, v);
  sort(v.begin(), v.end());
  for (auto e: v) {
    if (r.size() && r.back().first == e) r.back().second++;
    else r.push_back({ e, 1 });
  }
  return r;
}
int main() {
  ll x;
  while (cin >> x) {
    ll r = 1;
    for (auto [e, c]: pollard_rho(x)) r *= (c+1);
    cout << r << "\n";
  }
}