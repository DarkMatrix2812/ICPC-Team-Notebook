/*
Description: Sorting by any rule. A comparator is a function that takes two elements and answers one question: “must a come before b?”. Pass its name as the third argument of sort. The same pattern covers every case: compare the most important key first; only if it is equal go to the next key.
How it works: sortcalls the comparator on pairs of elements and places a first whenever it returns true. Rule that must never be broken: for two equal elements it has to return false (use < or >, never <= or >=), otherwise sort may crash or loop forever.
Modify / tips: flip < to > on a key to make that key descending. Built-in shortcuts: sort(v.rbegin(), v.rend()) = descending; pairs and vectors already sort by first element, then second, and so on, so storing {key, value} pairs (or -key for descending) often avoids a comparator. stable_sort keeps the input order of equal elements. Sort by a fraction a.x/a.y without doubles: return a.x * b.y < b.x * a.y; (positive y). Arrange numbers as strings to form the largest number: return a + b > b + a;
Usage: sort(v.begin(), v.end(), by_second);
Time: O(nlog n) comparisons
*/

// (1) pairs: by second value, ties by first value
bool by_second(const pair<int, int>& a, const pair<int, int>& b) {
  if (a.second != b.second) return a.second < b.second;
  return a.first < b.first;
}
// (2) list of groups (cycles, components, paths): the
// biggest group first, equal sizes: smaller content first
bool by_size(const vector<int>& a, const vector<int>& b) {
  if (a.size() != b.size()) return a.size() > b.size();
  return a < b;
}
// (3) records with several keys
struct Student {
  string name;
  int marks, age;
  20 lines
};
bool by_marks(const Student& a, const Student& b) {
  if (a.marks != b.marks) return a.marks > b.marks;  // high
  if (a.age != b.age) return a.age < b.age;          // then young
  return a.name < b.name;                            // then alphabetical
}
// (4) sort positions, not values: order[k] = index of the
// k-th smallest element (original array stays untouched)
vector<int> sorted_indices(vector<int>& a) {
  int n = a.size();
  vector<int> order(n);
  for (int i = 0; i < n; i++) order[i] = i;
  // a comparator written in place; [&] lets it read a
  sort(order.begin(), order.end(), [&](int i, int j) {
    if (a[i] != a[j]) return a[i] < a[j];  // MODIFY: the key
    return i < j;
  });
  return order;
}
// (5) custom order inside set / map / priority_queue needs
// a struct with operator() instead of a function
struct BySecond {
  bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {
    if (a.second != b.second) return a.second < b.second;
    return a.first < b.first;
  }
};
// set<pair<int,int>, BySecond> s;
// *s.begin() = smallest second. Elements for which
// neither comes before the other count as duplicates
// priority_queue<pair<int,int>, vector<pair<int,int>>,
// BySecond> pq;
// pq.top() = the LAST element of this order (largest
// second). For smallest on top flip < to > in BySecond
