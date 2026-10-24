/*
Description: Binary exponentiation, baseexp mod M. Use for modular powers and for inverses under a prime modulus: a^−1 = a^(M−2) . Needs base<M and M2 to fit in 64 bits.
How it works: write exp in binary. base becomes base1 ,base2 ,base4 ,base8  ,... by squaring; multiply it into the result whenever the current bit of exp is 1.
Modify / tips: division under a prime modulus: x/a≡x·binExp(a, M - 2, M). For M near 1018 use pow mod from MillerRabin. Huge exponent b^c : reduce it as binExp(a, binExp(b, c, M - 1), M) (M prime).
Time: O(log exp)
*/

int binExp(int base, int exp, int M) {  // base^
  exp % M int result = 1;
  while (exp > 0) {
    if (exp % 2 == 1) result = (result * base) % M;
    base = (base * base) % M;  // next power of two
    exp /= 2;
  }
  return result;
}
