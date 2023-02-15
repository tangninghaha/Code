#include <cstdio>

/* Constant */
const int MAXN = 1e5 + 5;
const long long mod = 1e9 + 7;

/* Solution1 */
namespace Solution1
{
    int fa[25];
    int tr[25][25];
    int tr_cnt[25];
    int real_cnt[25];
    int a[25];
    void Dfs(int x);
    int n;
    int Main();
    long long ans = 0;
};

void Solution1::Dfs(int x)
{
    if (x > n)
    {
        int sum = 0, ret;
        for (int i = 1; i <= n; ++i)
        {
            if (real_cnt[i] > 1)
            {
                ret = tr[i][1];
                for (int j = 2; j <= tr_cnt[i]; ++j)
                {
                    ret ^= tr[i][j];
                }
                sum += ret;
                sum %= mod;
            }
        }
        ans += sum;
        ans %= mod;
        return;
    }
    ++tr_cnt[fa[x]];
    ++real_cnt[fa[x]];
    tr[fa[x]][tr_cnt[fa[x]]] = a[x];
    tr[x][1] = 0;
    --real_cnt[x];
    Dfs(x + 1);
    --tr_cnt[fa[x]];
    tr[x][1] = a[x];
    ++real_cnt[x];
    --real_cnt[fa[x]];
    Dfs(x + 1);
    return;
}
int Solution1::Main()
{
    for (int i = 1; i <= n; ++i)
    {
        real_cnt[i] = 1;
        tr_cnt[i] = 1;
        scanf("%d", &a[i]);
        tr[i][1] = a[i];
    }
    for (int i = 2; i <= n; ++i)
    {
        scanf("%d", &fa[i]);
    }
    Dfs(2);
    printf("%lld", ans);
    return 0;
}

/* Declaration */
int main();

/* Definition */
int main()
{
    freopen("climb.in", "r", stdin);
    freopen("climb.out", "w", stdout);
    int n;
    scanf("%d", &n);
    if (n <= 20)
    {
        Solution1::n = n;
        Solution1::Main();
        return 0;
    }
}
