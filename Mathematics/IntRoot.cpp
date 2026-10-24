/*
Description: ⌊y √x⌋by binary search with int128, no floating point error. Use for exact square/cube roots and perfect-power checks up to 1e18
How it works: binary search for the largest m with m^y ≤x. The power is built one multiplication at a time in __int128 and stopped as soon as it exceeds x, so nothing overflows.
Modify / tips: this is the general binary search on the answer skeleton: keep l, h, ans, replace the block that sets ok by any check that is true for small m and false for large m (“can we finish with capacity m”, “can we place cows at distance m”). If the check is false-then-true, swap the two branches.
Time: O(ylog x)
*/

int getRoot(int x, int y) {  // y-th root of x
  int l = 0, h = x, ans = 0;
  while (l <= h) {
    int m = l + (h - l) / 2;
    __int128 cur = 1;
    bool ok = true;
    for (int i = 0; i < y; i++) {
      cur *= m;
      if (cur > x) {
        ok = false;
        break;
      }
    }
    if (ok) {
      ans = m;
      l = m + 1;
    } else {
      h = m - 1;
    }
  }
  return ans;
}
bool isPerfectSquare(int n) {  // is n = r * r
  if (n < 0) return false;
  int r = getRoot(n, 2);
  return r * r == n;
}
