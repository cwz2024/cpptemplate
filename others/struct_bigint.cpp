#include <bits/stdc++.h>
using namespace std;

struct bigint
{
private:
    string s;
    int sign;

public:
    bigint() : sign(1){};
    bigint(string num) : s(num), sign(1)
    {
        reverse(s.begin(), s.end());
        if (s.back() == '-')
            s.pop_back(), sign = -1;
        for (auto &i : s)
        {
            i -= '0';
            assert(i >= 0 && i <= 9);
        }
    }
    bigint(long long v) : s(to_string(v)), sign(1)
    {
        reverse(s.begin(), s.end());
        if (s.back() == '-')
            sign = -1, s.pop_back();
        for (auto &i : s)
            i -= '0';
    }
    bigint abs() const
    {
        bigint ans = *this;
        ans.sign = 1;
        return ans;
    }

    friend ostream &operator<<(ostream &o, bigint a)
    {
        if (a.sign == -1)
            o << '-';
        for (int i = (int)size(a.s) - 1; i >= 0; i--)
            o << char(a.s[i] + '0');
        return o;
    }
    friend istream &operator>>(istream &i, bigint &a)
    {
        i >> a.s;
        reverse(a.s.begin(), a.s.end());
        if (a.s.back() == '-')
            a.sign = -1, a.s.pop_back();
        for (auto &i : a.s)
        {
            assert(isdigit(i));
            i -= '0';
        }
        while (a.s.back() == 0 && size(a.s) > 1)
        {
            a.s.pop_back();
        }
        return i;
    }

    friend bool operator==(const bigint &a, const bigint &b) { return a.sign == b.sign && a.s == b.s; }
    friend bool operator!=(const bigint &a, const bigint &b) { return !(a == b); }
    friend bool operator<(const bigint &a, const bigint &b)
    {
        if (a.sign < 0 && b.sign > 0)
            return true;
        if (a.sign > 0 && b.sign < 0)
            return false;
        if (size(a.s) != size(b.s))
            return (size(a.s) < size(b.s)) && (a.sign == 1);
        for (int i = (int)size(a.s) - 1; i >= 0; i--)
        {
            if (a.s[i] == b.s[i])
                continue;
            return (a.s[i] < b.s[i]) && (a.sign == 1);
        }
        return false;
    }
    friend bool operator>(const bigint &a, const bigint &b) { return b < a; }
    friend bool operator>=(const bigint &a, const bigint &b) { return !(a < b); }
    friend bool operator<=(const bigint &a, const bigint &b) { return !(a > b); }

    bigint operator+() const { return *this; }
    bigint operator-() const
    {
        bigint a = *this;
        a.sign *= -1;
        return a;
    }

    bigint &operator+=(const bigint &b)
    {
        size_t la = size(s), lb = size(b.s);
        if (sign == b.sign)
        {
            s.resize(max(la, lb) + 1);
            for (size_t i = 0; i < lb; i++)
            {
                s[i] += b.s[i];
            }
            for (size_t i = 0; i < size(s) - 1; i++)
            {
                s[i + 1] += char(s[i] / 10);
                s[i] %= 10;
            }
            if (s.back() == 0)
                s.pop_back();
            return *this;
        }
        else
        {
            if (abs() == b.abs())
            {
                *this = bigint(0);
                return *this;
            }
            if (abs() > b.abs())
            {
                for (size_t i = 0; i < lb; i++)
                {
                    s[i] -= b.s[i];
                    if (s[i] < 0)
                        s[i] += 10, s[i + 1]--;
                }
                for (size_t i = lb; i < la - 1; i++)
                {
                    if (s[i] < 0)
                        s[i] += 10, s[i + 1]--;
                }
                while (s.back() == 0 && size(s) > 1)
                    s.pop_back();
                return *this;
            }
            else
            {
                sign *= -1;
                s.resize(lb);
                for (size_t i = 0; i < la; i++)
                {
                    s[i] = b.s[i] - s[i];
                    if (s[i] < 0)
                    {
                        s[i] += 10;
                        s[i + 1]++;
                        if (i + 1 == la)
                            la++;
                    }
                }
                for (size_t i = la; i < lb; i++)
                    s[i] = b.s[i];
                while (s.back() == 0 && size(s) > 1)
                    s.pop_back();
                return *this;
            }
        }
    }
    bigint &operator-=(const bigint &b) { return *this += -b; }
    bigint &operator*=(const bigint &b)
    {
        auto fft = [](vector<complex<double>> &p, int g = 1) -> void
        {
            int n = (int)size(p), lg = __lg(n) - 1;
            if (n == 1)
                return;
            const double pi = acos(-1);
            vector<int> r(n);
            for (int i = 0; i < n; i++)
            {
                r[i] = r[i >> 1] >> 1 | ((i & 1) << lg);
                if (i < r[i])
                    swap(p[i], p[r[i]]);
            }
            for (int wid = 2; wid <= n; wid <<= 1)
            {
                complex<double> w(cos(2 * pi / wid * g), sin(2 * pi / wid * g));
                for (int l = 0; l < n; l += wid)
                {
                    complex<double> wi = 1;
                    for (int i = l; i < l + wid / 2; i++, wi *= w)
                    {
                        complex<double> x = p[i], y = p[i + wid / 2];
                        p[i] = x + wi * y;
                        p[i + wid / 2] = x - wi * y;
                    }
                }
            }
        };
        int n = int(size(s) + size(b.s)), lg = 0;
        while (1 << lg < n)
        {
            lg++;
        }
        n = 1 << lg;
        vector<complex<double>> p(n);
        for (int i = 0; i < n; i++)
        {
            p[i] = {double(i < int(size(s)) ? s[i] : 0), double(i < int(size(b.s)) ? b.s[i] : 0)};
        }
        fft(p);
        for (int i = 0; i < n; i++)
        {
            p[i] *= p[i];
        }
        fft(p, -1);
        s.resize(n);
        int plus = 0;
        for (int i = 0; i < n; i++)
        {
            int tmp = (int)round(p[i].imag() / (n << 1)) + plus;
            s[i] = char(tmp % 10);
            plus = tmp / 10;
        }
        while (s.back() == 0 && size(s) > 1)
            s.pop_back();
        sign *= b.sign;
        if (s.back() == 0)
            sign = 1;
        return *this;
    }
    bigint &operator/=(const bigint &b)
    {
        assert(b != 0);
        if (abs() < b.abs())
            return *this = 0;
        size_t lb = size(b.s), la = size(s);
        string sa(la - lb + 1, 0);
        auto judge = [&](int fix) -> bool
        {
            if (lb + fix < la)
                return true;
            for (int i = (int)size(b.s) - 1; i >= 0; i--)
            {
                if (s[i + fix] == b.s[i])
                    continue;
                return s[i + fix] > b.s[i];
            }
            return true;
        };
        for (int fix = int(la - lb); fix >= 0; fix--)
        {
            while (judge(fix))
            {
                sa[fix]++;
                for (size_t i = 0; i < lb; i++)
                {
                    s[i + fix] -= b.s[i];
                    if (s[i + fix] < 0)
                        s[i + fix] += 10, s[i + fix + 1]--;
                }
                for (size_t i = lb;; i++)
                {
                    if (s[i + fix] < 0)
                        s[i + fix] += 10, s[i + fix + 1]--;
                    else
                        break;
                }
                while (s.back() == 0 && la > 1)
                    s.pop_back(), la--;
            }
        }
        while (sa.back() == 0)
            sa.pop_back();
        s = sa, sign *= b.sign;
        return *this;
    }
    bigint &operator%=(const bigint &b)
    {
        assert(b != 0);
        if (abs() < b.abs())
            return *this;
        size_t lb = size(b.s), la = size(s);
        auto judge = [&](int fix) -> bool
        {
            if (lb + fix < la)
                return true;
            for (int i = (int)size(b.s) - 1; i >= 0; i--)
            {
                if (s[i + fix] == b.s[i])
                    continue;
                return s[i + fix] > b.s[i];
            }
            return true;
        };
        for (int fix = int(la - lb); fix >= 0; fix--)
        {
            while (judge(fix))
            {
                for (size_t i = 0; i < lb; i++)
                {
                    s[i + fix] -= b.s[i];
                    if (s[i + fix] < 0)
                        s[i + fix] += 10, s[i + fix + 1]--;
                }
                for (size_t i = lb;; i++)
                {
                    if (s[i + fix] < 0)
                        s[i + fix] += 10, s[i + fix + 1]--;
                    else
                        break;
                }
                while (s.back() == 0 && la > 1)
                    s.pop_back(), la--;
            }
        }
        if (la == 1 && s[0] == 0)
            sign = 1;
        return *this;
    }
    bigint &operator%=(const long long &b)
    {
        assert(b != 0);
        if (b > (long long)9e17)
        {
            return *this %= bigint(b);
        }
        long long ans = 0;
        for (int i = int(size(s)) - 1; i >= 0; i--)
        {
            ans = (ans * 10 + s[i]) % b;
        }
        *this = ans;
        return *this;
    }

    friend bigint operator+(const bigint &a, const bigint &b) { return bigint(a) += b; }
    friend bigint operator-(const bigint &a, const bigint &b) { return bigint(a) -= b; }
    friend bigint operator*(const bigint &a, const bigint &b) { return bigint(a) *= b; }
    friend bigint operator/(const bigint &a, const bigint &b) { return bigint(a) /= b; }
    friend bigint operator%(const bigint &a, const bigint &b) { return bigint(a) %= b; }
    friend bigint operator%(const bigint &a, const long long &b) { return bigint(a) %= b; }
};