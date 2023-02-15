#include <cstdio>

/* Constant */
const int MAXN = 1e5 + 5;

/* Decalration */
int main();

/* Variable */
long long a[MAXN];
long long s[MAXN];
int vis[MAXN];

/* Definition */
int main()
{
    freopen("checkin.in", "r", stdin);
    freopen("checkin.out", "w", stdout);
    int t;
    scanf("%d", &t);
    for (int tt = 1; tt <= t; ++tt)
    {
        int n;
        scanf("%d", &n);
        const long long mod = n;
        int i;
        for (i = 1; i <= n; ++i)
        {
            scanf("%lld", &a[i]);
            s[i] = s[i - 1] + a[i];
            s[i] = (s[i] % mod + mod) % mod;
            if (s[i] == 0)
            {
                printf("%d\n", i);
                for (int j = 1; j <= i; ++j)
                {
                    printf("%lld ", a[j]);
                }
                break;
            }
            if (vis[s[i]])
            {
                printf("%d\n", i - vis[s[i]]);
                for (int j = vis[s[i]] + 1; j <= i; ++j)
                {
                    printf("%lld ", a[j]);
                }
                break;
            }
            vis[s[i]] = i;
        }
        for (int j = 1; j <= i; ++j)
        {
            vis[s[j]] = 0;
            s[j] = 0;
        }
        ++i;
        for (; i <= n; ++i)
        {
            scanf("%lld", &a[i]);
        }
        printf("\n");
    }
}
