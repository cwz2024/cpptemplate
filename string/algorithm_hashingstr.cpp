#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
using haxi = pair<ull, ull>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count() ^ (uintptr_t)make_unique<char>().get());

// 双哈希，using haxi = pair<ull, ull>; pair 自带重载的 ==, != 运算符
// 第一重哈希固定 base = 17477417（质数），模数为 2^64（ull 的自然溢出）
// 第二重哈希使用 randbase，模数为 1e9+7（质数）保证其安全性
// 最终等价于一个模数的量级为 10^27 的哈希，自然的哈希冲突（生日悖论）几乎完全不可能造成冲突
// 哈希过程为倒着哈希，s[0]*p**(n-1)+s[1]*p**(n-2)+...+s[n-1]*p**0

// 初始化可以用一个字符串进行初始化，也可以不初始化，之后用 extend 函数把字符串拼上去
// 部分位置为了追求效率，传的是引用，如果要进行 extend(a+b) 这种操作的话改成传值
// val() 返回整个字符串的哈希值，如果单纯只要一个字符串的哈希值不需要存储，可以这样 auto val = Hash(str).val();

ull randbase = rng() % 20240327;
const ull p1 = 17477417, p2 = randbase + 131;
const ull mod2 = 1e9 + 7;
struct Hash
{
    vector<haxi> pw, pre;
    haxi val(void) { return pre.back(); }
    haxi val(int l, int r) // 从0开始，[l,r)
    {
        haxi ans;
        ans.first = pre[r].first - pre[l].first * pw[r - l].first;
        ans.second = (pre[r].second + mod2 - pre[l].second * pw[r - l].second % mod2) % mod2;
        return ans;
    }
    size_t size() { return pw.size() - 1; }
    void extend(const string &s)
    {
        int n = int(pw.size()), m = int(s.size());
        pw.resize(n + m);
        pre.resize(n + m);
        for (int i = n; i < n + m; ++i)
        {
            pw[i].first = pw[i - 1].first * p1;
            pw[i].second = pw[i - 1].second * p2 % mod2;
        }
        for (int i = n; i < n + m; ++i)
        {
            pre[i].first = pre[i - 1].first * p1 + s[i - n];
            pre[i].second = (pre[i - 1].second * p2 + s[i - n]) % mod2;
        }
    }
    Hash(const string &s) : pw(s.size() + 1), pre(s.size() + 1)
    {
        pw[0] = haxi(1, 1);
        for (int i = 1; i <= int(s.size()); ++i)
        {
            pw[i].first = pw[i - 1].first * p1;
            pw[i].second = pw[i - 1].second * p2 % mod2;
        }
        for (int i = 1; i <= int(s.size()); ++i)
        {
            pre[i].first = pre[i - 1].first * p1 + s[i - 1];
            pre[i].second = (pre[i - 1].second * p2 + s[i - 1]) % mod2;
        }
    }
    Hash() : pw(1), pre(1) { pw[0] = {1, 1}; }
};

haxi strhash(string s)
{
    const int P = 202403;
    static unsigned long long mod = rng() % 1145141919810 | 1;
    ull h1 = 0, h2 = 0;
    for (auto i : s)
    {
        h1 = (h1 * P % mod + i) % mod;
        h2 = h2 * P + i;
    }
    return haxi(h1, h2);
}

ull poorhash(string s)
{
    const int P = 17477417;
    ull h = 0;
    for (auto i : s)
    {
        h = h * P + i;
    }
    return h;
}

ull poorhash2(string s)
{
    const int P = 17477417, mod = 998244353;
    ull h = 0;
    for (auto i : s)
    {
        h = (h * P + i) % mod;
    }
    return h;
}