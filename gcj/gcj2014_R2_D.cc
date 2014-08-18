/*
  Distribute the set of strings to N servers. Each server will build a trie for the subset of strings.
  Find max number of trie nodes in all possible distributed situations.
*/

#include "set"
#include "string"
#include "vector"
#include "iostream"
#include "numeric"

int calcNumOfNodes(const std::vector<std::string>& server) {
  std::set<std::string> prefix;
  for (auto& str : server) {
    std::string now;
    prefix.insert(now);
    for (auto& ch : str) {
      now += ch;
      prefix.insert(now);
    }
  }
  return prefix.size();
}

void distribute(int i,
                const std::vector<std::string>& strs,
                std::vector<std::vector<std::string>>& servers,
                int& max,
                int& ways) {
  if (i == strs.size()) {
    int num = 0;
    for (auto& server : servers) {
      num += calcNumOfNodes(server);
    }
    if (num > max) {
      max = num;
      ways = 1;
    } else if (num == max) {
      ++ ways;
    }
    return;
  }
  for (auto& server : servers) {
    server.push_back(strs[i]);
    distribute(i+1, strs, servers, max, ways);
    server.pop_back();
  }
}

std::pair<int, int> distribute(const std::vector<std::string>& strs, int n) {
  int max = std::numeric_limits<int>::min();
  int ways = 0;
  std::vector<std::vector<std::string>> servers(n);
  distribute(0, strs, servers, max, ways);
  return {max, ways};
}

int main() {
  int T, n, m, t = 1;
  for (std::cin >> T; T--; ++t) {
    std::cout << "Case #" << t << ": ";
    std::cin >> m >> n;
    std::vector<std::string> strs(m);
    for (auto& s : strs) {
      std::cin >> s;
    }
    auto ans = distribute(strs, n);
    std::cout << ans.first << " " << ans.second << std::endl;
  }
}
