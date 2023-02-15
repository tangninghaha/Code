#include <stdio.h>
#include <cstring>

const int MAXN = 1e5 + 5;
const long long mod = 1e9 + 7;
char str_s[MAXN], str_t[MAXN], str_tem[MAXN];
long long ans = 0;
int n, k;

void Dfs(int x, int p);

int main()
{
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
    scanf("%d%d", &n, &k);
    scanf("%s", str_s);
    scanf("%s", str_t);
    Dfs(0, 0);
    printf("%lld\n", (ans + 1) % mod);
}

void Dfs(int x, int p)
{
    if (x >= k)
    {
        if (strcmp(str_tem, str_t) < 0)
        {
            ans++;
            ans %= mod;
        }
        return;
    }
    if (p >= n)
    {
        return;
    }
    str_tem[p] = str_s[p];
    for (int i = 1; i <= 26; i++)
    {
        if (str_s[p] - 'a' + 1 != i)
        {
            str_tem[p] = i + 'a' - 1;
            Dfs(x + 1, p + 1);
            str_tem[p] = str_s[p];
        }
        else
        {
            Dfs(x, p + 1);
        }
    }
}
