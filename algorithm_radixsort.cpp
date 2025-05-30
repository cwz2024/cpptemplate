#include <bits/stdc++.h>
using namespace std;

void radix_sort(vector<int> &a)
{
    vector<int> mem(a.size());
    for (int _ = 0; _ < 2; _++)
    {
        int bucket[65536] = {};
        for (int i = 0; i < int(a.size()); i++)
        {
            bucket[a[i] >> (_ << 4) & 65535]++;
        }
        for (int i = 1; i < 65536; i++)
        {
            bucket[i] += bucket[i - 1];
        }
        for (int i = int(a.size()) - 1; i >= 0; i--)
        {
            mem[--bucket[a[i] >> (_ << 4) & 65535]] = a[i];
        }
        a = mem;
    }
}

void radix_sort(int *a, int *mem, int len)
{
    for (int _ = 0; _ < 2; _++)
    {
        int bucket[65536] = {};
        for (int i = 0; i < len; i++)
        {
            bucket[a[i] >> (_ << 4) & 65535]++;
        }
        for (int i = 1; i < 65536; i++)
        {
            bucket[i] += bucket[i - 1];
        }
        for (int i = len - 1; i >= 0; i--)
        {
            mem[--bucket[a[i] >> (_ << 4) & 65535]] = a[i];
        }
        memcpy(a, mem, len * sizeof(int));
    }
}

void llradix_sort(long long *a, long long *mem, int len)
{
    for (int _ = 0; _ < 4; _++)
    {
        int bucket[65536] = {};
        for (int i = 0; i < len; i++)
        {
            bucket[a[i] >> (_ << 4) & 65535]++;
        }
        for (int i = 1; i < 65536; i++)
        {
            bucket[i] += bucket[i - 1];
        }
        for (int i = len - 1; i >= 0; i--)
        {
            mem[--bucket[a[i] >> (_ << 4) & 65535]] = a[i];
        }
        memcpy(a, mem, len * sizeof(long long));
    }
}