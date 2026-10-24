/*
Description: BFS started from many sources at once: every cell / vertex gets the distance to its nearest source. Use for “distance to the closest X for every cell”, “fire / infection / rot spreads from several places, when is everything reached” (answer = largest distance), “is the exit reached before the fire” (run it once per kind of source and compare). Lines marked MODIFY are the only ones that depend on the problem.
Time: O(nm) grid, O(V + E) graph
*/

vector<vector<int>> dist_grid;  // -1 = never reached
void multi_source_bfs(vector<string>& grid) {
  int n = grid.size(), m = grid[0].size();
  // MODIFY: allowed moves (add 4 diagonals for 8 directions)
  int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
  dist_grid.assign(n, vector<int>(m, -1));
  queue<pair<int, int>> q;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == 'S') {  // MODIFY: which cells start
        dist_grid[i][j] = 0;
        q.push({i, j});
      }
    }
  }
  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();
    for (int k = 0; k < 4; k++) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
      if (grid[nx][ny] == '#') continue;      // MODIFY: blocked
      if (dist_grid[nx][ny] != -1) continue;  // seen before
      dist_grid[nx][ny] = dist_grid[x][y] + 1;
      // MODIFY: to know WHICH source is nearest, also copy
      // owner[nx][ny] = owner[x][y] here
      q.push({nx, ny});
    }
  }
}
// same idea on a graph in adj: d[v] = edges to nearest source
// d.assign(n + 1, -1);
void multi_source_bfs_graph(vector<int>& sources) {
  queue<int> q;
  for (int s : sources) {  // MODIFY: the starting vertices
    d[s] = 0;
    q.push(s);
  }
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int u : adj[v]) {
      if (d[u] != -1) continue;
      d[u] = d[v] + 1;
      q.push(u);
    }
  }
}
