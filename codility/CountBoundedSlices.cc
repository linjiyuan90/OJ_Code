#include "iostream"
#include "algorithm"
#include "deque"
#include "vector"

// ***
// Calculate the number of slices in which (maximum - minimum <= K).

int solution(int K, std::vector<int> &A) {
  int ans = 0;
  std::deque<std::pair<int, int>> descend, ascend;
  for (size_t ix = 0, n = A.size(); ix < n; ++ix) {
    if (ix == 0) {
      descend.push_back(std::make_pair(0, 0));
      ascend.push_back(std::make_pair(0, 0));
    } else {
      int prev = ix;
      while (!descend.empty() && A[descend.back().first] <= A[ix]) {
	prev = descend.back().second; 
	descend.pop_back();
      }
      descend.push_back(std::make_pair(ix, prev));
      
      prev = ix;
      while (!ascend.empty() && A[ascend.back().first] >= A[ix]) {
	prev = ascend.back().second;
	ascend.pop_back();
      }
      ascend.push_back(std::make_pair(ix, prev));
    }
    
    while (A[descend.front().first] - A[ascend.front().first] > K) {
      if (descend.front().first < ascend.front().first) {
	// need to update second
	ascend.front().second = std::max(ascend.front().second, descend.front().first + 1);
	descend.pop_front();
      } else {
	descend.front().second = std::max(descend.front().second, ascend.front().first + 1);
	ascend.pop_front();
      }
    }
    
    ans += (ix - std::min(descend.front().second, ascend.front().second) + 1);
    ans = std::min(ans, 1000000000);
  }
  return ans;
}

// the trick is 
// for ascending deque
// record min{j}, where A[k] >= A[i], j <= k <= i

int main() {
  std::vector<int> A = {3, 5, 7, 6, 3};
  std::cout << solution(0, A) << std::endl << std::endl;
  std::cout << solution(1, A) << std::endl << std::endl;
  std::cout << solution(2, A) << std::endl << std::endl;
  std::cout << solution(3, A) << std::endl << std::endl;
  std::cout << solution(4, A) << std::endl << std::endl;
  return 0;
}
