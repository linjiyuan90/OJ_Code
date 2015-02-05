class Solution {
public:
    int threeSumClosest(vector<int> &num, int target) {
        sort(num.begin(), num.end());
        int ans = num[0] + num[1] + num[2];
        for (int a = 0, n = num.size(); a < n; ++a) {
            for (int b = a + 1, c = n - 1; b < c; ) {
                if (abs(ans - target) > abs(num[a] + num[b] + num[c] - target)) {
                    ans = num[a] + num[b] + num[c];
                }
                if (num[a] + num[b] + num[c] >= target) {
                    -- c;
                } else {
                    ++ b;
                }
            }
        }
        return ans;
    }
};
