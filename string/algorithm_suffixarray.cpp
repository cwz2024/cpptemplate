#include <bits/stdc++.h>
using namespace std;

vector<int> suffix_array(const string &s)
{
    int n = int(s.size());
    vector<int> sa(n), rnk(n), tmp(n), buck(128);
    copy(s.begin(), s.end(), rnk.begin());
    for (int i = 0; i < n; i++)
    {
        buck[rnk[i]]++;
    }
    for (int i = 1; i < 128; i++)
    {
        buck[i] += buck[i - 1];
    }
    for (int i = n - 1; i >= 0; i--)
    {
        sa[--buck[rnk[i]]] = i;
    }
    int base = *max_element(rnk.begin(), rnk.end()) + 1;
    for (int k = 1; k < n; k *= 2)
    {
        auto cmp = [&](int x, int y)
        {
            if (rnk[x] != rnk[y])
                return rnk[x] < rnk[y];
            int rx = x + k < n ? rnk[x + k] : -1;
            int ry = y + k < n ? rnk[y + k] : -1;
            return rx < ry;
        };
        vector<int> bucket(base);
        tmp = sa;
        int p = 0;
        for (int i = n - k; i < n; i++)
        {
            sa[p++] = i;
        }
        for (int i = 0; i < n; i++)
        {
            if (tmp[i] >= k)
                sa[p++] = tmp[i] - k;
        }
        tmp = sa;
        for (int i = 0; i < n; i++)
        {
            bucket[rnk[tmp[i]]]++;
        }
        for (int i = 1; i < base; i++)
        {
            bucket[i] += bucket[i - 1];
        }
        for (int i = n - 1; i >= 0; i--)
        {
            sa[--bucket[rnk[tmp[i]]]] = tmp[i];
        }
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++)
        {
            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        }
        base = tmp[sa[n - 1]] + 1;
        if (base == n)
            break;
        swap(tmp, rnk);
    }
    return sa;
}
vector<int> lcp_array(const string &s, const vector<int> &sa)
{
    int n = int(s.size());
    assert(n >= 1);
    vector<int> rnk(n);
    for (int i = 0; i < n; i++)
    {
        rnk[sa[i]] = i;
    }
    vector<int> lcp(n - 1);
    int h = 0;
    for (int i = 0; i < n; i++)
    {
        if (h > 0)
            h--;
        if (rnk[i] == 0)
            continue;
        int j = sa[rnk[i] - 1];
        for (; j + h < n && i + h < n; h++)
        {
            if (s[j + h] != s[i + h])
                break;
        }
        lcp[rnk[i] - 1] = h;
    }
    return lcp;
}