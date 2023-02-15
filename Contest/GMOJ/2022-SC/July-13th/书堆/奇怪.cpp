#include <stdio.h>

int main()
{
    long long n, m;
    long double ans = 1;
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        ans *= 0.5;
    }
    ans = 1 - ans;
    long long anss = m * ans;
    if (anss == m * ans)
    {
        --anss;
    }
    printf("%lld", anss);
}
