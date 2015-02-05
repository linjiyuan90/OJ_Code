class Solution {
public:
  vector<int> findSubstring(string S, vector<string>& L) {
    // for each start index i \in [0..l)
    // then check i, i+L, i+2L... whether it's ok
    std::vector<int> ans;
    if (!L.empty()) {
      int n = S.size();
      int m = L.front().size();
      int k = L.size();
      std::unordered_map<std::string, int> dict;
      for (auto& w : L) {
        ++dict[w];
      }
      for (int s = 0; s < m; ++s) {
        // need an map to record how many words have meet
        std::unordered_map<std::string, int> have;
        int numHave = 0;
        for (int i = s; i + m <= n; i += m) {
          if (i-m*k >= s) {
            const std::string w = S.substr(i-m*k, m);
            if (dict.count(w)) {
              if (have[w] == dict[w] + 1) {
                ++ numHave;
              }
              if (have[w] == dict[w]) {
                -- numHave;
              }
              --have[w];
            }
          }
          const std::string w = S.substr(i, m);
          if (dict.count(w)) {
            if (have[w] == dict[w] - 1) {
              ++ numHave;
            }
            if (have[w] == dict[w]) {
              -- numHave;
            }
            ++have[w];
          }
          if (numHave == dict.size()) {
            ans.push_back(i-m*(k-1));
          }
        }
      }
    }
    return ans;
  }
};
