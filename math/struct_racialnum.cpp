#include <bits/stdc++.h>
using namespace std;

struct racial
{
private:
    int _p, _q;

public:
    int p() const { return _p; }
    int q() const { return _q; }
    racial inv() const
    {
        assert(_p != 0);
        return racial(_q, _p);
    }

    racial &operator++()
    {
        _p += _q;
        return *this;
    }
    racial &operator--()
    {
        _p -= _q;
        return *this;
    }
    racial operator++(int)
    {
        racial result = *this;
        ++*this;
        return result;
    }
    racial operator--(int)
    {
        racial result = *this;
        --*this;
        return result;
    }

    racial operator+() const { return *this; }
    racial operator-() const { return racial(-_p, _q); }
    racial &operator+=(const racial &rhs)
    {
        if (rhs._q == 1)
        {
            _p += _q * rhs._p;
            return *this;
        }
        if (_q == rhs._q)
        {
            _p += rhs._p;
        }
        else
        {
            _p = _p * rhs._q + _q * rhs._p;
            _q *= rhs._q;
        }
        simp();
        return *this;
    }
    racial &operator-=(const racial &rhs)
    {
        return *this += (-rhs);
    }
    racial &operator*=(const racial &rhs)
    {
        _p *= rhs._p;
        _q *= rhs._q;
        simp();
        return *this;
    }
    racial &operator/=(const racial &rhs)
    {
        assert(rhs._p != 0);
        _p *= rhs._q;
        _q *= rhs._p;
        simp();
        return *this;
    }

    friend racial operator+(const racial &lhs, const racial &rhs) { return racial(lhs) += rhs; }
    friend racial operator-(const racial &lhs, const racial &rhs) { return racial(lhs) -= rhs; }
    friend racial operator*(const racial &lhs, const racial &rhs) { return racial(lhs) *= rhs; }
    friend racial operator/(const racial &lhs, const racial &rhs) { return racial(lhs) /= rhs; }

    friend bool operator==(const racial &lhs, const racial &rhs) { return lhs._p == rhs._p && lhs._q == rhs._q; }
    friend bool operator!=(const racial &lhs, const racial &rhs) { return !(lhs == rhs); }
    friend bool operator<(const racial &lhs, const racial &rhs)
    {
        return 1ll * lhs.p() * rhs.q() < 1ll * lhs.q() * rhs.p();
    }
    friend bool operator<=(const racial &lhs, const racial &rhs) { return lhs == rhs || lhs < rhs; }
    friend bool operator>(const racial &lhs, const racial &rhs) { return !(lhs <= rhs); }
    friend bool operator>=(const racial &lhs, const racial &rhs) { return !(lhs < rhs); }
    friend ostream &operator<<(ostream &o, const racial &rhs)
    {
        if (rhs._q == 1)
            return o << rhs._p;
        else
            return o << rhs._p << '/' << rhs._q;
    }

    racial() : _p(0), _q(1) {}
    racial(int p) : _p(p), _q(1) {}
    racial(int p, int q) : _p(p), _q(q)
    {
        assert(q != 0);
        simp();
    }

    operator double()
    {
        return double(_p) / _q;
    }

    operator int()
    {
        return int(double(*this));
    }

private:
    void simp()
    {
        if (_q < 0)
            _p = -_p, _q = -_q;
        int g = gcd(_p, _q);
        _p /= g, _q /= g;
    }
};