#include <stdio.h>
#define int long long

const int MAXN = 2e5 + 5;
struct QQ
{
    int p;
    int q;
    void Simp();
};
QQ operator-(const QQ &a, const QQ &b);
bool operator<(const QQ &a, const QQ &b);
bool operator==(const QQ &a, const QQ &b);
bool operator>(const QQ &a, const QQ &b);
struct Point
{
    int x;
    int y;
};
bool operator<(const Point &a, const Point &b);
bool operator>(const Point &a, const Point &b);

QQ Abs(const QQ &x);
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
QQ operator-(const QQ &a, const QQ &b)
{
    int l = Lcm(a.q, b.q);
    QQ tmp = (QQ){l / a.q * a.p - l / b.q * b.p, l};
    tmp.Simp();
    return tmp;
}
bool operator<(const QQ &a, const QQ &b)
{
    return (unsigned long long) a.p * b.q < (unsigned long long) a.q * b.p;
}
bool operator==(const QQ &a, const QQ &b)
{
    return (unsigned long long) a.p * b.q == (unsigned long long) a.q * b.p;
}
bool operator>(const QQ &a, const QQ &b)
{
    return (unsigned long long) a.p * b.q > (unsigned long long) a.q * b.p;
}


bool operator<(const Point &a, const Point &b)
{
    return P * a.x - Q * a.y < P * b.x - Q * b.y;
}
bool operator>(const Point &a, const Point &b)
{
    return P * a.x - Q * a.y > P * b.x - Q * b.y;
}

QQ Abs(const QQ &x)
{
    QQ tmp = x;
    if (tmp.p < 0)
    {
        tmp.p = -tmp.p;
    }
    if (tmp.q < 0)
    {
        tmp.q = -tmp.q;
    }
    return tmp;
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
    QQ t = (QQ){P, Q};
    t.Simp();
    QQ c = (QQ){P, Q};
    c.Simp();
    QQ ret = (QQ){0, 0};
    QQ tmp, n_c;
    bool pd;
    for (int i = 1; i < n; ++i)
    {
        pd = false;
        tmp = (QQ){A[i].y - A[i + 1].y, A[i].x - A[i + 1].x};
        if (tmp.p * tmp.q < 0)
        {
            continue;
        }
        tmp = Abs(tmp);
        tmp.Simp();
        if (tmp.p == 47804847 && tmp.q == 511496011)
        {
            printf("%d\n", i);
        }
        n_c = tmp - t;
//        if (n_c.p * n_c.q < 0)
//        {
//            continue;
//        }
        n_c = Abs(n_c);
        n_c.Simp();
        if (n_c < c)
        {
            ret = tmp;
            c = n_c;
        }
        else if(n_c == c)
        {
            if (tmp < ret)
            {
                ret = tmp;
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
