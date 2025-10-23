// 가장 먼 두 점, O(n)
int i2 = 1, p1, p2;
ll maxdist = 0;
for (int i1 = 0; i1 < cp.size();) {
  auto dist = (cp[i2]-cp[i1]).normll();
  if (maxdist <= dist) {
    maxdist = dist;
    p1 = i1;
    p2 = i2;
  }

  auto ccwv = ccw(cp[i1], cp[(i1+1)%cp.size()], cp[i2], cp[(i2+1)%cp.size()]);
  if (ccwv > 0) i2 = (i2+1)%cp.size();
  else i1++;
}