#include <stdio.h>
const int mod = 1e9 + 7;
void Dfs(int x, int y);
int n, m;
long long ans = 0;
int map[6][101];
int main()
{
    scanf("%d%d", &n, &m);
    Dfs(1, 1);
    printf("%lld", ans);
}
void Dfs(int x, int y)
{
    if (x > n)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                for (int k = 1; k < j; ++k)
                {
                    if (map[i][k] == 0)
                        continue;
                    if (map[i][j] != 3 || map[i][k] != 4)
                    {
                        return;
                    }
                }
                for (int k = j + 1; k <= m; ++k)
                {
                    if (map[i][k] == 0)
                        continue;
                    if (map[i][j] != 4 || map[i][k] != 3)
                    {
                        return;
                    }
                }
                for (int k = 1; k < i; ++k)
                {
                    if (map[k][j] == 0)
                        continue;
                    if (map[i][j] != 1 || map[k][j] != 2)
                    {
                        return;
                    }
                }
                for (int k = i + 1; k <= n; ++k)
                {
                    if (map[k][j] == 0)
                        continue;
                    if (map[i][j] != 2 || map[k][j] != 1)
                    {
                        return;
                    }
                }
            }
        }
        ++ans;
        ans %= mod;
        return;
    }
    for (int i = 1; i <= 4; ++i)
    {
        map[x][y] = i;
        if (y == m)
            Dfs(x + 1, 1);
        else
            Dfs(x, y + 1);
        map[x][y] = 0;
    }
    return;
}
