/* 
Description: DP over subsets, for n ≤20 (the hint is a tiny n). Bit i of mask = item i already used. Two standard shapes: dp[mask][last] when the order matters and the cost depends on the previous item (travelling salesman, shortest Hamiltonian path, ordering jobs); dp[mask] when items are matched one by one (assign n people to n jobs, pairing). To count instead of minimise: start with 1, replace min by + mod. Lines marked MODIFY depend on the problem.
Time: O(2^n * n^2) tsp, O(2^n * n) assignment
*/

// min cost to start at 0, visit every vertex once, return
int tsp(vector<vector<int>>& cost) {
  int n = cost.size(), FULL = (1LL << n);
  // dp[mask][last] = cheapest way to have visited the set mask and be standing
  // at last
  vector<vector<int>> dp(FULL, vector<int>(n, LLONG_MAX));
  dp[1][0] = 0;  // MODIFY: start (any start: dp[1 << i][i] = 0)
  for (int mask = 1; mask < FULL; mask++) {
    for (int last = 0; last < n; last++) {
      if (dp[mask][last] == LLONG_MAX) continue;
      for (int nxt = 0; nxt < n; nxt++) {
        if ((mask >> nxt) & 1) continue;  // already visited
        int new_mask = mask | (1LL << nxt);
        // MODIFY: cost of going from last to nxt
        dp[new_mask][nxt] =
            min(dp[new_mask][nxt], dp[mask][last] + cost[last][nxt]);
      }
    }
  }
  int best = LLONG_MAX;
  for (int last = 0; last < n; last++) {
    if (dp[FULL - 1][last] == LLONG_MAX) continue;
    // MODIFY: remove "+ cost[last][0]" if no return needed
    best = min(best, dp[FULL - 1][last] + cost[last][0]);
  }
  return best;
}
// min total cost giving each person a different job
int assignment(vector<vector<int>>& cost) {
  int n = cost.size(), FULL = (1LL << n);
  // dp[mask] = best cost when the first popcount(mask)
  // people have taken exactly the jobs in mask
  vector<int> dp(FULL, LLONG_MAX);
  dp[0] = 0;
  for (int mask = 0; mask < FULL - 1; mask++) {
    if (dp[mask] == LLONG_MAX) continue;
    int person = __builtin_popcountll(mask);
    for (int job = 0; job < n; job++) {
      if ((mask >> job) & 1) continue;  // job already taken
      int new_mask = mask | (1LL << job);
      // MODIFY: cost of giving this job to this person
      dp[new_mask] = min(dp[new_mask], dp[mask] + cost[person][job]);
    }
  }
  return dp[FULL - 1];
}
