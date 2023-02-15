#include <cstdio>
#include <cmath>

/* Class */
struct Point
{
    int x;
    int y;
    Point();
};

/* Declaration */
int main();
double Len(const Point&, const Point&);
template<typename T> T Pow2(T _x);

/* Definition */
int main()
{
    freopen("fountain.in", "r", stdin);
    freopen("fountain.out", "w", stdout);
    Point A, B, C;
    int r;
    int t;
    scanf("%d", &t);
    double x, y, a, b, k;
    double x_cut_y;
    for (int fot = 1; fot <= t; ++fot)
    {
        scanf("%d%d%d%d%d%d%d", &A.x, &A.y, &B.x, &B.y, &C.x, &C.y, &r);
        a = Len(A, C);
        b = Len(B, C);
        k = Len(A, B);
        x_cut_y = (a + b) * (a - b) / k;
        x = (k + x_cut_y) / 2.0;
        y = k - x;
        printf("%.2lf ", sqrt(a * a - x * x) - r);
        if (x > y)
        {
            printf("%.2lf\n", a + r);
        }
        else
        {
            printf("%.2lf\n", b + r);
        }
    }
    return 0;
}
Point::Point()
{
    x = 0;
    y = 0;
    return;
}
double Len(const Point& _a, const Point& _b)
{
    return sqrt(Pow2((long long)_a.x - _b.x) + Pow2((long long)_a.y - _b.y));
}
template<typename T> T Pow2(T _x)
{
    return _x * _x;
}
