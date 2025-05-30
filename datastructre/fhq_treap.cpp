#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng(random_device{}());
// 维护区间翻转，没有平衡树功能
struct fhq_treap
{
    using T = int;

private:
    struct node
    {
        node() : lson(nullptr), rson(nullptr) {}
        node(T value) : lson(nullptr), rson(nullptr),
                        value(value), priority((int)rng()), size(1), tag(false) {}

        void upd()
        {
            size = 1;
            if (lson)
            {
                size += lson->size;
            }
            if (rson)
            {
                size += rson->size;
            }
        }

        void check_tag()
        {
            if (tag)
            {
                tag = 0;
                swap(lson, rson);
                if (lson)
                    lson->tag ^= 1;
                if (rson)
                    rson->tag ^= 1;
            }
        }

        node *lson, *rson;
        T value;
        int priority;
        int size;
        bool tag;
    };

public:
    fhq_treap() : m_size(0), _root(nullptr) {}
    fhq_treap(const vector<T> &a) : m_size((int)a.size()), _root(nullptr)
    {
        vector<node *> stk;
        for (int i = 0; i < m_size; i++)
        {
            node *p = new node(a[i]), *cur = nullptr;
            while (stk.size() && stk.back()->priority)
            {
                cur = stk.back();
                stk.pop_back();
            }
            p->lson = cur;
            if (stk.size())
            {
                stk.back()->rson = p;
            }
            else
            {
                _root = p;
            }
            stk.push_back(p);
        }
        auto dfs = [&](auto self, node *c, node *p)
        {
            if (c == nullptr)
                return;
            c->size = 1;
            self(self, c->lson, c);
            self(self, c->rson, c);
            if (c != p)
            {
                p->size += c->size;
            }
        };
        dfs(dfs, _root, _root);
    }

    size_t size() const
    {
        return size_t(m_size);
    }

    void reverse(int l, int r) // [l, r)
    {
        auto p1 = split(_root, r);
        node *rht = p1.second, *mid = p1.first;
        auto p2 = split(mid, l);
        mid = p2.second;
        node *lft = p2.first;
        mid->tag ^= 1;
        _root = merge(merge(lft, mid), rht);
    }

    vector<T> val() const
    {
        vector<T> ans;
        ans.reserve(m_size);
        auto dfs = [&](auto self, node *p) -> void
        {
            if (p == nullptr)
                return;
            p->check_tag();
            self(self, p->lson);
            ans.push_back(p->value);
            self(self, p->rson);
        };
        dfs(dfs, _root);
        return ans;
    }

private:
    int m_size;
    node *_root;
    int get_size(node *p) const { return p == nullptr ? 0 : p->size; }
    pair<node *, node *> split(node *root, int size)
    {
        if (root == nullptr)
            return {nullptr, nullptr};
        root->check_tag();
        if (size <= get_size(root->lson))
        {
            auto tmp = split(root->lson, size);
            root->lson = tmp.second;
            root->upd();
            return {tmp.first, root};
        }
        else
        {
            auto tmp = split(root->rson, size - get_size(root->lson) - 1);
            root->rson = tmp.first;
            root->upd();
            return {root, tmp.second};
        }
    }

    node *merge(node *l, node *r)
    {
        if (l == nullptr && r == nullptr)
            return nullptr;
        if (l == nullptr)
            return r;
        if (r == nullptr)
            return l;
        l->check_tag(), r->check_tag();
        if (l->priority > r->priority)
        {
            l->rson = merge(l->rson, r);
            l->upd();
            return l;
        }
        else
        {
            r->lson = merge(l, r->lson);
            r->upd();
            return r;
        }
    }
};