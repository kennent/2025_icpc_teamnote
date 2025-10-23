struct S {
  bool check;
  int l, r, sum, len;
  S(int x = 0, int c = false): sum(0) { l = r = x; len = 1; check = c; }
  S(int l, int r, int sum, int len, int c): l(l), r(r), sum(sum), len(len) { check = c; }
};
using F = int;
const F ID = -1;
S op(S a, S b) {
  if (!a.check || !b.check) {
    if (!a.check && !b.check) return S();
    if (!a.check) return b;
    else if (!b.check) return a;
  }
  return S(a.l, b.r, a.sum+b.sum+(a.r==b.l), a.len+b.len, true);
}
S e() { return S(); }
S mapping(F f, S x) { 
  if (f == ID) return x;
  return S(f, f, x.len-1, x.len, true);
}
F composition(F f, F g) { return (f == ID ? g : f); }
F id() { return ID; }