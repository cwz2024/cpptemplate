#include <bits/stdc++.h>
using namespace std;

pair<vector<int>, vector<int>> manacher(string &s)
{
    int n = int(s.size());
    vector<int> d1(n), d2(n - 1);
    int l = 0, r = -1;
    int ans = 1;
    for (int i = 0; i < n; i++)
    {
        if (i > r)
        {
            for (int pl = i, pr = i; pl >= 0 && pr < n; pl--, pr++)
            {
                if (s[pl] == s[pr])
                    d1[i]++, l = pl, r = pr;
                else
                    break;
            }
            d1[i]--;
        }
        else
        {
            int rev = l + r - i;
            if (d1[rev] + i < r)
                d1[i] = d1[rev];
            else
            {
                d1[i] = r - i;
                for (int pl = i - d1[i] - 1, pr = r + 1; pl >= 0 && pr < n; pl--, pr++)
                {
                    if (s[pl] == s[pr])
                        d1[i]++, l = pl, r = pr;
                    else
                        break;
                }
            }
        }
        ans = max(ans, 2 * d1[i] + 1);
    }
    l = 0, r = -1;
    for (int i = 0; i < n - 1; i++)
    {
        if (i >= r)
        {
            for (int pl = i, pr = i + 1; pl >= 0 && pr < n; pl--, pr++)
            {
                if (s[pl] == s[pr])
                    d2[i]++, l = pl, r = pr;
                else
                    break;
            }
        }
        else
        {
            int rev = l + r - i - 1;
            if (d2[rev] + i < r)
                d2[i] = d2[rev];
            else
            {
                d2[i] = r - i;
                for (int pl = i - d2[i], pr = r + 1; pl >= 0 && pr < n; pl--, pr++)
                {
                    if (s[pl] == s[pr])
                        d2[i]++, l = pl, r = pr;
                    else
                        break;
                }
            }
        }
        ans = max(ans, 2 * d2[i]);
    }
    return {d1, d2};
}