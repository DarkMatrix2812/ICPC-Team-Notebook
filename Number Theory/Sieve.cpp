/*
Description: Sieve of Eratosthenes; prime[i] is true iff i is prime. Use when you only need primality of all numbers up to n (n≤1e7 or so).
How it works: every composite number has a prime factor ≤√n, sofor each prime p cross out its multiples starting from p^2
Modify / tips: to get the list of primes, loop over the result and push every i with prime[i]. Build it once in main, not per test.
Time: O(nlog log n)
*/

vector<bool> sieve(int n) {  // prime[i] = is i prime
  vector<bool> prime(n + 1, true);
  prime[0] = prime[1] = false;
  for (int p = 2; p * p <= n; ++p) {
    if (prime[p] == true) {
      for (int i = p * p; i <= n; i += p)  // multiples of p
        prime[i] = false;
    }
  }
  return prime;
}
