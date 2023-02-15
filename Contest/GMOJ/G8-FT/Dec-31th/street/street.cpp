#include <cstdio>

/* Constant */
const int MAXN = 205;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

/* Declaration */
int main();
void Dfs(int, int, int, int, long long);
int Min(int, int);

/* Variable */
long long ans = 1e18 + 5;
int a[MAXN][MAXN];
int b[MAXN][MAXN];
int d[MAXN][MAXN];
int e[MAXN][MAXN];
int edx, edy;
bool vis[MAXN][MAXN];
int hld;
int n, m, t;

int f[MAXN][MAXN];

/* Definition */
int main()
{
    freopen("street.in", "r", stdin);
    freopen("street.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &t);
    scanf("%d%d", &edx, &edy);
    bool pd = false;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            scanf("%d%d%d%d", &a[i][j], &b[i][j], &d[i][j], &e[i][j]);
            if (a[i][j] || b[i][j])
            {
                pd = true;
            }
        }
    }
    if (!pd)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                f[i][j] = Min(f[i][j - 1] + e[i][j - 1], f[i - 1][j] + d[i][j]);
            }
        }
        printf("%d", f[edx][edy]);
        return 0;
    }
    Dfs(1, 1, 1, 0, 0);
    printf("%lld", ans);
    return 0;
}

void Dfs(int _x, int _y, int fx, int _t, long long cost)
{
    if (cost > ans)
    {
        return;
    }
    if (_x == edx && _y == edy)
    {
        ans = cost;
        return;
    }
    vis[_x][_y] = true;
    int nx, ny;
    for (int i = 0; i < 4; ++i)
    {
        nx = _x + dx[i];
        ny = _y + dy[i];
        if (nx > 0 && nx <= n && ny > 0 && ny <= m && !vis[nx][ny])
        {
            hld = 0;
            if ((fx == 0 && i != 3 && t) || (fx == 1 && i != 2 && t))
            {
                hld = a[_x][_y] - _t % t;
                if (hld < 0)
                {
                    hld = 0;
                }
            }
            if ((fx == 2 && i != 0 && t) || (fx == 3 && i != 1 && t))
            {
                if (_t % t <= a[_x][_y])
                {
                    hld = 0;
                }
                else
                {
                    hld = t - _t % t;
                }
            }
            if (nx > _x)
                Dfs(nx, ny, i, _t + d[_x][_y] + hld, cost + d[_x][_y] + hld * 10);
            if (nx < _x)
                Dfs(nx, ny, i, _t + d[nx][_y] + hld, cost + d[nx][_y] + hld * 10);
            if (ny > _y)
                Dfs(nx, ny, i, _t + e[_x][_y] + hld, cost + e[_x][_y] + hld * 10);
            if (ny < _y)
                Dfs(nx, ny, i, _t + e[_x][ny] + hld, cost + e[_x][ny] + hld * 10);
        }
    }
    vis[_x][_y] = false;
}
int Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
