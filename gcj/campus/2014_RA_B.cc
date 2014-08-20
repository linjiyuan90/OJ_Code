/*
         p/q
  p/(p+q), (p+q)/q
  
  id(p, q) =
  1) 2 * id(p, q-p), p < q
  1) 2 * id(p-q, q) + 1, p > q
  id(1, 1) = 1  

  f(n) = 
  1) (p+q)/q, n is odd
  2) p/(p+q), n is even
  let p/q = f(n/2)

  Interesting problem, no need to connect it to some mathematics concept, like combination.
  Think it as a heap, and then just recursion!
*/

#include "iostream"
#include "ostream"

struct Ration {
  unsigned long long p, q;
  Ration(unsigned long long p, unsigned long long q): p(p), q(q) {
  }
};

std::ostream& operator << (std::ostream& os, const Ration& r) {
  return os << r.p << " " << r.q;
}

unsigned long long get_id(const Ration& r) {
  if (r.p == 1 && r.q == 1) {
    return 1;
  }
  if (r.p < r.q) {
    return 2 * get_id(Ration(r.p, r.q - r.p));
  } else {
    return 2 * get_id(Ration(r.p - r.q, r.q)) + 1;
  }
}

Ration get_ration(unsigned long long n) {
  if (n == 1) {
    return Ration(1, 1);
  }
  Ration sub = get_ration(n/2);
  if (n % 2) {
    return Ration(sub.p + sub.q, sub.q);
  } else {
    return Ration(sub.p, sub.p + sub.q);
  }
}

int main() {
  int T, n, t = 1;
  unsigned long long p, q;
  for (std::cin >> T; T--; ++t) {
    std::cout << "Case #" << t << ": ";
    std::cin >> n >> p;
    if (n == 2) {
      std::cin >> q;
      std::cout << get_id(Ration(p, q)) << std::endl;
    } else {
      std::cout << get_ration(p) << std::endl;
    }
  }
  return 0;
}
