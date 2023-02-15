#include <cstdio>

/* Constant */
const long long mod = 1e9 + 7;
/* Declaration */
int main();
long long qpow(long long x, int y);

/* Definition*/
int main()
{
    freopen("loop.in", "r", stdin);
    freopen("loop.out", "w", stdout);
    long long n, m;
    scanf("%lld%lld", &n, &m);
    long long ans = 0;
    long long sum1, tmp, sum2;
    long long mm = m % mod, nm = n % mod;
    sum1 = (((mm * mm) % mod) * mm) % mod;
    sum1 += (((2 * (mm % mod)) % mod) * mm) % mod;
    sum1 %= mod;
    sum1 += mm;
    sum1 %= mod;
    sum1 *= qpow(2, mod - 2);
    sum1 %= mod;
    tmp = (((mm * (mm + 1)) % mod) * (2 * mm + 1)) % mod;
    tmp *= qpow(6, mod - 2);
    tmp %= mod;
    sum1 -= tmp;
    sum1 = ((sum1 % mod) + mod) % mod;
    
    
    sum2 = (((nm * nm) % mod) * nm) % mod;
    sum2 += (((2 * (nm % mod)) % mod) * nm) % mod;
    sum2 %= mod;
    sum2 += nm;
    sum2 %= mod;
    sum2 *= qpow(2, mod - 2);
    sum2 %= mod;
    tmp = (((nm * (nm + 1)) % mod) * (2 * nm + 1)) % mod;
    tmp *= qpow(6, mod - 2);
    tmp %= mod;
    sum2 -= tmp;
    sum2 = ((sum2 % mod) + mod) % mod;
    ans = (sum1 * sum2) % mod;
    
//    for (int i = 1; i <= n; ++i)
//    {
//        ans += (((sum1 * ((n - i + 1) % mod)) % mod) * i) % mod;
//        ans %= mod;
//    }
    printf("%lld", ans);
    return 0;
}
long long qpow(long long x, int y)
{
    long long ret = 1;
    while (y)
    {
        if (y & 1)
        {
            ret *= x;
            ret %= mod;
        }
        x = x * x;
        x %= mod;
        y /= 2;
    }
    return ret;
}
