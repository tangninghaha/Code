#include <stdio.h>
#include <string.h>
int f[65536][17];
int s1[17][17], s2[17][17];
int two_pow[17];
char cha[500005];
int max(int a, int b);
int min(int a, int b);
int main()
{
    two_pow[0] = 1;
    for (int i = 1; i <= 16; ++i)
    {
        two_pow[i] = two_pow[i - 1] << 1;
    }
    int k;
    scanf("%d", &k);
    scanf("%s", cha + 1);
    cha[0] = '!';
    int len = strlen(cha) - 1;
//    for (int i = 1; i <= len / k; ++i)
//    {
//        for (int j = 1; j <= k; ++j)
//        {
//            printf("%c", cha[(i - 1) * k + j]);
//        }
//        printf("\n");
//    }
    for (int i = 1; i <= len / k; ++i)
    {
       for (int j = 1; j <= k; ++j)
        {
           for (int x = 1; x <= k; ++x)
            {
               if (j == x)
                    continue;
               if (cha[(i - 1) * k + j] == cha[(i - 1) * k + x])
                {
                    ++s1[j][x];
                }
            }
        }
    }
    for (int i = 1; i < len / k; ++i)
    {
        for (int j = 1; j <= k; ++j)
        {
            for (int x = 1; x <= k; ++x)
            {
                if (cha[(i - 1) * k + j] == cha[i * k + x])
                {
                    ++s2[j][x];
                }
            }
        }
    }
    int ans = len;
    int nxt_s;
    for (int x = 1; x <= k; ++x)
    {
        memset(f, 0, sizeof(f));
        f[two_pow[x - 1]][x] = len;
        for (int s = two_pow[x - 1]; s < two_pow[k] - 1; ++s)
        {
            if (!((s >> (x - 1)) & 1))
            {
                continue;
            }
            for (int i = 1; i <= k; ++i)
            {
                if ((s >> (i - 1)) & 1)
                {
                    continue;
                }
                nxt_s = s + two_pow[i - 1];
                if (!f[nxt_s][i])
                {
                    f[nxt_s][i] = len;
                }
                for (int j = 1; j <= k; ++j)
                {
                    if (j == x && s != two_pow[x - 1])
                    {
                        continue;
                    }
                    if (!((s >> (j - 1)) & 1))
                    {
                        continue;
                    }
                    f[nxt_s][i] = min(f[nxt_s][i], f[s][j] - s1[i][j]);
                }
            }
        }
        for (int i = 1; i <= k; ++i)
        {
            if (i != x)
                ans = min(ans, f[two_pow[k] - 1][i] - s2[i][x]);
        }
    }
    printf("%d", ans);
    return 0;
}
int max(int a, int b)
{
    return a > b ? a : b;
}
int min(int a, int b)
{
    return a < b ? a : b;
}
