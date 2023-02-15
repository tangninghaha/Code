#include <cstdio>
#include <cstring>

/* Constant */
const int MAXN = 1e6 + 5;

/* Declaration */
int main();
void Init(int);
int Min(int, int);
int Max(int, int);

/* Variable */
int f[MAXN][25];
int g[MAXN][25];
int twom[25];
int log_2[MAXN];
int a[MAXN];
int b[MAXN];

/* Definition */
void Init(int n)
{
    twom[0] = 1;
    for (int i = 1; i <= 24; ++i)
    {
        twom[i] = twom[i - 1] << 1;
    }
    memset(f, 127 / 3, sizeof(f));
    for (int i = 1; i <= n; ++i)
    {
        f[i][0] = a[i];
        g[i][0] = b[i];
    }
    for (int j = 1; j <= 24; ++j)
        for (int i = 1; i <= n; ++i)
    {
        {
            if (i + twom[j] - 1 > n)
                break;
            f[i][j] = Min(f[i][j - 1], f[i + twom[j - 1]][j - 1]);
            g[i][j] = Max(g[i][j - 1], g[i + twom[j - 1]][j - 1]);
        }
    }
    log_2[1] = 0;
    for (int i = 2; i <= n; ++i)
    {
        log_2[i] = log_2[i / 2] + 1;
    }
}
int main()
{
    freopen("fenshen.in", "r", stdin);
    freopen("fenshen.out", "w", stdout);

    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &b[i]);
    }
    Init(n);
    int lbound = 1, rbound = n;
    int mid;
    int ed;
    int lg;
    int maxx, minn;
    bool pd;
    int ans = -1;
    while (lbound <= rbound)
    {
        mid = (lbound + rbound) >> 1;
        lg = log_2[mid];
        pd = false;
        for (int i = 1; i <= n; ++i)
        {
            if (i + mid - 1 > n)
                break;
            ed = i + mid - 1;
            minn = Min(f[i][lg], f[ed - twom[lg] + 1][lg]);
            maxx = Max(g[i][lg], g[ed - twom[lg] + 1][lg]);
            if (maxx - minn >= k)
            {
                pd = true;
                break;
            }
        }
        if (pd)
        {
            ans = mid;
            rbound = mid - 1;
        }
        else
        {
            lbound = mid + 1;
        }
    }
    if (ans == -1)
    {
        printf("So Sad!");
    }
    else
    {
        printf("%d", ans);
    }
    return 0;
}
int Max(int _a, int _b)
{
    return _a > _b ? _a : _b;
}
int Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
