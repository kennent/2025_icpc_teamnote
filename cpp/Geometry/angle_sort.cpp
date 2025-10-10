sort(a, a+n, [&](const vector2 &a, const vector2 &b){
  if((tie(a.x, a.y) > tie(0, 0)) ^ (tie(b.x, b.y) > tie(0, 0))) return tie(a.x, a.y) > tie(b.x, b.y);
  if(ccw(a, b) != 0) return ccw(a, b) > 0; // ccw 잘 수정하셈
  return hypot(a) < hypot(b);	
});