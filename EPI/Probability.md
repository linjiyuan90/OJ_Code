# Random Number Generator
## 20.1 Generate k-subset with equal probability
* if the number of all elements n is known, the algorithm becomes: 
```c++
template<typename T>
std::vector<int> offline_sampling(std::vector<T> A, const int &k) {
  for (int i = 0; i < k; ++i) {
    // std::default_random_engine gen((std::random_device())());
    auto gen =  std::default_random_engine(std::random_device()());
    std::uniform_int_distribution<int> dis(i, A.size() - 1);
    std::swap(A[i], A[dis(gen)]);
  }
  A.resize(k);
  return A;
}
```
* if it's a stream or packets, n is unknown, need to traverse all the elements
```c++
template <typename T>
std::vector<T> reservoir_sampling(std::istringstream &sin, const int k) {
  T x;
  std::vector<T> R;
  for (int i = 0; i < k && sin >> x; ++i) {
    R.emplace_back(x);
  }
  int n = k;
  while (sin >> x) {
    std::default_random_engine gen((std::random_device())());
    // generate random int in [0, n+1)
    std::uniform_int_distribution<int> dis(0, ++n);
    int tar = dis(gen);
    if (tar < k) {
      R[tar] = x;
    }
  }
  return R;
}
```

## 20.4 Uniform integer distribution using zero_one_random
let `n = b - a + 1`, k is the least integer such that`n<=2^k`.
Each trail, call `std::zero_one_random()` k times, if the number m is in `[0, n)` output a + m, else do it again.
The expected trials is less than: `1(1/2)+2(1/2)^2+3(1/2)^3... = 2`
```c++
int uniform_random_a_b(const int &a, const int &b) {
  auto gen = std::default_random_engine(std::random_device()());
  // std::bernoulli_distribution(0.5);
  std::uniform_int_distribution<int> zero_one_random(0, 1);
  int n = b - a + 1, res;
  do {
    res = 0;
    for (int k = 0; (1<<k) < n; ++k) {
      res = (res << 1) | zero_one_random(gen);
    }
  } while (res >= n);
  return a + res;
}
```
