#include <stdio.h>
const int MAXN = 305;
const int mod = 1e9 + 7;

int a[MAXN][MAXN];
long long f[2][MAXN][2001];
long long g[MAXN][MAXN];
int tot_sum;
int sum[2005];
int num[1000005];

void FileIO();
void InitSum(int k);
int main();
long long Sovle(int n, int m, int k);

void FileIO()
{
    freopen("mobitel.in", "r", stdin);
    freopen("mobitel.out", "w", stdout);
    return;
}
void InitSum(int k)
{
    for (int i = 1; i < k; ++i)
    {
        if (!num[(k - 1) / i])
        {
            num[(k - 1) / i] = ++tot_sum;
            sum[tot_sum] = (k - 1) / i;
        }
    }
    return;
}
int main()
{
    FileIO();
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            scanf("%d", &a[i][j]);
        }
    }
    printf("%lld", Sovle(n, m, k));
    return 0;
}
long long Sovle(int n, int m, int k)
{
    InitSum(k);
    g[1][1] = 1;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            g[i][j] += g[i - 1][j];
            g[i][j] %= mod;
            g[i][j] += g[i][j - 1];
            g[i][j] %= mod;
        }
    }
    f[1][1][num[(k - 1) / a[1][1]]] = 1;
    for (int i = 1; i <= n; ++i)
    {
        if (i != n)
        {
            for (int j = 1; j <= m; ++j)
            {
                for (int x = 1; x <= tot_sum; ++x)
                {
                    f[(i + 1) & 1][j][x] = 0;
                }
            }
        }
        for (int j = 1; j <= m; ++j)
        {
            for (int x = 1; x <= tot_sum; ++x)
            {
                if (i < n)
                {
                    f[(i + 1) & 1][j][num[sum[x] / a[i + 1][j]]] += 
                    f[i & 1][j][x];
                    f[(i + 1) & 1][j][num[sum[x] / a[i + 1][j]]] %= mod;
                }
                if (j < m)
                {
                    f[i & 1][j + 1][num[sum[x] / a[i][j + 1]]] += 
                    f[i & 1][j][x];
                    f[i & 1][j + 1][num[sum[x] / a[i][j + 1]]] %= mod;
                }
            }
        }
    }
    long long ret = g[n][m];
    for (int i = 1; i <= tot_sum; ++i)
    {
        ret -= f[n & 1][m][i];
        ret = (ret % mod + mod) % mod;
    }
    return ret;
}
