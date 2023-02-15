#include <cstdio>
#include <cstring>

const long long mod = 990804011;
long long f[25][55][55][30];
bool vis[25][55][55][30];
char str[55][25];
int len[55];
int max_len;

long long Dfs(int i, int l, int r, int c);
void FileIO();
int main();
int Max(int a, int b);

long long Dfs(int i, int l, int r, int c)
{
    if (vis[i][l][r][c])
        return f[i][l][r][c] % mod;
    if (l > r)
        return 1;
    if (i > max_len)
    {
        return l == r;
    }
    if (c > 26)
        return 0;
    f[i][l][r][c] = Dfs(i, l, r, c + 1);
    f[i][l][r][c] %= mod;
    for (int mid = l; mid <= r; ++mid)
    {
        if (str[mid][i] - 'a' + 1 == c
            || (c == 0 && str[mid][i] == 'D')
            || (str[mid][i] == '?' && c != 0))
        {
            f[i][l][r][c] += (Dfs(i + 1, l, mid, 0)
                             * Dfs(i, mid + 1, r, c + 1)) % mod;
            f[i][l][r][c] %= mod;
        }
        else
        {
            break;
        }
    }
    vis[i][l][r][c] = true;
    return f[i][l][r][c] % mod;
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
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", str[i] + 1);
        str[i][0] = 'D';
        len[i] = strlen(str[i]) - 1;
    }
    for (int i = 1; i <= n; ++i)
    {
        max_len = Max(max_len, len[i]);
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = len[i] + 1; j <= max_len; ++j)
        {
            str[i][j] = 'D';
        }
    }
    printf("%lld", Dfs(1, 1, n, 0));
    return 0;
}
int Max(int a, int b)
{
    return a > b ? a : b;
}
