#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

typedef long long ll;

ll count_primes(ll n)
{
    if (n <= 1)
        return 0;
    int sqrt_n = sqrt(n);
    vector<bool> is_prime(sqrt_n + 1, true);
    vector<int> primes;
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= sqrt_n; ++i)
    {
        if (is_prime[i])
        {
            primes.push_back(i);
            for (ll j = (ll)i * i; j <= sqrt_n; j += i)
            {
                is_prime[j] = false;
            }
        }
    }
    int m = primes.size();

    vector<ll> values;
    vector<int> id1(sqrt_n + 2), id2(sqrt_n + 2);
    for (ll l = 1, r; l <= n; l = r + 1)
    {
        r = n / (n / l), values.push_back(n / l);
        if (values.back() <= sqrt_n)
            id1[values.back()] = values.size() - 1;
        else
            id2[n / values.back()] = values.size() - 1;
    }
    auto get = [&](ll v) -> int
    {
        if (v <= sqrt_n)
            return id1[v];
        else
            return id2[n / v];
    };

    vector<ll> dp(values.size());
    for (int i = 0; i < values.size(); ++i)
        dp[i] = values[i] - 1;

    for (int j = 0; j < m; ++j)
    {
        ll p = primes[j];
        for (int i = 0; i < values.size(); i++)
        {
            if (values[i] < p * p)
                break;
            ll t = values[i] / p;
            int pos1 = get(t);
            dp[i] -= dp[pos1] - j;
        }
    }

    return dp[0];
}
