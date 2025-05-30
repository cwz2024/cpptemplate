#include <bits/stdc++.h>
using namespace std;
std::pair<long long, long long> inv_gcd(long long a, long long b)
{
    a = a % b;
    if (a < 0)
        a += b;
    if (a == 0)
        return {b, 0};

    long long s = b, t = a;
    long long m0 = 0, m1 = 1;

    while (t)
    {
        long long u = s / t;
        s -= t * u;
        m0 -= m1 * u;

        auto tmp = s;
        s = t;
        t = tmp;
        tmp = m0;
        m0 = m1;
        m1 = tmp;
    }

    if (m0 < 0)
        m0 += b / s;
    return {s, m0};
}

// (rem, mod)
std::pair<long long, long long> crt(const std::vector<long long> &r,
                                    const std::vector<long long> &m)
{
    assert(r.size() == m.size());
    int n = int(r.size());
    // Contracts: 0 <= r0 < m0
    long long r0 = 0, m0 = 1;
    for (int i = 0; i < n; i++)
    {
        assert(1 <= m[i]);
        long long r1 = r[i] % m[i], m1 = m[i];
        if (r1 < 0)
            r1 += m[i];
        if (m0 < m1)
        {
            std::swap(r0, r1);
            std::swap(m0, m1);
        }
        if (m0 % m1 == 0)
        {
            if (r0 % m1 != r1)
                return {0, 0};
            continue;
        }
        // assume: m0 > m1, lcm(m0, m1) >= 2 * max(m0, m1)

        // (r0, m0), (r1, m1) -> (r2, m2 = lcm(m0, m1));
        // r2 % m0 = r0
        // r2 % m1 = r1
        // -> (r0 + x*m0) % m1 = r1
        // -> x*u0*g = r1-r0 (mod u1*g) (u0*g = m0, u1*g = m1)
        // -> x = (r1 - r0) / g * inv(u0) (mod u1)

        // im = inv(u0) (mod u1) (0 <= im < u1)
        long long g, im;
        std::tie(g, im) = inv_gcd(m0, m1);

        long long u1 = (m1 / g);
        // |r1 - r0| < (m0 + m1) <= lcm(m0, m1)
        if ((r1 - r0) % g)
            return {0, 0};

        // u1 * u1 <= m1 * m1 / g / g <= m0 * m1 / g = lcm(m0, m1)
        long long x = (r1 - r0) / g % u1 * im % u1;

        // |r0| + |m0 * x|
        // < m0 + m0 * (u1 - 1)
        // = m0 + m0 * m1 / g - m0
        // = lcm(m0, m1)
        r0 += x * m0;
        m0 *= u1; // -> lcm(m0, m1)
        if (r0 < 0)
            r0 += m0;
    }
    return {r0, m0};
}
