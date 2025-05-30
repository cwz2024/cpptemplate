#include <bits/stdc++.h>
using namespace std;

struct MaxInt
{
    using T = int;
    const T e = numeric_limits<int>::min();
    T op(T a, T b) { return max(a, b); }
};
struct MinInt
{
    using T = int;
    const T e = numeric_limits<int>::max();
    T op(T a, T b) { return min(a, b); }
};

template <class B>
struct sparse : public B
{
private:
    using T = typename B::T;
    int n, lg;
    vector<vector<T>> s;
    vector<int> log;

public:
    sparse(vector<T> a) : n(int(a.size())), lg(__lg(n) + 1), s(lg, vector<T>(n, B::e)), log(n + 1)
    {
        s[0] = a;
        for (int i = 1; i < lg; i++)
        {
            for (int j = 0; j + (1 << (i - 1)) < n; j++)
            {
                s[i][j] = B::op(s[i - 1][j], s[i - 1][j + (1 << (i - 1))]);
            }
        }
        log[0] = -1;
        for (int i = 1; i <= n; i++)
        {
            log[i] = log[i >> 1] + 1;
        }
    }
    T query(int l, int r) // [l, r)
    {
        int k = log[r - l];
        return B::op(s[k][l], s[k][r - (1 << k)]);
    }
};