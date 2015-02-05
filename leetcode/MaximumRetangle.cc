class Solution {
  
  int maximalRectangle(const vector<int>& height) {
    if (height.empty()) {
      return 0;
    }
    int n = height.size();
    // {last, height[i]}
    stack<pair<int, int>> stk;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      int last = i;
      while (!stk.empty() && stk.top().second >= height[i]) {
        last = stk.top().first;
        ans = max(ans, (i - last) * stk.top().second);
        stk.pop();
      }
      stk.push({last, height[i]});
    }
    while (!stk.empty()) {
      int last = stk.top().first;
      ans = max(ans, (n - last) * stk.top().second);
      stk.pop();
    }
    return ans;
  }

  int maximalRectangle2(const vector<int>& height) {
    if (height.empty()) {
      return 0;
    }
    int n = height.size();
    // this looks like the KMP, so O(n)
    // but how to analyse it concretely ?
    int ans = 0;
    vector<int> left(n), right(n);
    for (int c = 0; c < n; ++c) {
      for (left[c] = c - 1; left[c] != -1 && height[left[c]] >= height[c]; ) {
        left[c] = left[left[c]];
      }
    }
    for (int c = n-1; c >= 0; --c) {
      for (right[c] = c + 1; right[c] != n && height[right[c]] >= height[c]; ) {
        right[c] = right[right[c]];
      }
    }
    for (int c = 0; c < n; ++c) {
      ans = max(ans, height[c] * (right[c] - left[c] - 1));
    }
    return ans;
  }

public:
  int maximalRectangle(vector<vector<char>> &matrix) {
    if (matrix.empty()) {
      return 0;
    }
    size_t n = matrix.size(), m = matrix.front().size();
    vector<int> colH(m);
    int ans = 0;
    for (int r = 0; r < n; ++r) {
      for (int c = 0; c < m; ++c) {
        colH[c] = matrix[r][c] == '1' ? colH[c] + 1 : 0;
      }
      ans = max(ans, maximalRectangle(colH));
      // ans = max(ans, maximalRectangle2(colH));
    }
    return ans;
  }
};
