#include <bits/stdc++.h>
using namespace std;
using ll = long long;
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
    friend istream &operator>>(istream &i, mint &a) { return i >> a._v; }
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

int main(void)
{
    ll n;
    cin >> n;
    ll sq = sqrt(n);
    vector<bool> is_prime(sq + 1, true);
    vector<int> primes = {1};
    vector<mint> sump1 = {0}, sump2 = {0};
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= sq; ++i)
    {
        if (is_prime[i])
        {
            primes.push_back(i);
            sump1.push_back(sump1.back() + i);
            sump2.push_back(sump2.back() + 1ll * i * i);
            for (ll j = (ll)i * i; j <= sq; j += i)
            {
                is_prime[j] = false;
            }
        }
    }
    int m = primes.size() - 1;
    vector<ll> values;
    vector<int> id1(sq + 2), id2(sq + 2);
    for (ll l = 1, r; l <= n; l = r + 1)
    {
        r = n / (n / l), values.push_back(n / l);
        if (values.back() <= sq)
            id1[values.back()] = values.size() - 1;
        else
            id2[n / values.back()] = values.size() - 1;
    }
    auto get = [&](ll v) -> int
    {
        if (v <= sq)
            return id1[v];
        else
            return id2[n / v];
    };

    vector<mint> g1(values.size()), g2(g1);
    mint i2 = mint(2).inv(), i6 = mint(6).inv();
    for (int i = 0; i < values.size(); ++i)
    {
        g1[i] = mint(values[i]) * (values[i] + 1) * i2 - 1;
        g2[i] = mint(values[i]) * (values[i] + 1) * (2 * values[i] + 1) * i6 - 1;
    }
    for (int j = 0; j < m; j++)
    {
        ll p = primes[j + 1];
        for (int i = 0; i < values.size(); i++)
        {
            if (values[i] < p * p)
                break;
            ll t = values[i] / p;
            int pos = get(t);
            g1[i] -= (g1[pos] - sump1[j]) * p;
            g2[i] -= (g2[pos] - sump2[j]) * p * p;
        }
    }
    auto S = [&](auto self, ll n, int j) -> mint
    {
        if (primes[j] >= n)
            return 0;
        mint ans = g2[get(n)] - g1[get(n)] - (sump2[j] - sump1[j]);
        for (int i = j + 1; i <= m; i++)
        {
            ll p = primes[i];
            if (n < p * p)
                break;
            for (int e = 1; p <= n; p *= primes[i], e++)
            {
                ans += mint(p) * (p - 1) * (self(self, n / p, i) + (e > 1));
            }
        }
        return ans;
    };
    cout << S(S, n, 0) + 1;
    return 0;
}