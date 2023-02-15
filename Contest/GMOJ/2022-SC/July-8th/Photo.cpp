#include <stdio.h>

const int MAXM = 100005, MAXN = 200005;
int l[MAXM], r[MAXM], a[MAXN];

int max(int a, int b);
void Dfs(int x, int t);
int n, m;
int ans;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &l[i], &r[i]);
    }
    Dfs(1, 0);
    printf("%d", ans);
    return 0;
}

void Dfs(int x, int t)
{
    if (x > n)
    {
        int js;
        for (int i = 1; i <= m; ++i)
        {
            js = 0;
            for (int j = l[i]; j <= r[i]; ++j)
            {
                if (a[j] == 1)
                {
                    js++;
                    if (js > 1) return;
                }
            }
            if (js != 1)
                return;
        }
        ans = max(ans, t);
        return;
    }
    a[x] = 1;
    Dfs(x + 1, t + 1);
    a[x] = 0;
    Dfs(x + 1, t);
    return;
}

int max(int a, int b)
{
    return a > b ? a : b;
}
