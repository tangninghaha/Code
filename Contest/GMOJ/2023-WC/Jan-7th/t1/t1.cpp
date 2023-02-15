#include <cstdio>

/* Constant */
const int MAXN = 1e9 + 5;
const int N = 1e6 + 1;

/* Declaration */
int main();
long long qpow(long long, long long, const long long);

/* Variable */
int pd[N];
long long sum[N];

/* Definition */
int main()
{
    int n, m;
    long long a, b, c;
    long long x;
    scanf("%lld", &x);
    scanf("%lld%lld%lld", &a, &b, &c);
    scanf("%d%d", &n, &m);
    const long long mod = m;
    x %= mod;
    long long nxt;
    if (n <= 1e6)
    {
        for (int i = 1; i <= n; ++i)
        {
            nxt = a * x;
            nxt %= mod;
            nxt *= x;
            nxt %= mod;
            nxt += (b * x) % mod;
            nxt %= mod;
            nxt += c;
            nxt %= mod;
            x = nxt;
        }
        printf("%lld", x);
        return 0;
    }
    else if (mod <= 1e6)
    {
        for (int i = 1; i <= n; ++i)
        {
            nxt = a * x;
            nxt %= mod;
            nxt *= x;
            nxt %= mod;
            nxt += (b * x) % mod;
            nxt %= mod;
            nxt += c;
            nxt %= mod;
            x = nxt;
            if (pd[x])
            {
                int len = i - pd[x];
                n -= pd[x] - 1;
                printf("%lld", sum[pd[x] - 1 + (n % len)]);
                return 0;
            }
            pd[x] = i;
            sum[i] = x;
        }
        printf("%lld", x);
        return 0;
    }
    else
    {
        int k = b / 2 / a;
        int zs = qpow(2, n, mod -  1);
        --zs;
        zs = (zs % (mod - 1) + (mod - 1)) % (mod - 1);
        long long ans = qpow(a, zs, mod);
        ++zs;
        zs %= (mod - 1);
        ans *= qpow((x + k) % mod, zs, mod);
        ans %= mod;
        ans -= k;
        ans = (ans % mod + mod) % mod;
        printf("%lld", ans);
    }
    return 0;
}
long long qpow(long long _a, long long _b, const long long _mod)
{
    if (_b == 1)
    {
        return _a;
    }
    long long ret = qpow(_a, _b / 2, _mod);
    if (_b & 1)
    {
        return (((ret * ret) % _mod) * _a) % _mod;
    }
    else
    {
        return (ret * ret) % _mod;
    }
    return 1;
}
