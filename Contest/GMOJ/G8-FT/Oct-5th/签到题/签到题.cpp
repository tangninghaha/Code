#include <cstdio>

/* Constant */
const int MAXN = 1e5 + 5;

/* Declaration */
void Dfs(int, int, int);
int main();

/* Variable */
int n;
int a[MAXN];
int num[MAXN];
bool pd;

/* Definition */
int main()
{
    freopen("checkin.in", "r", stdin);
    freopen("checkin.out", "w", stdout);
    int t;
    scanf("%d", &t);
    for (int tt = 1; tt <= t; ++tt)
    {
        pd = false;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &a[i]);
        }
        Dfs(1, 0, 0);
        if (!pd)
            printf("-1\n");
        continue;
    }
    return 0;
}
void Dfs(int x, int chos_num, int value)
{
    if (x > n)
    {
        if (!value)
            return;
        if (!(n % value))
        {
            printf("%d\n", chos_num);
            for (int i = 1; i <= chos_num; ++i)
            {
                printf("%d ", num[i]);
            }
            pd = true;
        }
        return;
    }
    num[chos_num + 1] = a[x];
    if (pd)
        return;
    Dfs(x + 1, chos_num + 1, value + a[x]);
    if (pd)
        return;
    Dfs(x + 1, chos_num, value);
    if (pd)
        return;
}
