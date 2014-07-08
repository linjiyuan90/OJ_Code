
Store worthy codes & problems from the book: *<Elements of Programming Interviews>*

# ch15
## 15.7 Longest subarray which sum is <= k
* prefix_sum
* maintain a increasing prefix_sum, that's `prefix_sum[i] = max(prefix_sum[i], prefix_sum[i-1])`
* then at i, binary search first j which `prefix_sum[j] >= prefix_sum[i] - k`

  
