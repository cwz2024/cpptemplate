#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <class T>
ll merge_sort(T first, T last)
{
    int len = int(last - first);
    T mid = first + (last - first) / 2;
    if (len == 1)
        return 0;
    ll ans = 0;
    if (len > 2)
    {
        ans += merge_sort(first, mid);
        ans += merge_sort(mid, last);
    }
    vector arr_l(first, mid), arr_r(mid, last);
    int i, j, k;
    for (i = 0, j = 0, k = 0; i < int(arr_l.size()) && j < int(arr_r.size()); k++)
    {
        if (arr_l[i] <= arr_r[j])
            *(first + k) = arr_l[i++];
        else
            *(first + k) = arr_r[j++], ans += arr_l.size() - i;
    }
    while (i < int(arr_l.size()))
        *(first + k++) = arr_l[i++];
    while (j < int(arr_r.size()))
        *(first + k++) = arr_r[j++];
    return ans;
}