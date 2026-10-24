/*
Description: Exact primality test for one number up to 1e18 , far beyond the sieve (1e7) and trial division (1e12 , slow). Use when the input has huge numbers and asks “is it prime”, “next prime after n” (test n+ 1,n+ 2,...; gaps are small), or when there are many queries on numbers around 1e9..1e12
How it works: write n−1 = odd·2r . For a prime nand any base a, the sequence a^odd ,a^2·odd,... must start with 1 or hit n−1 before reaching 1. A composite n fails this for some base; the 12 fixed bases below are proven enough for every 64-bit number, so the answer is always correct.
Products are done in int128 because n^2 overflows 64 bits.
Time: O(12 log n) per number
*/

int mul_mod(int a, int b, int M) {  // a * b % M, no overflow
  return (__int128)a * b % M;
}
int pow_mod(int base, int exp, int M) {  // base^
  exp % M int result = 1;
  base %= M;
  while (exp > 0) {
    if (exp % 2 == 1) result = mul_mod(result, base, M);
    base = mul_mod(base, base, M);
    exp /= 2;
  }
  return result;
}
bool is_prime(int n) {
  if (n < 2) return false;
  vector<int> bases = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
  for (int p : bases) {  // small primes settle small n
    if (n % p == 0) return n == p;
  }
  int odd = n - 1, r = 0;
  while (odd % 2 == 0) {  // n - 1 = odd * 2^r
    odd /= 2;
    r++;
  }
  for (int a : bases) {
    int x = pow_mod(a, odd, n);
    if (x == 1 || x == n - 1) continue;  // passes this base
    bool composite = true;
    for (int i = 1; i < r; i++) {
      x = mul_mod(x, x, n);
      if (x == n - 1) {
        composite = false;
        break;
      }
    }
    if (composite) return false;  // a proves n is not prime
  }
  return true;
}
