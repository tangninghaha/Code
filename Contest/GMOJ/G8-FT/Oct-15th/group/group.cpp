#include <cstdio>

/* Constant */
const int MAXN = 2005;
const int MAXNUM = 2047;
const int INF = 1e9 + 5;

/* Declaration */
int main();
int Read();
int Max(int, int);
int Min(int, int);

/* Variable */
int f[MAXN][MAXNUM];
int dp[MAXN];
int num[MAXN];
int group[MAXN][MAXN];
int group_num[MAXN];

/* Definition */
int main()
{
    freopen("group.in", "r", stdin);
    freopen("group.out", "w", stdout);
    int n, m;
    n = Read();
    m = Read();
    int _a, _b;
    int max_group = 0;
    for (int i = 1; i <= n; ++i)
    {
        _a = Read();
        _b = Read();
        max_group = Max(max_group, _b);
        ++group_num[_b];
        group[_b][group_num[_b]] = _a;
    }
    int sum_group_num = 0;
    int edd;
    for (int i = 1; i <= max_group; ++i)
    {
        for (int j = 0; j <= group_num[i]; ++j)
        {
            for (int k = 0; k < MAXNUM; ++k)
                f[j][k] = INF;
        }
        f[0][0] = 0;
        for (int j = 1; j <= group_num[i]; ++j)
        {
            for (int k = 0; k < MAXNUM; ++k)
            {
                if (f[j - 1][k] != INF)
                {
                    f[j][k] = Min(f[j][k], f[j - 1][k]);
                    f[j][k ^ group[i][j]] = Min(f[j][k ^ group[i][j]], f[j][k] + 1);
                }
            }
        }
        for (int j = 0; j <= group_num[i]; ++j)
        {
            dp[j] = 0;
        }
        for (int j = 0; j < MAXNUM; ++j)
        {
            if (f[group_num[i]][j] == INF)
                continue;
            dp[f[group_num[i]][j]] = j;
        }
        edd = Min(sum_group_num, m);
        for (int j = edd; j >= 0; --j)
        {
            for (int k = 0; k <= group_num[i]; ++k)
            {
                num[j + k] = Max(num[j + k], num[j] + dp[k]);
            }
        }
        sum_group_num += group_num[i];
    }
    int ans = 0;
    for (int i = 1; i <= m; ++i)
    {
        ans = Max(ans, num[i]);
    }
    printf("%d", ans);
    return 0;
}
int Read()
{
    int ret = 0;
    char tmp = getchar();
    while (tmp < '0' || tmp > '9')
        tmp = getchar();
    while (tmp >= '0' && tmp <= '9')
    {
        ret = (ret << 1) + (ret << 3) + tmp - 48;
        tmp = getchar();
    }
    return ret;
}
int Max(int _a, int _b)
{
    return _a > _b ? _a : _b;
}
int Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
