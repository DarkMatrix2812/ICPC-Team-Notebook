/*
Description: Count the numbers in [L,R] whose digits satisfy a property, for Rup to 1e18 (the hint is a huge range plus a condition on digits).
Build the number digit by digit from the left. pos = digit being placed; state = the only thing you need to remember about the digits so far; tight = digits so far equal the prefix of N, so this digit cannot exceed N’s digit; started = a non-zero digit was already placed (false = still leading zeros). 
The example counts numbers whose digit sum is divisible by digit k. Other states: last digit (no two equal neighbours), count of some digit, number mod m (state * 10 + digit) % m, mask of used digits.
Usage: digit k = 7; int ans = count upto(R) - count upto(L - 1);
Time: O(digits·states·10)
*/

string digits;                     // decimal digits of N
int digit_k;                       // MODIFY: parameters of the property
vector<vector<vector<int>>> memo;  // [pos][state][started]
int digit_dp(int pos, int state, bool tight, bool started) {
  if (pos == (int)digits.size()) {
    // MODIFY: is the finished number good? (started is
    // false only for the number 0)
    return (started && state == 0) ? 1 : 0;
  }
  if (!tight && memo[pos][state][started] != -1) {
    return memo[pos][state][started];
  }
  int limit = tight ? digits[pos] - '0' : 9;
  int result = 0;
  for (int digit = 0; digit <= limit; digit++) {
    bool new_started = started || digit != 0;
    int new_state = state;
    if (new_started) {
      // MODIFY: how one more digit changes the state
      new_state = (state + digit) % digit_k;
    }
    // MODIFY: "continue;" here to forbid this digit
    result +=
        digit_dp(pos + 1, new_state, tight && digit == limit, new_started);
  }
  if (!tight) memo[pos][state][started] = result;
  return result;
}
int count_upto(int N) {  // good numbers in [1, N]
  if (N <= 0) return 0;
  digits = to_string(N);
  // MODIFY: digit_k = number of different states
  memo.assign(digits.size(), vector<vector<int>>(digit_k, vector<int>(2, -1)));
  return digit_dp(0, 0, true, false);
}
