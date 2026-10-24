/*
Description: Longest common subsequence of two strings, returned as the actual string (its .size() is the length). dp[i][j] = LCS length of the first i characters of a and first j of b. 
Use for edit-style problems: minimum deletions to make strings equal = n+ m−2·LCS, shortest common supersequence, longest palindromic subsequence (LCS of s and
reversed s). Memory is 8nm bytes, fine up to about n,m≤3000.
How it works: if the last characters match they are paired (diagonal+1); otherwise drop the last character of one string, whichever gives more. The answer is rebuilt by walking the table backwards.
Modify / tips: edit distance: dp[i][0] = i, dp[0][j] = j, equal characters copy the diagonal, otherwise 1 + min(up, left, diagonal). Works on vector<int> the same way.
Time: O(nm)
*/

string lcs(string a, string b) {
  int n = a.size(), m = b.size();
  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (a[i - 1] == b[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }
  string result; // walk back from dp[n][m]
  int i = n, j = m;
  while (i > 0 && j > 0) {
    if (a[i - 1] == b[j - 1]) {
      result.push_back(a[i - 1]);
      i--;
      j--;
    } else if (dp[i - 1][j] >= dp[i][j - 1]) {
      i--;
    } else {
      j--;
    }
  }
  reverse(result.begin(), result.end());
  return result;
}
