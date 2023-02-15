#include <stdio.h>

int main();
long long qpow(int a, int b);

int main()
{
    freopen("dice.in", "r", stdin);
    freopen("dice.out", "w", stdout);
    int m, n;
    scanf("%d%d", &m, &n);
    long long sum;
    long long z = qpow(m, n);
    double ans = 0;
    for (int i = 1; i <= m; ++i)
    {
        sum = 0;
        for (int j = 1; j <= n; ++j)
        {
            sum += qpow(i, j - 1) * qpow(i - 1, n - j);
        }
        ans += i * (1.0 * sum / z);
    }
    printf("%lf", ans);
    return 0;
}
long long qpow(int a, int b)
{
    if (!b)
    {
        return 1;
    }
    if (b == 1)
    {
        return a;
    }
    long long ret = qpow(a, b / 2);
    if (b & 1)
    {
        return ret * ret * a;
    }
    else
    {
        return ret * ret;
    }
    return 1;
}
