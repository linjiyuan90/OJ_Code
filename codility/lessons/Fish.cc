int solution(vector<int> &A, vector<int> &B) {
  std::stack<int> upstream, downstream;
  for (std::size_t i = 0, n = A.size(); i < n; ++i) {
    if (B[i] == 0) { // upstream
      while (!downstream.empty() && downstream.top() < A[i]) {
	downstream.pop();
      }
      if (downstream.empty()) {
	upstream.push(A[i]);
      }
    } else {
      downstream.push(A[i]);
    }
  }
  return upstream.size() + downstream.size();
}
