class Solution {
public:
  int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
    // the key point is to find a start position that can gather as much oil as possible
    // in the first serveral stations
    // that's to find an interval with max{sum{gas[i] - cost[i]}}, i \in interval
    // that's same to find an min prefix sum{gas[i] - cost[i]}
    int n = gas.size();
    std::vector<int> left(n);
    for(int i = 0; i < n; ++i) {
      left[i] = gas[i] - cost[i];
    }
    std::partial_sum(left.begin(), left.end(), left.begin());
    int p = std::min_element(left.begin(), left.end()) - left.begin();
    return left.back() < 0 ? -1 : (p+1) % n;
  }
};
