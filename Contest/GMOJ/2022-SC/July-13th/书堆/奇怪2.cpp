#include <stdio.h>
long double qpow(long double a, long long b);
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    long double qp = (1 - qpow(0.5, n));
    long long anss = qp * m;
    if (anss == qp * m)
    {
        --anss;
    }
    printf("%lld", anss);
    return 0;
}
long double qpow(long double a, long long b)
{
    if (b == 0)
        return 1;
    if (b == 1)
        return a;
    long double ret = qpow(a, b / 2);
    if (b % 2)
    {
        return ret * ret * a;
    }
    else
    {
        return ret * ret;
    }
    return ret;
}
