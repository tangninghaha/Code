#include <cstdio>

/* Declaration */
int main();
long long qpow(long long, long long);

/* Definition */
long long qpow(long long a, long long b)
{
    if (!b)
        return 1;
    if (b == 1)
        return a;
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
int main()
{
    long long k;
    scanf("%lld", &k);
    while (k)
    {
        long long ans = 0;
        long long xz, yz, xyz;
        for (long long z = 2; z <= 31; ++z)
        {
            for (long long x = 1; x <= 2147483647; ++x)
            {
                xz = qpow(x, z);
                if (xz > k)
                    break;
                for (long long y = x + 1; y <= 2147483647; ++y)
                {
                    yz = qpow(y, z);
                    if (yz > k)
                        break;
                    xyz = x * y * z;
                    if (xz + yz + xyz > k)
                        break;
                    if (xz + yz + xyz == k)
                    {
                        // printf("%lld %lld %lld\n", x, y, z);
                        ++ans;
                    }
                }
            }
        }
        printf("%lld\n", ans);
        scanf("%lld", &k);
    }
}
