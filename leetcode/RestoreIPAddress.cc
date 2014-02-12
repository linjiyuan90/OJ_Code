// Use 3-for may be more elegant than dfs
class Solution {
public:
  std::vector<std::string> restoreIpAddresses(std::string s) {
    std::vector<std::string> ans;
    // note!
    if (s.length() > 12) {
      return ans;
    }
    for (size_t ix0 = 0; ix0 < s.length(); ++ix0) {
      for (size_t ix1 = ix0 + 1; ix1 < s.length(); ++ix1) {
	for (size_t ix2 = ix1 + 1; ix2 < s.length(); ++ix2) {
	  std::string ip0 = s.substr(0, ix0 + 1);
	  std::string ip1 = s.substr(ix0 + 1, ix1 - ix0);
	  std::string ip2 = s.substr(ix1 + 1, ix2 - ix1);
	  std::string ip3 = s.substr(ix2 + 1);
	  if (isOk(ip0) && isOk(ip1) && isOk(ip2) && isOk(ip3)) {
	    ans.push_back(ip0 + "." + ip1 + "." + ip2 + "." + ip3);
	  }
	}
      }
    }
    return ans;
  }
private:
  bool isOk(std::string &ip) {
    if (ip.empty() || ip.length() > 3) {
      return false;
    }
    int num = 0;
    for (auto c : ip) {
      num = num * 10 + c - '0';
    }
    return num <= 255 && !(ip[0] == '0' && ip.size() > 1);
  }
};
