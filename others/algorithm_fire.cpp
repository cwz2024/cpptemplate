#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll fire(auto f, ll start, int e) // min of f(x)
{
    static mt19937 rnd(random_device{}());
    static uniform_real_distribution<double> rng(0, 1);
    const double T = 1e7, Tk = 1e-2;
    const double delta = 0.9995;
    double t = T;
    ll cur = start;
    ll ans = e;
    while (t > Tk)
    {
        ll tmp = cur + (2 * rng(rnd) - 1) * t;
        ll val = f(tmp);
        ll d = val - ans;
        if (exp(-d / (t * 1e-3)) > rng(rnd))
        {
            ans = val;
            cur = tmp;
        }
        t *= delta;
    }
    return ans;
}