#include "iostream"
#include "string"
#include "vector"

using namespace std;

typedef vector<string> VS;
  
// split s by specifying delimiters
// empty parts will be remove
VS split(const string &str, const string &delimiters) {
  VS result;
  for (size_t st = 0, ed = 0; ed != string::npos; ) {
    ed = str.find_first_of(delimiters, st);
    if (st < str.length() && st != ed) {
      result.push_back(str.substr(st, ed - st));
    }
    st = ed + 1;
  }
  return result;
}

void print(const VS &result) {
  cout << "result: " << result.size() << " ";
  for (size_t i = 0; i < result.size(); i++) {
    cout << result[i] << " ";
  }
  cout << endl;
}

int main() {
  VS result = split("a//", "/");
  print(result);
  result = split("a///e", "/");
  print(result);
  result = split("/ea/", "/");
  print(result);
  result = split("/a/bc/d", "/");
  print(result);
  result = split("d", "/");
  print(result);
  return 0;
}
