struct Suffix_Automaton {
  struct Node {
    int len, link, last, cnt = 1;
    int minpos = 0, maxpos = 0;
    // bool isleaf = true;
    map<int, int> nxt;
    // int nxt[26];
    Node(int len = 0, int link = 0, int last = 0): len(len), link(link), last(last) {}
  };
  vector<Node> v;
  vector<pii> sv; // len / original i
  int total;
  // ll substr_cnt = 0;
  Suffix_Automaton() { total = 0; v.push_back(Node(0, -1)); }
  void add(int c, int last = 0) {
    // int c = _c - 'A';
    v.push_back(Node(v[total].len+1, 0, last));
    int p = total;
    v[p].minpos = v[p].maxpos = v[p].len-1;
    total = v.size()-1;
    // cout << "[debug]" << (char)c << ": " << v[p].len << "," << v[p].link << "," << v[p].minpos << "," << v[p].maxpos << "\n";
    while (p != -1 && v[p].nxt.find(c) == v[p].nxt.cend()) {
      v[p].nxt.insert({ c, total });
      // v[p].nxt[c] = total;
      // if (v[p].link != -1) substr_cnt += v[p].len-v[v[p].link].len;
      // else substr_cnt++;
      p = v[p].link;
    }
    if (p != -1) {
      int q = v[p].nxt[c];
      int upd = q;
      if (v[p].len+1 < v[q].len) {
        upd = v.size();
        Node clone = v[q];
        clone.len = v[p].len + 1;
        clone.cnt = 0;
        v.push_back(clone);
        v[q].link = upd;
        for (int j = p; j != -1 && v[j].nxt[c] == q; j = v[j].link) v[j].nxt[c] = upd;
      }
      v[total].link = upd;
    }
  }
  // len, i
  pii lcs(string s) {
    int cur = 0;
    Node x = v[0];
    int l = 0, rl = 0, ri = 0;

    for (int i = 0; i < s.length(); i++) {
      x = v[cur];
      // cout << i << ": " << x.len << ", " << x.link << "\n";
      // cout << i << "(" << s[i] << "): " << x.len << " " << x.link << " => ";
      int idx = s[i] - 'a';
      // for (auto e: x.nxt) cout << e << " "; cout << " => ";
      while (x.len && x.nxt[idx] == -1) { 
        // l -= (x.len-v[x.link].len);
        l = v[x.link].len;
        cur = x.link;
        x = v[x.link];
      }
      if (x.nxt[idx] != -1) cur = v[cur].nxt[idx], l++;
      if (l > rl) rl = l, ri = i;
      // cout << x.len << " " << x.link << "\n";
    }
    return { rl, ri };
  }
  void clear() {
    total = 0;
    v.clear();
    v.push_back(Node(0, -1, 0));
  }
  // vector<int> search(string t) {
  //   vector<int> pos;
  //   int cur = 0, l = 0;
  //   for (int i = 0; i < t.length(); i++) {
  //     while (v[cur].len && v[cur].nxt.find(t[i]) == v[cur].nxt.cend()) {
  //       cur = v[cur].link;
  //       l = v[cur].len;
  //     }
  //     if (v[cur].nxt.find(t[i]) != v[cur].nxt.cend()) cur = v[cur].nxt[t[i]], l++;
  //     if (t.length() == l) pos.push_back(i-l+2);
  //   }
  //   return pos;
  // }
  // bool search(string t) {
  //   int cur = 0, l = 0;
  //   for (int i = 0; i < t.length(); i++) {
  //     while (v[cur].len && v[cur].nxt.find(t[i]) == v[cur].nxt.cend()) {
  //       cur = v[cur].link;
  //       l = v[cur].len;
  //     }
  //     if (v[cur].nxt.find(t[i]) != v[cur].nxt.cend()) cur = v[cur].nxt[t[i]], l++;
  //     if (t.length() == l) pos.push_back(i-l+2);
  //   }
  //   return pos;
  // }
  void sort() {
    sv = vector<pii>(v.size());
    for (int i = 0; i < v.size(); i++) sv[i] = { v[i].len, i };
    auto comp = [](pii a, pii b) -> bool {
      return a.first > b.first;
    };
    std::sort(sv.begin(), sv.end(), comp);
  }
};
Suffix_Automaton sa;