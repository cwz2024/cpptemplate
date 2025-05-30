#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 常用基类
// 需要包含的东西：
//  using T = <vector 里面放的类型>;
//  二元操作 op(a, b) 代表你要求的是区间和？区间最值？区间gcd？
//  单位根 e，其需要满足 op(e, x) == x 恒成立

struct MaxInt
{
    using T = int;
    T e = numeric_limits<int>::min();
    T op(T a, T b) { return max(a, b); }
};
struct MinInt
{
    using T = int;
    T e = numeric_limits<int>::max();
    T op(T a, T b) { return min(a, b); }
};
struct AddInt
{
    using T = long long;
    T e = 0;
    T op(T a, T b) { return a + b; }
};
int m;
struct AddModInt
{
    using T = int;
    T e = 0;
    T op(T a, T b) { return (a + b) % m; }
};
struct MinIntCnt
{
    using T = pair<int, int>;
    T e = {0x3f3f3f3f, 0};
    T op(T a, T b)
    {
        if (a.first == b.first)
            return {a.first, a.second + b.second};
        return min(a, b);
    }
};

// 经典懒标记基类（支持多个懒标记）
// 需要包含的东西：
//  using A = <懒标记类型>;
//      注意，如果想要实现多个懒标记的方法，那么把两个懒标记组合成一个 struct，并重载==和!=
//  二元操作 op(a, b)，表示两个懒标记碰一起了，得到的新懒标记是多少
//  单位根 e，其需要满足 op(e, x) == x 恒成立
//  void upd(T &_, const A l, int w)
//      代表，记录的区间宽度为 w 的，值为 _ ，头上戴着懒标记 l 的元素，在pushdown后的实际值怎么更新

struct AddLazy
{
    using A = long long;
    A e = 0;
    void upd(AddInt::T &_, const A l, int w)
    {
        _ += l * w;
    }
    A op(A a, A b) { return a + b; }
};
struct AddMulLazy
{
    struct A
    {
        int add, mul;
        bool operator==(A const &a) { return add == a.add && mul == a.mul; }
        bool operator!=(A const &a) { return !(*this == a); }
    };
    A e = {0, 1};
    void upd(AddModInt::T &_, const A l, int w)
    {
        _ = (1ll * _ * l.mul + 1ll * l.add * w) % m;
    }
    A op(A a, A b)
    {
        A ans;
        ans.mul = 1ll * a.mul * b.mul % m;
        ans.add = (1ll * a.add * b.mul + b.add) % m;
        return ans;
    }
};

// 不懒的线段树，可以单点修改，区间查询，利用区间可加性整个合适的基类即可
// 可以用 vector 初始化，也可以用尺寸初始化之后一个一个给成员 set（不建议）
// 内部线段树 s 的大小是两倍 size，对，就是恰好两倍 size，不是给 n 取 lg 加一之后再两倍
// 来自 https://codeforces.com/blog/entry/91235
// 优点：常数小（应该和树状数组差不多了），通用性高

template <class B>
struct segtree : public B
{
private:
    using T = typename B::T;

    int n;
    vector<T> s;

public:
    segtree(int n) : n(n), s(2 * n, B::e) {};
    segtree(vector<T> a) : n(int(size(a))), s(2 * n, B::e)
    {
        copy(a.begin(), a.end(), s.begin() + n);
        for (int i = n - 1; i > 0; --i)
            s[i] = B::op(s[i << 1], s[i << 1 | 1]);
    };
    void set(int i, T val) // s[i] := val
    {
        for (s[i += n] = val; i >>= 1;)
            s[i] = B::op(s[i << 1], s[i << 1 | 1]);
    }
    T query(int l, int r) // for [l,r)
    {
        T la = B::e, ra = B::e;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                la = B::op(la, s[l++]);
            if (r & 1)
                ra = B::op(s[--r], ra);
        }
        return B::op(la, ra);
    }
};

// 懒线段树，区间修改，区间查询，需要一个普通基类和一个 lazy 标签的基类
// 建议只用 vector 进行初始化
// 内部线段树 s 的大小是给 n 取 lg 加一之后再两倍
// 优点：通用性高，但代价是 lazy 基类写起来可能有些绕

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
    lazy_segtree(int _n) : n(1 << (__lg(_n)) << (1 << (__lg(_n)) < _n)), h(__lg(2 * n)), s(2 * n, B::e), d(2 * n) {};
    lazy_segtree(vector<T> a) : n(1 << (__lg(size(a))) << (1 << (__lg(size(a))) < (int)size(a))), h(__lg(2 * n)), s(2 * n, B::e), d(2 * n, Bl::e)
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