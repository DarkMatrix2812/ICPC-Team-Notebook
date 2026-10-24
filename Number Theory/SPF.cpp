/*
Description: Smallest-prime-factor sieve. primeFactors(n) returns the distinct primes of n ≤ N. Use to factorise many numbers quickly (spf[x] = x iff x is prime).
How it works: spf[x] = smallest prime dividing x. Dividing x by spf[x] again and again peels off its prime factors one at a time.
Modify / tips: to get exponents, count the iterations of the inner while; number of divisors = product(ei + 1), sum of divisors = product(p^(ei +1) −1)/(p−1).
Build once in main with N = largest value in the input.
Usage: buildSPF(N); auto pf = primeFactors(x);
Time: O(Nlog log N) build, O(log n) per query
*/

vector<int> spf;
void buildSPF(int N) {  // spf[i] = smallest prime of i
  spf.resize(N + 1);
  for (int i = 0; i <= N; i++) {
    spf[i] = i;
  }
  for (int i = 2; i * i <= N; i++) {
    if (spf[i] == i) {
      for (int j = i * i; j <= N; j += i) {
        if (spf[j] == j) {
          spf[j] = i;
        }
      }
    }
  }
}
vector<int> primeFactors(int n) {  // distinct primes of n
  vector<int> pf;
  while (n > 1) {
    int p = spf[n];
    pf.push_back(p);
    while (n % p == 0) {
      n /= p;
    }
  }
  return pf;
}
