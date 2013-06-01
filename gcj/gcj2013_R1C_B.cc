/*
	GCJ 2013 Round 1C.B
	求最小的n使得，x = a1+a2+..+ax, y = b1+b2+..+by
	要求|ai|, |bi|是{1..n}内的，且不重复不缺少

	3步
	确定最小的n
		n*(n+1)/2 >= abs(x) + abs(y) and （n*(n+1)/2 - (x+y)) % 2 == 0
		因为假设负数字之和为neg_sum，则n*(n+1)/2 - 2*neg_sum = x + y啦
	确定正数、负数集合
		通过neg_sum凑，唯一的
	确定正哪些是y的和负数哪些是x的
		通过pos_sum - sum(some k, k \in [1..n]) = x
		即sum(some k, k \in [1..n]) = pos_sum - x
		这些k也可以凑出来
		如果k属于负数集合，说明要给x的，属于正数集合，说明要给y的
*/

#include "sstream"
#include "iostream"
#include "cstdio"
#include "cstring"
#include "cmath"
#include "algorithm"
#include "vector"
#include "map"
#include "set"
#include "queue"
#include "deque"
#include "list"
#include "string"
#include "cassert"

using namespace std;

typedef pair<int, int> pii;

const int MAXN = 10086;

int sign[MAXN], xory[MAXN];

int main()
{
	int T, t = 1;
	for (scanf("%d", &T); T--; ) {
		printf("Case #%d: ", t++);
		int x, y;
		scanf("%d%d", &x, &y);
		int n = 0;
		long long sum = 0;
		while (sum < abs(x) + abs(y) || (sum - (x+y)) % 2) {
			sum += ++n;
		}
		sum -= (x+y);
		sum /= 2;
		fill(sign, sign + n + 1, 1);
		fill(xory, xory + n + 1, 0);
		long long neg_sum = sum;
		long long pos_sum = (long long)n*(n+1)/2 - neg_sum;
		for (int k = n;	sum > 0; k--) {
			if (sum >= k) {
				sum -= k;
				sign[k] = -1;
			}
		}
		//pos_sum - sum(k) = x
		//pos_sum - x = sum(k)
		sum = pos_sum - x;
		for (int k = n; k >= 1; k--) {
			if (sum >= k) {
				sum -= k;
				//-1 for x
				//1 for y
				xory[k] = sign[k];
			} else {
				xory[k] = -sign[k];
			}
		}
	
		for (int k = 1; k <= n; k++) {
			if (xory[k] == -1) { //x
				putchar(sign[k] == 1 ? 'E' : 'W');
			} else {
				putchar(sign[k] == 1 ? 'N' : 'S');
			}
		}
		puts("");
	}
	return 0;
}
