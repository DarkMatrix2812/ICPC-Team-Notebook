/*
Description: All divisors of n by trial division, unsorted. Use to enumerate divisors of a single number up to about 1e12
How it works: divisors come in pairs (i,n/i) with i≤√n.
Modify / tips: call sort on the result if order matters. For all numbers up to N at once use a harmonic loop: for i in 1..N, for j = i, 2i, .. : divs[j].push back(i) in O(Nlog N).
Time: O(√n)
*/

vector<int> factors(int n) {  // all divisors, unsorted
  vector<int> f;
  for (int i = 1; i * i <= n; i++) {
    if (n % i == 0) {
      f.push_back(i);
      if (i != n / i) f.push_back(n / i);
    }
  }
  return f;
}
