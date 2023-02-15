#include <cstdio>

/* Constant */
const int MAXN = 26;
const int MAXT = 1e3 + 5;
const int mod = 1e9 + 7;

/* Declaration */
int main();
int Len(int, int, int, int);
int Abs(int);

/* Variable */
int f[2][MAXN][MAXN];
int a[MAXT];

/* Declaration */
int main()
{
    freopen("lock.in", "r", stdin);
    freopen("lock.out", "w", stdout);
    int n, m, t;
    scanf("%d%d%d", &n, &m, &t);
    for (int i = 2; i <= t; ++i)
    {
        scanf("%d", &a[i]);
        if (a[i] > n * m - 1)
        {
            a[i] = n * m - 1;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            f[1][i][j] = 1;
        }
    }
    int now;
    for (int i = 2; i <= t; ++i)
    {
        now = i & 1;
        for (int stx = 1; stx <= n; ++stx)
        {
            for (int sty = 1; sty <= m; ++sty)
            {
                f[now][stx][sty] = 0;
                for (int x = 1; x <= n; ++x)
                {
                    for (int y = 1; y <= m; ++y)
                    {
                        if (Len(x, y, stx, sty) <= a[i])
                        {
                            f[now][stx][sty] += f[!now][x][y];
                            f[now][stx][sty] %= mod;
                        }
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            ans += f[now][i][j];
//            printf("%d ", f[now][i][j]);
            ans %= mod;
        }
//        printf("\n");
    }
    printf("%d", ans);
    return 0;
}
int Len(int x1, int y1, int x2, int y2)
{
    return Abs(x2 - x1) + Abs(y2 - y1);
}
int Abs(int _x)
{
    return _x < 0 ? -_x : _x;
}
