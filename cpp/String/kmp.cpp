vector<int> get_pi(string p) {
  vector<int> pi(p.length(), 0);

  for (int i = 1, j = 0; i < p.length(); i++) {
    while (j && p[i] != p[j]) j = pi[j-1];
    if (p[i] == p[j]) pi[i] = ++j;
  }
  return pi;
}
int kmp(string s, string p) {
  auto pi = get_pi(p);
  int lj = 0;

  for (int i = 0, j = 0; i < s.length(); i++) {
    lj = j;
    while (j && s[i] != p[j]) j = pi[j-1];
    if (s[i] == p[j]) {
      if (j == p.length() - 1) {
        // result.push_back(i-p.length()+1); if want result string
        j = pi[j];
      } else j++;
    }
  }
  return lj;
}