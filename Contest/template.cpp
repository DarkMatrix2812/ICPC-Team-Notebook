/*
Description: Base file for every solution. int is long long, so use int32_t main. Globals in this notebook must be (re)assigned inside solve() for each test.
How it works: #define int long long turns every int into 64 bits, so sums and products up to about 9·1e18 are safe; that is why main must be written int32_t main. solve() runs once per test case.
Modify / tips: problem with a single test: delete the line cin >> tt; Memory limit hit by a huge array: declare that array as vector<int32_t>.
Answer modulo something: take % MOD after every multiplication and addition, and write ((x % MOD) + MOD) % MOD after a subtraction.
*/

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define int long long
using namespace std;
#define MOD 1000000007
#define MOD2 998244353
void solve() {
  // REMEMBER TO ASSIGN IF NEEDED!!!!!!
}
int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt = 1;
  cin >> tt;
  while (tt--) {
    solve();
  }
}
