#include <stdio.h>
int f[205][205][205];
int st[205], ed[205], d[205];
int map[205][205];
char cha[205];
const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
int max(int a, int b);
int main()
{
    int n, m, x, y, k;
    scanf("%d%d%d%d%d", &n, &m, &x, &y, &k);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", cha + 1);
        for (int j = 1; j <= m; ++j)
        {
            if (cha[j] == '.')
                map[i][j] = 1;
        }
    }
    for (int i = 1; i <= k; ++i)
    {
        scanf("%d%d%d", &st[i], &ed[i], &d[i]);
		--d[i];
		d[i] = d[i] ^ 1;
    }
    f[0][x][y] = 1;
    int ans = 0, nx, ny;
    int len;
    for (int t = 1; t <= k; ++t)
    {
        len = ed[t] - st[t] + 1;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
				if (!map[i][j])
					continue;
                if (d[t] == 0)
                {
                    nx = i, ny = j;
                    while (nx >= 1 && nx <= n && i - nx  <= len && map[nx][j] == 1)
                    {
                        if (f[t - 1][nx][j])
                            f[t][i][j] = max(f[t][i][j], f[t - 1][nx][j] + i - nx);
                        --nx;
                    }
                }
                else if (d[t] == 1)
                {
                    nx = i, ny = j;
                    while (nx >= 1 && nx <= n && nx - i  <= len && map[nx][j] == 1)
                    {
                        if (f[t - 1][nx][j])
                            f[t][i][j] = max(f[t][i][j], f[t - 1][nx][j] + nx - i);
                        ++nx;
                    }
                }
                else if (d[t] == 2)
                {
                    ny = j;
                    while (ny >= 1 && ny <= m && j - ny  <= len && map[i][ny] == 1)
                    {
                        if (f[t - 1][i][ny])
                            f[t][i][j] = max(f[t][i][j], f[t - 1][i][ny] + j - ny);
                        --ny;
                    }
                }
                else if (d[t] == 3)
                {
                    ny = j;
                    while (ny >= 1 && ny <= m && ny - j  <= len && map[i][ny] == 1)
                    {
                        if (f[t - 1][i][ny])
                            f[t][i][j] = max(f[t][i][j], f[t - 1][i][ny] + ny - j);
                        ++ny;
                    }
                }
                ans = max(ans, f[t][i][j]);
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
