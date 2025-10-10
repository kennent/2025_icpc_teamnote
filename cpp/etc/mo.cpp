// O(nsqrt(n))
struct Query {
  ll l, r;
  int i;
};
ll n, m, cnt[100001], cntn[100001], ans[100001], sqrtn, a[100001];
Query query[100000];
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  cin >> m;
  for (int i = 0; i < m; i++) {
    cin >> query[i].l >> query[i].r;
    query[i].i = i;
  }
  sqrtn = sqrt(n);
  sort(query, query+m, [](Query q1, Query q2){
    if (q1.l/sqrtn == q2.l/sqrtn) return q1.r < q2.r;
    else return q1.l/sqrtn < q2.l/sqrtn;
  });

  cntn[0] = n;

  ll mcnt = 0, s = query[0].l, e = query[0].r;
  for (int i = s; i <= e; i++) {
    cntn[cnt[a[i]]]--;
    cnt[a[i]]++;
    cntn[cnt[a[i]]]++;
    mcnt = max(mcnt, cnt[a[i]]);
  }
  ans[query[0].i] = mcnt;

  int temp;
  for (int i = 1; i < m; i++) {
    while (s < query[i].l) { 
      cntn[cnt[a[s]]]--;
      cnt[a[s]]--;
      cntn[cnt[a[s]]]++;
      s++;
      while (cntn[mcnt] == 0) mcnt--;
    }
    while (query[i].l < s) {
      s--;
      cntn[cnt[a[s]]]--;
      if (cnt[a[s]] == mcnt) mcnt++;
      cnt[a[s]]++;
      cntn[cnt[a[s]]]++;
    }
    while (e < query[i].r) {
      e++;
      cntn[cnt[a[e]]]--;
      if (cnt[a[e]] == mcnt) mcnt++;
      cnt[a[e]]++;
      cntn[cnt[a[e]]]++;
    }
    while (query[i].r < e) {
      cntn[cnt[a[e]]]--;
      cnt[a[e]]--;
      cntn[cnt[a[e]]]++;
      e--;
      while (cntn[mcnt] == 0) mcnt--;
    }
    ans[query[i].i] = mcnt;
  }
}