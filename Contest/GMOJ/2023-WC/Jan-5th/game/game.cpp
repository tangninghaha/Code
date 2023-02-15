#include <cstdio>

/* Declaration */
int main();

/* Definition */
int main()
{
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    int n, m, w, h;
    scanf("%d%d", &n, &m);
    scanf("%d%d", &w, &h);
    int k1 = n / w;
    int k2 = m / h;
    if (k1 & 1)
    {
        ++k1;
    }
    if (k2 & 1)
    {
        ++k2;
    }
    k1 >>= 1;
    k2 >>= 1;
    long long ans = (long long)k1 * k2;
    printf("%lld", ans);
    return 0;
}
