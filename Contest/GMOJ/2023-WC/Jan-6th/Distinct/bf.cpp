#include <cstdio>

/* Constant */
const int MAXN = 1e3 + 5;
const int mod = 1e9 + 7;

/* Declaration */
int main();
void Dfs(int, int);
void Check();

/* Variable */
int n, m, k;
int a[MAXN][MAXN];
int ans;

/* Definition */
int main()
{
    freopen("out.txt", "w", stdout);
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            scanf("%d", &a[i][j]);
        }
    }
    if (n + m - 1 > k)
    {
        printf("0");
        return 0;
    }
    Dfs(1, 1);
    printf("%d", ans);
    return 0;
}
void Dfs(int _x, int _y)
{
    if (_x == n + 1)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
        printf("%d\n", ans + 1);
        printf("\n\n");
        ++ans;
        ans %= mod;
        return;
    }
    bool pd;
    if (!a[_x][_y])
    {
        for (int i = 1; i <= k; ++i)
        {
            a[_x][_y] = i;
            pd = false;
            for (int xx = 1; xx <= _x; ++xx)
            {
                for (int yy = 1; yy <= _y; ++yy)
                {
                    if (xx == _x && yy == _y)
                        break;
                    if (a[xx][yy] == i)
                    {
                        pd = true;
                        break;
                    }
                }
                if (pd)
                    break;
            }
            if (pd)
                continue;
            if (_y == m)
            {
                Dfs(_x + 1, 1);
            }
            else
            {
                Dfs(_x, _y + 1);
            }
        }
        a[_x][_y] = 0;
    }
    else
    {
        for (int x = 1; x <= _x; ++x)
        {
            for (int y = 1; y <= _y; ++y)
            {
                if (x == _x && y == _y)
                    break;
                if (a[x][y] == a[_x][_y])
                {
                    return;
                }
            }
        }
        if (_y == m)
        {
            Dfs(_x + 1, 1);
        }
        else
        {
            Dfs(_x, _y + 1);
        }
    }
}
