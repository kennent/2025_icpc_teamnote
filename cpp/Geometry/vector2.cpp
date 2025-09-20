double pi = acos(-1);
template<class T>
struct vector2 {
  T x, y; // double or ll, dot, cross, fix req
  explicit vector2(T _x = 0, T _y = 0): x(_x), y(_y)
  {}
  vector2 operator + (const vector2 &rhs) const {
		return vector2(x + rhs.x, y + rhs.y);
	}
  vector2 operator - (const vector2 &rhs) const {
    return vector2(x - rhs.x, y - rhs.y);
  }
  vector2 operator * (const double k) const {
    return vector2(k*x, k*y);
  }
  bool operator == (const vector2 &rhs) const {
    return x == rhs.x && y == rhs.y;
  }
  bool operator < (const vector2 &rhs) const {
    return x != rhs.x ? x < rhs.x : y < rhs.y;
  }
  T dot(const vector2 &rhs) const {
    return x*rhs.x + y*rhs.y;
  }
  T cross(const vector2 &rhs) const {
    return x * rhs.y - y * rhs.x;  
  }
  double norm() const {
    return hypot(x, y); 
  }
  T norm2() const {
    return x*x+y*y;
  }
  vector2 basis() const {
    double d = norm(); // req T=double
    return vector2(x/d, y/d);
  }
  vector2 reverse() const {
    return vector2(-1*x, -1*y);
  }
};
int doubleCompare(double x, double y, double eps = 1e-8) {
  if (fabs(x-y) <= eps) return 0; // 0 is true
  return (x-y > 0) ? 1 : -1;
}
ll ccw(vector2 v1, vector2 v2, vector2 v3) {
  if (doubleCompare((v2-v1).cross(v3-v2), 0) == 0) return 0;
  else return (v2-v1).cross(v3-v2); // 1(>0), -1(<0)
}
bool pointYCompare(const vector2 &a, const vector2 &b) {
  return a.x != b.x ? a.x < b.x : a.y < b.y;
}
bool pointThetaCompare(const vector2 &a, const vector2 &b) {
  if (ccw(vector2(), a, b) == 0) return a.norm() < b.norm();
  else return ccw(vector2(), a, b) > 0;
}
double safe_acos(double a) {
  if (a <= -1.0) return pi; // req acos(-1) = pi
  else if (a >= 1.0) return 0;
  else return acos(a);
}
// like cross
double f(vector2 p1, vector2 q1, vector2 p2, vector2 q2) {
  return ((p2-p1).cross(q2-p2) / (q1-p1).cross(q2-p2));
}
double k = f(p1, q1, p2, q2); // k배
double cx = p1.x + k*(p2.x-p1.x), cy = p1.y + k*(p2.y-p1.y); // p1->p1, p2->q2 교차점