/*
Description: Euler’s totient φ(n) = count of 1 ≤k ≤n coprime to n. getPhi for one large n, buildPhi for all n ≤N. Use for a^φ(m) ≡1, exponent reduction, counting coprime pairs / gcd sums.
How it works: φ(n) = n * product(1−1/p) over the distinct primes p of n; each result -= result / p applies one factor.
Modify / tips: summation(φ(d)) such that d|n = n; the count of k ≤n with gcd(k,n) = g is φ(n/g). Power towers: reduce the exponent mod φ(M).
Time: O(√n) single, O(Nlog log N) sieve
*/

int getPhi(int n) {  // phi of one n
  int result = n;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      while (n % i == 0) n /= i;
      result -= result / i;  // multiply by (1 - 1/i)
    }
  }
  if (n > 1) result -= result / n;
  return result;
}
vector<int> phi_arr;
void buildPhi(int N) {  // phi_arr[i] for all i <= N
  phi_arr.resize(N + 1);
  for (int i = 0; i <= N; i++) {
    phi_arr[i] = i;
  }
  for (int i = 2; i <= N; i++) {
    if (phi_arr[i] == i) {
      // i is a prime number
      for (int j = i; j <= N; j += i) {
        phi_arr[j] -= phi_arr[j] / i;
      }
    }
  }
}
