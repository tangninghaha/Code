#include <cstdio>
#include <cmath>

/* Constant */
const int MAXN = 51;
const int MAXS = 33554432;

/* Declaration */
int main();
int lowbit(int);

/* Variable */
long long twom[51];
int relationship[MAXN][MAXN];
long long friends[MAXN];
int log_2[MAXS];

bool f[MAXS];
int g[MAXS];

/* Definition */
int main()
{
    freopen("cows.in", "r", stdin);
    freopen("cows.out", "w", stdout);
    twom[0] = 1;
    for (int i = 1; i <= 50; ++i)
    {
        twom[i] = twom[i - 1] << 1;
    }
    log_2[1] = 0;
    for (int i = 2; i < MAXS; ++i)
    {
        log_2[i] = log_2[i / 2] + 1;
    }
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            scanf("%1d", &relationship[i][j]);
            friends[i] += twom[j - 1] * relationship[i][j];
        }
//        friends[i] += twom[i - 1];
    }

    f[0] = true;
    int x;
    int half_n = n / 2;
    for (int i = 0; i < half_n; ++i)
        f[twom[i]] = true;
    for (int i = 1; i < twom[half_n]; ++i)
    {
        if (f[i])
            continue;
        x = log_2[lowbit(i)] + 1;
        if (!f[i - twom[x - 1]])
            continue;
        if (((long long)i & friends[x]) == (i - twom[x - 1]))
        {
            f[i] = true;
        }
    }
    g[0] = 1;
    for (int i = 1; i < twom[n - half_n]; ++i)
    {
        x = log_2[lowbit(i)] + 1;
        g[i] = g[i - twom[x - 1]] + g[(friends[x + half_n] & ((long long)i << half_n)) >> half_n];
    }

    long long s;
    long long ans = 0;
    for (int i = 0; i < twom[half_n]; ++i)
    {
        if (f[i])
        {
            s = twom[n] - twom[half_n];
            for (int j = 1; j <= half_n; ++j)
            {
                if ((i >> (j - 1)) & 1)
                {
                    s = s & friends[j];
                }
            }
            ans += g[s >> half_n];
        }
    }
    printf("%lld", ans);
    return 0;
}
int lowbit(int _x)
{
    return _x & -_x;
}
