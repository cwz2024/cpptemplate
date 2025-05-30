#include <bits/stdc++.h>
using namespace std;

struct accept_automation
{
    using vi = vector<int>;
    int _n, _cnt;
    vector<int> fail, ind;
    vector<vector<int>> trie, tree;

    accept_automation() : _n(0), _cnt(0) {}
    accept_automation(vector<string> &dic) : _n(int(dic.size())), _cnt(0), ind(_n)
    {
        // trie 树构建
        new_cache();
        for (int i = 0; i < _n; i++)
        {
            int u = 0;
            string &s = dic[i];
            for (int j = 0; j < int(s.size()); j++)
            {
                if (!trie[u][s[j] - 'a'])
                {
                    trie[u][s[j] - 'a'] = _cnt;
                    new_cache();
                }
                u = trie[u][s[j] - 'a'];
            }
            ind[i] = u;
        }

        // fail 指针和 fail 反图构建
        queue<int> q;
        for (int i = 0; i < 26; i++)
        {
            if (trie[0][i])
                q.push(trie[0][i]);
        }
        while (q.size())
        {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 26; i++)
            {
                if (trie[u][i])
                    fail[trie[u][i]] = trie[fail[u]][i], q.push(trie[u][i]);
                else
                    trie[u][i] = trie[fail[u]][i];
            }
            tree[fail[u]].push_back(u);
        }
    }

    vector<int> cnt(string &s)
    {
        vector<int> cnt(_cnt), ans(_n);
        int u = 0;
        for (int i = 0; i < int(s.size()); i++)
        {
            u = trie[u][s[i] - 'a'];
            if (u)
                cnt[u]++;
        }
        auto dfs = [&](auto self, int c) -> void
        {
            for (auto i : tree[c])
            {
                self(self, i);
                cnt[c] += cnt[i];
            }
        };
        dfs(dfs, 0);
        for (int i = 0; i < _n; i++)
        {
            ans[i] = cnt[ind[i]];
        }
        return ans;
    }

private:
    void new_cache()
    {
        _cnt++, trie.push_back(vi(26)), tree.push_back(vi()), fail.push_back(0);
    }
};