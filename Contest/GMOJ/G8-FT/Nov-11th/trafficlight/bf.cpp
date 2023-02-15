#include <cstdio>

/* Constant */
const int MAXN = 1e5 + 5;
const int MAXM = 1e5 + 5;

/* Declaration */
int main();

/* Variable */
int a[MAXM];

/* Definition */
int main()
{
    freopen("trafficlight.in", "r", stdin);
    freopen("bf.out", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d", &a[i]);
    }
    long long now_time = 0;
    for (int i = 1; i <= n; ++i)
    {
        now_time = i;
        for (int j = 1; j <= m; ++j)
        {
            now_time += (a[j] - now_time % a[j]) % a[j];
        }
        printf("%lld ", now_time);
    }
}
