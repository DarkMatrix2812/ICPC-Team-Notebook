/*
Description: Strongly connected components (Tarjan) of a directed graph in adj, vertices 1..n, in one DFS and without a reversed graph. scc_root[v] = leader vertex of the component of v (NOT 0..k-1); u and v reach each other iff scc_root[u] == scc_root[v]. scc_comps[k] = vertices of the k-th component found. Components come out in REVERSE topological order (sinks first), the opposite of SCC.h. scc_adj = condensed graph on leaders (duplicate edges possible). Use for "mutually reachable" groups, shrinking a graph to a DAG, 2-SAT.
How it works: scc_in[u] = DFS entry time. scc_low[u] = smallest entry time reachable from u's subtree using one edge to a vertex still on the stack. Vertices stay on scc_stk until their component is complete. When scc_low[u] == scc_in[u], nothing below u reaches above u, so u and everything above it on the stack form one component: pop them.
Modify / tips: DP on the condensed DAG: walk scc_comps from first to last, every component reachable from the current one is already done. Remove duplicate edges of scc_adj with sort + unique if needed. Number of components = scc_comps.size(). scc_dfs is recursive, very deep graphs may overflow the stack.
Usage: scc_root, scc_in, scc_low .assign(n + 1, -1); scc_adj.assign(n + 1, {}); tarjan(n);
Time: O(V + E)
*/

vector<int> scc_stk, scc_root, scc_in, scc_low;
vector<vector<int>> scc_comps, scc_adj;
int scc_timer;
void scc_dfs(int u) {  // enter u, push on stack
  scc_low[u] = scc_in[u] = scc_timer++;
  scc_stk.push_back(u);
  for (int v : adj[u]) {
    if (scc_in[v] == -1) {  // tree edge
      scc_dfs(v);
      scc_low[u] = min(scc_low[u], scc_low[v]);
    } else if (scc_root[v] == -1) {  // v still on stack
      scc_low[u] = min(scc_low[u], scc_in[v]);
    }
  }
  if (scc_low[u] == scc_in[u]) {  // u is a component root
    scc_comps.push_back({u});
    while (true) {
      int v = scc_stk.back();
      scc_stk.pop_back();
      scc_root[v] = u;
      if (v == u) break;
      scc_comps.back().push_back(v);
    }
  }
}
void tarjan(int n) {  // vertices 1..n
  scc_stk.clear();
  scc_comps.clear();
  scc_timer = 0;
  for (int u = 1; u <= n; u++) {
    if (scc_in[u] == -1) scc_dfs(u);
  }
  for (int u = 1; u <= n; u++) {  // condensed graph
    for (int v : adj[u]) {
      if (scc_root[u] != scc_root[v])
        scc_adj[scc_root[u]].push_back(scc_root[v]);
    }
  }
}
