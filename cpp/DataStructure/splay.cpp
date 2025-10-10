// ref: nachia library, like ACL seg, lazy
struct SplayTreeByIdx{
  // ACL segと　ほぼ同じ
  struct S { ll l, r, ans, len; }; // affine monoid
  static S op(S l, S r) { 
    ll nl = (l.l == l.len ? l.len+r.l : l.l);
    ll nr = (r.r == r.len ? r.len+l.r : r.r);
    ll len = l.len+r.len;
    return { nl, nr, max({nl, nr, l.ans, r.ans, l.r+r.l}), len }; 
  }
  static S e() { return { 0, 0, 0, 0 }; }
  static void reverse_prod(S& x) { swap(x.l, x.r); } // 反転時に prod を更新する
  struct F { ll x; };
  static S mapping(F f, S x) { return x; }
  static F composition(F f, F x) { return x; }
  static F id() { return {0}; }
  struct Node{
    Node *l = 0, *r = 0, *p = 0;
    S a = e(); // 頂点が持つ値
    S prod = e(); // 集約（ rev==1 のときでも reverse_prod 作用済み）
    F f = id(); // 遅延（a,prod には作用済み）
    int i = -1; // 配列の index
    int z = 0; // 頂点の重み ( NIL なら 0 、普通の頂点は 1 ）
    int sumz = 0; // 部分木の重み
    int rev = 0; // 反転の遅延
  };
  using pNode = unique_ptr<Node>;
  pNode pNIL;
  Node *NIL = nullptr;
  vector<pNode> A;
  Node *R;
  SplayTreeByIdx() {
    if(!pNIL){
      pNIL = make_unique<Node>();
      NIL = pNIL.get();
      NIL->l = NIL->r = NIL->p = NIL;
      R = NIL;
    }
  }
  // 伝播
  void prepareDown(Node* c){
    if(c->l != NIL) {
      // a,prod への作用を忘れずに
      c->l->a = mapping(c->f, c->l->a);
      c->l->prod = mapping(c->f, c->l->prod);
      c->l->f = composition(c->f, c->l->f);
    }
    if(c->r != NIL) {
      // a,prod への作用を忘れずに
      c->r->a = mapping(c->f, c->r->a);
      c->r->prod = mapping(c->f, c->r->prod);
      c->r->f = composition(c->f, c->r->f);
    }
    if(c->rev) {
      swap(c->l, c->r);
      if(c->l != NIL) {
        c->l->rev ^= 1; // 伝播
        reverse_prod(c->l->prod);
      }
      if(c->r != NIL) {
        c->r->rev ^= 1; // 伝播
        reverse_prod(c->r->prod);
      }
      c->rev = 0;
    }
    c->f = id(); // 伝播済み
  }
  // 集約
  void prepareUp(Node* c) {
    c->sumz = c->l->sumz + c->r->sumz + 1; // 部分木の重み
    c->prod = op(op(c->l->prod,c->a),c->r->prod); // 集約　c は伝播済み
  }
  // （便利）
  // p の親が、子として p を参照するので、それを書き換えられるようにする
  // 根の場合に拡張して R の参照を返す。
  Node*& parentchild(Node* p) {
    if(p->p == NIL) return R;
    if(p->p->l == p) return p->p->l;
    else return p->p->r;
  }
  // 左回転
  void rotL(Node* c) {
    Node* p = c->p;
    parentchild(p) = c;
    c->p = p->p;
    p->p = c;
    if(c->l != NIL) c->l->p = p; // 子が NIL かもしれない
    p->r = c->l;
    c->l = p;
  }
  // 右回転
  void rotR(Node* c) {
    Node* p = c->p;
    parentchild(p) = c;
    c->p = p->p;
    p->p = c;
    if(c->r != NIL) c->r->p = p; // 子が NIL かもしれない
    p->l = c->r;
    c->r = p;
  }
  // splay 後、 c は伝播済み
  void splay(Node* c) {
    prepareDown(c); // ループが回らない時のために
    while(c->p != NIL) {
      Node* p = c->p;
      Node* pp = p->p;
      // 伝播は親から
      if (pp != NIL) prepareDown(pp);
      if (p != NIL) prepareDown(p);
      prepareDown(c);
      if (p->l == c) {
        if(pp == NIL) { rotR(c); }
        else if(pp->l == p) { rotR(p); rotR(c); }
        else if(pp->r == p) { rotR(c); rotL(c); }
      }
      else {
        if(pp == NIL) { rotL(c); }
        else if(pp->r == p) { rotL(p); rotL(c); }
        else if(pp->l == p) { rotL(c); rotR(c); }
      }
      // 集約は子から
      if(pp != NIL) prepareUp(pp);
      if(p != NIL) prepareUp(p);
      prepareUp(c);
    }
    prepareUp(c); // ループが回らない時のために
  }
  Node* kth_element(int k) {
    Node* c = R;
    while(true) {
      prepareDown(c);
      if(c->l->sumz == k) break;
      if(c->l->sumz > k){ c = c->l; continue; }
      k -= c->l->sumz + 1;
      c = c->r;
    }
    prepareDown(c);
    splay(c);
    return c;
  }
  void insert_at(int k, S x) {
    pNode pnx = make_unique<Node>(*NIL);
    Node* nx = pnx.get();
    nx->z = nx->sumz = 1;
    nx->i = A.size();
    nx->a = nx->prod = x;
    A.emplace_back(move(pnx));
    if(k == 0) {  // 左端
      nx->r = R;
      if(R != NIL) R->p = nx; // 元々 0 頂点かもしれない
      R = nx;
      prepareUp(nx); // 挿入したら集約
      return;
    }
    if(k == R->sumz) { // 右端（左端と同様）
      nx->l = R;
      if(R != NIL) R->p = nx;
      R = nx;
      prepareUp(nx);
      return;
    }
    auto p = kth_element(k);
    nx->l = p->l;
    nx->r = p;
    R = nx;
    p->l->p = nx;
    p->p = nx;
    p->l = NIL;
    prepareUp(p);  // split/merge の影響
    prepareUp(nx); //
  }
  void erase_at(int k) {
    auto p = kth_element(k);
    if(k == 0) { // 左端
      R = p->r;
      if(R != NIL) R->p = NIL; // 0 頂点になるかもしれない
    }
    else if(k == R->sumz-1) { // 右端
      R = p->l;
      if(R != NIL) R->p = NIL;
    }
    else {
      auto l = p->l;
      auto r = p->r;
      r->p = NIL;   // split
      R = r;        //
      kth_element(0);
      r = R;        // merge
      r->l = l;     //
      l->p = r;     //
      prepareUp(r); // split/merge の影響
    }
    swap(p->i,A.back()->i); // index が更新されるよ
    swap(A[p->i],A[A.back()->i]); // 後ろに移動して
    A.pop_back(); // 削除
  }
  Node* between(int l, int r) {
    if(l == 0 && r == R->sumz) return R; // 全域
    if(l == 0) return kth_element(r)->l; // 左端
    if(r == R->sumz) return kth_element(l-1)->r; // 右端
    auto rp = kth_element(r);
    auto lp = rp->l;
    R = lp;        // split
    lp->p = NIL;   //
    lp = kth_element(l-1);
    R = rp;        // merge
    rp->l = lp;    //
    lp->p = rp;    //
    prepareUp(rp); // split/merge の影響
    return lp->r;
  }
  void reverse(int l, int r) {
    auto c = between(l,r);
    c->rev ^= 1;
    reverse_prod(c->prod);
    splay(c);
  }
  void apply(int l, int r, F f) {
    auto c = between(l,r);
    c->a = mapping(f,c->a);
    c->prod = mapping(f,c->prod);
    c->f = composition(f,c->f);
    splay(c);
  }
  S prod(int l, int r) {
    return between(l,r)->prod;
  }
}; // end of struct SplayTreeByIdx
SplayTreeByIdx splay; // insert_at := i-thへデータ投入(splay node)