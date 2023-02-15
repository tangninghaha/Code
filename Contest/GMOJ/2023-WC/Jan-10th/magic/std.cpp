#include <cstdio>

/* Constant */
const int MAXN = 1e5 + 1;

/* Class */
struct Point
{
    int l;
    int r;
    bool operator<(const Point&);
};
bool Point::operator<(const Point& _a)
{
    return l < _a.l;
}

struct Tree
{
    int c[2 * MAXN];
    int lowbit(int);
    void Update(int, int);
    int query(int);
};
int Tree::lowbit(int _x)
{
    return _x & -_x;
}
void Tree::Update(int _x, int n)
{
    int i = _x;
    while (i <= n)
    {
        ++c[i];
        i += lowbit(i);
    }
    return;
}
int Tree::query(int _x)
{
    int ret = 0;
    while (_x >= 1)
    {
        ret += c[_x];
        _x -= lowbit(_x);
    }
    return ret;
}

/* Declaration */
int main();

template <typename T> void Qsort(int, int, T*);
template <typename T> void Swap(T&, T&);

/* Variable */
Point p[MAXN];

int x[MAXN];
int y[MAXN];
int z[MAXN];

int suml[MAXN * 2];
int sumr[MAXN * 2];

Tree T1, T2;

/* Definition */
int main()
{
    freopen("magic.in", "r", stdin);
    freopen("magic.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d", &p[i].l, &p[i].r);
        if (p[i].l > p[i].r)
        {
            Swap(p[i].l, p[i].r);
        }
        ++suml[p[i].l];
        ++sumr[p[i].r];
    }
    for (int i = 1; i <= 2 * n; ++i)
    {
        suml[i] += suml[i - 1];
        sumr[i] += sumr[i - 1];
    }
    Qsort(1, n, p);

    for (int i = 1; i <= n; ++i)
    {
        x[i] += sumr[p[i].l - 1];
        x[i] += suml[2 * n] - suml[p[i].r];
        x[i] += T1.query(2 * n) - T1.query(p[i].r);
        T1.Update(p[i].r, 2 * n);
    }
    for (int i = n; i >= 1; --i)
    {
        y[i] += T2.query(p[i].r);
        z[i] = n - x[i] - y[i] - 1;
        T2.Update(p[i].r, 2 * n);
    }

    long long ans = 0;
    long long sum = 0;
    for (int i = 1; i <= n; ++i)
    {
        ans += (long long)x[i] * y[i];
        sum += (((long long)x[i] + y[i]) * z[i]);
    }
    ans += sum / 2;
    printf("%lld", (long long)n * (n - 1) * (n - 2) / 6 - ans);
    return 0;
}

template <typename T> void Qsort(int l, int r, T* _a)
{
    T mid = _a[(l + r) >> 1];
    int i = l, j =r;
    while (i <= j)
    {
        while (_a[i] < mid)
            ++i;
        while (mid < _a[j])
            --j;
        if (i <= j)
        {
            Swap(_a[i], _a[j]);
            ++i;
            --j;
        }
    }
    if (i < r)
        Qsort(i, r, _a);
    if (l < j)
        Qsort(l, j, _a);
    return;
}
template <typename T> void Swap(T& _a, T& _b)
{
    T _t = _a;
    _a = _b;
    _b = _t;
    return;
}
