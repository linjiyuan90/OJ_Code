class Solution {
public:
  // find all the local minimums, deliver each of them with one candy
  // then, for its increasing neighbor, increase one for each
  int candy(std::vector<int> &ratings) {
    std::vector<int> candy(ratings.size(), 0);
    for (int ix = 0; ix < ratings.size(); ++ix) {
      if ((ix == 0 || ratings[ix-1] >= ratings[ix]) && 
	  (ix == ratings.size() - 1 || ratings[ix + 1] >= ratings[ix])) {
	// local minimum
	candy[ix] = 1;
      }
    }
    
    for (int ix = 0; ix < ratings.size(); ++ix) {
      if (candy[ix] == 1) {
	for (int jx = ix - 1; jx >= 0 &&
	       ratings[jx] > ratings[jx + 1]; --jx) {
	  candy[jx] = std::max(candy[jx], candy[jx+1]+1);
	}
	for (int jx = ix + 1; jx < ratings.size() &&
	       ratings[jx] > ratings[jx - 1]; ++jx) {
	  candy[jx] = std::max(candy[jx], candy[jx-1]+1);
	}
      }
    }
    
    return std::accumulate(candy.begin(), candy.end(), 0);
  }
};


// TODO
// Using no extra space
