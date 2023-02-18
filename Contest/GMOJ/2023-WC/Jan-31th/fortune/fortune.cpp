#include <cstdio>

/* Constant */
const int N = 81;

/* Declaration */
int main();
void Dfs(int, int, int, int);
int Max(int, int);

/* Variable */
int n;
int ans = 0;
int x[N], y[N], z[N];

/* Definition */
int main()
{
    freopen("fortune.in", "r", stdin);
    freopen("fortune.out", "w", stdout);
    int t;
    scanf("%d", &t);
    scanf("%d", &t);
    for (int fot = 1; fot <= t; ++fot)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d%d%d", &x[i], &y[i], &z[i]);
        }
        Dfs(1, 0, 0, 0);
        printf("%d\n", ans);
    }
    return 0;
}
void Dfs(int _x, int num, int mjl, int fsqd)
{
    if (_x > n)
    {
        ans = Max(ans, num);
        return;
    }
    Dfs(_x + 1, num + x[_x] + fsqd, mjl, fsqd + mjl);
    Dfs(_x + 1, num, mjl, fsqd + y[_x] + mjl);
    Dfs(_x + 1, num, mjl + z[_x], fsqd + mjl);
    return;
}
int Max(int _a, int _b)
{
    return _a > _b ? _a : _b;
}
