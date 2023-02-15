#include <cstdio>
#include <cmath>

/* Constant */
const int MAXN = 1e5 + 5;
const double EXP = 1e-10;

/* Class */
class Point
{
    public:
        double x;
        double y;
};
class Vector
{
    public:
        double x;
        double y;
};
double Dot(const Vector& _a, const Vector& _b)
{
    return _a.x * _b.x + _a.y * _b.y;
}
double Length(const Vector& _a)
{
    return sqrt(Dot(_a, _a));
}
Vector operator-(const Point& _a, const Point& _b)
{
    return (Vector){_a.x - _b.x, _a.y - _b.y};
}
double operator*(const Vector& _a, const Vector& _b)
{
    return _a.x * _b.y - _a.y * _b.x;
}

/* Declaration */
int Cmp(double);

int main();

void Qsort(int, int);
template<typename T>void Swap(T&, T&);

bool operator<(const Point&, const Point&);

/* Variable */
Point p[MAXN];
int convex_hull[MAXN];

/* Definition */
bool operator<(const Point& _a, const Point& _b)
{
    if (Cmp(_a.x - _b.x) == 0)
        return Cmp(_a.y - _b.y) < 0;
    return Cmp(_a.x - _b.x) < 0;
}
int Cmp(double _a)
{
    return abs(_a) <= EXP ? 0 : (_a < 0 ? -1 : 1);
}
int main()
{
    freopen("in.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lf%lf", &p[i].x, &p[i].y);
    Qsort(1, n);
    int top = 1;
    convex_hull[1] = 1;
    for (int i = 1; i <= n; ++i)
    {
        while (top > 1 && Cmp((p[convex_hull[top]] - p[convex_hull[top - 1]]) * (p[i] - p[convex_hull[top]])) <= 0)
            --top;
        convex_hull[++top] = i;
    }
    int k = top;
    for (int i = n - 1; i >= 1; --i)
    {
        while (top > k && Cmp((p[convex_hull[top]] - p[convex_hull[top - 1]]) * (p[i] - p[convex_hull[top]])) <= 0)
            --top;
        convex_hull[++top] = i;
    }
//    for (int i = 1; i <= n; ++i)
//    {
//        printf("%d ", convex_hull[i]);
//    }
    double ans = 0;
    for (int i = 2; i <= top; ++i)
    {
        ans += Length(p[convex_hull[i]] - p[convex_hull[i - 1]]);
    }
    printf("%.2lf", ans);
    return 0;
}
void Qsort(int l, int r)
{
    int i = l;
    int j = r;
    Point mid = p[l + r >> 1];
    while (i <= j)
    {
        while (p[i] < mid)
            ++i;
        while (mid < p[j])
            --j;
        if (i <= j)
        {
            Swap(p[i], p[j]);
            ++i;
            --j;
        }
    }
    if (i < r)
        Qsort(i, r);
    if (l < j)
        Qsort(l, j);
    return;
}
template<typename T>void Swap(T& _a, T& _b)
{
    T tmp = _a;
    _a = _b;
    _b = tmp;
    return;
}
