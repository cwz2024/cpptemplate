#include <bits/stdc++.h>
using namespace std;

template <class B, class Bl>
struct lazy_segtree : public B, Bl
{
private:
    using T = typename B::T;
    using A = typename Bl::A;
    int n, h;
    vector<T> s;
    vector<A> d;

    void push(int p, int w)
    {
        if (p < n && d[p] != Bl::e)
        {
            upd(p << 1, d[p], w >> 1);
            upd(p << 1 | 1, d[p], w >> 1);
            d[p] = Bl::e;
        }
    }
    void upd(int p, A val, int w)
    {
        Bl::upd(s[p], val, w);
        if (p < n)
            d[p] = Bl::op(d[p], val);
    }
    T query(int l, int r, int node, int w)
    {
        push(node, w);
        if (r <= 0 || w <= l)
            return B::e;
        if (l <= 0 && w <= r)
            return s[node];
        w >>= 1;
        return B::op(query(l, r, 2 * node, w), query(l - w, r - w, 2 * node + 1, w));
    }
    void apply(int l, int r, A val, int node, int w)
    {
        push(node, w);
        if (r <= 0 || w <= l)
            return;
        if (l <= 0 && w <= r)
        {
            d[node] = Bl::op(d[node], val);
            Bl::upd(s[node], val, w);
            push(node, w);
        }
        else
        {
            w >>= 1;
            apply(l, r, val, node << 1, w);
            apply(l - w, r - w, val, node << 1 | 1, w);
            s[node] = B::op(s[node << 1], s[node << 1 | 1]);
        }
    }

public:
    lazy_segtree() = default;
    lazy_segtree(int _n) : n(1 << (__lg(_n)) << (1 << (__lg(_n)) < _n)), h(__lg(2 * n)), s(2 * n, B::e), d(2 * n) {};
    lazy_segtree(const vector<T> &a) : n(1 << (__lg(size(a))) << (1 << (__lg(size(a))) < (int)size(a))), h(__lg(2 * n)), s(2 * n, B::e), d(2 * n, Bl::e)
    {
        copy(a.begin(), a.end(), s.begin() + n);
        for (int i = n - 1; i > 0; --i)
            s[i] = B::op(s[i << 1], s[i << 1 | 1]);
    };
    void apply(int l, int r, A val) // for[l,r)
    {
        apply(l, r, val, 1, n);
    }
    T query(int l, int r) // for[l,r)
    {
        return query(l, r, 1, n);
    }
};
struct barrett
{
    unsigned int _m;
    unsigned long long im;

    // @param m `1 <= m`
    explicit barrett(unsigned int m) : _m(m), im((unsigned long long)(-1) / m + 1) {}

    friend unsigned int operator%(unsigned long long z, barrett &m)
    {
        unsigned long long x =
            (unsigned long long)(((unsigned __int128)(z)*m.im) >> 64);

        unsigned long long y = x * m._m;
        return (unsigned int)(z - y + (z < y ? m._m : 0));
    }
};
int mod;
barrett bm(1);
struct AddModInt
{
    using T = int;
    T e = 0;
    T op(T a, T b)
    {
        return a + b >= mod ? a + b - mod : a + b;
    }
};
struct AddModLazy
{
    using A = int;
    A e = 0;
    void upd(AddModInt::T &_, const A l, int w)
    {
        _ += 1ll * l * w % bm;
        if (_ >= mod)
            _ -= mod;
    }
    A op(A a, A b)
    {
        return a + b >= mod ? a + b - mod : a + b;
    }
};

struct heavy_light_decomposion
{
    using dstype = lazy_segtree<AddModInt, AddModLazy>;
    heavy_light_decomposion(vector<vector<int>> &tree, int root = 0)
        : _n((int)tree.size()), top(_n), hson(_n, -1), dfn(_n), rnk(_n),
          dep(_n), pa(_n, -1), bottom(_n)
    {
        auto dfs_1 = [&](auto self, int c, int p) -> int
        {
            int usize = 1, mx = 0;
            if (c != p)
                dep[c] = dep[p] + 1, pa[c] = p;
            for (auto i : tree[c])
            {
                if (i == p)
                    continue;
                int s = self(self, i, c);
                if (s > mx)
                    mx = s, hson[c] = i;
                usize += s;
            }
            return usize;
        };
        dfs_1(dfs_1, root, root);
        int cnt = 0;
        auto dfs_2 = [&](auto self, int c, int p, int tp) -> void
        {
            top[c] = tp;
            dfn[c] = cnt;
            rnk[cnt++] = c;
            if (hson[c] != -1)
            {
                self(self, hson[c], c, tp);
            }
            for (auto i : tree[c])
            {
                if (i == p || i == hson[c])
                    continue;
                self(self, i, c, i);
            }
            bottom[c] = cnt;
        };

        dfs_2(dfs_2, root, root, root);
    }

    void init(vector<int> &w)
    {
        seg = dstype(trans(w));
    }

    void apply(int u, int v, int val) // path
    {
        while (top[u] != top[v])
        {
            if (dep[top[u]] > dep[top[v]])
            {
                seg.apply(dfn[top[u]], dfn[u] + 1, val);
                u = pa[top[u]];
            }
            else
            {
                seg.apply(dfn[top[v]], dfn[v] + 1, val);
                v = pa[top[v]];
            }
        }
        if (dfn[u] > dfn[v])
            seg.apply(dfn[v], dfn[u] + 1, val);
        else
            seg.apply(dfn[u], dfn[v] + 1, val);
    }

    void apply(int root, int val) // subtree
    {
        seg.apply(dfn[root], bottom[root], val);
    }

    int query(int u, int v) // path
    {
        int ans = 0;
        while (top[u] != top[v])
        {
            if (dep[top[u]] > dep[top[v]])
            {
                ans += seg.query(dfn[top[u]], dfn[u] + 1);
                if (ans >= mod)
                    ans -= mod;
                u = pa[top[u]];
            }
            else
            {
                ans += seg.query(dfn[top[v]], dfn[v] + 1);
                if (ans >= mod)
                    ans -= mod;
                v = pa[top[v]];
            }
        }
        if (dfn[u] > dfn[v])
            ans += seg.query(dfn[v], dfn[u] + 1);
        else
            ans += seg.query(dfn[u], dfn[v] + 1);
        if (ans >= mod)
            ans -= mod;
        return ans;
    }

    int query(int root) // subtree
    {
        return seg.query(dfn[root], bottom[root]);
    }

    int lca(int u, int v)
    {
        while (top[u] != top[v])
        {
            if (dep[top[u]] > dep[top[v]])
                u = pa[top[u]];
            else
                v = pa[top[v]];
        }
        return dep[u] > dep[v] ? v : u;
    }

private:
    int _n;
    vector<int> top, hson, dfn, rnk, dep, pa, bottom;
    dstype seg;
    vector<int> trans(vector<int> &w)
    {
        assert(w.size() == _n);
        vector<int> ans(w.size());
        for (int i = 0; i < _n; i++)
        {
            ans[i] = w[rnk[i]];
        }
        return ans;
    }
};