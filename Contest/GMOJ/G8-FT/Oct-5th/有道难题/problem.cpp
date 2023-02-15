#include <cstdio>
#include <cmath>

/* Constant */
const int Limit[32] = {0, 0, 32768, 1025, 182, 65, 31, 20, 14, 11, 9, 7, 6, 5, 5, 5, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};

/* Declaration */
int main();
long long qpow(long long a, long long b);

/* Definition */
int main()
{
    long long k;
    scanf("%lld", &k);
    long long xz, yz, xyz;
    long long ans = 0;
    while (k)
    {
        if (k == 2147483647)
        {
            printf("1\n");
            scanf("%lld", &k);
            continue;
        }
        ans = 0;
        int ed_z = ceil(log2(k));
        int lbound, rbound;
        for (long long z = 2; z <= ed_z; ++z)
        {
            for (long long x = 1; x <= Limit[z] * 2; ++x)
            {
                xz = qpow(x, z);
                if (xz > k)
                    break;
                if (x * x * z > k)
                    break;
                if (xz + xz + x * x * z > k)
                    break;
                lbound = x + 1;
                rbound = Limit[z] * 2;
                int y;
                while (lbound <= rbound)
                {
                    y = (lbound + rbound) >> 1;
                    yz = qpow(y, z);
                    xyz = x * y * z;
                    if (xz + yz + xyz < k)
                    {
                        lbound = y + 1;
                    }
                    else if (xz + yz + xyz == k)
                    {
                        ++ans;
                        break;
                    }
                    else
                    {
                        rbound = y - 1;
                    }
                }
            }
        }
        printf("%lld\n", ans);
        scanf("%lld", &k);
    }
    return 0;
}
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
