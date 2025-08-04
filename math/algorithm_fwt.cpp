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
using vm = vector<mint>;
using vvm = vector<vm>;

/* Cnm = n! / (m!*(n - m)!) */
void fwt_or(vector<mint> &f, mint g) // g=1, ig=-1
{
    int n = int(f.size());
    for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
        for (int i = 0; i < n; i += o)
            for (int j = 0; j < k; j++)
                f[i + j + k] += f[i + j] * g;
}
void fwt_and(vector<mint> &f, mint g) // g=1, ig=-1
{
    int n = int(f.size());
    for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
        for (int i = 0; i < n; i += o)
            for (int j = 0; j < k; j++)
                f[i + j] += f[i + j + k] * g;
}
void fwt_xor(vector<mint> &f, mint g) // g=1, ig=0.5
{
    int n = int(f.size());
    for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
        for (int i = 0; i < n; i += o)
            for (int j = 0; j < k; j++)
            {
                f[i + j] += f[i + j + k];
                f[i + j + k] = f[i + j] - f[i + j + k] - f[i + j + k];
                f[i + j] *= g, f[i + j + k] *= g;
            }
}
vector<mint> fwtconvolution(vector<mint> a, vector<mint> b, void (*op)(vector<mint> &, mint), mint g, mint ig)
{
    assert(a.size() == b.size());
    int n = int(a.size());
    assert((n & -n) == n);
    vector<mint> c(n);
    op(a, g), op(b, g);
    for (int i = 0; i < n; i++)
        c[i] = a[i] * b[i];
    op(c, ig);
    return c;
}