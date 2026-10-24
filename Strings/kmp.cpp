/*
Description: pi[i] = length of the longest proper prefix of s[0..i] that is also its suffix. kmp returns all 0-indexed start positions of substr in parent. Use for pattern matching, borders, smallest period (n−pi[n−1] if it divides n).
How it works: j= how many characters of the pattern currently match. On a mismatch, instead of restarting, drop to the next shorter prefix that is still a suffix of what was matched (pi[j - 1]).
Modify / tips: number of occurrences = matches.size(). Longest prefix of s that is also a suffix = pi[n-1]. Works on vectors too.
Time: O(|substr|+ |parent|)
*/

// pi[i] = border of s[0..i]
vector<int> prefix_function(string s) {
  int n = s.length();
  vector<int> pi(n, 0);
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) { // try shorter border
    j = pi[j - 1];
    }
    if (s[i] == s[j]) j++;
    pi[i] = j;
  }
  return pi;
}
// starts of substr in parent
vector<int> kmp(string substr, string parent) {
  vector<int> matches;
  if (substr.empty() || parent.empty() || substr.length() > parent.length()) return matches;
  vector<int> pi = prefix_function(substr);
  int j = 0;
  for (int i = 0; i < parent.length(); i++) {
    while (j > 0 && parent[i] != substr[j]) {
      j = pi[j - 1];
    }
    if (parent[i] == substr[j]) j++;
    if (j == substr.length()) { // whole pattern matched
      matches.push_back(i - j + 1);
      j = pi[j - 1];
    }
  }
  return matches;
}
