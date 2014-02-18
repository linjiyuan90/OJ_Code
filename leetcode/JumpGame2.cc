class Solution {
public:
  int jump(int A[], int n) {
    // like bfs
    int s[2], e[2];
    int now = 0, pre = 1;
    s[pre] = e[pre] = 0;
    for (int d = 0; ; ++d) {
      if (e[pre] >= n-1) {
	return d;
      }
      e[now] = e[pre];
      for (int i = s[pre]; i <= e[pre]; ++i) {
	e[now] = std::max(e[now], i + A[i]);
      }
      s[now] = e[pre] + 1;
      std::swap(now, pre);
    }
  }
};
