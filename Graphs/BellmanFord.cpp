/*
Description: Shortest paths from swith negative edges allowed, vertices 1..n, adjbf[u] holds {to, weight}. After it, run the commented loop: any edge that still relaxes means a negative cycle reachable from s. Use for negative weights, arbitrage, systems of difference constraints.
How it works: a shortest path uses at most n−1 edges, so relaxing every edge n−1 times is enough. If something can still be improved after that, a negative cycle exists.
Modify / tips: longest path: negate the weights. Difference constraints xv−xu ≤w: add edge u→v with weight w.
Time: O(VE)
*/

vector<vector<pair<int, int>>> adjbf;
vector<int> bellman_dist;
// adjbf.assign(n + 1, {});
// bellman_dist.assign(n + 1, LLONG_MAX);
void bellmanFord(int n, int s) {  // negative edges allowed
  bellman_dist.assign(n + 1, LLONG_MAX);
  bellman_dist[s] = 0;
  for (int i = 1; i <= n - 1; i++) {  // n - 1 rounds
    for (int u = 1; u <= n; u++) {
      if (bellman_dist[u] == LLONG_MAX) continue;
      for (auto [v, w] : adjbf[u]) {
        if (bellman_dist[v] > bellman_dist[u] + w) {
          bellman_dist[v] = bellman_dist[u] + w;
        }
      }
    }
  }
}
// for (int u = 1; u <= n; u++) {
//   if (bellman_dist[u] == LLONG_MAX) continue;
//   for (auto [v, w] : adjbf[u]) {
//     if (bellman_dist[v] > bellman_dist[u] + w) {
//       // Negative cycle detected.
//       // Handle according to the problem.
//     }
//   }
// }
