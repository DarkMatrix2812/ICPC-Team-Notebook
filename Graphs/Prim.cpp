/*
Description: Minimum spanning tree (Prim) of an undirected weighted graph in adjd (add every edge in both directions). Returns the total weight, or LLONG MAX if the graph is not connected; mst parent[v]= the vertex v was attached to. Use for “cheapest way to connect everything”, minimising the largest edge on paths (the MST also minimises the maximum edge). For a maximum spanning tree negate all weights.
Alternative (Kruskal): sort edges by weight and union sets the ends of every edge whose ends are in different sets.
How it works: grow one tree from vertex 1; the heap holds every edge leaving the tree and the cheapest one that reaches a new vertex is always taken.
Time: O(Elog V)
*/

vector<int> mst_parent;
int prim(int n) {  // vertices 1..n
  vector<bool> in_tree(n + 1, false);
  mst_parent.assign(n + 1, -1);
  // {edge weight, {vertex, attached to}}
  priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
  pq.push({0, {1, -1}});  // start from vertex 1
  int total = 0, taken = 0;
  while (!pq.empty()) {
    int w = pq.top().first;
    int v = pq.top().second.first;
    int from = pq.top().second.second;
    pq.pop();
    if (in_tree[v]) continue;
    in_tree[v] = true;  // cheapest edge leaving the tree
    mst_parent[v] = from;
    total += w;
    taken++;
    for (auto [u, weight_u] : adjd[v]) {
      if (!in_tree[u]) pq.push({weight_u, {u, v}});
    }
  }
  if (taken < n) return LLONG_MAX;  // not connected
  return total;
}
