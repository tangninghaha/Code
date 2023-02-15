#include <stdio.h>

const int MAXN = 1005;
int a[MAXN][MAXN];
bool g[MAXN][MAXN][2];
int ans[2 * MAXN][2];

void FileIO();
int main();

void FileIO()
{
    freopen("happiness.in", "r", stdin);
    freopen("happiness.out", "w", stdout);
    return;
}

int main()
{
    FileIO();
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            scanf("%d", &a[i][j]);
        }
    }
    g[n][m][0] = true;
    g[n][m][1] = true;
    for (int i = n; i >= 1; --i)
    {
        for (int j = m; j >= 1; --j)
        {
            if (i == n && j == m)
                continue;
            if (a[i][j] == 0)
            {
                g[i][j][0] = false;
                g[i][j][1] = false;
            }
            else
            {
                if (g[i][j + 1][0] || g[i][j + 1][1])
                {
                    g[i][j][0] = true;
                }
                if (g[i + 1][j][0] || g[i + 1][j][1])
                {
                    g[i][j][1] = true;
                }
            }
        }
    }
    ans[1][0] = 1;
    ans[1][1] = 1;
    int x = 1, y = 1;
    bool pd = false;
    for (int i = 2; i <= n + m - 1; ++i)
    {
        if (g[x][y][0] && !g[x][y][1])
        {
            ans[i][0] = x;
            ans[i][1] = y + 1;
            ++y;
        }
        else if (g[x][y][1] && !g[x][y][0])
        {
            ans[i][0] = x + 1;
            ans[i][1] = y;
            ++x;
        }
        else if (!g[x][y][0] && !g[x][y][1])
        {
            pd = true;
            break;
        }
        else
        {
            if (a[x][y + 1] < a[x + 1][y])
            {
                ans[i][0] = x;
                ans[i][1] = y + 1;
                ++y;
            }
            else
            {
                ans[i][0] = x + 1;
                ans[i][1] = y;
                ++x;
            }
        }
    }
    if (pd)
    {
        printf("Oh,the life is too difficult!");
        return 0;
    }
    for (int i = 1; i <= n + m - 1; ++i)
    {
        printf("%d ", a[ans[i][0]][ans[i][1]]);
    }
    return 0;
}
