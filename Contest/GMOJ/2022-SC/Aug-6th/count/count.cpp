#include <stdio.h>

int lowbit(int x)
{
    return x & -x;
}
int GetNum(int x)
{
    int ret = 0;
    while (x)
    {
        x -= lowbit(x);
        ++ret;
    }
    return ret;
}
int main()
{
    freopen("count.in", "r", stdin);
    freopen("count.out", "w", stdout);
    int t;
    scanf("%d", &t);
    int a, n;
    long long b;
    for (int i = 1; i <= t; ++i)
    {
        scanf("%d%lld%d", &a, &b, &n);
        long long num = b;
        long long ans = 0;
        for (int j = 1; j <= n; ++j)
        {
            num += a;
            ans += GetNum(num);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
