class Solution {
public:
  // O(n)
  std::vector<int> twoSum(std::vector<int> &numbers, int target) {
    int n = numbers.size();
    std::vector<int> sorted_ix(n);
    for (int i = 0; i < n; ++i) {
      sorted_ix[i] = i;
    }
    std::sort(sorted_ix.begin(), sorted_ix.end(),
	      [&numbers](const int &a, const int &b) {
		return numbers[a] < numbers[b];
	      });
    for (int i = 0, j = n - 1; i != j; ) {
      int sum = numbers[sorted_ix[i]] + numbers[sorted_ix[j]];
      if (sum == target) {
	int a = sorted_ix[i] + 1, b = sorted_ix[j] + 1;
	if (a > b) {
	  std::swap(a, b);
	}
	return std::vector<int> {a, b};
      } else if (sum > target) {
	-- j;
      } else {
	++ i;
      }
    }
  }
};
