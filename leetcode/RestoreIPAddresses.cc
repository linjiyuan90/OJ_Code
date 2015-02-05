class Solution {
public:
  vector<string> restoreIpAddresses(string s) {
    vector<string> ips;
    int n = s.size();
    for (int a = 1; a <= 3; ++a) {
      for (int b = 1; b <= 3; ++b) {
        for (int c = 1; c <= 3; ++c) {
          int d =  n - (a + b + c);
          if (d < 1 || d > 3) {
            continue;
          }
          vector<string> parts = {
            s.substr(0, a),
            s.substr(a, b),
            s.substr(a+b, c),
            s.substr(a+b+c)
          };
          if (all_of(parts.cbegin(), parts.cend(), [](const string& s) {
                int x = stoi(s);
                return 0 <= x && x <= 255 && to_string(x) == s;
              })) {
            ips.push_back(accumulate(parts.begin() + 1,
                                     parts.end(), 
                                     parts.front(),
                                     [](const string& a, const string& b) {
                                       return a + "." + b;
                                     }));
          }
        }
      }
    }
    return ips;
  }
};
