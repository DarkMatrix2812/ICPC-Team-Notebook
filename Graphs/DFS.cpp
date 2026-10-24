/*
Description: Depth-first search with entry/exit times. color: 0 unvisited, 1 on stack, 2 done. Use for subtree ranges (u is an ancestor of v iff tin[u] ≤tin[v] and tout[v] ≤tout[u]), cycle detection (edge to a colour-1 vertex), topological order (reverse tout). The iterative version is safe for depth >1e5
How it works: go as deep as possible, then back up. tin / tout are clock values on entering and leaving a vertex; everything entered between them is in the subtree. The iterative version pushes each vertex twice: once to enter, once to leave.
Modify / tips: cycle in a directed graph: while entering v, a neighbour with colour 1. Subtree queries: number vertices by entry order; the sub- tree of v becomes one contiguous range, so a Fenwick / segment tree can answer “sum in subtree”. timer here counts entries and exits together (0..2n−1). Call once per unvisited vertex if the graph is disconnected (then delete the line timer = 0; and reset it yourself once).
Time: O(V + E)
*/

vector<int> color, tin, tout;
int timer;
// color.assign(n + 1, 0);
// tin.assign(n + 1, -1);
// tout.assign(n + 1, -1);
void iterative_dfs(int root) {  // tin[], tout[], no recursion
  timer = 0;
  stack<pair<int, int>> st;
  st.push({root, 0});  // 0 = enter, 1 = exit
  while (!st.empty()) {
    auto [v, state] = st.top();
    st.pop();
    if (state == 0) {
      if (color[v] != 0) continue;  // already entered
      tin[v] = timer++;
      color[v] = 1;
      st.push({v, 1});
      for (int i = (int)adj[v].size() - 1; i >= 0; i--) {
        int u = adj[v][i];
        if (color[u] == 0) st.push({u, 0});
      }
    } else {
      color[v] = 2;
      tout[v] = timer++;
    }
  }
}
void recursive_dfs(int v) {  // marks vis[] reachable from v
  vis[v] = 1;
  for (int u : adj[v]) {
    if (vis[u]) continue;
    recursive_dfs(u);
  }
}
