class Solution {
public:
  int trap(int A[], int n) {
    // using a stack to maintain a decreasing height
    // also for each element in the stack, record area between it and 
    // its previous heigher one
    // note this problem is to sum all the area, note the max area
    std::stack<std::pair<int, int>> desc;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      std::pair<int, int> top = {i, 0};
      while (!desc.empty() && A[desc.top().first] <= A[top.first]){
        auto last = desc.top();
        desc.pop();
        if (!desc.empty()) {
          top.second += 
            (std::min(A[desc.top().first], A[top.first]) - A[last.first]) * (top.first - desc.top().first - 1);
        }
      } 
      desc.push(top);
      ans += top.second;
    }
    return ans;
  }
};
