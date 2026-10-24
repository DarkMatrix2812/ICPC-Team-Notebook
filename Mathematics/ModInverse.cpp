/*
Description: Modular inverse by extended Euclid. Works for any modulus (not only primes); returns−1 when gcd(a,M) ̸= 1. Use when M is composite or unknown.
How it works: runs Euclid’s algorithm on (a,M) while tracking a number u with a·u ≡(current remainder) mod M; when the remainder reaches 1, u is the inverse.
Modify / tips: to divide under a modulus multiply by the inverse: x * modinv(a, M) % M. An inverse exists only if gcd(a,M) = 1.
Time: O(log M)
*/

int modinv(int a, int M) {  // a^-1 mod M, -1 if none
  int b = M, u = 1, v = 0;
  while (b) {
    int t = a / b;
    a -= t * b;
    swap(a, b);
    u -= t * v;
    swap(u, v);
  }
  u %= M;
  if (u < 0) u += M;
  return u;
  if (a != 1) return -1;  // gcd != 1: no inverse
}
