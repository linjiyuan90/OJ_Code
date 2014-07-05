/* 
   Calculate the values of counters after applying all alternating operations: 
   increase counter by 1; 
   set value of all counters to current maximum.

   Time: O(N+M)
*/
vector<int> solution(int N, vector<int> &A) {
  // write your code in C++11
  std::vector<int> res(N);
  int max = 0, _max = 0;
  for (auto& x : A) {
    --x;
    if (x < N) {
      res[x] = std::max(res[x], max) + 1;
      _max = std::max(_max, res[x]);
    } else {
      max = _max;
    }
  }
  for (auto& e : res) {
    e = std::max(e, max);
  }
  return res;
}
