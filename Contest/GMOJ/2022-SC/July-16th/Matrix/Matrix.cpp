#include <stdio.h>
const int mod = 1e9 + 7;
long long a[1001][1001];
void FileIO();
int main()
{
    FileIO();
    long long n, m, k;
    scanf("%lld%lld%lld", &n, &m, &k);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            a[i][j] = (i - 1) * m + j;
        }
    }
    char cha;
    int x, y;
    for (int i = 1; i <= k; ++i)
    {
        cha = getchar();
        while (cha != 'R' && cha != 'S')
            cha = getchar();
        scanf("%d%d", &x, &y);
        if (cha == 'R')
        {
            for (int j = 1; j <= m; ++j)
            {
                a[x][j] *= y;
                a[x][j] %= mod;
            }
        }
        if (cha == 'S')
        {
            for (int j = 1; j <= n; ++j)
            {
                a[j][x] *= y;
                a[j][x] %= mod;
            }
        }
    }
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            ans += a[i][j];
            ans %= mod;
        }
    }
    printf("%lld", ans);
    return 0;
}
void FileIO()
{
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    return;
}
