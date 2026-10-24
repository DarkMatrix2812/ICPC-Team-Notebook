/*
Description: Connected components (“islands”) by BFS. components is for a graph in adj; islands is for a grid where equal cells touching by a side belong together. Use to count / list isolated groups, sizes of regions, flood fill. For 8 directions extend dx, dy with the 4 diagonals.
Time: O(V + E) graph, O(nm) grid
*/

// groups[k] = all vertices of the k-th component
// number of components = groups.size()
vector<vector<int>> components(int n) {  // vertices 1..n
  vector<vector<int>> groups;
  vector<bool> seen(n + 1, false);
  for (int s = 1; s <= n; s++) {
    if (seen[s]) continue;
    groups.push_back({});
    queue<int> q;
    q.push(s);
    seen[s] = true;
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      groups.back().push_back(v);
      for (int u : adj[v]) {
        if (!seen[u]) {
          seen[u] = true;
          q.push(u);
        }
      }
    }
  }
  return groups;
}
// island_id[i][j] = which island cell (i, j) is in,
// -1 if the cell is not land. Returns number of islands.
vector<vector<int>> island_id;
int islands(vector<string>& grid, char land) {
  int n = grid.size(), m = grid[0].size(), total = 0;
  int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
  island_id.assign(n, vector<int>(m, -1));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] != land) continue;
      if (island_id[i][j] != -1) continue;
      queue<pair<int, int>> q;
      q.push({i, j});
      island_id[i][j] = total;
      while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int k = 0; k < 4; k++) {
          int nx = x + dx[k], ny = y + dy[k];
          if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
          if (grid[nx][ny] != land) continue;
          if (island_id[nx][ny] != -1) continue;
          island_id[nx][ny] = total;
          q.push({nx, ny});
        }
      }
      total++;
    }
  }
  return total;
}
