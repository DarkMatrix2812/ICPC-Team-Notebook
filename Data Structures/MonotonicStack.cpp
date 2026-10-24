/*
Description: Stack that is kept sorted, so every index is pushed and popped once. next greater: for each i the nearest index to the right with a strictly larger value. largest rectangle: biggest rectangle under a histogram. Use for “first bigger / smaller element on the left / right”, how far each element stays the minimum or maximum (sum of subarray minimums: count subarrays where a[i] is the minimum using previous-smaller and next-smaller), stock span, largest rectangle of 1s in a 0/1 matrix (per row keep h[j] = number of consecutive 1s ending at this row, call largest rectangle(h) on every row).
How it works: the stack holds indices that have not found their answer yet; their values are sorted, so when a new element arrives it answers (and pops) everything on top that it beats.
Time: O(n)
*/

// result[i] = index of the next element > a[i], -1 if none
vector<int> next_greater(vector<int>& a) {
  int n = a.size();
  vector<int> result(n, -1);
  stack<int> st;  // indices still waiting for an answer
  // MODIFY: loop i from n - 1 down to 0 for PREVIOUS greater
  for (int i = 0; i < n; i++) {
    // MODIFY the comparison: < next greater
    // <= next greater or equal > next smaller
    // >= next smaller or equal
    while (!st.empty() && a[st.top()] < a[i]) {
      result[st.top()] = i;  // a[i] is the answer for the top
      st.pop();
    }
    st.push(i);
  }
  return result;
}
// largest area of a rectangle inside the histogram h
int largest_rectangle(vector<int>& h) {
  int n = h.size(), best = 0;
  stack<int> st;  // indices of bars, heights increasing
  for (int i = 0; i <= n; i++) {
    int cur = (i == n) ? 0 : h[i];  // 0 at the end empties st
    while (!st.empty() && h[st.top()] >= cur) {
      int height = h[st.top()];  // this bar is the lowest
      st.pop();
      // it extends from the bar below it on the stack to i
      int left = st.empty() ? -1 : st.top();
      best = max(best, height * (i - left - 1));
    }
    st.push(i);
  }
  return best;
}
