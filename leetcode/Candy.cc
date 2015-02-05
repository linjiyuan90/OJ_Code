class Solution {
public:
  int candy(vector<int>& ratings) {
    int n = ratings.size();
    std::vector<int> candies(n, 1);
    // two scans
    for (int i = 1; i < n; ++i) {
      if (ratings[i] > ratings[i-1]) {
	candies[i] = std::max(candies[i], candies[i-1] + 1);
      }
    }
    for (int i = n-2; i >= 0; --i) {
      if (ratings[i] > ratings[i+1]) {
	candies[i] = std::max(candies[i], candies[i+1] + 1);
      }
    }
    return std::accumulate(candies.begin(), candies.end(), 0);
  }
};
