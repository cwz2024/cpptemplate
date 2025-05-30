#include <bits/stdc++.h>
using namespace std;

struct state
{
    int len, link;
    int tr[26];
};
const int MAXLEN = 1000005;
state st[MAXLEN * 2];
int times[MAXLEN * 2];
vector<int> tree[MAXLEN * 2];
int sz, last;
void sa_init()
{
    st[0].len = 0;
    st[0].link = -1;
    sz++;
    last = 0;
}
void sa_extend(char c)
{
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    int p = last;
    while (p != -1 && !st[p].tr[c - 'a'])
    {
        st[p].tr[c - 'a'] = cur;
        p = st[p].link;
    }
    if (p == -1)
    {
        st[cur].link = 0;
    }
    else
    {
        int q = st[p].tr[c - 'a'];
        if (st[p].len + 1 == st[q].len)
        {
            st[cur].link = q;
        }
        else
        {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            memcpy(st[clone].tr, st[q].tr, sizeof(st[q].tr));
            st[clone].link = st[q].link;
            while (p != -1 && st[p].tr[c - 'a'] == q)
            {
                st[p].tr[c - 'a'] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    times[cur]++;
    last = cur;
}