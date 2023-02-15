#include <stdio.h>
#define INF 1000000010
const int MAXN = 1001;
int a[MAXN][MAXN];
bool broken[MAXN][MAXN];
int diss[MAXN];
bool vis[MAXN];
int min(int a, int b);
int main()
{
    freopen("road.in", "r", stdin);
    freopen("road.out", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            a[i][j] = INF;
        }
    }
    int x, y, len;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d%d", &x, &y, &len);
        if (a[x][y] == INF)
        {
            a[x][y] = len;
            a[y][x] = len;
        }
        else
        {
            a[x][y] = min(len, a[x][y]);
            a[x][y] = min(len, a[x][y]);
        }
    }
    int d;
    scanf("%d", &d);
    for (int i = 1; i <= d; ++i)
    {
        scanf("%d%d", &x, &y);
        broken[x][y] = true;
        broken[y][x] = true;
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (a[i][j] != INF)
                a[i][j] *= broken[i][j];
        }
    }
    scanf("%d%d", &x, &y);
    for (int i = 1; i <= n; ++i)
    {
        diss[i] = INF;
    }
    diss[x] = 0;
    int minn = INF + 5, minp = 0;
    for (int i = 1; i <= n; ++i)
    {
        minp = 0;
        minn = INF + 5;
        for (int j = 1; j <= n; ++j)
        {
            if (diss[j] < minn && !vis[j])
            {
                minn = diss[j];
                minp = j;
            }
        }
        vis[minp] = true;
        for (int j = 1; j <= n; ++j)
        {
            if (a[minp][j] != INF && !vis[j])
            {
                if (a[minp][j] + diss[minp] < diss[j])
                {
                    diss[j] = a[minp][j] + diss[minp];
                }
            }
        }
    }
    printf("%d", diss[y]);
    return 0;
}
int min(int a, int b)
{
    return a < b ? a : b;
}
