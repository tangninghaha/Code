#include <cstdio>

/* Constant */
const int MAXN = 101;
const int MAXM = 201;
const int MAXG = 19;
const int MAXK = 262145;
const int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};

const int INF = 1 << 29;

/* Declaration */
void Dfs(int, int);
void Bfs(int);
int main();
int Min(int, int);

/* Variable */
int n, m, g_tot;
int twom[MAXG];
int onenum[MAXK];
int f[MAXG][MAXK];
int point_g[MAXG][2];
char map[MAXN][MAXN];
int bh[MAXN][MAXN];

int diss[MAXG][MAXG];
int vis[MAXN][MAXN];
int clear_vis[MAXN][MAXN];
int queue[MAXN * MAXN * MAXM][3];
int st, ed;

/* Definition */
int main()
{
    freopen("lalo.in", "r", stdin);
    freopen("lalo.out", "w", stdout);
    twom[0] = 1;
    for (int i = 1; i <= 18; ++i)
        twom[i] = twom[i - 1] << 1;
    int temp;
    for (int i = 0; i < twom[18]; ++i)
    {
        temp = i;
        for (int j = 0; j < 18; ++j)
        {
            if (temp & 1)
                ++onenum[i];
            temp >>= 1;
        }
    }
    scanf("%d%d", &n, &m);
    char tmp;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            while(tmp != 'G' && tmp != 'E' && tmp != 'X' && tmp != '-' && tmp != '#')
                tmp = getchar();
            map[i][j] = tmp;
            if (tmp == 'G' || tmp == 'E' || tmp == 'X')
            {
                ++g_tot;
                bh[i][j] = g_tot;
                point_g[g_tot][0] = i;
                point_g[g_tot][1] = j;
                if (tmp == 'E')
                {
                    st = g_tot;
                }
                else if (tmp == 'X')
                {
                    ed = g_tot;
                }
            }
            tmp = getchar();
        }
    }
    for (int i = 1; i <= g_tot; ++i)
        Bfs(i);
        
    for (int k = 1; k <= g_tot; ++k)
        for (int i = 1; i <= g_tot; ++i)
            for (int j = 1; j <= g_tot; ++j)
            {
                if (i == j)
                    continue;
                diss[i][j] = Min(diss[i][j], diss[i][k] + diss[k][j]);
            }
    for (int i = 1; i <= g_tot; ++i)
        for (int j = 0; j < twom[g_tot]; ++j)
            f[i][j] = INF;
    f[st][twom[st - 1]] = 0;

//    Dfs(st, twom[st - 1]);
    for (int s = 0; s < twom[g_tot]; ++s)
        for (int i = 1; i <= g_tot; ++i)
            for (int j = 1; j <= g_tot; ++j)
                f[j][s | twom[j - 1]] = Min(f[j][s | twom[j - 1]], f[i][s] + diss[i][j]);
    int ans_value = 0;
    int ans_cost = 0;
    for (int i = 0; i < twom[g_tot]; ++i)
        if (f[ed][i] != INF)
        {
            if (onenum[i] > ans_value)
            {
                ans_value = onenum[i];
                ans_cost = f[ed][i];
            }
            else if (onenum[i] == ans_value)
            {
                ans_cost = f[ed][i];
            }
        }
    printf("%d %d", ans_value - 2, ans_cost);
    return 0;
}
void Bfs(int _x)
{
    int head = 0, tail = 1;
    queue[tail][0] = point_g[_x][0];
    queue[tail][1] = point_g[_x][1];
    queue[tail][2] = 0;
    vis[queue[tail][0]][queue[tail][1]] = 0;
    clear_vis[queue[tail][2]][queue[tail][1]] = _x;
    int x, y, t;
    int nx, ny;
    while (head < tail)
    {
        ++head;
        x = queue[head][0];
        y = queue[head][1];
        t = queue[head][2];
        for (int tt = 0; tt < 4; ++tt)
        {
            nx = x + dx[tt];
            ny = y + dy[tt];
            if (nx < 1 || ny < 1 || nx > n || ny > n)
                continue;
            if (map[nx][ny] == '#')
                continue;
            if (map[nx][ny] == '-')
            {
                if (t == m)
                    continue;
                if (clear_vis[nx][ny] != _x)
                {
                    vis[nx][ny] = INF;
                    clear_vis[nx][ny] = _x;
                }
                if (vis[nx][ny] <= vis[x][y] + 1)
                    continue;
                ++tail;
                queue[tail][0] = nx;
                queue[tail][1] = ny;
                queue[tail][2] = t + 1;
                vis[nx][ny] = vis[x][y] + 1;
            }
            else
            {
                if (clear_vis[nx][ny] != _x)
                {
                    vis[nx][ny] = INF;
                    clear_vis[nx][ny] = _x;
                }
                if (vis[nx][ny] <= vis[x][y])
                    continue;
//                ++tail;
//                queue[tail][0] = nx;
//                queue[tail][1] = ny;
//                queue[tail][2] = 0;
                vis[nx][ny] = vis[x][y];
            }
        }
    }
    for (int i = 1; i <= g_tot; ++i)
    {
        diss[i][_x] = diss[_x][i] = INF;
        if (i == _x)
            continue;
        x = point_g[i][0];
        y = point_g[i][1];
        if (clear_vis[x][y] != _x)
            continue;
        diss[i][_x] = diss[_x][i] = vis[x][y];
    }
    return;
}
void Dfs(int _x, int _s)
{
//    printf("%d %d %d\n", _x, _s, f[_x][_s]);
    for (int i = 1; i <= g_tot; ++i)
    {
        if ((_s >> (i - 1)) & 1)
        {
            if (f[i][_s] > f[_x][_s] + diss[_x][i])
            {
                f[i][_s] = f[_x][_s] + diss[_x][i];
                Dfs(i, _s);
            }
        }
        else
        {
            if (f[i][_s + twom[i - 1]] > f[_x][_s] + diss[_x][i])
            {
                f[i][_s + twom[i - 1]] = f[_x][_s] + diss[_x][i];
                Dfs(i, _s + twom[i - 1]);
            }
        }
    }
    return;
}
int Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
