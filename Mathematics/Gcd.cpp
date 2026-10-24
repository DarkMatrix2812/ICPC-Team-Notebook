/*
Description: Euclid’s gcd and overflow-safe lcm (divides before multiplying). Use for fraction reduction, periods, divisibility arguments.
How it works: gcd(a,b) = gcd(b,amod b) until b= 0.
Modify / tips: lcm can overflow when the answer exceeds 9·1e18 ; cap it if the problem only needs “> limit”. gcd of a whole array: fold g = gcd(g, a[i]) starting from 0.
Time: O(log min(a,b))
*/

int gcd(int a, int b) {  // greatest common divisor
  return (!b ? a : gcd(b, a % b));
}
int lcm(int a, int b) {  // least common multiple
  return a / gcd(a, b) * b;
}
