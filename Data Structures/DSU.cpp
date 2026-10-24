/*
Description: Disjoint set union with path compression and union by size. Use for connectivity under edge additions, Kruskal’s MST, counting components, offline merging.
How it works: each set is a tree; parent[v] points one step towards the set’s leader (the root). find_set walks to the root and re-points everything on the way directly to it. union sets hangs the smaller tree under the larger.
Modify / tips: to keep data per set (sum, min, edge count) store it at the leader and combine it inside union sets next to sz[a] += sz[b].
Number of components: start at n, subtract 1 on every successful union. 
Cycle in an undirected graph: an edge whose two ends already have the same leader. 
Kruskal MST: sort edges by weight, take an edge if its ends have different leaders. Edges are only ever added; for deletions process the queries backwards.
Usage: parent.resize(n+1); sz.resize(n+1); make_set(v) for all v;
Time: O(α(n)) amortised per operation
*/

vector<int> parent;
vector<int> sz;
void make_set(int v) {  // v alone in a new set
  parent[v] = v;
  sz[v] = 1;
}
int find_set(int v) {  // leader of the set of v
  if (v == parent[v]) return v;
  return parent[v] = find_set(parent[v]);  // point to leader
}
void union_sets(int a, int b) {  // merge sets of a and b
  a = find_set(a);
  b = find_set(b);
  if (a != b) {
    if (sz[a] < sz[b]) swap(a, b);  // a = bigger set
    parent[b] = a;
    sz[a] += sz[b];
  }
}
