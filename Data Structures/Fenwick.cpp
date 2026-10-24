/*
Description: Fenwick tree (BIT), 1-indexed : point add, prefix sum. Sum of [l,r] is query(r) - query(l-1). Use for dynamic prefix sums, inversion counting, order statistics on compressed values.
How it works: bit arr[i] holds the sum of the last (i & -i) elements ending at i. A prefix is covered by O(log n) such blocks, and one element lies in O(log n) blocks.
Modify / tips: range add + single element read: fenwick update(l, x); fenwick update(r + 1, -x); then fenwick query(i) is a[i].
Inversion count: compress values to 1..n, go right to left, add fenwick query(a[i] - 1), then fenwick update(a[i], 1). A 0-indexed array must be shifted by 1.
Usage: bit n = n; bit arr.assign(bit n + 1, 0);
Time: O(log n) per operation
*/

// bit_arr[i] = sum of a block of a[] ending at i
// sum of a[l..r] = fenwick_query(r) - fenwick_query(l - 1)
int bit_n;
vector<int> bit_arr;
// bit_n = n;
// bit_arr.assign(bit_n + 1, 0);
void fenwick_update(int i, int val) {  // a[i] += val, 1-indexed
  // i & -i = lowest set bit: go to next block holding i
  for (; i <= bit_n; i += i & -i) bit_arr[i] += val;
}
int fenwick_query(int i) {  // a[1] + ... + a[i]
  int sum = 0;
  // drop lowest set bit: go to block before this one
  for (; i > 0; i -= i & -i) sum += bit_arr[i];
  return sum;
}
