#include <stdio.h>

const int MAXN = 1e5 + 5;
long double f[MAXN];

int main();
long double qpow(long double a, int x);

int main()
{
    int n, m;
    scanf("%d%d", &m, &n);
    long double s = 0;
    long double ans = 0;
    for (int i = 1; i <= m; ++i)
    {
        f[i] = qpow(1.0 * i / m, n) - s;
        s += f[i];
        ans += f[i] * i;
    }
    printf("%Lf", ans);
    return 0;
}
long double qpow(long double a, int x)
{
    if (!x)
    {
        if (!a)
            return 0;
        return 1.0;
    }
    if (x == 1)
    {
        return a;
    }
    long double ret = qpow(a, x / 2);
    if (x & 1)
    {
        return ret * ret * a;
    }
    else
    {
        return ret * ret;
    }
}
