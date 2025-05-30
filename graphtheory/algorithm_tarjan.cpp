#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> tarjan(auto &graph, bool hasdirection = false)
{
    int n = int(graph.size());
    vector<int> stk, low(n, -1);
    set<pair<int, int>> edge;
    vector<int> visstk(n);
    vector<vector<int>> ans;
    int dfn = 0;
    auto dfs = [&](auto self, int c) -> void
    {
        stk.push_back(c);
        visstk[c]++;
        int id = dfn++;
        low[c] = id;
        for (auto i : graph[c])
        {
            if (!hasdirection)
            {
                if (edge.count(minmax(i, c)))
                    continue;
                edge.emplace(minmax(i, c));
            }
            if (low[i] == -1)
                self(self, i);
            if (visstk[i])
                low[c] = min(low[c], low[i]);
        }
        if (low[c] == id)
        {
            ans.push_back(vector<int>());
            while (stk.back() != c)
            {
                ans.rbegin()->push_back(stk.back());
                visstk[stk.back()]--;
                stk.pop_back();
            }
            ans.rbegin()->push_back(stk.back());
            visstk[stk.back()]--;
            stk.pop_back();
        }
    };
    for (int i = 0; i < n; i++)
    {
        if (low[i] == -1)
        {
            dfn = 0;
            dfs(dfs, i);
        }
    }
    return ans;
}