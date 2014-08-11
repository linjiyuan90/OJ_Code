// Rotate by 3 reverse requires bidirectional iterator
// here, cplusplus provide a nice rotate implementation with Forward Only Iterator
// http://www.cplusplus.com/reference/algorithm/rotate/?kw=rotate

#include "algorithm"
#include "numeric"
#include "forward_list"
#include "iostream"

template<class ForwardIterator>
void roteate(ForwardIterator first, 
	     ForwardIterator middle,
	     ForwardIterator last) {
  ForwardIterator next = middle;
  while(first != next) {
    std::swap(*first++, *next++);
    if (next == last) {
      next = middle;
    } else if (first == middle) {
      middle = next;
    }
  }
}


int main() {
  std::forward_list<int> list(10);
  std::iota(list.begin(), list.end(), 0);
  auto m = std::next(list.begin(), 3);
  // std::forward_list can't be reversed!
  /*
  std::reverse(list.begin(), m);
  std::reverse(m, list.end());
  std::reverse(list.begin(), list.end());
  */
  for (auto& e : list) {
    std::cout << e << " ";
  }
  std::cout << std::endl;
  std::iota(list.begin(), list.end(), 0);
  rotate(list.begin(), m, list.end());
  for (auto& e : list) {
    std::cout << e << " ";
  }
  std::cout << std::endl;  
  return 0;
}
