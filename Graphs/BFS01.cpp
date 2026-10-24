/*
Description: Dijkstra specialised to edge weights 0 or 1 using a deque (0-edges go to the front, 1-edges to the back). Use for “minimum number of paid moves / flips / walls broken” problems.
How it works: a 0-edge keeps the distance equal, so its end goes to the front of the deque; a 1-edge goes to the back. The deque therefore stays sorted by distance without a heap.
Time: O(V + E)
*/

// dist.assign(n + 1, LLONG_MAX);
// p.assign(n + 1, -1);
// basically dijkstra but optimized because we have
// weights only as 0-1
void bfs01(int s) {  // dist[] from s, p[] = parent
  deque<int> q;
  dist[s] = 0;
  q.push_front(s);
  while (!q.empty()) {
    int v = q.front();
    q.pop_front();
    for (auto [u, w] : adjd[v]) {
      if (dist[v] + w < dist[u]) {
        dist[u] = dist[v] + w;
        p[u] = v;
        if (w == 1) {  // cost 1: back, cost 0: front
          q.push_back(u);
        } else {
          q.push_front(u);
        }
      }
    }
  }
}
