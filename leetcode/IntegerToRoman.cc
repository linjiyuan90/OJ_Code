class Solution {
public:
  std::string intToRoman(int num) {
    std::string ans = "";
    int i = 0;
    while (num > 0) {
      int c = num % 10;
      if (c < 4) {
	ans = std::string(c, NUM[i]) + ans;
      } else if (c < 6) {
	ans = std::string(5 - c, NUM[i]) + std::string(1, NUM[i+1]) + ans;
      } else if (c < 9) {
	ans = std::string(1, NUM[i+1]) + std::string(c - 5, NUM[i]) + ans;
      } else {
	ans = std::string(10 - c, NUM[i]) + std::string(1, NUM[i+2]) + ans; 
      }
      num /= 10;
      i += 2;
    }
    return ans;
  }
  
private:
  const char* NUM = "IVXLCDM";
  // 1, 5, 10, 50, 100, 500, 1000
};
