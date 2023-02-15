#include <stdio.h>
int f[305][305][305];
int g[2][305][305];
int sum_h[305][305];
int map[305][305];
char cha[305];
int max(int a, int b);
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", cha + 1);
        for (int j = 1; j <= n; ++j)
        {
            if (cha[j] == '*')
            {
                map[i][j] = 1;
            }
            sum_h[i][j] = sum_h[i][j - 1] + map[i][j];
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int l = 1; l <= n; ++l)
        {
            for (int r = l; r <= n; ++r)
            {
                if (map[i][l] == 1 || map[i][r] == 1)
                {
                    f[i][l][r] = 0;
                }
                else if (sum_h[i][r] == sum_h[i][l - 1])
                {
                    f[i][l][r] = max(f[i - 1][l][r] + 1, 1);
                }
                else if (f[i - 1][l][r])
                {
                    f[i][l][r] = f[i - 1][l][r] + 1;
                }
                else
                {
                    f[i][l][r] = 0;
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int len = 1; len <= n; ++len)
        {
            for (int l = 1; l <= n - len + 1; ++l)
            {
                int r = l + len - 1;
                if (f[i][l][r] > 2 && r - l + 1 > 2)
                {
                    f[i][l][r] = (f[i][l][r] - 2) * (r - l - 1);
                }
                else
                {
                    f[i][l][r] = 0;
                }
                f[i][l][r] = max(f[i][l][r], 
                                 max(f[i][l + 1][r], f[i][l][r - 1]));
            }
        }
    }
    int ans = -1;
    for (int i = n; i >= 1; --i)
    {
        for (int l = 1; l <= n; ++l)
        {
            for (int r = l; r <= n; ++r)
            {
                g[i % 2][l][r] = 0;
                if (map[i][l] == 1 || map[i][r] == 1)
                {
                    g[i % 2][l][r] = 0;
                }    
                else if (sum_h[i][r] == sum_h[i][l - 1])
                {
                    g[i % 2][l][r] = max(g[(i + 1) % 2][l][r] + 1, 1);
                }
                else if (g[(i + 1) % 2][l][r])
                {
                    g[i % 2][l][r] = g[(i + 1) % 2][l][r] + 1;
                }
                else
                {
                    g[i % 2][l][r] = 0;
                }
                if (g[i % 2][l][r] > 2 && r - l + 1 > 2
                    && sum_h[i][r] == sum_h[i][l - 1])
                    ans = max(ans, 
                              (g[i % 2][l][r] - 2) * (r - l - 1) * f[i][l][r]);
            }
        }
    }
    printf("%d", ans == 0 ? -1 : ans);
    return 0;
}
int max(int a, int b)
{
    return a > b ? a : b;
}
