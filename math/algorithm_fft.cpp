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

vector<mint> convolution(vector<mint> a, vector<mint> b) // ntt
{
    int n = int(size(a) + size(b)), lg = 0;
    while (1 << lg < n)
        lg++;
    n = 1 << lg;
    a.resize(n);
    b.resize(n);
    vector<mint> p(n);
    ntt(a, G), ntt(b, G);
    for (int i = 0; i < n; i++)
    {
        p[i] = a[i] * b[i];
    }
    ntt(p, Gi);
    mint inv = mint(1) / n;
    for (int i = 0; i < n; i++)
        p[i] *= inv;
    return p;
}
vector<mint> poly_inv(vector<mint> a)
{
    int n = int(a.size()), lg = 0;
    while (1 << lg < n)
        lg++;
    a.resize(1 << lg);
    vector<mint> ans = {a[0].inv()};
    while (ans.size() < a.size())
    {
        ans.resize(2 * ans.size());
        vector<mint> b = ans;
        b.resize(ans.size() * 2);
        vector<mint> f(ans.size() * 2);
        copy(a.begin(), a.begin() + ans.size(), f.begin());
        ntt(b, G), ntt(f, G);
        for (int i = 0; i < int(b.size()); i++)
            b[i] *= b[i] * f[i];
        ntt(b, Gi);
        mint inv = mint(b.size()).inv();
        for (int i = 0; i < int(ans.size()); i++)
            ans[i] = 2 * ans[i] - b[i] * inv;
    }
    ans.resize(n);
    return ans;
}
pair<vector<mint>, vector<mint>> poly_div(vector<mint> lhs, vector<mint> rhs) // {div, mod}
{
    int n = int(lhs.size()), m = int(rhs.size());
    vector<mint> fr(lhs.rbegin(), lhs.rend()), gr(rhs.rbegin(), rhs.rend());
    fr.resize(n - m + 2);
    gr.resize(n - m + 2);
    vector<mint> qr = convolution(fr, poly_inv(gr));
    qr.resize(n - m + 1);
    reverse(qr.begin(), qr.end());
    vector<mint> b = convolution(qr, rhs);
    vector<mint> rem(m - 1);
    for (int i = 0; i < m - 1; i++)
        rem[i] = lhs[i] - b[i];
    return {qr, rem};
}
vector<mint> poly_ln(vector<mint> a)
{
    vector<mint> da(a.size());
    for (int i = 0; i < (int)a.size() - 1; i++)
        da[i] = (i + 1) * a[i + 1];
    vector<mint> dlna = convolution(da, poly_inv(a));
    dlna.resize(a.size());
    for (int i = (int)a.size() - 1; i > 0; i--)
        dlna[i] = dlna[i - 1] / i;
    dlna[0] = 0;
    return dlna;
}
vector<mint> poly_exp(vector<mint> a)
{
    vector<mint> ans = {1, 0};
    while (ans.size() / 2 < a.size())
    {
        vector<mint> b = poly_ln(ans);
        for (int i = 0; i < (int)ans.size(); i++)
            if (i < (int)a.size())
                b[i] = a[i] - b[i];
            else
                b[i] = -b[i];
        b[0]++;
        ans = convolution(b, ans);
    }
    ans.resize(a.size());
    return ans;
}
vector<mint> poly_multiget(vector<mint> poly, vector<mint> x)
{
    int m = int(x.size()), mx = (int)max(poly.size(), x.size()), lg = 0;
    while (1 << lg < mx)
        lg++;
    x.resize(mx);
    vector<vector<mint>> g(1 << (lg + 1));
    auto init = [&](auto self, int l, int r, int node) -> void
    {
        if (r - l == 1)
        {
            g[node] = {-x[l], 1};
            return;
        }
        int mid = (l + r) >> 1;
        self(self, l, mid, node << 1);
        self(self, mid, r, node << 1 | 1);
        g[node] = convolution(g[node << 1], g[node << 1 | 1]);
        while (g[node].back() == 0)
            g[node].pop_back();
    };
    init(init, 0, mx, 1);
    vector<mint> ans(m);
    auto solve = [&](auto self, vector<mint> poly, int l, int r, int node) -> void
    {
        if (r - l == 1)
        {
            ans[l] = poly[0];
            return;
        }
        int mid = (l + r) >> 1;
        vector<mint> f0 = poly_div(poly, g[node << 1]).second;
        self(self, f0, l, mid, node << 1);
        if (mid < m)
        {
            f0 = poly_div(poly, g[node << 1 | 1]).second;
            self(self, f0, mid, r, node << 1 | 1);
        }
    };
    solve(solve, poly, 0, mx, 1);
    return ans;
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