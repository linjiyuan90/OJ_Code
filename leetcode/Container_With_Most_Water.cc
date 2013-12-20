#include "iostream"
#include "vector"
#include "algorithm"
#include "deque"

// The core operation in this problem is to query
// leftmost/rightmost line which height >= x
// A data structure like binary indexed tree or segmented tree
// will tackle these queries.
// However, this takes O(nlogn)

// A simpler way is to maintain an increasing sequence
// and use binary search to find the first one >= x
// O(nlogn)

// Is there a O(n) algorithm?
class Solution {
public:
  int maxArea(std::vector<int> &height) {
    int ans = one_side_max_area(height);
    std::reverse(height.begin(), height.end());
    return std::max(ans, one_side_max_area(height));
  }
  
private:
  int one_side_max_area(std::vector<int> &height) {
    auto cmp = [&height](const int &a, const int &b) {
      return height[a] < height[b];
    };
    int ans = 0;
    std::vector<int> desc_ix;
    for (int ix = 0; ix < height.size(); ++ix) {
      auto it = std::lower_bound(desc_ix.begin(), desc_ix.end(), ix, cmp);
      if (it != desc_ix.end()) {
	int h = std::min(height[*it], height[ix]);
	int len = ix - *it;
	ans = std::max(ans, h * len); 
      }
      if (desc_ix.empty() || height[desc_ix.back()] < height[ix]) {
	desc_ix.push_back(ix);
      }
    }
    return ans;
  }
};
