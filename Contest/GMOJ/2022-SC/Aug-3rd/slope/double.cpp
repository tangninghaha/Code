#include <stdio.h>
#define int long long

const int MAXN = 2e5 + 5;
struct QQ
{
    int p;
    int q;
    void Simp();
};
struct Point
{
    int x;
    int y;
};
bool operator<(const Point &a, const Point &b);
bool operator>(const Point &a, const Point &b);

double Abs(double x);
void FileIO();
int Gcd(int a, int b);
int Lcm(int a, int b);
signed main();
void Qsort(int l, int r);
QQ Sovle(int n);
void Swap(Point &a, Point &b);

Point A[MAXN];
int P, Q;

void QQ::Simp()
{
    int g = Gcd(p, q);
    p /= g;
    q /= g;
    return;
}


bool operator<(const Point &a, const Point &b)
{
    return P * a.x - Q * a.y < P * b.x - Q * b.y;
}
bool operator>(const Point &a, const Point &b)
{
    return P * a.x - Q * a.y > P * b.x - Q * b.y;
}

double Abs(double x)
{
    return x > 0 ? x : -x;
}
void FileIO()
{
    freopen("slope.in", "r", stdin);
    freopen("slope.out", "w", stdout);
    return;
}
int Gcd(int a, int b)
{
    if (!b)
    {
        return a;
    }
    return Gcd(b, a % b);
}
int Lcm(int a, int b)
{
    return a / Gcd(a, b) * b;
}
signed main()
{
    FileIO();
    int n;
    scanf("%lld%lld%lld", &n, &P, &Q);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld%lld", &A[i].x, &A[i].y);
    }
    QQ ans = Sovle(n);
    ans.Simp();
    printf("%lld/%lld", ans.p, ans.q);
    return 0;
}
void Qsort(int l, int r)
{
    int i = l, j = r;
    Point mid = A[(l + r) >> 1];
    while (i <= j)
    {
        while (A[i] < mid)
            ++i;
        while (A[j] > mid)
            --j;
        if (i <= j)
        {
            Swap(A[i], A[j]);
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
QQ Sovle(int n)
{
    Qsort(1, n);
    double t = 1.0 * P / Q;
    double c = 1.0 * P / Q;
    QQ ret = (QQ){0, 0};
    double tmp;
    double n_c;
    double ret_num = t;
    for (int i = 1; i < n; ++i)
    {
        tmp = 1.0 * (A[i].y - A[i + 1].y) / (A[i].x - A[i + 1].x);
        if (tmp < 0)
        {
            continue;
        }
        n_c = tmp - t;
        n_c = Abs(n_c);
        if (n_c < c)
        {
            ret = (QQ){A[i].y - A[i + 1].y, A[i].x - A[i + 1].x};
            c = n_c;
            ret_num = tmp;
        }
        else if(n_c == c)
        {
            if (tmp < ret_num)
            {
                ret = (QQ){A[i].y - A[i + 1].y, A[i].x - A[i + 1].x};
                ret_num = tmp;
            }
        }
    }
    return ret;
}
void Swap(Point &a, Point &b)
{
    Point tmp = a;
    a = b;
    b = tmp;
}
