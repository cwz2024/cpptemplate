#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

ll Pollard_Rho(ll x)
{
    ll t = 0;
    ll c = rng() % (x - 1) + 1;
    ll s = t;
    ll step = 0, goal = 1;
    ll val = 1;
    for (goal = 1;; goal <<= 1, s = t, val = 1)
    {
        for (step = 1; step <= goal; ++step)
        {
            t = ll((i128(t) * t + c) % x);
            val = ll((i128)val * abs(t - s) % x);
            // 如果 val 为 0，退出重新分解
            if (!val)
                return x;
            if (step % 127 == 0)
            {
                ll d = gcd(val, x);
                if (d > 1)
                    return d;
            }
        }
        ll d = gcd(val, x);
        if (d > 1)
            return d;
    }
}
bool Miller_Rabin(long long a, long long n)
{
    using T = long long;
    using LT = __int128;
    T u = n - 1;
    while (!(u & 1))
        u >>= 1;
    T v = 1, _base = a, _n = u;
    while (_n)
    {
        if (_n & 1)
            v = T(v * (LT)_base % n);
        _base = T((LT)_base * _base % n);
        _n >>= 1;
    }
    if (v == 1)
        return 1;
    while (u <= n - 1)
    {
        if (v == n - 1)
            return 1;
        if (v == 1)
            return 0;
        v = T((LT)v * v % n);
        u *= 2;
    }
    return 0;
}
bool isprime(long long n)
{
    if (n == 2 || n == 3 || n == 5)
        return true;
    if (n == 1)
        return false;
    if (n % 2 == 0 || n % 3 == 0 || n % 5 == 0)
        return false;
    long long a[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    for (auto i : a)
    {
        if (i % n == 0)
            continue;
        if (!Miller_Rabin(i, n))
            return false;
    }
    return true;
}
vector<ll> pfactor(ll n)
{
    vector<ll> ans;
    if (n == 1)
        return ans;
    ll p = n;
    if (isprime(n))
    {
        ans.push_back(n);
        return ans;
    }
    else
    {
        while (p == n)
            p = Pollard_Rho(n);
    }
    auto v1 = pfactor(n / p), v2 = pfactor(p);
    for (auto i : v1)
        ans.push_back(i);
    for (auto i : v2)
        ans.push_back(i);
    return ans;
}
vector<ll> facs(vector<ll> pfac)
{
    vector<ll> ans = {1};
    sort(pfac.begin(), pfac.end());
    vector<pair<ll, int>> cnt;
    ll lst = -1;
    for (auto i : pfac)
    {
        if (i != lst)
        {
            lst = i;
            cnt.push_back({i, 1});
        }
        else
        {
            cnt.rbegin()->second++;
        }
    }
    for (auto [p, c] : cnt)
    {
        vector<ll> v(c);
        v[0] = p;
        for (int i = 1; i < c; ++i)
        {
            v[i] = v[i - 1] * p;
        }
        int siz = int(ans.size());
        for (auto f : v)
        {
            for (int i = 0; i < siz; ++i)
            {
                ans.push_back(ans[i] * f);
            }
        }
    }
    return ans;
}