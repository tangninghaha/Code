#include <cstdio>

/* Constant */
const int MAXN = 21;
const int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};

/* Declaration */
int main();
bool Pd(char);
void Dfs(int, int, int);
int Max(int, int);

/* Variable */
int cost[MAXN][MAXN];
int gt[MAXN][MAXN];
bool vis[MAXN][MAXN];
int ans;
int n, m;

/* Definition */
int main()
{
    freopen("revolution.in", "r", stdin);
    freopen("revolution.out", "w", stdout);
    scanf("%d%d", &n, &m);
    char cha = getchar();
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            while (!Pd(cha))
            {
                cha = getchar();
            }
            if (cha >= '0' && cha <= '9')
            {
                cost[i][j] = cha - '0';
            }
            else if (cha >= 'a' && cha <= 'z')
            {
                cost[i][j] = cha - 'a' + 10;
            }
            else
            {
                cost[i][j] = cha - 'A' + 36;
            }
            cha = getchar();
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            while (!Pd(cha))
            {
                cha = getchar();
            }
            if (cha >= '0' && cha <= '9')
            {
                gt[i][j] = cha - '0';
            }
            else if (cha >= 'a' && cha <= 'z')
            {
                gt[i][j] = cha - 'a' + 10;
            }
            else
            {
                gt[i][j] = cha - 'A' + 36;
            }
            cha = getchar();
        }
    }
    Dfs(1, 1, 0);
    printf("%d", ans);
    return 0;
}
bool Pd(char _x)
{
    return (_x >= 'a' && _x <= 'z') || (_x >= 'A' && _x <= 'Z') || (_x >= '0' && _x <= '9');
}
void Dfs(int _x, int _y, int money)
{
    if (_x == n + 1)
    {
        bool pd;
        int nx, ny;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                pd = true;
                if (vis[i][j])
                    continue;
                for (int t = 0; t < 4; ++t)
                {
                    nx = i + dx[t];
                    ny = j + dy[t];
                    if (nx > 0 && nx <= n && ny > 0 && ny <= m)
                    {
                        if (!vis[nx][ny])
                        {
                            pd = false;
                            break;
                        }
                    }
                }
                if (pd)
                {
                    money += gt[i][j];
                }
            }
        }
        ans = Max(ans, money);
        return;
    }
    if (_y != m)
    {
        Dfs(_x, _y + 1, money);
        vis[_x][_y] = true;
        Dfs(_x, _y + 1, money - cost[_x][_y] + gt[_x][_y]);
        vis[_x][_y] = false;
    }
    else
    {
        Dfs(_x + 1, 1, money);
        vis[_x][_y] = true;
        Dfs(_x + 1, 1, money - cost[_x][_y] + gt[_x][_y]);
        vis[_x][_y] = false;
    }
}
int Max(int _a, int _b)
{
    return _a > _b ? _a : _b;
}
