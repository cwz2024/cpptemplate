#include <bits/stdc++.h>
using namespace std;

size_t kmp(string s, string sub)
{
    int n = int(s.size()), m = int(sub.size());
    if (n < m)
        return string::npos;
    vector<int> nxt(m + 1);
    s = '#' + s, sub = '#' + sub;
    for (int i = 2, j = 0; i <= m; i++)
    {
        while (j && sub[j + 1] != sub[i])
            j = nxt[j];
        if (sub[j + 1] == sub[i])
            j++;
        nxt[i] = j;
    }
    for (int i = 0, j = 0; i < n; i++)
    {
        while (j && sub[j + 1] != s[i + 1])
            j = nxt[j];

        if (sub[j + 1] == s[i + 1])
            j++;

        if (j == m)
            return i - m + 1;
    }
    return string::npos;
}
int kmps(string s, string sub)
{
    int n = size(s), m = size(sub);
    int sum = 0;
    vector<int> nxt(m);
    nxt[0] = -1;
    for (int i = 1; i < m; i++)
    {
        int k = nxt[i - 1];
        while (k != -1 && sub[i - 1] != sub[k])
            k = nxt[k];
        nxt[i] = k + 1;
    }
    int i = 0, j = 0;
    while (i < n)
    {
        while (j != -1 && sub[j] != s[i])
        {
            j = nxt[j];
        }
        ++i, ++j;
        if (j == m)
        {
            sum++;
            j = 0;
        }
    }
    return sum;
}