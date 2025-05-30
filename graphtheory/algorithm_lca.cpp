#include <bits/stdc++.h>
using namespace std;
struct LCA
{
    LCA(vector<vector<int>> &tree, int root) : n(int(tree.size())), lg(__lg(n) + 1), a(n), dfn(n), log(n + 1), s(lg, vector<int>(n, -1))
    {
        int id = 0;
        auto dfs = [&](auto self, int c, int p) -> void
        {
            dfn[c] = id;
            s[0][id++] = p;
            for (auto i : tree[c])
            {
                if (i == p)
                    continue;
                self(self, i, c);
            }
        };
        dfs(dfs, root, root);
        for (int i = 1; i < lg; i++)
        {
            for (int j = 0; j + (1 << (i - 1)) < n; j++)
            {
                s[i][j] = op(s[i - 1][j], s[i - 1][j + (1 << (i - 1))]);
            }
        }
        log[0] = -1;
        for (int i = 1; i <= n; i++)
        {
            log[i] = log[i >> 1] + 1;
        }
    }
    int query(int node1, int node2)
    {
        if (node1 == node2)
            return node1;
        int l = dfn[node1], r = dfn[node2];
        if (l > r)
            swap(l, r);
        r++, l++;
        int k = log[r - l];
        return op(s[k][l], s[k][r - (1 << k)]);
    }

private:
    int n, lg;
    vector<int> a, dfn, log;
    vector<vector<int>> s;
    int op(int a, int b)
    {
        if (a == -1 || b == -1)
            return a + b + 1;
        if (dfn[a] < dfn[b])
            return a;
        else
            return b;
    }
};

struct lca
{
public:
    lca(vector<vector<int>> &tree, int root) : n(int(tree.size())), lg(__lg(n) + 1), dep(n), ansestor(n, vector<int>(lg))
    {
        auto dfs = [&](auto self, int c, int p) -> void
        {
            if (c != p)
            {
                dep[c] = dep[p] + 1;
            }
            ansestor[c][0] = p;
            for (int i = 1; i < lg; i++)
            {
                ansestor[c][i] = ansestor[ansestor[c][i - 1]][i - 1];
            }
            for (auto i : tree[c])
            {
                if (i == p)
                    continue;
                self(self, i, c);
            }
        };
        dfs(dfs, root, root);
    }
    int query(int x, int y)
    {
        if (dep[x] < dep[y])
            swap(x, y);
        int sub = dep[x] - dep[y];
        for (int i = 0; i < lg; i++)
        {
            if (1 << i & sub)
            {
                x = ansestor[x][i];
            }
        }
        if (x == y)
            return x;
        for (int i = lg - 1; i >= 0; i--)
        {
            if (ansestor[x][i] != ansestor[y][i])
                x = ansestor[x][i], y = ansestor[y][i];
        }
        return ansestor[x][0];
    }

private:
    int n, lg;
    vector<int> dep;
    vector<vector<int>> ansestor;
};
