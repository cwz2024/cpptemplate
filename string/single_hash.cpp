#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count() ^ (uintptr_t)make_unique<char>().get());
int randbase = int(rng() % 20240327);
const int base = randbase + 131;
const int hmod = 1e9 + 7;
struct Hash
{
    vector<int> pw, pre;
    int val(void) { return pre.back(); }
    int val(int l, int r) // 从0开始，[l,r)
    {
        int ans = int(pre[r] + hmod - 1ll * pre[l] * pw[r - l] % hmod);
        if (ans >= hmod)
            ans -= hmod;
        return ans;
    }
    size_t size() { return pw.size() - 1; }
    void extend(const string &s)
    {
        int n = int(pw.size()), m = int(s.size());
        pw.resize(n + m);
        pre.resize(n + m);
        for (int i = n; i < n + m; ++i)
        {
            pw[i] = int(1ll * pw[i - 1] * base % hmod);
            pre[i] = int((1ll * pre[i - 1] * base + s[i - n]) % hmod);
        }
    }
    Hash(const string &s) : pw(s.size() + 1), pre(s.size() + 1)
    {
        pw[0] = 1;
        for (int i = 1; i <= int(s.size()); ++i)
        {
            pw[i] = int(1ll * pw[i - 1] * base % hmod);
            pre[i] = int((1ll * pre[i - 1] * base + s[i - 1]) % hmod);
        }
    }
    Hash() : pw(1), pre(1) { pw[0] = 1; }
};