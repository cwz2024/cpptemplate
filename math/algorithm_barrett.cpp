struct barrett
{
    unsigned int _m;
    unsigned long long im;

    // @param m `1 <= m`
    explicit barrett(unsigned int m) : _m(m), im((unsigned long long)(-1) / m + 1) {}

    friend unsigned int operator%(unsigned long long z, barrett m)
    {
        unsigned long long x =
            (unsigned long long)(((unsigned __int128)(z)*m.im) >> 64);

        unsigned long long y = x * m._m;
        return (unsigned int)(z - y + (z < y ? m._m : 0));
    }
};