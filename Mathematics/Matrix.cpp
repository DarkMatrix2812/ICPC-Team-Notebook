/*
Description: Matrix product and fast power mod MOD. Use for linear recurrences (Fibonacci-like, k-term DP transitions) and counting walks of length exp in a graph.
How it works: if every new value is a fixed linear mix of the previous few values, write one step as (new vector) = T·(old vector). Then ksteps are Tk , computed by squaring like binExp. Fibonacci: T= {{1,1},{1,0}} and Fk = Tk [0][1].
Modify / tips: row iof T says how new element i is built from the old elements. For fn = afn−1 + bfn−2 + cuse the vector (fn−1 ,fn−2 ,1) and T= {{a,b,c},{1,0,0},{0,0,1}}. Number of walks of length k from u to v = (adjacency matrix)k [u][v]. Keep the size ≤100.
Usage: auto R = matrixExp(T, k);
Time: O(n^3) multiply, O(n^3 * log(exp)) power
*/

vector<vector<int>> identityMatrix(int n) {  // n x n identity
  vector<vector<int>> I(n, vector<int>(n, 0));
  for (int i = 0; i < n; i++) I[i][i] = 1;
  return I;
}
vector<vector<int>> matrixMultiply(vector<vector<int>> &A, vector<vector<int>> &B) {  // A * B mod MOD
  int n = A.size(), m = B[0].size(), K = A[0].size();
  vector<vector<int>> product(n, vector<int>(m, 0));
  for (int i = 0; i < n; i++) {
    for (int k = 0; k < K; k++) {
      if (A[i][k] == 0) continue;
      for (int j = 0; j < m; j++) {
        product[i][j] = (product[i][j] + A[i][k] * B[k][j]) % MOD;
      }
    }
  }
  return product;
}
vector<vector<int>> matrixExp(vector<vector<int>> base, int exp) {  // base^
  exp mod MOD vector<vector<int>> result = identityMatrix(base.size());
  while (exp > 0) {
    if (exp & 1) result = matrixMultiply(result, base);
    base = matrixMultiply(base, base);
    exp >>= 1;
  }
  return result;
}
