#include <stdio.h>
#define INF 1000000010

const int MAXN = 105;
int Edge[MAXN][MAXN];
bool cang[MAXN][MAXN];
int n, m, k, ans = INF;
bool vis[MAXN];
int f[MAXN][11];

int min(int a, int b);
void Init();
void Dfs(int x, int t, int k_used);

int main()
{
//    freopen("data3.in", "r", stdin);
    Init();
    scanf("%d%d%d", &n, &m, &k);
    int u, v, w;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        cang[u][v] = 1;
        if (Edge[u][v] != INF)
        {
            if (Edge[u][v] > w)
                Edge[u][v] = w;
        }
        else
            Edge[u][v] = w;
    }
    for (int k = 1; k <= n; ++k)
    {
        for  (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (i != j && j != k && i != k)
                {
                    if (cang[i][k] && cang[k][j])
                    {
                        cang[i][j] = 1;
                    }
                }
            }
        }
    }
    vis[1] = 1;
    Dfs(1, 0, 0);
    printf("%d", ans == INF ? -1 : ans);
    return 0;
}

void Init()
{
    for (int i = 0; i < MAXN; ++i)
    {
        for (int j = 0; j < MAXN; ++j)
        {
            Edge[i][j] = INF;
        }
    }
    for (int i = 0; i < MAXN; ++i)
    {
        for (int j = 0; j < 11; ++j)
        {
            f[i][j] = INF;
        }
    }
}

void Dfs(int x, int t, int k_used)
{
    if (k_used > k) return;
    if (f[x][k_used] <= t) return;
    f[x][k_used] = t;
    if (x == n)
    {
        ans = min(ans, t);
        return;
    }
    int cango;
    for (int i = 1; i <= n; ++i)
    {
        if (Edge[x][i] != INF && x != i && !vis[i])
        {
            cango = !cang[i][x];
            vis[i] = 1;
            Dfs(i, t + Edge[x][i] + cango * Edge[x][i], k_used + cango);
            vis[i] = 0;
        }
    }
    return;
}

int min(int a, int b)
{
    return a < b ? a : b;
}
