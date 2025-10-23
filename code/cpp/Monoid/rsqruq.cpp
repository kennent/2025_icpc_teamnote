struct S { ll x; int sz; };
S op(S a, S b) { return {a.x+b.x, a.sz+b.sz}; }
S e() { return {0, 0}; }
S mapping(F f, S x) { if(f != ID) x.x = f*x.sz; return x; }
F composition(F f, F g) { return (f == ID ? g : f); }
F id() { return ID; }