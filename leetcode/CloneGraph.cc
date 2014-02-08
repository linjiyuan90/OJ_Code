class Solution {
public:
  UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
    if (node == NULL) {
      return NULL;
    }
    // traverse the graph, clone new node and push it back as neighbors
    dfs_clone(node);
    UndirectedGraphNode *new_node = node->neighbors.back();
    // traverse the graph again to remove the new nodes
    dfs_remove(node);
    return new_node;
  }

private:
  bool not_clone(UndirectedGraphNode *u) {
    return u->neighbors.empty() ||
      !(u->neighbors.back()->label == u->label && u->neighbors.back() != u);
  }
  void clone(UndirectedGraphNode *u) {
    UndirectedGraphNode *v = new UndirectedGraphNode(u->label);
    u->neighbors.push_back(v);
  }
  void dfs_clone(UndirectedGraphNode *u) {
    if (not_clone(u)) {
      clone(u);
    }
    auto v = u->neighbors.back(); // the new node
    for (auto e : u->neighbors) {
      if (e == v) {
	continue;
      }
      if (not_clone(e)) {
	clone(e);  // clone it first, since there may exists self-loop!
	dfs_clone(e);
      }
      v->neighbors.push_back(e->neighbors.back());
    }
  }
  void dfs_remove(UndirectedGraphNode *u) {
    u->neighbors.pop_back();
    for (auto e : u->neighbors) {
      if (!not_clone(e)) {
	dfs_remove(e);
      }
    }
  }
};

class Solution {
public:
  // Using unordered_map will lead to elegant code
  UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
    if (node == NULL) {
      return NULL;
    }
    std::unordered_map<UndirectedGraphNode *, UndirectedGraphNode *> hash_node;
    return dfs_clone(hash_node, node);
  }
  
  UndirectedGraphNode *
  dfs_clone(std::unordered_map<UndirectedGraphNode *, UndirectedGraphNode *>
	     &hash_node, 
	     UndirectedGraphNode *node) {
    if (hash_node.count(node)) {
      return hash_node[node];
    }
    auto new_node = new UndirectedGraphNode(node->label);
    hash_node[node] = new_node;
    for (auto e : node->neighbors) {
      new_node->neighbors.push_back(dfs_clone(hash_node, e));
    }
    return new_node;
  }
};
