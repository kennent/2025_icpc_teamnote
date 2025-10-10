// req vector2
struct line2 {
  vector2 p1, p2;

  void setLeftRight() {
    if (p2 < p1) {
      vector2 temp = p2;
      p2 = p1;
      p1 = temp;
    } 
  }
};
int line_intersection(vector2 s1, vector2 e1, vector2 s2, vector2 e2) {
  if (e1 < s1) swap(s1, e1);
  if (e2 < s2) swap(s2, e2);
  int c1s = iccw(s1, e1, s2), c1e = iccw(s1, e1, e2),
    c2s = iccw(s2, e2, s1), c2e = iccw(s2, e2, e1);

  if (c1s * c1e == -1 && c2s * c2e == -1) return 2; 
  else if (c1s == 0 && c1e == 0 && c2s == 0 && c2e == 0) {
    if (s1.x == e1.x) {
      // 세로 두 직선
      if (s1.y > s2.y) swap(s1, s2), swap(e1, e2);
      if (e1.y < s2.y) return 0;
      if (doubleCompare(e1.y, s2.y) == 0) return 1;
    } else {
      // 가로 두 직선
      if (s1.x > s2.x) swap(s1, s2), swap(e1, e2);
      if (e1.x < s2.x) return 0;
      if (doubleCompare(e1.x, s2.x) == 0) return 1;
    }
    return 3;
    if (s1.x > s2.x) swap(s1, s2), swap(e1, e2);
    if (e1.x < s2.x) return 0;
    if (s1.y > s2.y) swap(s1, s2), swap(e1, e2);
    if (e1.y < s2.y) return 0;
    if (e1.y == s2.y) return 1;
    if (s1.x > s2.x) swap(s1, s2), swap(e1, e2);
    if (e1.x == s2.x) return 1;
    return 3;
  } else if (c1s * c1e * c2s * c2e == 0) {
    if ((c1s * c1e == 0 && c2s * c2e == 1) 
      || (c1s * c1e == 1 && c2s * c2e == 0)
    ) return 0; else return 1;
  } else return 0;
}
double f(vector2 p1, vector2 q1, vector2 p2, vector2 q2) {
  return ((p2-p1).cross(q2-p2) / (q1-p1).cross(q2-p2));
}
// 교차점 계산
double w = f(v[i], v[j], v[k], v[nk]);
double cx = v[i].x + w*(v[j].x-v[i].x), cy = v[i].y + w*(v[j].y-v[i].y);
// 반사
vector2 p, np, fp;
p.input();
double k = (e-s).dot(p-s)/(e-s).get_size();
np = s + (e-s).basis()*k;
fp = p+(np-p)*2; // x1의 경우 사영
cout << fp.x << " " << fp.y << "\n";