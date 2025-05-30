#include <bits/stdc++.h>
using namespace std;

vector<int> anti_unorder(int n, int cpp_version, int mx = 1e9)
{
    int mod;
    if (cpp_version == 20)
        mod = 85229; // 2357
    else if (cpp_version == 17)
        mod = 107897; // 3209
    else
        mod = 126271; // 3739
    auto nxt = [&]() -> int
    {
        static int e = 114514;
        e += mod;
        if (e >= mx)
            e = e % mod + 1;
        return e;
    };
    vector<int> a(n);
    generate(a.begin(), a.end(), nxt);
    return a;
}