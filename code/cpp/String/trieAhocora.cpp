// include Trie
struct Trie {
  map<char, Trie*> ch;
  Trie* fail;
  bool end;
  Trie() { end = false; }
  ~Trie() {
    for (auto trie: ch) delete trie.second;
    ch.clear();
  }
  void insert(string s, int i = 0) {
    if (i == s.length()) {
      this->end = true;
      return;
    }
    if (!ch[s[i]]) ch[s[i]] = new Trie();
    ch[s[i]]->insert(s, i+1);
  }
};
Trie trie;
void set_fail() {
  queue<Trie*> q;
  trie.fail = &trie;
  q.push(&trie);
  while (q.size()) {
    Trie* cur = q.front();
    q.pop();
    for (auto [c, nxt]: cur->ch) {
      if (cur == &trie) nxt->fail = &trie;
      else {
        auto dest = cur->fail;
        while (dest != &trie && dest->ch.find(c) == dest->ch.cend()) dest = dest->fail;
        if (dest->ch.find(c) != dest->ch.cend()) dest = dest->ch[c];
        nxt->fail = dest;
      }
      if (nxt->fail->end) nxt->end = true;
      q.push(nxt);
    }
  }
}
int main() {
  // put all string to trie
  set_fail();
  cin >> n;
  while (n--) {
    cin >> s;
    bool result = false;
    Trie* cur = &trie;
    for (auto c: s) {
      while (cur != &trie && cur->ch.find(c) == cur->ch.cend()) cur = cur->fail;
      if (cur->ch.find(c) != cur->ch.cend()) cur = cur->ch[c];
      if (cur->end) result = true;
    }
    cout << (result ? "YES" : "NO") << (n ? "\n" : "");
  }
}