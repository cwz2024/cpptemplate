#include <bits/stdc++.h>
using namespace std;

template <class... T>
void ask(const T &...b)
{
    cout << "?";
    (cout << ... << (cout << ' ', b));
    cout << endl;
}
template <class... T>
void ans(const T &...b)
{
    cout << "!";
    (cout << ... << (cout << ' ', b));
    cout << endl;
}