#include <stdio.h>

const int MAXN = 16;
const long long MAXANS = 1e15;
long long a[MAXN];

long long gcd(long long a, long long b);

int main()
{
    int n;
    long long k;
    scanf("%d%lld", &n, &k);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", &a[i]);
    }
    bool pd;
    long long k_used = 0;
    int bh;
    for (long long i = 1; i <= MAXANS; ++i)
    {
        bh = 0;
        for (int j = 1; j <= n; ++j)
        {
            if (!(i % a[j]))
            {
                bh = j;
                break;
            }
        }
        if (!bh) continue;
        pd = 0;
        for (int k = 1; k <= n; ++k)
        {
            if (k != bh && gcd(a[k], i) == a[k])
            {
                pd = true;
                break;
            }
        }
        if (!pd)
        {
            ++k_used;
            if (k_used == k)
            {
                printf("%lld", i);
                return 0;
            }
        }
    }
    return 0;
}

long long gcd(long long a, long long b)
{
    return !b ? a : gcd(b, a % b);
}
