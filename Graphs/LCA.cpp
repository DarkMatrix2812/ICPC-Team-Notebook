/*
Description: Lowest common ancestor by binary lifting on a tree in adj.lca(u, v) = deepest vertex that is an ancestor of both; tree_dist = number of edges on the path. Use for distance / path queries between two vertices, checking if a vertex lies on a path, k-th ancestor (jump with up). Built with BFS, so deep trees are safe.
How it works: up[v][j] is the ancestor 2^j steps above v (the root’s ancestor is itself). To answer: lift the deeper vertex to the same depth, then lift both by the largest jumps that keep them different; their parent is the answer.
Modify / tips: k-th ancestor: jump by the 1-bits of k. Weighted distance: keep dist_root[v] and use it in place of depth in tree_dist. Max edge on a path: store mx[v][j] next to up[v][j] and combine it on every jump. Is x on the path u..v: tree_dist(u,x) + tree_dist(x,v) == tree_dist(u,v).
Usage: build_lca(root, n); lca(u, v); tree_dist(u, v);
Time: O(nlog n) build, O(log n) per query
*/

const int LOG = 20;                // need 2^LOG > n
vector<vector<int>> up;            // up[v][j] = 2^j-th ancestor of v
vector<int> depth;                 // edges from root to v
void build_lca(int root, int n) {  // vertices 1..n
  up.assign(n + 1, vector<int>(LOG, root));
  depth.assign(n + 1, 0);
  queue<int> q;
  q.push(root);
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int j = 1; j < LOG; j++) {
      up[v][j] = up[up[v][j - 1]][j - 1];
    }
    for (int u : adj[v]) {
      if (u == up[v][0]) continue;  // skip the parent
      up[u][0] = v;
      depth[u] = depth[v] + 1;
      q.push(u);
    }
  }
}
int lca(int u, int v) {
  if (depth[u] < depth[v]) swap(u, v);
  int diff = depth[u] - depth[v];
  for (int j = 0; j < LOG; j++) {  // lift u to depth of v
    if ((diff >> j) & 1) u = up[u][j];
  }
  if (u == v) return u;
  for (int j = LOG - 1; j >= 0; j--) {  // lift both below lca
    if (up[u][j] != up[v][j]) {
      u = up[u][j];
      v = up[v][j];
    }
  }
  return up[u][0];
}
int tree_dist(int u, int v) {  // edges between u and v
  return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}
