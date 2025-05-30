#include <bits/stdc++.h>
using namespace std;

struct wavelet_tree
{
private:
    int lo, hi;
    wavelet_tree *l, *r;
    vector<int> b;

public:
    // nos are in range `[x,y]`
    // array indices are `[from, to)`
    // @param from `A forward iterator`
    // @param to `A forward iterator`
    // @param x `min element of the array`
    // @param y `max element of the array`
    template <class T>
    wavelet_tree(T from, T to, int x, int y) : lo(x), hi(y), l(nullptr), r(nullptr), b()
    {
        assert(x <= y);
        if (lo == hi or from >= to)
            return;
        int mid = (lo + hi) / 2;
        auto f = [mid](int x)
        {
            return x <= mid;
        };
        b.reserve(to - from + 1);
        b.push_back(0);
        for (auto it = from; it != to; it++)
            b.push_back(b.back() + f(*it));
        // see how lambda function is used here
        auto pivot = stable_partition(from, to, f);
        l = new wavelet_tree(from, pivot, lo, mid);
        r = new wavelet_tree(pivot, to, mid + 1, hi);
    }

    // kth smallest element in `[l, r)`
    // @param k `1 <= k <= r - l`
    int kth(int l, int r, int k)
    {
        if (l + 1 > r)
            return 0;
        if (lo == hi)
            return lo;
        int inLeft = b[r] - b[l];
        int lb = b[l]; // amt of nos in first (l-1) nos that go in left
        int rb = b[r]; // amt of nos in first (r) nos that go in left
        if (k <= inLeft)
            return this->l->kth(lb, rb, k);
        return this->r->kth(l - lb, r - rb, k - inLeft);
    }

    // count of nos in `[l, r)` Less than or equal to k
    int LTE(int l, int r, int k)
    {
        if (l + 1 > r or k < lo)
            return 0;
        if (hi <= k)
            return r - l;
        int lb = b[l], rb = b[r];
        return this->l->LTE(lb, rb, k) + this->r->LTE(l - lb, r - rb, k);
    }

    // count of nos in `[l, r)` equal to k
    int count(int l, int r, int k)
    {
        if (l + 1 > r or k < lo or k > hi)
            return 0;
        if (lo == hi)
            return r - l;
        int lb = b[l], rb = b[r], mid = (lo + hi) / 2;
        if (k <= mid)
            return this->l->count(lb, rb, k);
        return this->r->count(l - lb, r - rb, k);
    }
    ~wavelet_tree()
    {
        delete l;
        delete r;
    }
};