#include <stdio.h>

int n, m;

const int mod = 1000000007;
long long qpow(int a, int b);

int main()
{
    scanf("%d%d", &n, &m);
    if (n == 2)
    {
        printf("%lld", (qpow(2, m + 1) * 3) % mod);
        return 0;
    }
    if (m == 2)
    {
        printf("%lld", (qpow(2, n + 1) * 3) % mod);
        return 0;
    }
    printf("%lld", (((((qpow(2, m + 1) - 8) % mod + mod) % mod) * 3) % mod + (qpow(2, n + 1) * 3) %mod) %mod);
    return 0;
}

long long qpow(int a, int b)
{
    if (b == 0) return 1;
    if (b == 1) return a;
    long long ret = qpow(a, b / 2) % mod;
    if (b & 1)
    {
        return (((ret * ret) % mod) * a) % mod;
    }
    else
    {
        return (ret * ret) % mod;
    }
    return 1;
}
