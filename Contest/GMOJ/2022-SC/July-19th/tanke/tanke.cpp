#include <stdio.h>
const int MAXN = 7001;
long long f[MAXN], g[MAXN];
struct Point
{
    int x;
    int y;
};
void swap(Point &a, Point &b);
void Qsort(int l, int r);
Point p[MAXN];

int main()
{
    int n;
    long long q;
    long long ans = 0;
    scanf("%d%lld", &n, &q);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d", &p[i].x, &p[i].y);
    }
    Qsort(1, n);
    for (int i = 1; i <= n; ++i)
    {
        f[i] = g[i] = 1;
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = i - 1; j >= 1; --j)
        {
            if (p[i].y > p[j].y)
            {
                f[i] += g[j];
                f[i] %= q;
            }
            else
            {
                g[j] += f[i];
                g[j] %= q;
            }
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        ans += f[i];
        ans %= q;
        ans += g[i];
        ans %= q;
    }
    ans = ((ans - n) % q + q) % q;
    printf("%lld", ans);
}

void Qsort(int l, int r)
{
    int i = l, j = r;
    Point mid = p[(l + r) / 2];
    while (i <= j)
    {
        while (p[i].x < mid.x)
            ++i;
        while (p[j].x > mid.x)
            --j;
        if (i <= j)
        {
            swap(p[i], p[j]);
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
void swap(Point &a, Point &b)
{
    Point t = a;
    a = b;
    b = t;
}
