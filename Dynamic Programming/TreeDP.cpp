/*
Description: DP on subtrees skeleton.
Recipe: 
(1) decide what dp[v] means for the subtree of v only, with one array per choice made at v; 
(2) write the value for v alone; 
(3) after solving a child u, merge its answer into v; 
(4) read the answer at the root. 
The example is maximum total weight of vertices with no two adjacent (dp take: vchosen, dp skip: v not chosen). To adapt, change only the numbered lines. Common variants: count instead of max (use + / ×mod), subtree[v] for sizes, longest path through v = two largest child depths. Tree in adj, undirected; recursion depth is the tree height.
Time: O(n)
*/

vector<int> weight, subtree, dp_take, dp_skip;
// subtree.assign(n + 1, 0);
// dp_take.assign(n + 1, 0);
// dp_skip.assign(n + 1, 0);
// tree_dp(root, 0);
void tree_dp(int v, int par) {
  subtree[v] = 1;  // (2) v alone
  dp_take[v] = weight[v];
  dp_skip[v] = 0;
  for (int u : adj[v]) {
    if (u == par) continue;
    tree_dp(u, v);             // solve the child first
    subtree[v] += subtree[u];  // (3) merge child u into v
    dp_take[v] += dp_skip[u];
    dp_skip[v] += max(dp_take[u], dp_skip[u]);
  }
}
// (4) answer = max(dp_take[root], dp_skip[root])
