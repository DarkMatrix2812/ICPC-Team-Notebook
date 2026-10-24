/*
Description: Factorials and inverse factorials mod prime M, giving nCr and nPr in O(1). Use for any counting problem; needs N <M. Requires binExp.
How it works: nCr = n! / (r! (n−r)!) . Division mod M is multiplication by an inverse, so store inverse factorials: one binExp gives invfact[N], then invfact[i] = invfact[i+1] * (i+1).
Modify / tips: call build fact once in main with the largest n(2·e5 or 1e6 ), not per test. Formulas: split nequal items into k boxes = (n+k−1) C (k−1); grid paths right/down = (r+c) C r ; Catalan = 2nCn /(n+ 1); arrangements with repeats = n!/(c1 ! c2 !···).
Usage: build fact(N, MOD); nCr(n, r, MOD);
Time: O(N+ log M) build, O(1) per query
*/

vector<int> fact, invfact;
void build_fact(int N, int M) {  // fact[], invfact[] up to N
  fact = vector<int>(N + 1, 0);
  invfact = vector<int>(N + 1, 0);
  fact[0] = 1;
  for (int i = 1; i <= N; i++) {
    fact[i] = fact[i - 1] * i % M;
  }
  invfact[N] = binExp(fact[N], M - 2, M);  // 1 / N!
  for (int i = N - 1; i >= 0; i--) {
    invfact[i] = invfact[i + 1] * (i + 1) % M;
  }
}
int nCr(int n, int r, int M) {  // choose r of n, order ignored
  if (r < 0 || r > n) return 0;
  return fact[n] * invfact[r] % M * invfact[n - r] % M;
}
int nPr(int n, int r, int M) {  // arrange r of n, order matters
  if (r < 0 || r > n) return 0;
  return fact[n] * invfact[n - r] % M;
}
