#include <cstdio>
#include <cstring>
const int MAXN = 3005;
const int INF = 1e8 + 5;

int l[MAXN], r[MAXN], w[MAXN];
bool xx[MAXN];
bool chos_num[MAXN];
int n, m;
int ans = INF;

int Min(int a, int b);
void Dfs(int x, int t)
{
    if (x > 1)
    {
        memset(xx, 0, sizeof(xx));
        for (int i = 1; i <= n; ++i)
        {
            if (chos_num[i])
            {
                for (int k = l[i]; k <= r[i]; ++k)
                {
                    xx[k] = true;
                }
            }
        }
        bool pd = true;
        for (int i = 1; i <= m; ++i)
        {
            if (!xx[i])
            {
                pd = false;
                break;
            }
        }
        if (pd)
        {
            ans = Min(ans, t);
        }
    }
    if (x > n)
        return;
    chos_num[x] = true;
    Dfs(x + 1, t + w[x]);
    chos_num[x] = false;
    Dfs(x + 1, t);
    return;
}
int main()
{
    freopen("intervals.in", "r", stdin);
    freopen("intervals.out", "w", stdout);
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d%d%d", &l[i], &r[i], &w[i]);
        }
        Dfs(1, 0);
        if (ans == INF)
        {
            printf("-1");
        }
        else
        {
            printf("%d\n", ans);
        }
    }
}
int Min(int a, int b)
{
    return a < b ? a : b;
}
