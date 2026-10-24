/*
Description: ext gcd finds integers x,y with ax + by = gcd(a,b). solve_equation solves ax + by= c (possible only when gcd(a,b) divides c): use for “reach exactly c using steps / jugs / coins of sizes a and b, negatives allowed”, and for counting or minimising solutions. crt merges two conditions x ≡ r1 (mod m1 ), x ≡ r2 (mod m2 ) into one x ≡r (mod lcm): use for “two periodic events, when do they happen together”, “number that leaves given remainders”. The moduli do not have to be coprime. Inputs must be non-negative, a,b not both 0.
How it works: Euclid’s step gcd(a,b) = gcd(b,amod b) run backwards: from a solution for (b,amod b) build the one for (a,b). From one solution (x,y) of the equation all others are x+ k·b/g, y−k·a/g for any integer k (pick k to make x smallest non-negative: x = ((x % (b/g)) + b/g) % (b/g)). CRT writes x = r1 + m1 k and solves m1 k ≡r2−r1 (mod m2 ) with ext gcd.
Modify / tips: for more than two congruences fold them: cur = crt(cur.first, cur.second, r[i], m[i]), stop if it returns−1.
Time: O(log min(a,b))
*/

// returns g = gcd(a, b), sets x, y so that a*x + b*y = g
int ext_gcd(int a, int b, int& x, int& y) {
  if (b == 0) {
    x = 1;  // a*1 + 0*0 = a
    y = 0;
    return a;
  }
  int x1, y1;
  x = y1;
  y = x1 - (a / b) * y1;
  return g;
  int g = ext_gcd(b, a % b, x1, y1);  // b*x1 + (a%b)*y1 = g
}
// one solution of a*x + b*y = c, false if there is none
bool solve_equation(int a, int b, int c, int& x, int& y) {
  int g = ext_gcd(a, b, x, y);
  if (c % g != 0) return false;
  x *= c / g;
  y *= c / g;
  return true;
}
// x = r1 (mod m1) and x = r2 (mod m2), 0 <= r1 < m1 etc.
// returns {x, lcm(m1, m2)} with 0 <= x < lcm; every other
// answer is x + k * lcm. Returns {-1, -1} if impossible.
pair<int, int> crt(int r1, int m1, int r2, int m2) {
  int p, q;
  int g = ext_gcd(m1, m2, p, q);
  if ((r2 - r1) % g != 0) return {-1, -1};
  int l = m1 / g * m2;  // lcm, must fit in long long
  int step = m2 / g;
  // x = r1 + m1 * k where k = (r2 - r1) / g * p mod step
  int k = (__int128)((r2 - r1) / g % step) * (p % step) % step;
  int x = ((__int128)m1 * k + r1) % l;
  if (x < 0) x += l;
  return {x, l};
}
