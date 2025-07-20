#include <bits/stdc++.h>
using namespace std;
struct dsu
{
private:
    int _n;
    vector<int> _parent, _s, _dep;

public:
    int parentof(int a)
    {
        assert(a < _n && a >= 0);
        int d = 1;
        while (_parent[a] != a)
        {
            a = _parent[a];
            _dep[a] = max(_dep[a], ++d);
        }
        return a;
    }
    int merge(int a, int b)
    {
        int p1 = parentof(a);
        int p2 = parentof(b);
        if (p1 == p2)
            return 0;
        if (_dep[p1] < _dep[p2])
        {
            _s[p2] += _s[p1];
            _parent[p1] = p2;
        }
        else
        {
            if (_dep[p1] == _dep[p2])
                _dep[p1]++;
            _s[p1] += _s[p2];
            _parent[p2] = p1;
        }
        return 1;
    }
    int size(int a) { return _s[parentof(a)]; }
    bool same(int a, int b) { return parentof(a) == parentof(b); }
    vector<vector<int>> groups()
    {
        vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++)
        {
            leader_buf[i] = parentof(i);
            group_size[leader_buf[i]]++;
        }
        vector<vector<int>> result(_n);
        for (int i = 0; i < _n; i++)
        {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++)
        {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(remove_if(result.begin(), result.end(),
                               [&](const std::vector<int> &v)
                               { return v.empty(); }),
                     result.end());
        return result;
    }
    dsu(int n) : _n(n), _parent(n), _s(n, 1), _dep(n, 1)
    {
        iota(_parent.begin(), _parent.end(), 0);
    }
};
struct wdsu
{
    using ll = long long;

private:
    int _n;
    vector<int> _parent;
    vector<ll> dist;

public:
    int parentof(int a)
    {
        assert(a < _n && a >= 0);
        if (_parent[a] == a)
            return a;
        int lst = _parent[a];
        _parent[a] = parentof(_parent[a]);
        dist[a] += dist[lst];
        return _parent[a];
    }
    int merge(int a, int b, ll v)
    {
        int p1 = parentof(a);
        int p2 = parentof(b);
        if (p1 == p2)
            return 0;
        _parent[p1] = p2;
        dist[p1] = -dist[a] + dist[b] + v;
        return 1;
    }
    bool same(int a, int b) { return parentof(a) == parentof(b); }
    ll get_dist(int a, int b)
    {
        assert(same(a, b));
        return dist[a] - dist[b];
    }
    vector<vector<int>> groups()
    {
        vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++)
        {
            leader_buf[i] = parentof(i);
            group_size[leader_buf[i]]++;
        }
        vector<vector<int>> result(_n);
        for (int i = 0; i < _n; i++)
        {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++)
        {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(remove_if(result.begin(), result.end(),
                               [&](const std::vector<int> &v)
                               { return v.empty(); }),
                     result.end());
        return result;
    }
    wdsu(int n) : _n(n), _parent(n), dist(n)
    {
        iota(_parent.begin(), _parent.end(), 0);
    }
};