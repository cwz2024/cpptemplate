#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count() ^ (uintptr_t)make_unique<char>().get());

int rndbase = rng() % 20240327 + 133;
const int mod = 1e9 + 7;

unsigned int pw[200006]; // 这个记得要初始化啊啊啊啊
int valh[26];            // 这个也要记得初始化啊啊啊啊
// 哈希过程为正着哈希，s[0]*p**0+s[1]*p**1+...+s[n-1]*p**(n-1)
struct seghash
{
    using T = unsigned int;

    int n;
    vector<T> s;
    vector<int> len;

public:
    seghash(int n) : n(n), s(2 * n, 0), len(2 * n, 1)
    {
        for (int i = n - 1; i > 0; --i)
            len[i] = len[i << 1] + len[i << 1 | 1];
    };
    seghash(const string &a) : n(int(size(a))), s(2 * n, 0), len(2 * n, 1)
    {
        for (int i = n - 1; i > 0; --i)
            len[i] = len[i << 1] + len[i << 1 | 1];
        for (int i = n; i < 2 * n; i++)
            s[i] = valh[a[i - n] - 'a'];
        for (int i = n - 1; i > 0; --i)
            s[i] = T((s[i << 1] + s[i << 1 | 1] * 1ll * pw[len[i << 1]]) % mod);
    };
    void set(int i, char val) // s[i] := val
    {
        for (s[i += n] = valh[val - 'a']; i >>= 1;)
            s[i] = T((s[i << 1] + s[i << 1 | 1] * 1ll * pw[len[i << 1]]) % mod);
    }
    T query(int l, int r) // for [l,r)
    {
        T la = 0, ra = 0;
        int lenl = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
            {
                la = T((la + s[l] * 1ll * pw[lenl]) % mod);
                lenl += len[l];
                l++;
            }
            if (r & 1)
            {
                --r;
                ra = T((s[r] + ra * 1ll * pw[len[r]]) % mod);
            }
        }
        return T((la + ra * 1ll * pw[lenl]) % mod);
    }
};