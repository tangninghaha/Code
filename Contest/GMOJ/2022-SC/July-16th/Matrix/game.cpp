#include <stdio.h>
const int MAXN = 1e6 + 1;
const int MAXK = 1e5 + 1;
const int mod = 1e9 + 7;
long long h[MAXN];
long long t[2][MAXN];
int hc[MAXK][2], lc[MAXK][2];
int hc_tot, lc_tot;
void FileIO();
int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; ++i)
    {
        t[0][i] = i;
        t[0][i] %= mod;
        t[1][i] = m + i;
        t[1][i] %= mod;
    }
    char cha;
    int x, y;
    for (int i = 1; i <= k; ++i)
    {
        cha = getchar();
        while (cha != 'R' && cha != 'S')
        {
            cha = getchar();
        }
        scanf("%d%d", &x, &y);
        if (cha == 'R')
        {
            ++hc_tot;
            hc[hc_tot][0] = x;
            hc[hc_tot][1] = y;
        }
        else
        {
            ++lc_tot;
            lc[lc_tot][0] = x;
            lc[lc_tot][1] = y;
        }
    }
    for (int i = 1; i <= lc_tot; ++i)
    {
        t[0][lc[i][0]] *= lc[i][1];
        t[0][lc[i][0]] %= mod;
        t[1][lc[i][0]] *= lc[i][1];
        t[1][lc[i][0]] %= mod;
    }
    long long sum1 = 0, sum2 = 0;
    for (int i = 1; i <= m; ++i)
    {
        sum1 += t[0][i];
        sum1 %= mod;
        sum2 += t[1][i];
        sum2 %= mod;
    }
    h[1] = sum1;
    h[2] = sum2;
    long long c = ((sum2 - sum1) % mod + mod) % mod;
    for (int i = 3; i <= n; ++i)
    {
        h[i] = h[i - 1] + c;
        h[i] %= mod;
    }
    for (int i = 1; i <= hc_tot; ++i)
    {
        h[hc[i][0]] *= hc[i][1];
        h[hc[i][0]] %= mod;
    }
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        ans += h[i];
        ans %= mod;
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
