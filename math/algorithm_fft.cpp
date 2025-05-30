#include <bits/stdc++.h>
using namespace std;

void fft(vector<complex<double>> &p, int g = 1)
{
    assert(g == 1 || g == -1);
    int n = (int)size(p), lg = __lg(n) - 1;
    if (n == 1)
        return;
    const double pi = acos(-1);
    vector<int> r(n);
    for (int i = 0; i < n; i++)
    {
        r[i] = r[i >> 1] >> 1 | ((i & 1) << lg);
        if (i < r[i])
            swap(p[i], p[r[i]]);
    }
    for (int wid = 2; wid <= n; wid <<= 1)
    {
        complex<double> w(cos(2 * pi / wid * g), sin(2 * pi / wid * g));
        for (int l = 0; l < n; l += wid)
        {
            complex<double> wi = 1;
            for (int i = l; i < l + wid / 2; i++, wi *= w)
            {
                complex<double> x = p[i], y = p[i + wid / 2];
                p[i] = x + wi * y;
                p[i + wid / 2] = x - wi * y;
            }
        }
    }
}

const int mod = 998244353;
struct mint
{
private:
    int _v;

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
        mint a = *this;
        ++*this;
        return a;
    }
    mint operator--(int)
    {
        mint a = *this;
        --*this;
        return a;
    }
    mint operator+() { return *this; }
    mint operator+(mint a) { return mint(_v + a._v); }
    mint operator+=(mint a)
    {
        _v = (_v + a._v) % mod;
        return *this;
    }
    mint operator-() { return mint() - *this; }
    mint operator-(mint a) { return mint(_v - a._v); }
    mint operator-=(mint a)
    {
        _v = (_v - a._v + mod) % mod;
        return *this;
    }
    mint operator*(mint a) { return mint(1ll * _v * a._v % mod); }
    mint operator*=(mint a)
    {
        _v = int((1ll * _v * a._v) % mod);
        return *this;
    }
    mint operator^(long long n)
    {
        mint ans = 1, base = _v;
        while (n)
        {
            if (n & 1)
                ans *= base;
            base *= base;
            n >>= 1;
        }
        return ans;
    }
    mint operator^=(long long n)
    {
        _v = operator^(n)._v;
        return *this;
    }
    mint operator/(mint a) { return operator*(a ^ (mod - 2)); }
    mint operator/=(mint a)
    {
        _v = operator*(a ^ (mod - 2))._v;
        return *this;
    }
    bool operator==(mint a) { return _v == a._v; }
    bool operator!=(mint a) { return _v != a._v; }
    friend ostream &operator<<(ostream &i, mint a) { return i << a.val(); }
    friend istream &operator>>(istream &i, mint &a) { return i >> a._v; }
    int val() { return _v; }
    mint() { _v = 0; }
    mint(int a) { _v = (a % mod + mod) % mod; }
    mint(long long a) { _v = int((a % mod + mod) % mod); }
};
const mint G = 3, Gi = mint(1) / G;

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
        mint w = g ^ ((mod - 1) / wid);
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

vector<int> convolution(vector<int> &a, vector<int> &b) // ntt
{
    int n = int(size(a) + size(b)), lg = 0;
    while (1 << lg < n)
    {
        lg++;
    }
    n = 1 << lg;
    vector<mint> pa(n), pb(n), p(n);
    for (int i = 0; i < (int)size(a); i++)
    {
        pa[i] = a[i];
    }
    for (int i = 0; i < (int)size(b); i++)
    {
        pb[i] = b[i];
    }
    ntt(pa, G), ntt(pb, G);
    for (int i = 0; i < n; i++)
    {
        p[i] = pa[i] * pb[i];
    }
    ntt(p, Gi);
    mint inv = mint(1) / n;
    for (int i = 0; i < n; i++)
        p[i] *= inv;
    vector<int> y(n);
    for (int i = 0; i < n; i++)
    {
        y[i] = p[i].val();
    }
    while (y.back() == 0)
    {
        y.pop_back();
    }
    return y;
}

vector<int> dumbconvolution(vector<int> &a, vector<int> &b) // fft
{
    int n = int(size(a) + size(b)), lg = 0;
    while (1 << lg < n)
    {
        lg++;
    }
    n = 1 << lg;
    vector<complex<double>> p(n);
    for (int i = 0; i < n; i++)
    {
        p[i] = {double(i < int(size(a)) ? a[i] : 0), double(i < int(size(b)) ? b[i] : 0)};
    }

    fft(p);
    for (int i = 0; i < n; i++)
    {
        p[i] *= p[i];
    }
    fft(p, -1);

    vector<int> y(n);
    for (int i = 0; i < n; i++)
    {
        y[i] = (int)round(p[i].imag() / (2 * n));
    }
    while (y.back() == 0)
    {
        y.pop_back();
    }
    return y;
}

struct barrett
{
    unsigned int _m;
    unsigned long long im;

    // @param m `1 <= m`
    explicit barrett(unsigned int m) : _m(m), im((unsigned long long)(-1) / m + 1) {}

    friend unsigned int operator%(unsigned long long z, barrett m)
    {
        unsigned long long x =
            (unsigned long long)(((unsigned __int128)(z)*m.im) >> 64);

        unsigned long long y = x * m._m;
        return (unsigned int)(z - y + (z < y ? m._m : 0));
    }
};
vector<int> convolution_p(vector<int> a, vector<int> b, int p)
{
    using ll = long long;
    barrett pmod(p); // 可以用，用处不大
    int len = int(a.size() + b.size() - 1), anssize = len;
    if ((len & -len) != len)
    {
        len = 1 << (__lg(len) + 1);
    }
    a.resize(len), b.resize(len);
    vector<complex<double>> P1(len), P2(len), Q(len); // 改成 long double
    for (int i = 0; i < len; ++i)
    {
        P1[i] = {a[i] >> 15, a[i] & 0x7fff};
        P2[i] = {a[i] >> 15, -(a[i] & 0x7fff)};
        Q[i] = {b[i] >> 15, b[i] & 0x7fff};
    }
    fft(P1), fft(Q), fft(P2);
    for (int i = 0; i < len; ++i)
    {
        P1[i] *= Q[i];
        P2[i] *= Q[i];
    }
    fft(P1, -1), fft(P2, -1);
    for (int i = 0; i < len; ++i)
    {
        P1[i] /= len;
        P2[i] /= len;
    }
    const int p30 = 1 << 30, p15 = 1 << 15;
    vector<int> ans(len);
    for (int i = 0; i < len; ++i)
    {
        auto c1 = P1[i] + P2[i], c2 = P2[i] - P1[i];
        ll a1b1 = ll(c1.real() / 2 + 0.49) % pmod;
        ll a1b2 = ll(c1.imag() / 2 + 0.49) % pmod;
        ll a2b1 = (ll(P1[i].imag() + 0.49) - a1b2) % pmod;
        ll a2b2 = (ll(P2[i].real() + 0.49) - a1b1) % pmod;
        a1b1 = (a1b1 * p30 % pmod);
        a1b2 = (a1b2 * p15 % pmod);
        a2b1 = (a2b1 * p15 % pmod);
        ans[i] = int((a1b1 + a1b2 + a2b1 + a2b2) % pmod);
    }
    ans.resize(anssize);
    return ans;
}