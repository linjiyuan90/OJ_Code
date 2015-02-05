/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
  UndirectedGraphNode* dfsClone(
				UndirectedGraphNode* node,
				std::unordered_map<UndirectedGraphNode*, UndirectedGraphNode*>& clone
				) {
    if (!clone.count(node)) {
      UndirectedGraphNode* newNode = new UndirectedGraphNode(node->label);
      clone[node] = newNode;
      for (auto& v : node->neighbors) {
	newNode->neighbors.push_back(dfsClone(v, clone));
      }
    }
    return clone[node];
  }
public:
  UndirectedGraphNode* cloneGraph(UndirectedGraphNode* node) {
    if (node == NULL) {
      return NULL;
    }
    std::unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> clone;
    return dfsClone(node, clone);
  }
};
