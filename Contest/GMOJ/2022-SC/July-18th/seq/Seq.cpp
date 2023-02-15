#include <stdio.h>
const int mod = 998244353;
long long f[205];
int b[205];
long long qpow(long long a, long long b);
int main()
{
    freopen("seq.in", "r", stdin);
    freopen("seq.out", "w", stdout);
    int n, k;
    scanf("%d%d", &n, &k);
    int tmp_s = 0;
    long long tmp_c = 0;
    for (int i = 1; i <= k; ++i)
    {
        scanf("%d", &b[i]);
        tmp_s += b[i];
    }
    for (int i = 1; i <= k; ++i)
    {
        scanf("%lld", &f[k - i + 1]);
        tmp_c *= f[k - i + 1];
    }
    if (tmp_s == k)
    {
        int st = 2;
        long long x;
        for (int i = k + 1; i <= n; ++i)
        {
            --st;
            if (st <= 0)
            {
                st += k;
            }
            x = 1;
            for (int j = 1; j <= k; ++j)
            {
                x *= f[(st + (j - 1) - 1) % k + 1];
                x %= mod;
            }
            f[k - ((i - 1) % k + 1) + 1] = x;
        }
        printf("%lld", x % mod);
        return 0;
    }
    long long x;
    int st = 2;
    for (int i = k + 1; i <= n; ++i)
    {
        --st;
        if (st <= 0)
        {
            st += k;
        }
        x = 1;
        for (int j = 1; j <= k; ++j)
        {
            x *= qpow(f[(st + (j - 1) - 1) % k + 1], b[j]) % mod;
            x %= mod;
        }
        f[k - ((i - 1) % k + 1) + 1] = x;
    }
    printf("%lld", x % mod);
    return 0;
}
long long qpow(long long a, long long b)
{
    if (b == 0)
        return 1;
    if (b == 1)
        return a;
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
