#include <stdio.h>
#include <cmath>

const int MAXN = 15;
int a[MAXN];
int c[MAXN];
int two_pow[16];
long long f[(int)pow(2, 15)];
int tot;

long long GetNum();
long long Dfs(int x, int t);
long long gcd(long long a, long long b);
long long lcm(long long a, long long b);
long long nans;
int n;
long long k;

int main()
{
    two_pow[0] = 1;
    for (int i = 1; i < 16; ++i)
    {
        two_pow[i] = two_pow[i - 1] << 1;
    }
    scanf("%d%lld", &n, &k);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &a[i]);
    }
    int totf = pow(2, n);
    for (int i = 0; i < totf; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i >> j & 1)
            {
                if (!f[i])
                    f[i] = a[j];
                else
                {
                    f[i] = lcm(f[i], a[j]);
                }
                // printf("%lld ", f[i]);
            }
        }
        // printf("\n");
    }
    long long lbound = 1, rbound = 1000000000000000, ret, ans;
    while (lbound <= rbound)
    {
        nans = lbound + rbound >> 1;
        ret = GetNum();
        if (ret < k)
        {
            lbound = nans + 1;
        }
        else if(ret > k)
        {
            rbound = nans - 1;
        }
        else
        {
            rbound = nans;
            ans = nans;
            if (lbound == rbound) break;
        }
    }
    printf("%lld", ans);
}

long long GetNum()
{
    long long ret = 0;
    for (int i = 1; i <= n; ++i)
    {
        ret += Dfs(0, i) * (i & 1 ? 1 : -1);
    }
    return ret;
}
long long Dfs(int x, int t)
{
    long long ret = 0;
    if (tot == t)
    {
        long long g;
        int zt = 0;
        for (int i = 0; i < tot; ++i)
        {
            zt += two_pow[c[i]];
        }
        g = f[zt];
        ret += nans / g;
        return ret;
    }
    if (x >= n) return 0;
    c[tot] = x;
    ++tot;
    ret += Dfs(x + 1, t);
    --tot;
    c[tot] = 0;
    ret += Dfs(x + 1, t);
    return ret;
}

long long gcd(long long a, long long b)
{

    return b == 0 ? a : gcd(b, a % b);
}
long long lcm(long long a, long long b)
{
    return a / gcd(a, b) * b;
}
