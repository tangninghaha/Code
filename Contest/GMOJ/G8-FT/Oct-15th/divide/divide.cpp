#include <cstdio>

/* Constant */
const int MAXN = 1005;
const int MAXTIMEX = 240;
const int GLTIME = 10080;
const int INF = 1e8 + 5;

/* Declaration */
int Read();
int main();
int Min(int, int);

/* Variable */
int f[MAXN];
int a[MAXN];
int s[MAXN];

/* Definition */
int main()
{
    freopen("divide.in", "r", stdin);
    freopen("divide.out", "w", stdout);
    int n = Read();
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        s[i] = s[i - 1] + a[i];
    }
    int ans = INF;
    for (int i = 1; i <= n; ++i)
    {
        f[i] = INF;
        for (int j = 0; j < i; ++j)
        {
            f[i] = Min(f[i], f[j] + s[i] - s[j]
                             + ((s[i] - s[j] >= MAXTIMEX) * GLTIME) + 400);
        }
        ans = Min(ans, f[i] + s[n] - s[i]
                       + ((s[n] - s[i] >= MAXTIMEX) * GLTIME) + (i != n) * 400);
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
int Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
