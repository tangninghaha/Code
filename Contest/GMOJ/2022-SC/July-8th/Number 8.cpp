#include <stdio.h>

const int MAXN = 301;
int a[MAXN][MAXN];
int map[MAXN][MAXN];
int min(int a, int b);
long long max(long long a, long long b);
int s[MAXN][MAXN];

int main()
{
    int n;
    scanf("%d", &n);
    char c;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            c = getchar();
            while (c != '.' && c != '*')
            {
                c = getchar();
            }
            if (c == '.')
            {
                map[i][j] = 0;
            }
            else
            {
                map[i][j] = 1;
            }
            s[i][j] = s[i][j - 1] + map[i][j];
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (map[i][j]) continue;
            if (!map[i - 1][j]) a[i][j] = a[i - 1][j];
            for (int k = i; k <= n; ++k)
            {
                if (map[k][j])
                {
                    a[i][j] = k - 1;
                    break;
                }
            }
            if (!a[i][j])
                a[i][j] = n;
        }
    }
    long long ans = 0;
    int x2ed, ed;
    for (int x1 = 1; x1 <= n; ++x1)
    {
        for (int y1 = 1; y1 <= n; ++y1)
        {
            if (map[x1][y1]) continue;
            for (int y2 = y1 + 2; y2 <= n; ++y2)
            {
                if (map[x1][y2]) continue;
                if (s[x1][y2] - s[x1][y1 - 1]) continue;
                x2ed = min(a[x1][y1], a[x1][y2]);
                for (int x2 = x1 + 2; x2 <= x2ed; ++x2)
                {
                    for (int y3 = 1; y3 <= y1; ++y3)
                    {
                        if (map[x2][y3]) continue;
                        for (int y4 = y2; y4 <= n; ++y4)
                        {
                            if (map[x2][y4]) continue;
                            if (s[x2][y4] - s[x2][y3 - 1]) continue;
                            ed = min(a[x2][y3], a[x2][y4]);
                            for (int x3 = x2 + 2; x3 <= ed; ++x3)
                            {
                                if(s[x3][y4] - s[x3][y3 - 1]) continue;
                                ans = max(ans, (x3 - x2 - 1) * (y4 - y3 - 1)
                                               * (x2 - x1 - 1) * (y2 - y1 - 1));
                            }
                        }
                    }
                }
            }
        }
    }
    printf("%lld", ans);
    return 0;
}

int min(int a, int b)
{
    return a < b ? a : b;
}
long long max(long long a, long long b)
{
    return a > b ? a : b;
}
