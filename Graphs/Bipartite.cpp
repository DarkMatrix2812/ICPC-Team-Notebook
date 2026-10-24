/*
Description: Two-colouring check of an undirected graph in adj (vertices 1..n, every edge stored in both directions). Returns true iff the graph has no odd cycle; side[v] in {0, 1} is then a valid colouring, i.e. the two sides. Works for disconnected graphs. Use for "split into two groups with no conflict inside a group", odd-cycle detection, setting up bipartite matching.
How it works: colour a start vertex 0 and run BFS; every neighbour must get the opposite colour. A neighbour that already has the same colour closes an odd cycle. A graph is bipartite iff it has no odd cycle.
Modify / tips: a self-loop makes the answer false. If the graph is bipartite, the number of valid 2-colourings is 2^(number of components). On a grid the colouring is simply (i + j) % 2, no search needed.
Usage: side.assign(n + 1, -1); bool ok = bipartite(n);
Time: O(V + E)
*/

vector<int> side;        // 0 / 1 colour, -1 = not coloured yet
bool bipartite(int n) {  // vertices 1..n
  bool ok = true;
  for (int s = 1; s <= n; s++) {
    if (side[s] != -1) continue;
    queue<int> q;
    q.push(s);
    side[s] = 0;
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (int u : adj[v]) {
        if (side[u] == -1) {
          side[u] = side[v] ^ 1;  // opposite colour
          q.push(u);
        } else if (side[u] == side[v]) {
          ok = false;  // odd cycle
        }
      }
    }
  }
  return ok;
}
