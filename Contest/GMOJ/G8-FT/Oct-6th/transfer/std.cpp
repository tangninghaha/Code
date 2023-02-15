#include <cstdio>

/* Constant */
const int MAXN = 1005;
const int INF = 1e8 + 5;

/* Declaration */
int main();
int Read();
int Min(int, int);
int Abs(int);

/* Variable */
int f[MAXN][MAXN][2];
int a[MAXN];
int b[MAXN];

/* Definition */
int main()
{
    freopen("transfer.in", "r", stdin);
    freopen("transfer.out", "w", stdout);
    int n, m, k, q;
    n = Read();
    m = Read();
    k = Read();
    q = Read();
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &b[i]);
    }
    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j <= n; ++j)
        {
            f[i][j][0] = f[i][j][1] = INF;
        }
    }
    f[0][0][0] = 0;
    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j <= n; ++j)
        {
            if (i >= 1)
                if (a[i] - a[i - 1]  <= m)
                {
                    f[i][j][0] = Min(f[i][j][0], f[i - 1][j][0]);
                    f[i][j][1] = Min(f[i][j][1], f[i - 1][j][1]);
                }
                else if (a[i] - a[i - 1] <= k)
                {
                    f[i][j][0] = Min(f[i - 1][j][0], f[i][j][0]);
                }
            if (j >= 1)
                if (b[j] - b[j - 1]  <= m)
                {
                    f[i][j][0] = Min(f[i][j][0], f[i][j - 1][0]);
                    f[i][j][1] = Min(f[i][j][1], f[i][j - 1][1]);
                }
                else if (b[j] - b[j - 1] <= k)
                {
                    f[i][j][1] = Min(f[i][j - 1][1], f[i][j][1]);
                }
            if (Abs(a[i] - b[j]) <= q)
            {
                f[i][j][0] = Min(f[i][j][1] + 1, f[i][j][0]);
                f[i][j][1] = Min(f[i][j][0] + 1, f[i][j][1]);
                f[i][j][0] = Min(f[i][j][1] + 1, f[i][j][0]);
                f[i][j][1] = Min(f[i][j][0] + 1, f[i][j][1]);
            }
        }
    }
    printf("%d", Min(f[n][n][0], f[n][n][1]));
    return 0;
}
int Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
int Abs(int _x)
{
    return _x < 0 ? -_x : _x;
}
int Read()
{
    int ret = 0;
    char tmp = getchar();
    while (tmp < '0' || tmp > '9')
    {
        tmp = getchar();
    }
    while (tmp >= '0' && tmp <= '9')
    {
        ret = (ret << 1) + (ret << 3) + tmp - 48;
        tmp = getchar();
    }
    return ret;
}
