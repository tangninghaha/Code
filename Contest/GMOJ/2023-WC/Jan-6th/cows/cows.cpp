#include <cstdio>

/* Constant */
const int MAXN = 55;

/* Declaration */
int main();
void Dfs(int);

/* Variable */
int ans;
int a[MAXN][MAXN];
int n;
int tot;
int chos[MAXN];

/* Definition */
int main()
{
    freopen("cows.in", "r", stdin);
    freopen("cows.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            scanf("%1d", &a[i][j]);
        }
    }
    Dfs(1);
    printf("%d", ans + 1);
    return 0;
}
void Dfs(int _x)
{
    if (_x > n)
    {
        if (!tot)
            return;
        for (int i = 1; i <= tot; ++i)
        {
            for (int j = 1; j <= tot; ++j)
            {
                if (i != j && !a[chos[i]][chos[j]])
                {
                    return;
                }
            }
        }
        ++ans;
        return;
    }
    ++tot;
    chos[tot] = _x;
    Dfs(_x + 1);
    --tot;
    Dfs(_x + 1);
    return;
}
