#include <cstdio>
const long long T = 1e17;

int main()
{
    freopen("test.txt", "w", stdout);
    int n = 1e6;
    long long sum1 = 0;
    long long sum2 = 0;
    for (int i = 1; i <= n; ++i)
    {
        sum1 += (long long)i * i * 1000;
        if (sum1 >= T)
        {
            sum2 += sum1 / T;
            sum1 %= T;
        }
        printf("%d ", i);
        if (sum2)
        {
            printf("%lld%017lld\n", sum2, sum1);
        }
        else
            printf("%lld\n", sum1);
    }
    return 0;
}
