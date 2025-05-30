#include <stdio.h>
#include <math.h>
#define Pi acos(-1)
const double eps = 1e-8;
typedef struct Point
{
    double x;
    double y;
} point;
typedef struct Line
{
    point p1;
    point p2;
} line;
point crossing_point(line l1, line l2)
{
    const double eps = 1e-8;
    point p1, p2, p3, p4;
    p1 = l1.p1, p2 = l1.p2, p3 = l2.p1, p4 = l2.p2;
    point n = {1e9, 1e9};
    double k = -(p1.y - p2.y) * (p3.x - p4.x) + (p3.y - p4.y) * (p1.x - p2.x);
    double l = (p3.y * p4.x - p3.x * p4.y) * (p1.y - p2.y) - (p1.y * p2.x - p1.x * p2.y) * (p3.y - p4.y);
    double m = (p3.y * p4.x - p3.x * p4.y) * (p1.x - p2.x) - (p1.y * p2.x - p1.x * p2.y) * (p3.x - p4.x);
    if ((k > 0 ? k : -k) < eps)
        return n;
    n.y = l / k;
    n.x = m / k;
    return n;
}
double kOf(line l)
{
    const double eps = 1e-8;
    double dx = l.p1.x - l.p2.x, dy = l.p1.y - l.p2.y;
    if (fabs(dx) < eps)
        return 1e9;
    else
        return dy / dx;
}
line makeLine(point p, double k)
{
    line ans = {p};
    if (k > 1e8)
    {
        point p2 = {p.x, p.y + 10};
        ans.p2 = p2;
    }
    else
    {
        point p2 = {p.x + 5, p.y + 5 * k};
        ans.p2 = p2;
    }
    return ans;
}
double dist(point p1, point p2)
{
    double ans = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    return ans;
}
point midPoint(point p1, point p2)
{
    point p = {(p1.x + p2.x) / 2, (p1.y + p2.y) / 2};
    return p;
}
double angleOf(point p1, point p0, point p2)
{
    double l01 = dist(p1, p0), l02 = dist(p0, p2), l12 = dist(p1, p2);
    return acos((l01 * l01 + l02 * l02 - l12 * l12) / (2 * l01 * l02));
}
double tri_area(point a, point b, point c)
{
    double x1 = b.x - a.x, x2 = c.x - a.x;
    double y1 = b.y - a.y, y2 = c.y - a.y;
    return fabs(x1 * y2 - x2 * y1) / 2;
}