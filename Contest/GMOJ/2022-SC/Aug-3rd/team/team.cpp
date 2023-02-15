#include <stdio.h>
const int MAXN = 1e5 + 5;
int n;
int ans;
int l[MAXN], a[MAXN], r[MAXN];
int chos_num;
int chos[MAXN];
int Max(int a, int b);
void Dfs(int x, int chosed);
int main()
{
    freopen("team.in", "r", stdin);
    freopen("team.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d%d", &l[i], &a[i], &r[i]);
    }
    Dfs(1, 0);
    printf("%d", ans);
    return 0;
}
int Max(int aa, int bb)
{
    return aa > bb ? aa : bb;
}
void Dfs(int x, int chosed)
{
    if (chosed + n - x + 1 <= ans)
        return;
    for (int i = 1; i <= chosed; ++i)
    {
        for (int j = 1; j <= chosed; ++j)
        {
            if (a[chos[i]] < l[chos[j]] || a[chos[i]] > r[chos[j]])
                return;
        }
    }
    if (x > n)
        return;
    ans = Max(ans, chosed);
    chos[chosed + 1] = x;
    Dfs(x + 1, chosed + 1);
    Dfs(x + 1, chosed);
    return;
}
