#include <stdio.h>
const int MAXN = 1001;
int rk[MAXN][2];
int num[MAXN];
int bh[MAXN];
int r[MAXN];
int c[MAXN];
int tot;
int main()
{
    freopen("number", "r", stdin);
    int n, k;
    scanf("%d%d", &n, &k);
    int x;
    for (int i = 1; i <= k; ++i)
    {
        scanf("%d%d%d", &x, &r[i], &c[i]);
        bool pd = false;
        for (int j = 1; j <= tot; ++j)
        {
            if (num[j] == x)
            {
                pd = true;
                bh[i] = j;
                break;
            }
        }
        if (pd)
            continue;
        ++tot;
        rk[tot][0] = (x - 1) / n + 1;
        rk[tot][1] = (x - 1) % n + 1;
        num[tot] = x;
        bh[i] = tot;
    }
    for (int i = 1; i <= k; ++i)
    {
        int len1 = ((c[i] - rk[bh[i]][1]) + n) % n;
        int len2 = ((r[i] - rk[bh[i]][0]) + n) % n;
        for (int j = 1; j <= tot; ++j)
        {
            if (bh[i] != j && rk[bh[i]][0] == rk[j][0])
            {
               rk[j][1] += len1;
               rk[j][1] = (rk[j][1] - 1) % n + 1;
            }
        }
        rk[bh[i]][1] = c[i];
        for (int j = 1; j <= tot; ++j)
        {
            if (bh[i] != j && rk[bh[i]][1] == rk[j][1])
            {
               rk[j][0] += len2;
               rk[j][0] = (rk[j][0] - 1) % n + 1;
            }
        }
        rk[bh[i]][0] = r[i];
        printf("%d\n", len1 + len2);
    }
    return 0;
}
