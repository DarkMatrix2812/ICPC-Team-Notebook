/*
Description: 64-bit builtins and single-bit operations. Use for bitmask DP, subset iteration, finding the lowest/highest set bit. clz/ctz are un- defined for x= 0.
How it works: a set of up to 62 items is stored in one number: bit i is 1 when item i is in the set. All subsets of n items are the numbers 0..2n −1: for (int mask = 0; mask < (1LL << n); mask++).
Modify / tips: always write 1LL << k, never 1 << k (overflows for k ≥31). XOR facts: x⊕x = 0, a prefix-XOR array gives the XOR of a range like prefix sums.
*/

// number of 1-bits in x
__builtin_popcountll(x);
// 1 if popcount is odd, 0 if even
__builtin_parityll(x);
// count leading zeros in 64-bit
__builtin_clzll(x);  // x != 0
// count trailing zeros (use: lowest set bit, bit iteration)
__builtin_ctzll(x);  // x != 0
// index of highest 1-bit (use: power of 2 <= x)
int msb = 63 - __builtin_clzll(x);
// index of lowest 1-bit
int lsb = __builtin_ctzll(x);
// check if power of two
(x > 0 && (x & (x - 1)) == 0);
// check k-th bit
(x >> k) & 1;
// set k-th bit
x | (1LL << k);
// toggle k-th bit
x ^ (1LL << k);
// clear k-th bit
x & ~(1LL << k);
