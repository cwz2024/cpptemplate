#include <bits/stdc++.h>
using namespace std;

bool Miller_Rabin(int a, int n)
{
    using T = int;
    using LT = long long;
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
bool isprime(int n)
{
    if (n == 2 || n == 3 || n == 7 || n == 61)
        return true;
    if (n == 1)
        return false;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    int a[] = {2, 7, 61};
    for (auto i : a)
    {
        if (!Miller_Rabin(i, n))
            return false;
    }
    return true;
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