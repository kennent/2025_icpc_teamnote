ll n, s, e;
using Matrix = vector<vector<ll>>;
Matrix matrix;
Matrix operator* (const Matrix &op1, const Matrix &op2) {
  Matrix result(op1.size(), vector<ll>(op1[0].size()));
  for (int i = 0; i < 5*n; i++) {
    for (int j = 0; j < 5*n; j++) {
      for (int k = 0; k < 5*n; k++) {
        result[i][j] += op1[i][k] * op2[k][j];
        result[i][j] %= DIV;
      }
    }
  }
  return result;
}
Matrix matrix_pow(ll k) {
  if (k == 1) return matrix;
  else if (k % 2) return matrix_pow(k-1) * matrix;
  else {
    Matrix _matrix = matrix_pow(k/2);
    return _matrix * _matrix;
  }
}
int main() {
  Matrix result;
  ll k;
  scanf("%lld %lld %lld %lld", &n, &s, &e, &k);
  for (int i = 0; i < n; i++) {
    vector<ll> v;
    int x;
    for (int j = 0; j < n; j++) {
      scanf("%1d", &x);
      for (int d = 5; d > 0; d--) {
        if (d == x) v.push_back(1);
        else v.push_back(0);
      }
    }
    for (int d = 0; d < 4; d++) {
      vector<ll> temp;
      for (int ti = 1; ti <= 5*n; ti++) {
        if (5*i + d + 1 == ti - 1) temp.push_back(1); else temp.push_back(0);
      }
      matrix.push_back(temp);
    }
    matrix.push_back(v);
  }
  result = matrix_pow(k);
}