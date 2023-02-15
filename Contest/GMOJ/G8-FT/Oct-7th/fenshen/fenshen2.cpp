#include <cstdio>

/* Constant */
const int MAXN = 1e7 + 5;
const int INF = 1e8 + 5;

/* Declaration */
int main();
void Qsort(int, int);
void Swap(int&, int&);
bool Cmp(int, int);
int Min(int, int);
int Abs(int);
int Max(int, int);

/* Variable */
int a[MAXN];
int b[MAXN];
int rnk[MAXN];
int rnk_max[MAXN];
int rnk_min[MAXN];

/* Definition */
int main()
{
    freopen("fenshen.in", "r", stdin);
    freopen("fenshen.out", "w", stdout);
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &b[i]);
    }
    for (int i = 1; i <= n; ++i)
    {
        rnk[i] = i;
    }
    Qsort(1, n);
    rnk[n + 1] = n + 1;
    for (int i = n; i >= 1; --i)
    {
        rnk_min[i] = Min(rnk_min[i + 1], rnk[i]);
        rnk_max[i] = Max(rnk_max[i + 1], rnk[i]);
    }
    int lbound, rbound, mid;
    int to;
    int l, r;
    int f;
    int ans = INF;
    for (int i = 1; i <= n; ++i)
    {
        to = a[i] + k;
        lbound = 1;
        rbound = n;
        l = -1;
        r = -1;
        while (lbound <= rbound)
        {
            mid = (lbound + rbound) >> 1;
            if (b[mid] >= to)
            {
                l = rnk_min[mid];
                r = rnk_max[mid];
                f = mid;
                rbound = mid - 1;
            }
            else
            {
                lbound = mid + 1;
            }
        }
        if (l == -1)
            continue;
        if (r <= i)
        {
            ans = Min(ans, i - r + 1);
            continue;
        }
        if (i <= l)
        {
            ans = Min(ans, l - i + 1);
            continue;
        }
        for (int j = f; j <= n; ++j)
        {
            if (b[j] >= to)
            {
                ans = Min(ans, Abs(i - rnk[j] + 1));
            }
        }
    }
    if (ans != INF)
        printf("%d", ans);
    else
        printf("So Sad!");
    return 0;
}
void Qsort(int l, int r)
{
    int i = l, j = r;
    int mid = (l + r) >> 1;
    while (i <= j)
    {
        while (Cmp(i, mid))
            ++i;
        while (Cmp(mid, j))
            --j;
        if (i <= j)
        {
            Swap(b[i], b[j]);
            Swap(rnk[i], rnk[j]);
            if (mid == i)
                mid = j;
            else if (mid == j)
                mid = i;
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
void Swap(int& _a, int& _b)
{
    int tmp = _a;
    _a = _b;
    _b = tmp;
    return;
}
bool Cmp(int x, int y)
{
    if (b[x] == b[y])
    {
        return rnk[x] < rnk[y];
    }
    return b[x] < b[y];
}
int Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
int Abs(int _x)
{
    return _x < 0 ? -_x : _x;
}
int Max(int _a, int _b)
{
    return _a > _b ? _a : _b;
}
