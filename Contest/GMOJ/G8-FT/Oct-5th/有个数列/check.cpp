#include <cstdio>
#define B

/* Constant */
const int MAXN = 1e5 + 5;
const long long INF = 1e15 + 5;

/* Declaration */
int main();

/* Variable */
long long a[MAXN * 2];

/* Definition */
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", &a[i]);
        a[i + n] = a[i];
    }
#ifdef A
    int l, r;
    scanf("%d%d", &l, &r);
    long long sum = 0;
    for (int i = l; i <= r; ++i)
    {
        sum += a[i];
    }
    printf("%lld", sum);
#endif
#ifdef B
    int ansl, ansr;
    long long ans = -INF;
    for (int l = 1; l <= 2 * n; ++l)
    {
        for (int r = l; r <= 2 * n; ++r)
        {
            if (r - l + 1 > n)
                break;
            long long sum = 0;
            for (int k = l; k <= r; ++k)
            {
                sum += a[k];
            }
            if (sum > ans)
            {
                ansl = l;
                ans = sum;
                ansr = r;
            }
        }
    }
    printf("%d %d\n", ansl, ansr);
    printf("%lld", ans);
#endif
    return 0;
}
