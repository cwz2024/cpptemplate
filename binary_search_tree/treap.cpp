#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng(random_device{}());

// 只 new 不 delete
template <class T>
struct treap
{
private:
    struct node
    {
        node() : pa(nullptr), lson(nullptr), rson(nullptr) {}
        node(T key) : pa(nullptr), lson(nullptr), rson(nullptr),
                      key(key), priority((int)rng()), size(1) {}
        node *pa, *lson, *rson;
        T key;
        int priority;
        int size;
    };

public:
    struct iterator
    {
        node *u;
        iterator() : u(nullptr) {}
        iterator(node *u) : u(u) {}

        T const &operator*()
        {
            return u->key;
        }

        iterator &operator++()
        {
            if (!u->rson)
            {
                while (u->pa && u->pa->rson == u)
                {
                    u = u->pa;
                }
                u = u->pa;
                return *this;
            }
            else
            {
                u = u->rson;
                while (u->lson)
                    u = u->lson;
            }
            return *this;
        }
        iterator &operator--()
        {
            if (!u->lson)
            {
                while (u->pa && u->pa->lson == u)
                {
                    u = u->pa;
                }
                u = u->pa;
                return *this;
            }
            else
            {
                u = u->lson;
                while (u->rson)
                    u = u->rson;
            }
            return *this;
        }
        iterator operator++(int)
        {
            iterator result = *this;
            ++*this;
            return result;
        }
        iterator operator--(int)
        {
            iterator result = *this;
            --*this;
            return result;
        }
        bool operator==(const iterator &rhs)
        {
            return u == rhs.u;
        }
        bool operator!=(const iterator &rhs)
        {
            return u != rhs.u;
        }
    };

    treap() : m_size(0), _root(nullptr), _begin(nullptr), _rbegin(nullptr) {}

    iterator begin() const { return iterator(_begin); }
    iterator end() const { return iterator(nullptr); }

    iterator find(T v) const
    {
        if (m_size == 0)
            return end();
        node *p = find_pos(v);
        if (p->key == v)
            return iterator(p);
        return end();
    }
    int count(T v) const
    {
        return find(v) != end();
    }
    void insert(T v)
    {
        node *p;
        if (_root == nullptr)
        {
            p = new node(v);
            _rbegin = _begin = _root = p;
            m_size++;
            return;
        }
        else
        {
            node *pos = find_pos(v);
            if (pos->key == v)
                return;
            p = new node(v);
            if (v < pos->key)
            {
                pos->lson = p;
                if (pos == _begin)
                    _begin = p;
            }
            else
            {
                pos->rson = p;
                if (pos == _rbegin)
                    _rbegin = p;
            }
            p->pa = pos;
            while (pos)
            {
                pos->size++;
                pos = pos->pa;
            }
        }
        m_size++;
        node *cur = p;
        while (cur->pa && cur->priority > cur->pa->priority)
        {
            if (cur == cur->pa->lson)
                right_turn(cur->pa);
            else
                left_turn(cur->pa);
        }
    }
    void erase(T v)
    {
        if (empty())
            return;
        node *p = find_pos(v);
        if (p->key != v)
            return;
        m_size--;
        if (m_size == 0)
        {
            clear();
            return;
        }

        while (p->lson && p->rson)
        {
            if (p->lson->priority > p->rson->priority)
                right_turn(p);
            else
                left_turn(p);
        }
        if (p == _begin)
        {
            _begin = (++iterator(p)).u;
        }
        else if (p == _rbegin)
        {
            _rbegin = (--iterator(p)).u;
        }
        if (p == _root)
        {
            if (p->lson)
                p->lson->pa = nullptr, _root = p->lson;
            if (p->rson)
                p->rson->pa = nullptr, _root = p->rson;
            return;
        }
        if (p->pa->lson == p)
            p->pa->lson = p->lson ? p->lson : p->rson;
        else
            p->pa->rson = p->lson ? p->lson : p->rson;
        node *up = p->pa;
        while (up)
        {
            up->size--;
            up = up->pa;
        }
        if (p->lson)
            p->lson->pa = p->pa;
        if (p->rson)
            p->rson->pa = p->pa;
    }

    T const &at(int i) const
    {
        if (i < 0 || i >= m_size)
        {
            throw out_of_range("");
        }
        int cur = 0;
        auto pos = [&](node *p)
        {
            if (p->lson)
                return cur + p->lson->size;
            else
                return cur;
        };
        node *p = _root;
        while (1)
        {
            if (pos(p) == i)
            {
                break;
            }
            else if (pos(p) < i)
            {
                cur += p->lson ? p->lson->size + 1 : 1;
                p = p->rson;
            }
            else
            {
                p = p->lson;
            }
        }
        return p->key;
    }

    T lt(T v) const
    {
        node *p = find_pos(v);
        if (p->key < v)
            return p->key;
        else
            return *(--iterator(p));
    }

    T gt(T v) const
    {
        node *p = find_pos(v);
        if (p->key > v)
            return p->key;
        else
            return *(++iterator(p));
    }

    int rank(T v) const // 小于 v 的元素个数加 1
    {
        int cur = 0;
        node *p = _root;
        while (p)
        {
            if (p->key >= v)
                p = p->lson;
            else
            {
                if (p->rson)
                    cur += p->size - p->rson->size;
                else
                    cur += p->size;
                p = p->rson;
            }
        }
        return cur + 1;
    }

    vector<T> val() const
    {
        vector<T> ans;
        ans.reserve(m_size);
        auto dfs = [&](auto self, node *p) -> void
        {
            if (p == nullptr)
                return;
            self(self, p->lson);
            ans.push_back(p->key);
            self(self, p->rson);
        };
        dfs(dfs, _root);
        return ans;
    }

    size_t size() const
    {
        return size_t(m_size);
    }

    bool empty() const
    {
        return size() == 0;
    }

    void clear()
    {
        _begin = _rbegin = _root = nullptr;
        m_size = 0;
    }

private:
    int m_size;
    node *_root, *_begin, *_rbegin;

    node *find_pos(T v) const
    {
        node *p = _root, *lst = nullptr;
        while (p)
        {
            lst = p;
            if (p->key == v)
                return p;
            else if (p->key < v)
                p = p->rson;
            else
                p = p->lson;
        }
        assert(lst != nullptr);
        return lst;
    }

    void right_turn(node *root)
    {
        if (root == _root)
            _root = root->lson;
        else
        {
            node *p = root->pa;
            if (p->lson == root)
                p->lson = root->lson;
            else
                p->rson = root->lson;
        }
        root->lson->size = root->size;
        node *tmp = root->lson;
        root->lson = tmp->rson;
        tmp->rson = root;
        if (root->lson)
            root->lson->pa = root;
        if (tmp)
            tmp->pa = root->pa;
        if (root)
            root->pa = tmp;
        if (tmp->lson)
            root->size -= tmp->lson->size + 1;
        else
            root->size--;
    }
    void left_turn(node *root)
    {
        if (root == _root)
            _root = root->rson;
        else
        {
            node *p = root->pa;
            if (p->lson == root)
                p->lson = root->rson;
            else
                p->rson = root->rson;
        }
        root->rson->size = root->size;
        node *tmp = root->rson;
        root->rson = tmp->lson;
        tmp->lson = root;
        if (root->rson)
            root->rson->pa = root;
        if (tmp)
            tmp->pa = root->pa;
        if (root)
            root->pa = tmp;
        if (tmp->rson)
            root->size -= tmp->rson->size + 1;
        else
            root->size--;
    }
};