#include <bits/stdc++.h>
using namespace std;
auto RANDSEED = chrono::steady_clock::now().time_since_epoch().count() ^ (uintptr_t)make_unique<char>().get();

struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        return splitmix64(x + RANDSEED);
    }
};
template <class T>
using uset = unordered_set<T, custom_hash>;
template <class T, class S>
using umap = unordered_map<T, S, custom_hash>;