#include <cstdio>

/* Constant */
const int MAXN = 55;

/* Declaration */
int main();
void Dfs(int, int);

double Min(double, double);
double Max(double, double);

/* Variable */
int n, m;
int hl[MAXN];
double ans = 1e8 + 5;

int a[MAXN];
int b[MAXN];

bool can_att[MAXN][MAXN];
bool is_att[MAXN][MAXN];

/* Declaration */
void Dfs(int _x, int _y)
{
    if (_x == m + 1)
    {
        for (int i = 1; i <= n; ++i)
        {
            if (!hl[i])
                return;
        }
        double sum = 0;
        double tmp = 0;
        for (int i = 1; i <= m; ++i)
        {
            tmp = 0;
            for (int j = 1; j <= n; ++j)
            {
                if (is_att[i][j])
                    tmp += (double)a[j] / hl[j];
            }
            sum = Max(sum, tmp);
        }
        ans = Min(ans, sum);
        return;
    }
    if (_y != n)
        Dfs(_x, _y + 1);
    else
        Dfs(_x + 1, 1);
    if (!can_att[_x][_y])
        return;
    hl[_y] += b[_x];
    is_att[_x][_y] = true;
    if (_y != n)
        Dfs(_x, _y + 1);
    else
        Dfs(_x + 1, 1);
    hl[_y] -= b[_x];
    is_att[_x][_y] = false;
    return;
}
double Min(double _x, double _y)
{
    return _x < _y ? _x : _y;
}
double Max(double _x, double _y)
{
    return _x > _y ? _x : _y;
}
int main()
{
    freopen("war.in", "r", stdin);
    freopen("war.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d", &b[i]);
    }
    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            scanf("%d", &can_att[i][j]);
        }
    }
    Dfs(1, 1);
    printf("%f", ans);
    return 0;
}
