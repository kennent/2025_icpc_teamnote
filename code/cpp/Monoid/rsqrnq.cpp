struct S { ll x; int sz; };
S op(S a, S b){ return {a.x+b.x, a.sz+b.sz}; }
S e(){ return {0, 0}; }
S mapping(F f, S x){ return {x.x + f*x.x, x.sz}; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }