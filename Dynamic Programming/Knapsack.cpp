/*
Description: All knapsack variants. dp[w] = best answer using total weight (or sum) exactly / at most w. Which one: each item usable once →0/1 (inner loop goes down); unlimited copies →unbounded (inner loop goes up); limited copies →bounded; only “is it possible” → subset sum; “how many ways” →counting; “fewest items” →min coins; capacity up to 1e9 but values small →by value. For “weight exactly W” in (1)–(3) start with dp[0] = 0 and all others LLONG MIN and skip those.
Splitting an array into two parts with minimal difference = subset sum on half the total.
Time: O(nW) each; bounded O(W*sum(log cnt)); by value O(n*sum(val))
*/

// (1) 0/1: every item at most once, max value, weight <= W
int knapsack_01(vector<int>& wt, vector<int>& val, int W) {
  int n = wt.size();
  vector<int> dp(W + 1, 0);
  for (int i = 0; i < n; i++) {
    for (int w = W; w >= wt[i]; w--) {  // DOWN: used once
      dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
    }
  }
  return dp[W];
}
// (2) unbounded: every item any number of times
int knapsack_unbounded(vector<int>& wt, vector<int>& val, int W) {
  int n = wt.size();
  vector<int> dp(W + 1, 0);
  for (int i = 0; i < n; i++) {
    for (int w = wt[i]; w <= W; w++) {  // UP: reused
      dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
    }
  }
  return dp[W];
}
// (3) bounded: item i at most cnt[i] times. Split cnt[i]
// into packs of 1, 2, 4, ... and treat each pack as 0/1
int knapsack_bounded(vector<int>& wt, vector<int>& val, vector<int>& cnt, int W) {
  int n = wt.size();
  vector<int> dp(W + 1, 0);
  for (int i = 0; i < n; i++) {
    int left = cnt[i];
    for (int pack = 1; left > 0; pack *= 2) {
      int take = min(pack, left);
      left -= take;
      for (int w = W; w >= take * wt[i]; w--) {
        dp[w] = max(dp[w], dp[w - take * wt[i]] + take * val[i]);
      }
    }
  }
  return dp[W];
}
// (4) subset sum: can some items add up to exactly S
// faster: bitset<100001> b; b[0] = 1; b |= b << x; per x
bool subset_sum(vector<int>& a, int S) {
  vector<bool> dp(S + 1, false);
  dp[0] = true;
  for (int x : a) {
    for (int s = S; s >= x; s--) {
      if (dp[s - x]) dp[s] = true;
    }
  }
  return dp[S];
}
// (5a) number of subsets with sum exactly S (each item once)
int count_subsets(vector<int>& a, int S) {
  vector<int> dp(S + 1, 0);
  dp[0] = 1;
  for (int x : a) {
    for (int s = S; s >= x; s--) {
      dp[s] = (dp[s] + dp[s - x]) % MOD;
    }
  }
  return dp[S];
}
// (5b) ways to make S with unlimited coins, order ignored
// (1+2 and 2+1 are the same). If order MATTERS, swap the
// two loops: sum outside, coins inside
int coin_ways(vector<int>& coins, int S) {
  vector<int> dp(S + 1, 0);
  dp[0] = 1;
  for (int c : coins) {
    for (int s = c; s <= S; s++) {
      dp[s] = (dp[s] + dp[s - c]) % MOD;
    }
  }
  return dp[S];
}
// (6) fewest coins to make exactly S, -1 if impossible
int min_coins(vector<int>& coins, int S) {
  vector<int> dp(S + 1, LLONG_MAX);
  dp[0] = 0;
  for (int c : coins) {
    for (int s = c; s <= S; s++) {  // DOWN if each coin once
      if (dp[s - c] == LLONG_MAX) continue;
      dp[s] = min(dp[s], dp[s - c] + 1);
    }
  }
  return dp[S] == LLONG_MAX ? -1 : dp[S];
}
// (7) 0/1 when W is huge but values are small:
// dp[v] = smallest weight that gives value exactly v
int knapsack_by_value(vector<int>& wt, vector<int>& val, int W) {
  int n = wt.size(), total = 0;
  for (int v : val) total += v;
  vector<int> dp(total + 1, LLONG_MAX);
  dp[0] = 0;
  for (int i = 0; i < n; i++) {
    for (int v = total; v >= val[i]; v--) {
      if (dp[v - val[i]] == LLONG_MAX) continue;
      dp[v] = min(dp[v], dp[v - val[i]] + wt[i]);
    }
  }
  int best = 0;
  for (int v = 0; v <= total; v++) {
    if (dp[v] <= W) best = v;
  }
  return best;
}
