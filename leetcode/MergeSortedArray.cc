class Solution {
public:
  void merge(int A[], int m, int B[], int n) {
    // at first, shift right A
    std::copy(A, A + m, A + n);
    // then merge
    int* a = A + n;
    int* b = B;
    int* aEnd = A + m + n;
    int* bEnd = B + n;
    int* c = A;
    while (a < aEnd || b < bEnd) {
      if (b == bEnd || a < aEnd && *a < *b) {
        *c++ = *a++;
      } else {
        *c++ = *b++;
      }
    }
  }
};
