#include <stdio.h>

int n, m;

const int MAXN = 1e3 + 5;
const int mod = 1000000007;
int a[MAXN][MAXN];
void Dfs(int x, int y);
bool pd(int x, int y);
long long qpow(int a, int b);
int ans;

int main()
{
    scanf("%d%d", &n, &m);
    if (n == 2)
    {
        printf("%lld", (qpow(2, m + 1) * 3) % mod);
        return 0;
    }
    if (m == 2)
    {
        printf("%lld", (qpow(2, n + 1) * 3) % mod);
        return 0;
    }
    Dfs(1, 1);
    printf("%d", ans);
    return 0;
}

void Dfs(int x, int y)
{
    if (x == n && y == m)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (pd(i, j)) return;
            }
        }
        ans++;
        ans %= mod;
        return;
    }
    for (int i = 1; i <= 4; ++i)
    {
        a[x][y] = i;
        if (y != m) Dfs(x, y + 1);
        else Dfs(x + 1, 1);
        a[x][y] = 0;
    }
    return;
}

bool pd(int x, int y)
{
    if(x > 1 && y > 1)
    {
        if (a[x - 1][y - 1] == a[x][y] || a[x - 1][y] == a[x][y] || a[x][y - 1] == a[x][y]) return 1;
    }
    if (x > 1 && y < m)
    {
        if (a[x + 1][y - 1] == a[x][y] || a[x + 1][y] == a[x][y] || a[x][y - 1] == a[x][y]) return 1;
    }
    if (x < n && y < m)
    {
        if (a[x + 1][y + 1] == a[x][y] || a[x + 1][y] == a[x][y] || a[x][y + 1] == a[x][y]) return 1;
    }
    if (x < n && y > 1)
    {
        if (a[x + 1][y - 1] == a[x][y] || a[x + 1][y] == a[x][y] || a[x][y - 1] == a[x][y]) return 1;
    }
    return 0;
}

long long qpow(int a, int b)
{
    if (b == 0) return 1;
    if (b == 1) return a;
    long long ret = qpow(a, b / 2) % mod;
    if (b & 1)
    {
        return (((ret * ret) % mod) * a) % mod;
    }
    else
    {
        return (ret * ret) % mod;
    }
    return 1;
}
