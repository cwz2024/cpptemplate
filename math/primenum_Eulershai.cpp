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