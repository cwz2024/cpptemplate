#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
template <class T>
class matrix
{
private:
    int r, c;
    vector<vector<T>> arr;
    vector<T> &operator[](int i) { return arr[i]; }

public:
    matrix operator~()
    {
        matrix ans(c, r, 0);
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                ans[j][i] = arr[i][j];
            }
        }
        return ans;
    }
    matrix operator+() { return *this; }
    matrix operator-()
    {
        matrix ans(r, c, 0);
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                ans[i][j] = -arr[i][j];
            }
        }
        return ans;
    }
    matrix operator+(matrix a)
    {
        assert(a.r == r && a.c == c);
        matrix ans(r, c, 0);
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                ans[i][j] = arr[i][j] + a[i][j];
            }
        }
        return ans;
    }
    matrix operator-(matrix a) { return operator+(-a); }
    matrix operator*(matrix a)
    {
        assert(c == a.r);
        int i, j, k;
        matrix ans(r, a.c, 0);
        for (i = 0; i < r; i++)
        {
            for (j = 0; j < a.c; j++)
            {
                for (k = 0; k < c; k++)
                {
                    ans[i][j] += arr[i][k] * a[k][j];
                }
            }
        }
        return ans;
    }
    matrix pow(long long n)
    {
        assert(r == c);
        matrix ans(r, c, 1), base(arr);
        while (n)
        {
            if (n & 1)
            {
                ans = ans * base;
            }
            base = base * base;
            n >>= 1;
        }
        return ans;
    }
    vector<vector<T>> val() const { return arr; }
    matrix() : r(0), c(0) {}
    matrix(int r, int c, T val = 0) : r(r), c(c), arr(r, vector<T>(c))
    {
        if (val != 0)
            for (int i = 0; i < min(r, c); i++)
            {
                arr[i][i] = val;
            }
    }
    matrix(vector<vector<T>> val)
    {
        assert(!val.empty());
        for (auto i : val)
        {
            assert(i.size() == val[0].size());
        }
        arr = val;
        r = int(val.size());
        c = int(val[0].size());
    }
    matrix(initializer_list<initializer_list<T>> a)
    {
        for (auto v : a)
        {
            arr.push_back(v);
        }
        assert(arr.size());
        for (auto v : arr)
        {
            assert(v.size() == arr[0].size());
        }
        r = int(arr.size());
        c = int(arr[0].size());
    }
};