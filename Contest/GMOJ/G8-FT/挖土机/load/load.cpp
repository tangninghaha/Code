#include <cstdio>

/* Constant */
const int MAXN = 25;
const int INF = 1e9 + 5;

/* Declaration */
int main();
void FileIO();
void Dfs(int, int, int);
bool Check();
int Min(int, int);
void Zhuan(int, int);

/* Variable */
int n;
int map[MAXN][MAXN];
int ans = INF;
int status[5][5];
char tmp[MAXN];
int nmap[MAXN][MAXN];
int temp[5][5];

/* Definition */
void Zhuan(int _x, int _y)
{
    for (int i = (_x - 1) * n + 1; i <= _x * 3; ++i)
    {
        for (int j = (_y - 1) * n + 1; j <= _y * 3; ++j)
        {

        }
    }
}
void FileIO()
{
    freopen("load.in", "r", stdin);
    freopen("load.out", "w", stdout);
    return;
}
int main()
{
    FileIO();
    printf("-1");
    return 0;
    scanf("%d", &n);
    int n2 = n * n;
    for (int i = 1; i <= n2; ++i)
    {
        scanf("%s", tmp);
        for (int j = 1; j <= n2; ++j)
        {
            if (tmp[j - 1] >= 'A')
            {
                map[i][j] = 10 + tmp[j - 1] - 'A';
            }
            else
            {
                map[i][j] = tmp[j - 1] - '0';
            }
        }
    }
    Dfs(1, 1, 0);
}
void Dfs(int _x, int _y, int step)
{
    if (_x == n + 1)
    {
        if (Check())
        {
            ans = Min(ans, step);
        }
        return;
    }
    for (int i = 0; i <= 3; ++i)
    {
        status[_x][_y] = i;
        if (_y != n)
            Dfs(_x, _y + 1, step + i);
        else
            Dfs(_x + 1, 1, step + i);
    }
    return;
}
bool Check()
{
    int n2 = n * n;
    for (int i = 1; i <= n2; ++i)
    {
        for (int j = 1; j <= n2; ++j)
        {
            nmap[i][j] = map[i][j];
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            for (int k = 1; k <= status[i][j]; ++k)
                Zhuan(i, j);
        }
    }
    for (int i = 1; i <= n2; ++i)
    {
        for (int j = 1; j <= n2; ++j)
        {
            vis[j] = false;
        }
        for (int j = 1; j <= n2; ++j)
        {
            if (vis[nmap[i][j]])
            {
                return false;
            }
            vis[nmap[i][j]] = true;
        }
    }
    for (int i = 1; i <= n2; ++i)
    {
        for (int j = 1; j <= n2; ++j)
        {
            vis[j] = false;
        }
        for (int j = 1; j <= n2; ++j)
        {
            if (vis[nmap[j][i]])
            {
                return false;
            }
            vis[nmap[j][i]] = true;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            for (int k = 1; k <= n2; ++k)
            {
                vis[k] = false;
            }
            for (int k1 = (i - 1) * n + 1; k1 <= i * n; ++k1)
            {
                for (int k2 = (j - 1) * n + 1; k2 <= j * n; ++k2)
                {
                    if (vis[nmap[k1][k2]])
                    {
                        return false;
                    }
                    vis[nmap[k1][k2]] = true;
                }
            }
        }
    }
}
void Zhuan(i, j)
int Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
