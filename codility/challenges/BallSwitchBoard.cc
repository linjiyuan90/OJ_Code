/*
  Given a board of switchs, 
  1) case 0, ball pass through it
  2) case 1, ball will change direction to right
  3) case -1, ball will change direction to bottom
  Once a ball pass the switch, the switch flips.

  Given K balls from the left-top corner, how many will come out from the
  right-buttom corner.

  Very interesting problem!
  At first, I was stuck about thinking "cycle" ...
  http://blog.csdn.net/caopengcs/article/details/10041229
  Not neccessary, just simulate it!
  Record how many balls comes from the top to current switch, bottom[i][j], and
  balls come from left to current switch, right[i][j] (in fact, this is not needed).

  Time O(NM)
  Space O(M)
*/

int solution(const vector<vector<int>> &A, int K) {
  if (A.empty()) {
    return 0;
  }
  int n = A.size(), m = A.front().size();
  std::vector<int> buttom(m);
  buttom[0] = K;
  for (int i = 0; i < n; ++i) {
    for (int j = 0, right = 0; j < m; ++j) {
      if (A[i][j] == 0) {
	// do nothing
      } else if (A[i][j] == -1) {
	// half go down, the left go right
	int all = buttom[j] + right;
	right = all / 2;
	buttom[j] = all - right;
      } else {
	int all = buttom[j] + right;
	right = (all+1) / 2;
	buttom[j] = all - right;
      }
    }
  }
  return buttom[m-1];
}
