#include <stdio.h>

const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
int f[2][201][201];
int map[201][201];
int d[100005];

int max(int a, int b);

int main()
{
    int n, m, x, y, k;
    scanf("%d%d%d%d%d", &n, &m, &x, &y, &k);
    char cha;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            cha = getchar();
            while (cha != '.' && cha != 'x')
            {
                cha = getchar();
            }
            if (cha == '.')
                map[i][j] = 1;
            if (cha == 'x')
                map[i][j] = 0;
        }
    }
    int s, t, di;
    for (int i = 1; i <= k; ++i)
    {
        scanf("%d%d%d", &s, &t, &di);
        --di;
        for (int j = s; j <= t; ++j)
        {
            d[j] = di;
        }
    }
    f[0][x][y] = 1;
    int ans = 1;
    for (int ti = 1; ti <= t; ++ti)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (map[i][j] == 1)
                {
                    if (map[i - dx[d[ti]]][j - dy[d[ti]]] == 1
                        && f[(ti - 1) % 2][i - dx[d[ti]]][j - dy[d[ti]]])
                    {
                        f[ti % 2][i][j] = max(f[(ti - 1) % 2][i][j], 
                                          f[(ti - 1) % 2][i - dx[d[ti]]][j - dy[d[ti]]] + 1);
                    }
                    else
                    {
                        f[ti % 2][i][j] = f[(ti - 1) % 2][i][j];
                    }
                    ans = max(ans, f[ti % 2][i][j]);
                }
            }
        }
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                f[(ti - 1) % 2][i][j] = 0;
            }
        }
    }
    printf("%d", ans - 1);
    return 0;
}
int max(int a, int b)
{
    return a > b ? a : b;
}
