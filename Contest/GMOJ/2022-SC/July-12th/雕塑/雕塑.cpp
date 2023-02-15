#include <stdio.h>

const int MAXM = 11, MAXN = 21;
int a[MAXM][2];
int chos[MAXM], tot_chos;
bool is_chos[MAXM];
long long ans = 1;
long long jc[21];

long long Dfs(int x, int k);
int n, m;

int main()
{
    jc[0] = 1;
    jc[1] = 1;
    for (int i = 2; i <= 20; ++i)
    {
        jc[i] = jc[i - 1] * i;
    }
    scanf("%d%d", &n, &m);
    int x, y;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &x, &y);
        a[i][0] = x;
        a[i][1] = y;
    }
    ans = jc[n];
    long long tj = 0;
    for (int i = 1; i <= m; ++i)
    {
        tj += Dfs(1, i) * (i % 2 ? 1 : -1);
    }
    ans -= tj;
    printf("%lld", ans);
}

long long Dfs(int x, int k)
{
    long long ret = 0;
    if (tot_chos == k)
    {
        for (int i = 1; i <= k; ++i)
        {
            for (int j = 1; j <= k; ++j)
            {
                if (a[chos[i]][0] == a[chos[j]][0] || a[chos[i]][1] == a[chos[j]][1])
                {
                    if (i != j)
                    {
                        return 0;
                    }
                }
            }
        }
        ret += jc[n - k];
        return ret;
    }
    if (x > m)
        return 0;
    ++tot_chos;
    chos[tot_chos] = x;
    is_chos[x] = true;
    ret += Dfs(x + 1, k);
    --tot_chos;
    is_chos[x] = false;
    ret += Dfs(x + 1, k);
    return ret;
}
