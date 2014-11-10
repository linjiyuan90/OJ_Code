// Tree serialization/deserialization
//      1      
//     / \      
//    2   5    
//   / \       
//  3   4      
//             
// is written as 1(2(3 4) 5).
// Note situation when multiple ')', like '1(2(3(4)))'

#include "iostream"
#include "vector"
#include "string"
#include "algorithm"
#include "stack"

struct TreeNode {
  int val;
  std::vector<TreeNode*> children;

  TreeNode(int val = 0): val(val) {
  }
};

std::string serialize(TreeNode* root) {
  if (root == nullptr) {
    return "";
  }
  std::string str = std::to_string(root->val);
  bool blank = false;
  for (TreeNode* ch : root->children) {
    if (blank) {
      str += " ";
    } else {
      str += "(";
    }
    blank = true;
    str += serialize(ch);
  }
  if (!root->children.empty()) {
    str += ")";
  }
  return str;
}

TreeNode* deserialize(const std::string& str) {
  static const std::string Digits = "0123456789";
  if (str.empty()) {
    return nullptr;
  }
  std::stack<TreeNode*> nodes;
  nodes.push(new TreeNode());  // dummy node
  for (std::size_t p = 0, q; p < str.size(); ) {
    if (str[p] == ')') {
      nodes.pop();
      ++p;
      continue;
    }
    if (str[p] == ' ') {
      ++p;
      continue;
    }
    if (str[p] == '(') {
      nodes.push(nodes.top()->children.back());
      ++p;
      continue;
    }
    q = str.find_first_not_of(Digits, p);
    if (q == std::string::npos) {
      q = str.size();
    }
    TreeNode* node = new TreeNode(std::stoi(str.substr(p, q-p)));
    nodes.top()->children.push_back(node);
    p = q;
  }
  return nodes.top()->children.front();
}

int main() {
  std::cout << serialize(deserialize("12(23(34 45) 56)")) << std::endl;
  std::cout << serialize(deserialize("")) << std::endl;
  std::cout << serialize(deserialize("12")) << std::endl;
  std::cout << serialize(deserialize("23(34 45 56 78)")) << std::endl;
  std::cout << serialize(deserialize("12(23(34) 56(78) 910(1011 1112 1213 1314(1415)))")) << std::endl;
  std::cout << serialize(deserialize("1(2(3(4)))")) << std::endl;
  return 0;
}
