#include <stdio.h>
#include <cstring>

int a[17];
int two_pow[17];
bool pd[65536], vis[17], vis_l[17], vis_w[17];

int n;
int ans;

void Dfs1(int x, int sum1, int sum2);
void Dfs2(int x, int l, int w, int lk, int wk);
int max(int a, int b);

int main()
{
    two_pow[0] = 1;
    for (int i = 1; i <= 16; i++)
    {
        two_pow[i] = two_pow[i - 1] << 1;
    }
    scanf ("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    if (n < 4)
    {
        printf("No Solution");
        return 0;
    }
    Dfs1(1, 0, 0);
    Dfs2(1, 0, 0, 0, 0);
    if (ans == 0)
        printf ("No Solution");
    else
        printf("%d", ans);
}
void Dfs1(int x, int sum1, int sum2)
{
    if (x > n)
    {
        if (sum1 == sum2)
        {
            int k = 0;
            for (int i = 1; i <= n; i++)
            {
                k += vis[i] * two_pow[i - 1];
            }
            pd[k] = 1;
        }
        return;
    }
    vis[x] = 1;
    Dfs1(x + 1, sum1 + a[x], sum2);
    Dfs1(x + 1, sum1, sum2 + a[x]);
    vis[x] = 0;
    Dfs1(x + 1, sum1, sum2);
    return;
}
void Dfs2(int x, int l, int w, int lk, int wk)
{
    if (x > n)
    {
//        int lk = 0, wk = 0;
//        for (int i = 1; i <= n; i++)
//        {
//           lk += vis_l[i] * two_pow[i - 1];
//        }
//        for (int i = 1; i <= n; i++)
//        {
//           wk += vis_w[i] * two_pow[i - 1];
//        }
        if (pd[lk] && pd[wk])
        {
            ans = max(ans, l * w / 4);
        }
        return;
    }
    vis_l[x] = 1;
    Dfs2(x + 1, l + a[x], w, lk + two_pow[x - 1], wk);
    vis_l[x] = 1;
    vis_w[x] = 1;
    Dfs2(x + 1, l, w + a[x], lk, wk + two_pow[x - 1]);
    vis_w[x] = 0;
    Dfs2(x + 1, l, w, lk, wk);
}
int max(int a, int b)
{
    return a > b ? a : b;
}
