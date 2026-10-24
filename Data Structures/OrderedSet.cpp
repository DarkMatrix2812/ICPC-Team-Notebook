/*
Description: GNU policy tree (PBDS) = a set that also answers “how many elements are smaller than x” and “what is the k-th smallest” in O(log n). Use for inversion counts, rank / k-th queries with insertions and deletions, sliding-window medians. With this using, do not name a variable tree.
Time: O(log n) per operation
*/

// put these 3 lines right after #include <bits/stdc++.h>
// (BEFORE #define int long long)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
// put the typedefs after #define int long long
typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_set;
// ordered_set s; (no duplicates, like set<int>)
// s.insert(x); s.erase(x); s.size(); s.find(x);
// s.order_of_key(x); number of elements < x
// *s.find_by_order(k); k-th smallest, k starts from 0
// (only valid when k < s.size())
// s.lower_bound(x), s.upper_bound(x) work like in set
// duplicates: store {value, unique id}
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_multiset;
// ordered_multiset ms; int id = 0;
// ms.insert({x, id++});
// ms.order_of_key({x, 0}); elements < x
// ms.order_of_key({x, LLONG_MAX}); elements <= x
// ms.find_by_order(k)->first; k-th smallest value
// erase ONE copy of x:
// auto it = ms.lower_bound({x, 0});
// if (it != ms.end() && it->first == x) ms.erase(it);
