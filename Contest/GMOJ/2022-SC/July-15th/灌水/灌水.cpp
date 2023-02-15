#include <stdio.h>
const int MAXN = 25;
int map[MAXN][MAXN];
int f[MAXN];
int new_f[MAXN];
int tot_f[MAXN];
int main()
{
    int n, h;
    scanf("%d%d", &n, &h);
    char cha;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            cha = getchar();
            while (cha < '0' || cha > '1')
            {
                cha = getchar();
            }
            map[i][j] = cha - '0';
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        if (map[1][i])
        {
            f[i] = 1;
            tot_f[i] = 1;
        }
    }
    for (int t = 2; t <= h; ++t)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (map[i][j])
                {
                    new_f[j] += 1 + !(f[i] % 2);
                }
            }
        }
        for (int i = 1; i <= n; ++i)
        {
            f[i] = new_f[i];
            new_f[i] = 0;
            tot_f[i] += f[i];
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        ans += tot_f[i];
    }
    printf("%d", ans);
    return 0;
}
