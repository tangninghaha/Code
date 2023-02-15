#include <stdio.h>
const int MAXN = 1005;
int a[MAXN][MAXN];
void Dfs(int x, int y, int num);
bool vis;
int n, m;
int nans[MAXN];
int ans[MAXN];
int main()
{
	// freopen("happiness.in", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            scanf("%d", &a[i][j]);
        }
    }
    nans[1] = a[1][1];
    Dfs(1, 1, 2);
    if (!vis)
    {
        printf("Oh,the life is too difficult!");
    }
    else
    {
        for (int i = 1; i <= n + m - 1; ++i)
        {
            printf("%d ", ans[i]);
        }
    }
    return 0;
}
void Dfs(int x, int y, int num)
{
    if (x == n && y == m)
    {
        bool pd = false;
        for (int i = 1; i <= n + m - 1; ++i)
        {
            if (nans[i] < ans[i])
            {
                pd = true;
                break;
            }
            else if (nans[i] > ans[i])
            {
            	break;
			}
        }
        if (pd || !vis)
        {
            for (int i = 1; i <= n + m - 1; ++i)
            {
                ans[i] = nans[i];
            }
            vis = true;
        }
    }
    if (a[x][y] == 0)
        return;
    nans[num] = a[x + 1][y];
    Dfs(x + 1, y, num + 1);
    nans[num] = a[x][y + 1];
    Dfs(x, y + 1, num + 1);
    return;
}
