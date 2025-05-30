#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<long long>;
using vvi = vector<vi>;
using vvll = vector<vll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

pair<vi, vll> dijk(vector<vector<pii>> &graph, int start)
{
    int n = int(graph.size());
    vll len(n, 1e18);
    len[start] = 0;
    vi path(n, -1);
    int flag = 1, s = start;
    using node = pair<long long, int>;
    priority_queue<node, vector<node>, greater<node>> prior;
    while (flag)
    {
        flag = 0;
        for (auto p : graph[s])
        {
            ll t = len[s] + p.second;
            int pos = p.first;
            if (len[pos] > t)
            {
                len[pos] = t;
                prior.emplace(t, pos);
                path[pos] = s;
            }
        }
        while (!prior.empty())
        {
            if (prior.top().first == len[prior.top().second])
                break;
            prior.pop();
        }

        if (!prior.empty())
        {
            flag = 1;
            s = prior.top().second;
            prior.pop();
        }
    }
    return pair<vi, vll>(path, len);
}