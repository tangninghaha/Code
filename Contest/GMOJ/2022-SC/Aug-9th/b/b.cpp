#include <cstdio>
#include <cstring>

char str[55][25];
int len[55];
const long long mod = 990804011;
long long f[55][25];
long long g[55][55][25];
bool vis[55][55][25];

long long Dfs(int x, int ed, int last);
void FileIO();
int main();
int Max(int a, int b);
long long qpow(int x, int y);

long long Dfs(int x, int ed, int last)
{
    if (vis[x][ed][last])
        return g[x][ed][last];
    long long ret = 0;
    if (x == ed + 1)
    {
        return 1;
    }
    for (int i = 1; i <= last; ++i)
    {
        ret += Dfs(x + 1, ed, last);
        ret %= mod;
    }
    vis[x][ed][last] = true;
    g[x][ed][last] = ret;
    return ret % mod;
}
void FileIO()
{
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    return;
}
int main()
{
    FileIO();
    int n;
    scanf("%d", &n);
    int l = 0;
    int num = 0;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", str[i] + 1);
        str[i][0] = '~';
        len[i] = strlen(str[i]) - 1;
        str[i][0] = 0;
        l = Max(l, len[i]);
        for (int j = 1; j <= n; ++j)
        {
            if (str[i][j] == '?')
            {
                ++num;
            }
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        f[i][0] = 1;
        f[0][i] = 1;
    }
    int k;
    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j <= l; ++j)
        {
            if (!str[i][j])
            {
                str[i][j] = 'z';
            }
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= l; ++j)
        {
            k = i;
            while (str[k][j] == '?' && k > 0)
            {
                --k;
            }
            if (k == 0)
            {
                f[i][j] = (f[i][j - 1] * Dfs(k + 1, i, str[k][j] - 'a' + 1))
                          % mod;
            }
            else
            {
                f[i][j] = (((f[i][j - 1] * f[k - 1][j]) % mod) * 
                          Dfs(k + 1, i, str[k][j] - 'a' + 1)) % mod;
            }
        }
    }
    long long ans = qpow(26, num);
    ans -= f[n][l];
    printf("%lld", ans);
}
int Max(int a, int b)
{
    return a > b ? a : b;
}
long long qpow(int x, int y)
{
    if (!y)
        return 1;
    if (y == 1)
        return x;
    long long ret = qpow(x, y / 2);
    if (x & 1)
    {
        return (((ret * ret) % mod) * x) % mod;
    }
    else
    {
        return (ret * ret) % mod;
    }
    return 1;
}
