#include <cstdio>

/* Constant */
const int MAXN = 11;
const int MAXM = 31;
const int mod = 1e9 + 7;

/* Declaration */
int main();
void Dfs(int);

/* Variable */
int a[MAXN];
int b[MAXN];
int twom[MAXM];
int n, m;
long long ans;

/* Definition */
int main()
{
    freopen("and.in", "r", stdin);
    freopen("and.out", "w", stdout);
    twom[0] = 1;
    for (int i = 1; i <= 30; ++i)
    {
        twom[i] = twom[i - 1] * 2;
    }
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &b[i]);
    }
    a[0] = twom[m] - 1;
    b[0] = twom[m] - 1;
    Dfs(1);
    printf("%lld", ans);
    return 0;
}
void Dfs(int x_)
{
    if (x_ > n)
    {
        ++ans;
        ans %= mod;
        return;
    }
    for (int i = 0; i < twom[m]; ++i)
    {
        a[x_] = i;
        if (x_ == 1)
        {
            Dfs(x_ + 1);
        }
        else if (((a[x_] & b[x_]) >= (a[x_ - 1] & b[x_ - 1]))
            && ((a[x_] | b[x_]) <= (a[x_ - 1] | b[x_ - 1])))
        {
            Dfs(x_ + 1);
        }
    }
    return;
}
