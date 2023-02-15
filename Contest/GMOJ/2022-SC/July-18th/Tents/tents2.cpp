#include <stdio.h>
long long f[3005][3005];
const long long mod = 1e9 + 7;
long long C(int n, int m);
void FileIO();
int main()
{
    FileIO();
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        f[0][i] = 1;
    }
    for (int i = 0; i <= n; ++i)
    {
        f[i][0] = 1;
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            f[i][j] += f[i - 1][j];
            f[i][j] %= mod;
            f[i][j] += f[i - 1][j - 1] * 4 * j;
            f[i][j] %= mod;
            if (i >= 2)
            {
                f[i][j] += f[i - 2][j - 1] * j * (i - 1);
                f[i][j] %= mod;
            }
            if (j >= 2)
            {
                f[i][j] += f[i - 1][j - 2] * C(j, 2);
                f[i][j] %= mod;
            }
        }
    }
    printf("%lld", ((f[n][m] - 1) % mod + mod) % mod);
    return 0;
}
long long C(int n, int m)
{
    long long ret = 1;
    for (int i = 1; i <= m; ++i)
    {
        ret *= (n - i + 1);
    }
    for (int i = 1; i <= m; ++i)
    {
        ret /= i;
    }
    return ret;
}
void FileIO()
{
    freopen("tents.in", "r", stdin);
    freopen("tents.out", "w", stdout);
    return;
}
