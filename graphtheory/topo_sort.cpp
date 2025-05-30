#include <bits/stdc++.h>
using namespace std;

pair<vector<int>, bool> topo_sort(vector<vector<int>> &graph)
{
    int n = int(graph.size());
    vector<int> a, in(n);
    vector<bool> vis(n);
    for (int i = 0; i < n; i++)
    {
        for (auto j : graph[i])
        {
            in[j]++;
        }
    }
    queue<int> qu;
    for (int i = 0; i < n; i++)
    {
        if (in[i] == 0)
            qu.push(i);
    }
    while (qu.size())
    {
        int p = qu.front();
        qu.pop();
        if (vis[p])
            break;
        vis[p] = 1;
        a.push_back(p);
        for (auto j : graph[p])
        {
            if (--in[j] == 0)
                qu.push(j);
        }
    }
    return {a, a.size() == n};
}