/*
Description: Segment tree with lazy propagation: range add, range sum, 0-indexed inclusive [l,r]. Use when both updates and queries are on ranges; change the combine in build/update/seg sumand the tag logic in push for min/max/assign.
How it works: node v stores the sum of a segment; its children are the two halves. A range operation only touches O(log n) nodes that lie fully inside the range. Instead of updating all elements below such a node, the amount is parked in lazy[v] and handed to the children (push) only when something later needs to go deeper.
Modify / tips: range add + range min: in build, update, seg sum replace + of the two children by min, return LLONG MAX for an empty range, and add lazy to t without multiplying by the length. Range assign: keep a second array saying “lazy is set”, and overwrite (=) instead of +=.
Usage: buildSegTree(a); seg add(l, r, val); query sum(l, r);
Time: O(n) build, O(log n) per operation
*/

// node v covers a[tl..tr], root v = 1, children 2v, 2v+1
// t[v] = sum of the node, lazy[v] = add owed to children
int seg_n;
vector<int> t, lazy;
// internal: fill t[] for node v from a[tl..tr]
void build(int v, int tl, int tr, const vector<int>& a) {
  if (tl == tr) {
    t[v] = a[tl];
  } else {
    int tm = (tl + tr) / 2;
    build(v * 2, tl, tm, a);
    build(v * 2 + 1, tm + 1, tr, a);
    t[v] = t[v * 2] + t[v * 2 + 1];
  }
}
void push(int v, int tl, int tr) {  // give lazy[v] to children
  if (lazy[v]) {
    int tm = (tl + tr) / 2;
    t[v * 2] += lazy[v] * (tm - tl + 1);
    lazy[v * 2] += lazy[v];
    t[v * 2 + 1] += lazy[v] * (tr - tm);
    lazy[v * 2 + 1] += lazy[v];
    lazy[v] = 0;
  }
}
// internal: a[i] += addend for all l <= i <= r
void update(int v, int tl, int tr, int l, int r, int addend) {
  if (l > r) return;
  if (l == tl && r == tr) {  // node fully inside: stop here
    t[v] += addend * (tr - tl + 1);
    lazy[v] += addend;
  } else {
    push(v, tl, tr);
    int tm = (tl + tr) / 2;
    update(v * 2, tl, tm, l, min(r, tm), addend);
    update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, addend);
    t[v] = t[v * 2] + t[v * 2 + 1];
  }
}
// internal: sum of a[l..r] inside node v
int seg_sum(int v, int tl, int tr, int l, int r) {
  if (l > r) return 0;
  if (l == tl && r == tr) {
    return t[v];
  }
  push(v, tl, tr);
  int tm = (tl + tr) / 2;
  return seg_sum(v * 2, tl, tm, l, min(r, tm)) +
         seg_sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
}
// CALL ONCE: sizes t, lazy to 4 * seg_n, builds from a
void buildSegTree(const vector<int>& a) {
  seg_n = a.size();
  t.assign(4 * seg_n, 0);
  lazy.assign(4 * seg_n, 0);
  if (seg_n > 0) build(1, 0, seg_n - 1, a);
}
// CALL: a[i] += val for all l <= i <= r (0-indexed)
void seg_add(int l, int r, int val) {
  if (seg_n > 0) update(1, 0, seg_n - 1, l, r, val);
}
// CALL: a[l] + ... + a[r] (0-indexed)
int query_sum(int l, int r) {
  if (seg_n == 0) return 0;
  return seg_sum(1, 0, seg_n - 1, l, r);
}
