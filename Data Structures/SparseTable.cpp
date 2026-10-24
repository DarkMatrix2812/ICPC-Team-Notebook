/*
Description: Sparse table for range min and max on a static array, 0-indexed inclusive [L,R]. Use for RMQ with no updates, LCA via Euler tour, or any idempotent function (gcd, and, or).
How it works: st min[i][j] = minimum of the 2j elements starting at i, built from two halves of size 2^j−1 . A query [L,R] is covered by two blocks of size 2^j (one starting at L, one ending at R) that may overlap, which is fine for min / max.
Modify / tips: works for gcd, AND, OR (overlap does not matter) but not for sum. If the array changes, use MinMaxSegTree.
Usage: buildSparseTable(a); query_min(L, R);
Time: O(nlog n) build, O(1) per query
*/

int st_n, max_log;
vector<vector<int>> st_min, st_max;
vector<int> log_table;
// call once, a must not change
void buildSparseTable(vector<int>& a) {
  st_n = a.size();
  log_table.assign(st_n + 1, 0);
  for (int i = 2; i <= st_n; i++) log_table[i] = log_table[i / 2] + 1;
  max_log = log_table[st_n] + 1;
  st_min.assign(st_n, vector<int>(max_log));
  st_max.assign(st_n, vector<int>(max_log));
  for (int i = 0; i < st_n; i++) {
    st_min[i][0] = a[i];
    st_max[i][0] = a[i];
  }
  for (int j = 1; j < max_log; j++) {
    for (int i = 0; i + (1 << j) <= st_n; i++) {
      st_min[i][j] = min(st_min[i][j - 1], st_min[i + (1 << (j - 1))][j - 1]);
      st_max[i][j] = max(st_max[i][j - 1], st_max[i + (1 << (j - 1))][j - 1]);
    }
  }
}
int query_min(int L, int R) {    // min of a[L..R]
  int j = log_table[R - L + 1];  // largest 2^j <= length
  return min(st_min[L][j], st_min[R - (1 << j) + 1][j]);
}
int query_max(int L, int R) {    // max of a[L..R]
  int j = log_table[R - L + 1];  // largest 2^j <= length
  return max(st_max[L][j], st_max[R - (1 << j) + 1][j]);
}
