/*
  Generate k smallest numbers with form: a + b*sqrt(2)
*/

#include "iostream"
#include "unordered_set"
#include "queue"
#include "functional"
#include "vector"

class Num {
  static const double sqrt2;
  double val;

public:
  Num(int a, int b): a(a), b(b) {
    val = a + b * sqrt2;
  }

  std::string to_string() {
    return std::to_string(a) + "+" + std::to_string(b) + "√2";
  }
  
  bool operator < (const Num& that) const {
    return val < that.val;
  }

  bool operator > (const Num& that) const {
    return val > that.val;
  }

  bool operator == (const Num& that) const {
    return val == that.val;
  }

  struct NumHash {
    const std::size_t operator()(const Num& num) const {
      return std::hash<int>()(num.a) ^ std::hash<int>()(num.b);
    }
  };

  int a, b;
};

// static const data member must have initilization(definition) outside class except integral
const double Num::sqrt2 = ::sqrt(2.0);

std::vector<Num> generateKNumbers(int k) {
  std::vector<Num> ans;
  std::unordered_set<Num, Num::NumHash> hash;
  std::priority_queue<Num, std::vector<Num>, std::greater<Num>> pq;
  pq.push(Num(0, 0));
  hash.insert(Num(0, 0));
  while(ans.size() < k) {
    Num now = pq.top();
    ans.push_back(now);
    hash.erase(now);  // to save memory!
    pq.pop();
    Num next1 = Num(now.a + 1, now.b);
    Num next2 = Num(now.a, now.b + 1);
    if (hash.insert(next1).second) {  // insert and judge, nice!
      pq.push(next1);
    }
    if (hash.insert(next2).second) {
      pq.push(next2);
    }
  }
  return ans;
}

int main() {
  for (auto& num : generateKNumbers(10)) {
    std::cout << num.to_string() << std::endl;
  }
  return 0;
}
