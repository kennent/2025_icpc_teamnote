// ncr
struct Combination {
  const ll MAX, MOD;
  vector<ll> inv, fac, fi;
  Combination(ll max, ll mod): MAX(max), MOD(mod) {
    inv = vector<ll>(max+1);
    fac = vector<ll>(max+1);
    fi = vector<ll>(max+1);
    fac[1] = inv[1] = fi[1] = 1;
    for (ll i = 2; i <= max; i++) {
      fac[i] = (fac[i-1]*i) % mod;
      inv[i] = (mod - mod/i) * inv[mod%i] % mod;
      fi[i] = fi[i-1]*inv[i]  % mod;
    }
  }
  ll ncr(ll n, ll r) {
    if (r == 0 || n == r) return 1;
    return (fac[n]*fi[r]%MOD)*fi[n-r]%MOD;
  }
};