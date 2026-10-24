/*
Description: Shortest paths from s with non-negative edge weights; adjd[v] holds {to, weight}. Unreachable vertices keep LLONG MAX. Use for weighted shortest paths; run on a state graph (vertex, extra) for constrained variants.
How it works: repeatedly take the unfinished vertex with the smallest known distance (top of the min-heap) and try to improve its neighbours through it. A vertex can sit in the heap several times; outdated copies are skipped.
Modify / tips: add edges with adjd[u].push back({v, w}) (both directions if undirected). Path: store p[u] = v where dist[u] improves.
Extra resource (one free ride, k coupons): make the vertex number v * (k + 1) + used and add the extra transitions. Minimise the largest edge instead of the sum: replace d + w by max(d, w).
Time: O((V + E) log V)
*/
  
vector<vector<pair<int, int>>> adjd;
vector<int> dist;
// dist.assign(n + 1, LLONG_MAX);
void dijkstra(int s) {  // dist[] from s, weights >= 0
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  dist[s] = 0;
  pq.push({0, s});
  while (!pq.empty()) {
    auto [d, v] = pq.top();
    pq.pop();
    if (d != dist[v]) continue;  // outdated copy
    for (auto [u, w] : adjd[v]) {
      if (dist[u] > d + w) {  // shorter way to u via v
        dist[u] = d + w;
        pq.push({dist[u], u});
      }
    }
  }
}
