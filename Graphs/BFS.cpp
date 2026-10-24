/*
Description: Breadth-first search from s: d[v] = fewest edges from s (−1 if unreachable), p[v]= parent on a shortest path. Use for unweighted shortest paths, path recovery (follow p), grid/level problems.
How it works: the queue hands out vertices in order of distance from s, so the first time a vertex is reached is along a shortest path.
Modify / tips: path from s to t: start at t, follow p[] until−1, reverse. Grid: a vertex is a cell, neighbours come from dx, dy (see MultiSourceBFS). Two-colouring / bipartite check: give uthe opposite colour of v; a neighbour with the same colour means an odd cycle. Extra condition (keys, remaining jumps): BFS over pairs (vertex, condition).
Time: O(V + E)
*/

vector<vector<int>> adj;
vector<int> d, p;
vector<bool> vis;
// d.assign(n + 1, -1);
// p.assign(n + 1, -1);
// vis.assign(n + 1, false);
void bfs(int s) {  // d[] = edges from s, p[] = parent
  queue<int> q;
  q.push(s);
  vis[s] = true;
  d[s] = 0;
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int u : adj[v]) {
      if (!vis[u]) {  // first visit = shortest
        vis[u] = true;
        d[u] = d[v] + 1;
        p[u] = v;
        q.push(u);
      }
    }
  }
}
