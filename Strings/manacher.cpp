/* 
Description: Longest palindrome around every centre in O(n). Works on t = s with '#' between and around the characters and sentinels '^' '$' at the ends (t has 2|s| + 3 characters). 
p[i] = length of the longest palindrome of s centred at t[i]: odd length if t[i] is a letter, even length if t[i] is '#'. 
It starts at index (i - p[i]) / 2 of s. Use for longest palindromic substring, counting palindromic substrings, and O(1) "is s[l..r] a palindrome" queries. 
How it works: keep the palindrome that reaches furthest right (centre C, right end R). For a new centre i inside it, the mirror position 2C - i has the same radius (cut at R - i), so expanding starts from there. R only moves right, so all expansions together cost O(n).
Modify / tips: longest palindrome: i = argmax p[i], answer is s.substr((i - p[i]) / 2, p[i]). 
Number of palindromic substrings = sum of (p[i] + 1) / 2. 
s[l..r] (0-indexed) is a palindrome iff p[l + r + 2] >= r - l + 1. 
The characters '^', '#', '$' must not appear in s, else change the sentinels.
Time: O(n)
*/

vector<int> manacher(string s) { // p[] on t
    if (s.empty()) return {};
    string t = "^";
    for (char c : s) {
        t += '#';
        t += c;
    }
    t += "#$";
    int n = t.size();
    vector<int> p(n, 0);
    int C = 0, R = 0; // rightmost palindrome: centre, end
    for (int i = 1; i < n - 1; i++) {
        if (R > i) p[i] = min(R - i, p[2 * C - i]); // mirror
        while (t[i + 1 + p[i]] == t[i - 1 - p[i]]) p[i]++;
        if (i + p[i] > R) {
            C = i;
            R = i + p[i];
        }
    }
    return p;
}
