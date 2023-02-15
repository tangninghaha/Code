#include <cstdio>

/* Constant */
const int MAXN = 1e3 + 5;
const long long mod = 1e9 + 7;

/* Declaration */
int main();

/* Variable */
int n, m, k;
int a[MAXN][MAXN];

/* Definition */
int main()
{
    int num = 0;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            scanf("%d", &a[i][j]);
            if (!a[i][j])
                ++num;
        }
    }
    if (n + m - 1 > k)
    {
        printf("0");
        return 0;
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (!a[i][j])
                continue;
            for (int x = 1; x <= i; ++x)
            {
                for (int y = 1; y <= j; ++y)
                {
                    if (x == i && y == j)
                        break;
                    if (a[x][y] == a[i][j])
                    {
                        printf("0");
                        return 0;
                    }
                }
            }
        }
    }
    long long ans = 1;
    int tk = n + m - 1;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (a[i][j])
                continue;
            ans *= (tk - (i + j - 1) + 1);
            ans %= mod;
        }
    }
    if (k != tk)
    {
        ans *= k - tk;
        ans %= mod;
        ans *= num;
        ans %= mod;
    }
    printf("%lld", ans);
    return 0;
}
