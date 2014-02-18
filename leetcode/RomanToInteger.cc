class Solution {
public:
  int romanToInt(std::string s) {
    int num = 0;
    for (int i = 0; i < s.length();) {
      if (i + 1 < s.length() && NUM[s[i]] < NUM[s[i+1]]) {
	num += NUM[s[i+1]] - NUM[s[i]];
	i += 2;
      } else {
	num += NUM[s[i++]];
      }
    }
    return num;
  }
  
private:
  std::map<char, int> NUM = {
    {'I', 1}, {'V', 5},
    {'X', 10}, {'L', 50},
    {'C', 100}, {'D', 500},
    {'M', 1000}
  };
};
