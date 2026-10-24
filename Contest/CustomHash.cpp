/*
Description: Hash for unordered map / unordered set. Needed in two situations: (a) the key is a pair – C++ has no built-in hash for pairs, so it does not even compile without one; (b) keys are integers and the tests are built to break the default hash, which turns every operation into O(n) and gives TLE. When neither speed nor (a) matters, a plain map / set is always safe and needs nothing: it works with pairs, vectors and strings as keys in O(log n).
How it works: the key is added to a number taken from the clock when the program starts (nobody can predict it) and then scrambled by splitmix64, so no prepared input can make many keys collide.
Modify / tips: for a key with three numbers scramble them one after another like the pair version. For vector / string keys use map.
Usage: unordered map<int, int, custom hash> mp;
Time: O(1) average per operation
*/

const uint64_t HASH_SEED =
    chrono::steady_clock::now().time_since_epoch().count();
struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {  // scrambles bits
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  size_t operator()(uint64_t x) const {  // integer keys
    return splitmix64(x + HASH_SEED);
  }
  size_t operator()(const pair<int, int>& p) const {  // pairs
    uint64_t h = splitmix64(p.first + HASH_SEED);
    return splitmix64(h + p.second);
  }
};
// unordered_map<int, int, custom_hash> mp;
// unordered_map<pair<int,int>, int, custom_hash> cell;
// unordered_set<pair<int,int>, custom_hash> seen;
// mp.reserve(1 << 20); optional: avoids slow regrowing
// if (mp.count(x)) ... check a key WITHOUT creating it
// (mp[x] creates the key with 0)
