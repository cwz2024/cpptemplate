#include <bits/stdc++.h>
using namespace std;
int num_coprime(int n, int max) // O(log n sqrt n)
{
    vector<int> p;
    for (int j = 2; j * j <= n; j++)
    {
        if (n % j == 0)
        {
            p.push_back(j);
            while (n % j == 0)
            {
                n /= j;
            }
        }
    }
    if (n != 1)
    {
        p.push_back(n);
    }
    int sz = p.size(), cnt = 0;
    for (int mask = 0; mask < 1 << sz; mask++)
    {
        int base = 1;
        for (int k = 0; k < sz; k++)
        {
            if (mask >> k & 1)
            {
                base *= p[k];
            }
        }
        if (__builtin_popcount(mask) % 2 == 1)
        {
            cnt -= max / base;
        }
        else
        {
            cnt += max / base;
        }
    }
    return cnt;
}
int get_phi(int n) // O(sqrt n)
{
    int phi = n, i;
    for (i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            while (n % i == 0)
                n /= i;
            phi -= phi / i;
        }
    }
    if (n > 1)
        phi -= phi / n;
    return phi;
}

#define N 10000007
vector<int> pri;
bool not_prime[N];
int phi[N];

void pre(int n)
{
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (!not_prime[i])
        {
            pri.push_back(i);
            phi[i] = i - 1;
        }
        for (int pri_j : pri)
        {
            if (i * pri_j > n)
                break;
            not_prime[i * pri_j] = true;
            if (i % pri_j == 0)
            {
                phi[i * pri_j] = phi[i] * pri_j;
                break;
            }
            phi[i * pri_j] = phi[i] * phi[pri_j];
        }
    }
}