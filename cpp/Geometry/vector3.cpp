// fix vector2 -> 3, this template only v3
vector3 cross(const vector3 &rhs) const {
  return vector3(y*rhs.z-z*rhs.y, z*rhs.x-x*rhs.z, x*rhs.y-y*rhs.x);
}
double norm() const {
  return sqrt(x*x + y*y + z*z);
}
