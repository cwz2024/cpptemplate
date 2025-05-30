#include <bits/stdc++.h>

using namespace std;

struct fenwick_tree
{
    using T = int;
    using U = unsigned int;

public:
    fenwick_tree() : _n(0) {}
    explicit fenwick_tree(int n) : _n(n), data(n) {}

    void add(int p, T x)
    {
        assert(0 <= p && p < _n);
        p++;
        while (p <= _n)
        {
            data[p - 1] += U(x);
            p += p & -p;
        }
    }

    T sum(int l, int r)
    {
        assert(0 <= l && l <= r && r <= _n);
        return sum(r) - sum(l);
    }

private:
    int _n;
    vector<U> data;

    U sum(int r)
    {
        U s = 0;
        while (r > 0)
        {
            s += data[r - 1];
            r -= r & -r;
        }
        return s;
    }
};