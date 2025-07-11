#include <bits/stdc++.h>
using namespace std;
vector<int> primearr(int n) // max value
{
    vector<int> arr;
    vector<int> p(n + 1, 0);
    int i, j;
    for (i = 2; i <= n; i++)
    {
        if (!p[i])
        {
            arr.push_back(i);
        }
        j = i;
        for (auto i : arr)
        {
            if (j * i > n)
                break;
            p[j * i] = 1;
            if (j % i == 0)
                break;
        }
    }
    return arr;
}
vector<int> min_p_n(int n) // max value
{
    vector<int> arr;
    vector<int> p(n + 1, 0); // min prime div for i
    int i, j;
    for (i = 2; i <= n; i++)
    {
        if (!p[i])
        {
            arr.push_back(i);
            p[i] = i;
        }
        j = i;
        for (auto i : arr)
        {
            if (j * i > n)
                break;
            p[j * i] = i;
            if (j % i == 0)
                break;
        }
    }
    return p;
}
vector<long long> big_primearr(long long l, long long r)
{
    int n = int(sqrt(r)) + 3;
    vector<bool> p(n + 1), bigp(r - l + 1);
    for (int i = 2; i <= n; i++)
    {
        if (p[i])
            continue;
        for (int j = 2 * i; j <= n; j += i)
            p[j] = 1;
        for (long long j = (l + i - 1) / i * i; j <= r; j += i)
            bigp[j - l] = 1;
    }
    vector<long long> arr;
    for (long long j = l; j <= r; j++)
    {
        if (!bigp[j - l])
            arr.push_back(j);
    }
    return arr;
}