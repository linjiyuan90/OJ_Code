#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;

const int NumUglyFactor = 3;
const int UglyFactors[NumUglyFactor] = {2, 3, 5};

// this is nice, think in a different way:
// "each number times each factor"
// =>
// "each factor times each number", record how many number each factor has multiplied
int nthUglyNumber(const int& n) {
  vector<int> number(n, 1);
  vector<int> pivot(NumUglyFactor);
  for (int i = 1; i < n; ++i) {
    vector<int> candidates(NumUglyFactor);
    for (int j = 0; j < NumUglyFactor; ++j) {
      candidates[j] = number[pivot[j]] * UglyFactors[j];
    }
    vector<int>::iterator it = min_element(candidates.begin(), candidates.end());
    number[i] = *it;
    for (size_t j = 0; j < NumUglyFactor; ++j) {
      if (candidates[j] == *it) {
        ++pivot[j];
      }
    }
  }
  return number.back();
}

// this solution may extend too large and overflow risk!!!
int nthUglyNumber2(const int& n) {
  vector<int> number(n + 1, 1);
  vector<int> pivot(NumUglyFactor);
  for (int i = 0, m = 1; i < n - 1; ++i) {
    for (int j = 0; j < NumUglyFactor; ++j) {
      int cand = number[i] * UglyFactors[j];
      if (cand < 0) {  // overflow
        continue;
      }
      vector<int>::iterator it = 
        lower_bound(number.begin(), number.begin() + m, cand);
      if (it == number.begin() + m || *it != cand) {
        copy_backward(it, number.begin() + m, number.begin() + m + 1);
        *it = cand;
        m = min(n, m+1);
      }
    }
  }
  return number[n-1];
}



int main() {
  for (int n; cin >> n, n; ) {
    cout << nthUglyNumber2(n) << endl;
  }
  return 0;
}
