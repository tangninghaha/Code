#include <stdio.h>
const int mod = 1e9 + 7;
int f[3005][3005][4];
int s_h[3005][3005][4];
int s_l[3005][3005][4];
int main()
{
    freopen("tents.in", "r", stdin);
    freopen("tents.out", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    int t;
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            t = 0;
            for (int k = 0; k < 4; ++k)
            {
                t += s_h[i - 1][j - 1][k];
                t %= mod;
            }
            f[i][j][0] = f[i][j][1] = f[i][j][2] = f[i][j][3] = (1 + t) % mod;
//            f[i][j][1] += s_l[j][i - 1][0];
//            f[i][j][3] += s_h[i][j - 1][2];
//            f[i][j][1] %= mod;
//            f[i][j][3] %= mod;
            for (int k = 0; k < 4; ++k)
            {
                s_h[i][j][k] = s_h[i][j - 1][k] + f[i][j][k];
                s_h[i][j][k] %= mod;
                s_l[j][i][k] = s_l[j][i - 1][k] + f[i][j][k];
                s_l[j][i][k] %= mod;
            }
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            ans += (long long)f[i][j][0] + f[i][j][1] + f[i][j][2] + f[i][j][3];
            ans %= mod;
            for (int k = j + 1; k <= m; ++k)
            {
                ans += (long long)f[i][j][3] * f[i][k][2];
                ans %= mod;
            }
            for (int k = i + 1; k <= n; ++k)
            {
                ans += (long long)f[i][j][1] * f[k][j][0];
                ans %= mod;
            }
        }
    }
    printf("%lld", ans % mod);
    return 0;
}
