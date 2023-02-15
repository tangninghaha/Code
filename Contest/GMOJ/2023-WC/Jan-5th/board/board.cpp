#include <cstdio>

/* Constant */
const int MAXN = 1e3 + 5;
const int INF = 1e8 + 5;

/* Declaration */
int main();
int Min(int, int);

/* Variable */
int f[MAXN][MAXN];
int g[MAXN][MAXN];
int gg[MAXN][MAXN];
int a[MAXN];

/* Definition */
int main()
{
    freopen("board.in", "r", stdin);
//    freopen("board.out", "w", stdout);
    int n, s, k;
    scanf("%d%d%d", &n, &s, &k);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j < i; ++j)
        {
            if (a[j] < a[i])
            {
                ++g[a[i]][a[j]];
                ++gg[a[i]][a[j]];
            }
        }
    }
    for (int i = 1; i <= s; ++i)
    {
        for (int j = 1; j <= s; ++j)
        {
            g[i][j] += g[i][j - 1];
        }
    }
    for (int j = 1; j <= s; ++j)
    {
        for (int i = 1; i <= s; ++i)
        {
            g[i][j] += g[i - 1][j];
        }
    }
//    for (int i = 1; i <= s; ++i)
//    {
//        f[0][i] = g[i][i];
//    }
    for (int i = 0; i <= k; ++i)
    {
        for (int j = 1; j <= s; ++j)
        {
            f[i][j] = INF;
        }
    }
    f[0][0] = 0;
    for (int i = 1; i <= k; ++i)
    {
        for (int j = i; j <= s; ++j)
        {
            f[i][j] = INF;
            for (int x = i - 1; x < j; ++x)
            {
                f[i][j] = Min(f[i][j], f[i - 1][x] + g[j][j] - g[j][x]);
            }
        }
    }
    printf("%d", f[k][s]);
    return 0;
}

int Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
