#include <cstdio>

/* Constant */
const int MAXN = 505;

/* Declaration */
int main();
void FileIO();
int Max(int, int);

/* Variable */
int f[MAXN][MAXN];
int cost[MAXN];
int fr[MAXN];
int be[MAXN];
int g[MAXN];

/* Definition */
int main()
{
    FileIO();
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d%d", &cost[i], &fr[i], &be[i]);
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 500; j >= 0; --j)
        {
            if (j >= cost[i])
            {
                g[j] = Max(g[j - cost[i]] + be[i], g[j]);
                for (int k = 500 - fr[i]; k <= 500; ++k)
                {
                    g[j] = Max(g[j], f[j - cost[i]][k] + be[i]);
                }
                for (int k = 500; k >= 0; --k)
                {
                    if (k >= fr[i])
                        f[j][k] = Max(f[j][k],
                                      f[j - cost[i]][k - fr[i]] + be[i]);
                }
            }
            else
                break;
        }
    }
    for (int j = 0; j <= 500; ++j)
    {
        for (int k = 1; k <= 500; ++k)
        {
            f[k][j] = Max(f[k][j], f[k - 1][j]);
        }
    }
    for (int j = 0; j <= 500; ++j)
    {
        for (int k = 499; k >= 0; --k)
        {
            f[j][k] = Max(f[j][k], f[j][k + 1]);
        }
    }
    for (int j = 1; j <= 500; ++j)
    {
        g[j] = Max(g[j], g[j - 1]);
    }
    int c, j;
    for (int i = 1; i <= q; ++i)
    {
        scanf("%d%d", &c, &j);
        printf("%d\n", Max(f[c][j], g[c]));
    }
    return 0;
}
int Max(int _a, int _b)
{
    return _a > _b ? _a : _b;
}
void FileIO()
{
    freopen("buy.in", "r", stdin);
    freopen("buy.out", "w", stdout);
    return;
}
