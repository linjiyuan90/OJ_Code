// 24 Game
// Given number from 1 to n. At each time, erase two numbers a, b
// do a+b, a-b, or a*b, then put the result back.

// One construction is:
// n - (n-1) = 1
// 1 * 1 = 1
// ...
// 4*3*2*1 or 5*4+3-1+2

#include "iostream"
#include "string"

int main() {
  for (int n; std::cin >> n; ) {
    if (n < 4) {
      std::cout << "NO" << std::endl;
    } else {
      std::cout << "YES" << std::endl;
      while(n > 5) {
        std::cout << n << " - " << n-1 << " = 1" << std::endl;
        std::cout << "1 * 1 = 1" << std::endl;
        n -= 2;
      }
      if (n == 4) {
        std::cout << "4 * 3 = 12" << std::endl;
        std::cout << "12 * 2 = 24" << std::endl;
        std::cout << "24 * 1 = 24" << std::endl;
      } else { 
        std::cout << "5 * 4 = 20" << std::endl;
        std::cout << "3 - 1 = 2" << std::endl;
        std::cout << "20 + 2 = 22" << std::endl;
        std::cout << "22 + 2 = 24" << std::endl;
     }
    }
  }
  return 0;
}
