#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
pair<string, string> hackpoorhash() // mod为2^n（自然溢出）
{
    const int Q = 11;
    const int N = 1 << Q;
    std::string S(N, ' '), T(N, ' ');

    for (int i = 0; i < N; i++)
        S[i] = 'a' + __builtin_popcount(i) % 2;
    for (int i = 0; i < N; i++)
        T[i] = 'b' - __builtin_popcount(i) % 2;
    return make_pair(S, T);
}
vector<string> hackSlightlyStrongerHash(int l, ull hash(string))
{
    auto rand_str = [](int l)
    {
        string s;
        while (l--)
        {
            s += rng() % 26 + 'a';
        }
        return s;
    };
    int k = 200410;
    map<ull, vector<string>> c;
    while (k--)
    {
        auto s = rand_str(l);
        ull h = hash(s);
        c[h].push_back(s);
    }
    int cnt = 1;
    vector<string> h;
    for (auto i : c)
    {
        if (i.second.size() > cnt)
        {
            cnt = i.second.size();
            h = i.second;
        }
    }
    if (cnt == 1)
        cerr << "fail to find, try again!" << endl;
    return h;
}