template <int P>
class mod_int {
  using Z = mod_int;

private:
  static int mo(int x) { return x < 0 ? x + P : x; }

public:
  int x;
  int val() const { return x; }
  mod_int() : x(0) {}
  template <class T>
  mod_int(const T &x_) : x(x_ >= 0 && x_ < P ? static_cast<int>(x_) : mo(static_cast<int>(x_ % P))) {}
  bool operator==(const Z &rhs) const { return x == rhs.x; }
  bool operator!=(const Z &rhs) const { return x != rhs.x; }
  Z operator-() const { return Z(x ? P - x : 0); }
  Z pow(long long k) const {
    Z res = 1, t = *this;
    while (k) {
      if (k & 1) res *= t;
      if (k >>= 1) t *= t;
    }
    return res;
  }
  Z &operator++() {
    x < P - 1 ? ++x : x = 0;
    return *this;
  }
  Z &operator--() {
    x ? --x : x = P - 1;
    return *this;
  }
  Z operator++(int) {
    Z ret = x;
    x < P - 1 ? ++x : x = 0;
    return ret;
  }
  Z operator--(int) {
    Z ret = x;
    x ? --x : x = P - 1;
    return ret;
  }
  Z inv() const { return pow(P - 2); }
  Z &operator+=(const Z &rhs) {
    (x += rhs.x) >= P && (x -= P);
    return *this;
  }
  Z &operator-=(const Z &rhs) {
    (x -= rhs.x) < 0 && (x += P);
    return *this;
  }
  Z &operator*=(const Z &rhs) {
    x = 1ULL * x * rhs.x % P;
    return *this;
  }
  Z &operator/=(const Z &rhs) { return *this *= rhs.inv(); }
#define setO(T, o)                                 \
  friend T operator o(const Z &lhs, const Z &rhs) {\
    Z res = lhs;                                   \
    return res o## = rhs;                          \
  }
  setO(Z, +) setO(Z, -) setO(Z, *) setO(Z, /)
#undef setO
};
const int P = 998244353;
using Z = mod_int<P>;
