/*
  Count all slices that are palindrome.
  Need Manachor's O(n) algorithm
*/
int solution(const string &S) {
  int n = S.length(), m = 2*n+1;
  std::string str(m, '#');
  for (int i = 0; i < n; ++i) {
    str[2*i+1] = S[i];
  }
  std::vector<int> part(m);
  for (int i = 0, C = 0, R = 0; i < m; ++i) {
    int ii = C - (i - C);
    part[i] = R > i ? std::min(part[ii], R - i) : 0;
    while (i+part[i]+1 < m
	   && i-part[i]-1 >= 0
	   && str[i+part[i]+1] == str[i-part[i]-1]) {
      ++ part[i];
    }  
    if (i+part[i] > R) {
      R = i+part[i];
      C = i;
    }
  }
  int res = 0;
  for (int i = 0; i < m; ++i) {
    res += part[i]/2;
    if (res > 100000000) {
      res = -1;
      break;
    }
  }
  return res;
}
