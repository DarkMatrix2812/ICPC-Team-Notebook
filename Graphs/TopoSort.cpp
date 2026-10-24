/*
Description: Topological order of a directed graph in adj (Kahn’s algorithm): every edge u→v has u before v. If the result has fewer than n vertices the graph has a cycle. Use for dependency ordering, DP on a DAG (process vertices in this order), cycle detection in directed graphs. Swap the queue for a min-heap to get the lexicographically smallest order.
How it works: a vertex with no incoming edges can go first; remove it, which may free its neighbours.
Modify / tips: DP on a DAG: walk the returned order and push values along edges, dp[u] = max(dp[u], dp[v] + 1) for the longest path, dp[u] += dp[v] to count paths.
Time: O(V + E)
*/

vector<int> topo_sort(int n) {  // vertices 1..n
  vector<int> indegree(n + 1, 0), order;
  for (int v = 1; v <= n; v++) {
    for (int u : adj[v]) indegree[u]++;
  }
  queue<int> q;
  for (int v = 1; v <= n; v++) {
    if (indegree[v] == 0) q.push(v);
  }
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    order.push_back(v);
    for (int u : adj[v]) {
      indegree[u]--;
      if (indegree[u] == 0) q.push(u);
    }
  }
  return order;  // order.size() < n means there is a cycle
}
