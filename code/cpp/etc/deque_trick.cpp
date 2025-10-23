int n, l;
deque<pii> dq;
cin >> n >> l;
for (int i = 0; i < n; i++) {
  int x;
  cin >> x;
  while (dq.size() && dq.back().first >= x) dq.pop_back();
  dq.push_back({x, i});
  while (dq.size() && dq.front().second <= i-l) dq.pop_front();
  cout << dq.front().first << " ";
}