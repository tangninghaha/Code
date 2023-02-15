#include <stdio.h>
#include <cstring>

const int MAXN = 110, MAXM = 1010;
int f[MAXN][MAXM];
int a[MAXN][MAXN];
int n, m;

void Dfs(int x, int k);
int min(int a, int b);

int main()
{
//    freopen("t0.in", "r", stdin);
    int c;
    scanf ("%d%d%d", &n, &m, &c);
    int u, v, w;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            a[i][j] = -1;
        }
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        a[u][v] = w;
    }
    memset(f, 127 / 3, sizeof(f));
    f[1][0] = 0;
    Dfs(1, 0);
    for (int i = 0; i <= m; i++)
    {
        if (f[n][i] <= c)
        {
            printf("%d", i);
            break;
        }
    }
    return 0;
}

void Dfs(int x, int k)
{
    for (int i = 1; i <= n; i++)
    {
        if (a[x][i] != -1)
        {
            for (int j = 0; j <= m; j++)
            {
                f[i][j] = min(f[i][j], f[x][j] + a[x][i]);
                if (j >= 1) f[i][j] = min(f[i][j], f[x][j - 1]);
            }
            Dfs(i, k + 1);
        }
    }
}

int min(int a, int b)
{
    return a < b ? a : b;
}
