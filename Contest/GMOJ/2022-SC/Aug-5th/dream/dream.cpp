#include <stdio.h>

const int mod = 1000000007;
int n, m;
int Abs(int x);
void FileIO();
long long Dfs(int t, int x);
int main();
int f[205][105][105];
bool vis[205][105][105];

int Abs(int x)
{
    return x > 0 ? x : -x;
}
void FileIO()
{
    freopen("dream.in", "r", stdin);
    freopen("dream.out", "w", stdout);
    return;
}
long long Dfs(int t, int x, int last)
{
    if (vis[t][x][last])
        return f[t][x][last] % mod;
    vis[t][x][last] = 1;
    if (Abs(x - 100) + t - last > m)
        return 0;
    long long ret = 0;
    if (t == n)
    {
        if (x == 100)
        {
            f[t][x][last] = 1;
            return 1;
        }
        return 0;
    }
    if (t - last > m)
    {
        return 0;
    }
    if (x == 100)
    {
        ret += Dfs(t + 1, x + 1, t);
        ret %= mod;
        ret += Dfs(t + 1, x - 1, t);
        ret %= mod;
    }
    else
    {
        ret += Dfs(t + 1, x + 1, last);
        ret %= mod;
        ret += Dfs(t + 1, x - 1, last);
        ret %= mod;
    }
    f[t][x][last] = ret;
    return ret % mod;
}
int main()
{
    FileIO();
    scanf("%d%d", &n, &m);
    printf("%lld", Dfs(0, 100, 0));
    return 0;
}
