/*
  Given led lights, some of the segments are broken and could not be lit.
  Given a decreasing states from these led lights, find out whether it's possible to get the next state.

  Enumerate the broken segments, then try to match start position.
  If there multiple possible next states, echo ERROR.
*/

#include "iostream"
#include "vector"
#include "string"
#include "bitset"
#include "algorithm"
#include "set"

typedef std::bitset<7> Segment;

std::vector<Segment> Segments = {
  Segment("1111110"),
  Segment("0110000"),
  Segment("1101101"),
  Segment("1111001"),
  Segment("0110011"),
  Segment("1011011"),
  Segment("1011111"),
  Segment("1110000"),
  Segment("1111111"),
  Segment("1111011")
};

// there may be serveral next states!
std::vector<int> next_states(const std::vector<Segment>& segments, const Segment& mask) {
  std::vector<int> nexts;
  int n = segments.size();
  for (int s = 0, i, j; s < 10; ++s) {
    for (i = 0, j = s; i < n; ++i, j = j == 0 ? 9 : j-1) {
      if ((Segments[j] & ~mask) != (segments[i] & ~mask)) {
        break;
      }
    }
    if (i == n) {
      nexts.push_back(j);
    }
  }
  return nexts;
}

int main() {
  int T, t = 1, n;
  for (std::cin >> T; T--; ++t) {
    std::cout << "Case #" << t << ": ";
    std::cin >> n;
    std::vector<Segment> segments(n);
    for (auto& seg : segments) {
      std::cin >> seg;
    }
    std::set<std::string> ways;
    for (int maskInt = 0, all = (1<<7)-1; maskInt <= all; ++maskInt) {
      Segment mask(maskInt);
      // check they're not lit!
      if (std::any_of(segments.begin(),
                      segments.end(), 
                      [&mask](const Segment& seg) {
                        return (seg&mask).any();
                      })) {
        continue;
      }
      auto nexts = next_states(segments, mask);
      for (auto& next : nexts) {
        auto ansSeg = Segments[next] & ~mask;
        ways.insert(ansSeg.to_string());
      }
    }
    if (ways.size() != 1) {
      std::cout << "ERROR!" << std::endl;
    } else {
      std::cout << *(ways.begin()) << std::endl;
    }
  }
}
