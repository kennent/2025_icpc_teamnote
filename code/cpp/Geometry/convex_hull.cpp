// cps: 컨헐집합, [0]이 제일 외곽, O(nlogn)
vector<vector2> p;
vector<vector<vector2>> cps;
int n, check[1050], ci = 1, cnt = 0;
double oa = 0, ia = 0;
int main () {
  cin >> n;
  p = vector<vector2>(n);
  for (int i = 0; i < n; i++) {
    check[i] = 0;
    cin >> p[i].x >> p[i].y;
    p[i].i = i;
  }
  while (p.size() >= 3) {
    sort(p.begin(), p.end(), pointYCompare);
    vector2 save = p.front();
    for (int i = 1; i < p.size(); i++) {
      p[i].x = p[i].x - p[0].x;
      p[i].y = p[i].y - p[0].y; 
    }
    sort(next(p.begin()), p.end(), pointThetaCompare);
    vector<vector2> np, cp;
    p[0] = vector2();
    p[0].i = save.i;
    cp.push_back(p[0]);
    cp.push_back(p[1]);
    for (int i = 2; i < p.size(); i++) {
      while (cp.size() > 1) {
        if (ccw(cp[cp.size()-2], cp[cp.size()-1], p[i]) <= 0) {
          np.push_back(cp.back());
          cp.pop_back();
        } else break;
      }
      cp.push_back(p[i]);
    }
    if (cp.size() < 3) break;
    for (auto &e: cp) check[e.i] = ci, e.x += save.x, e.y += save.y;
    for (auto &e: np) e.x += save.x, e.y += save.y;
    swap(p, np);
    cps.push_back(cp);
    ci++;
  }
}