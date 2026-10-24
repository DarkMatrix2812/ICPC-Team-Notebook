/*
Description: Longest strictly increasing subsequence with binary search, returned as the actual values (its .size() is the length). tail[k] = smallest possible last value of an increasing subsequence of length k + 1. 
For non-decreasing (equal values allowed) change lower bound to upper bound. For longest decreasing, negate or reverse the array first. Use for nested envelopes / boxes (sort by one side first), minimum number of decreasing chains, patience-sort style problems.
How it works: go left to right; each element replaces the first tail that is ≥it (found by binary search) or extends the list. previous[] remembers what came before each element so the sequence can be rebuilt.
Time: O(nlog n)
*/

vector<int> lis(vector<int>& a) {
  int n = a.size();
  vector<int> tail, tail_index, previous(n, -1);
  for (int i = 0; i < n; i++) {
    int pos = lower_bound(tail.begin(), tail.end(), a[i]) - tail.begin();
    if (pos == (int)tail.size()) {
      tail.push_back(a[i]);
      tail_index.push_back(i);
    } else {
      tail[pos] = a[i];
      tail_index[pos] = i;
    }
    if (pos > 0) previous[i] = tail_index[pos - 1];
  }
  vector<int> result; // rebuild from the last element
  if (n == 0) return result;
  for (int i = tail_index.back(); i != -1; i = previous[i]) {
    result.push_back(a[i]);
  }
  reverse(result.begin(), result.end());
  return result;
}
