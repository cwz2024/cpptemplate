#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
struct mint // from ac-library
{
private:
    unsigned int _v;

public:
    mint &operator++()
    {
        _v++;
        if (_v == mod)
            _v = 0;
        return *this;
    }
    mint &operator--()
    {
        if (_v == 0)
            _v = mod;
        _v--;
        return *this;
    }
    mint operator++(int)
    {
        mint result = *this;
        ++*this;
        return result;
    }
    mint operator--(int)
    {
        mint result = *this;
        --*this;
        return result;
    }

    mint &operator+=(const mint &rhs)
    {
        _v += rhs._v;
        if (_v >= mod)
            _v -= mod;
        return *this;
    }
    mint &operator-=(const mint &rhs)
    {
        _v -= rhs._v;
        if (_v >= mod)
            _v += mod;
        return *this;
    }
    mint &operator*=(const mint &rhs)
    {
        unsigned long long z = _v;
        z *= rhs._v;
        _v = (unsigned int)(z % mod);
        return *this;
    }
    mint &operator/=(const mint &rhs) { return *this = *this * rhs.inv(); }

    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }

    mint pow(long long n) const
    {
        assert(0 <= n);
        mint x = *this, r = 1;
        while (n)
        {
            if (n & 1)
                r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    mint inv() const { return pow(mod - 2); }

    friend mint operator+(const mint &a, const mint &b) { return mint(a) += b; }
    friend mint operator-(const mint &a, const mint &b) { return mint(a) -= b; }
    friend mint operator*(const mint &a, const mint &b) { return mint(a) *= b; }
    friend mint operator/(const mint &a, const mint &b) { return mint(a) /= b; }
    friend bool operator==(const mint &a, const mint &b) { return a._v == b._v; }
    friend bool operator!=(const mint &a, const mint &b) { return a._v != b._v; }
    friend ostream &operator<<(ostream &i, mint a) { return i << a.val(); }
    friend istream &operator>>(istream &i, mint &a)
    {
        long long v;
        istream &ans = i >> v;
        long long x = (long long)(v % (long long)(mod));
        if (x < 0)
            x += mod;
        a._v = (unsigned int)(x);
        return ans;
    }
    unsigned int val() const { return _v; }
    mint() : _v(0) {}
    template <class T>
    mint(T v)
    {
        long long x = (long long)(v % (long long)(mod));
        if (x < 0)
            x += mod;
        _v = (unsigned int)(x);
    }
};

void ntt(vector<mint> &p, mint g)
{
    int n = (int)size(p), lg = __lg(n) - 1;
    if (n == 1)
        return;
    vector<int> r(n);
    for (int i = 0; i < n; i++)
    {
        r[i] = r[i >> 1] >> 1 | ((i & 1) << lg);
        if (i < r[i])
            swap(p[i], p[r[i]]);
    }
    for (int wid = 2; wid <= n; wid <<= 1)
    {
        mint w = g.pow((mod - 1) / wid);
        for (int l = 0; l < n; l += wid)
        {
            mint wi = 1;
            for (int i = l; i < l + wid / 2; i++, wi *= w)
            {
                mint x = p[i], y = p[i + wid / 2];
                p[i] = x + wi * y;
                p[i + wid / 2] = x - wi * y;
            }
        }
    }
}

vector<int> fft_match(string s, string sub) // 有通配符，sub在s的各个位置能否匹配
{
    int m = int(sub.size()), n = int(s.size());
    if (m > n)
        return vector<int>(n);
    int len = 1 << (__lg(n) + 1);
    const char match_all = '*';
    reverse(sub.begin(), sub.end());
    vector<int> aa(m), bb(n);
    for (int i = 0; i < m; i++)
        aa[i] = sub[i] == match_all ? 0 : sub[i] - 'a' + 2;
    for (int i = 0; i < n; i++)
        bb[i] = s[i] == match_all ? 0 : s[i] - 'a' + 2;
    vector<mint> f(len), g(len), p(len);
    for (int i = 0; i < m; i++)
        f[i] = aa[i];
    for (int i = 0; i < n; i++)
        g[i] = bb[i] * bb[i] * bb[i];
    ntt(f, 3), ntt(g, 3);
    for (int i = 0; i < len; i++)
        p[i] += f[i] * g[i];
    fill(f.begin(), f.end(), mint()), fill(g.begin(), g.end(), mint());
    for (int i = 0; i < m; i++)
        f[i] = aa[i] * aa[i] * aa[i];
    for (int i = 0; i < n; i++)
        g[i] = bb[i];
    ntt(f, 3), ntt(g, 3);
    for (int i = 0; i < len; i++)
        p[i] += f[i] * g[i];
    fill(f.begin(), f.end(), mint()), fill(g.begin(), g.end(), mint());
    for (int i = 0; i < m; i++)
        f[i] = aa[i] * aa[i];
    for (int i = 0; i < n; i++)
        g[i] = bb[i] * bb[i];
    ntt(f, 3), ntt(g, 3);
    for (int i = 0; i < len; i++)
        p[i] -= f[i] * g[i], p[i] -= f[i] * g[i];
    ntt(p, mint(3).inv());
    vector<int> ans(n);
    for (int i = 0; i < n - m + 1; i++)
        ans[i] = p[i + m - 1] == 0;
    return ans;
}