/*
Description: Segment tree for range minimum and maximum where single elements can change (0-indexed, inclusive [l,r]). Use instead of the sparse table as soon as the problem has updates mixed with queries, e.g. “set a[i] = x” and “min / max of a[l..r]”. first_at_least finds the first position from l whose value is ≥x (“first free hotel with enough rooms”, “next element that fits”).
How it works: every node stores the min and max of its segment. An update walks from the root down to one leaf and recomputes the nodes on the way back; a query collects O(log n) nodes that exactly cover [l,r]. The search goes left whenever the left child’s max is big enough.
Modify / tips: for sum / gcd / xor replace min and LLONG MAX by the operation and its neutral value (0). For “add to a[pos]” write += value at the leaf. For range updates use the lazy tree instead.
Usage: buildMinMaxTree(a); seg_set(pos, value); range_min(l, r); range_max(l, r); first_at_least(l, x);
Time: O(n) build, O(log n) per operation
*/

int mm_n;
vector<int> mm_min, mm_max;
// node v covers a[tl..tr], children 2v and 2v+1
void mm_build(int v, int tl, int tr, const vector<int>& a) {
  if (tl == tr) {
    mm_min[v] = mm_max[v] = a[tl];
  } else {
    int tm = (tl + tr) / 2;
    mm_build(v * 2, tl, tm, a);
    mm_build(v * 2 + 1, tm + 1, tr, a);
    mm_min[v] = min(mm_min[v * 2], mm_min[v * 2 + 1]);
    mm_max[v] = max(mm_max[v * 2], mm_max[v * 2 + 1]);
  }
}
// internal: a[pos] = value
void mm_update(int v, int tl, int tr, int pos, int value) {
  if (tl == tr) {
    mm_min[v] = mm_max[v] = value;  // the leaf of a[pos]
  } else {
    int tm = (tl + tr) / 2;
    if (pos <= tm) {
      mm_update(v * 2, tl, tm, pos, value);
    } else {
      mm_update(v * 2 + 1, tm + 1, tr, pos, value);
    }
    mm_min[v] = min(mm_min[v * 2], mm_min[v * 2 + 1]);
    mm_max[v] = max(mm_max[v * 2], mm_max[v * 2 + 1]);
  }
}
int mm_get_min(int v, int tl, int tr, int l, int r) {
  if (l > r) return LLONG_MAX;  // empty: neutral for min
  if (l == tl && r == tr) return mm_min[v];
  int tm = (tl + tr) / 2;
  return min(mm_get_min(v * 2, tl, tm, l, min(r, tm)),
             mm_get_min(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
}
int mm_get_max(int v, int tl, int tr, int l, int r) {
  if (l > r) return LLONG_MIN;  // empty: neutral for max
  if (l == tl && r == tr) return mm_max[v];
  int tm = (tl + tr) / 2;
  return max(mm_get_max(v * 2, tl, tm, l, min(r, tm)),
             mm_get_max(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
}
// internal: smallest index >= l with a[index] >= x, or -1
int mm_first(int v, int tl, int tr, int l, int x) {
  if (tr < l || mm_max[v] < x) return -1;  // nothing here
  if (tl == tr) return tl;
  int tm = (tl + tr) / 2;
  int left = mm_first(v * 2, tl, tm, l, x);
  if (left != -1) return left;
  return mm_first(v * 2 + 1, tm + 1, tr, l, x);
}
// CALL ONCE
void buildMinMaxTree(const vector<int>& a) {
  mm_n = a.size();
  mm_min.assign(4 * mm_n, LLONG_MAX);
  mm_max.assign(4 * mm_n, LLONG_MIN);
  if (mm_n > 0) mm_build(1, 0, mm_n - 1, a);
}
// CALL: a[pos] = value
void seg_set(int pos, int value) { mm_update(1, 0, mm_n - 1, pos, value); }
// CALL: smallest / largest of a[l..r]
int range_min(int l, int r) { return mm_get_min(1, 0, mm_n - 1, l, r); }
int range_max(int l, int r) { return mm_get_max(1, 0, mm_n - 1, l, r); }
// CALL: first index >= l with a[index] >= x, -1 if none
int first_at_least(int l, int x) {
  if (mm_n == 0) return -1;
  return mm_first(1, 0, mm_n - 1, l, x);
}
