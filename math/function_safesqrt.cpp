int savesqrt(long long n)
{
    // assert(n < 4e18 && n >= 0);
    long long l = 0, r = 2e9, mid = (l + r) / 2;
    while (r - l > 1)
    {
        if (1ll * mid * mid <= n)
            l = mid;
        else
            r = mid;
        mid = (l + r) / 2;
    }
    return (int)l;
}