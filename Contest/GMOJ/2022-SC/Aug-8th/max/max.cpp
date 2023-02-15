#include <stdio.h>
const int MAXN = 305;
int a[MAXN][MAXN];
long long s[MAXN][MAXN];

void FileIO();
int main();
int Max(int aa, int bb);

void FileIO()
{
    freopen("max.in", "r", stdin);
    freopen("max.out", "w", stdout);
    return;
}
int main()
{
    FileIO();
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            scanf("%d", &a[i][j]);
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j];
        }
    }
    long long sum;
    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            for (int x = i; x <= n; ++x)
            {
                for (int y = j; y <= m; ++y)
                {
                    sum = s[x][y] - s[i - 1][y] - s[x][j - 1] + s[i - 1][j - 1];
                    if (sum > 0)
                    {
                        ans = Max(ans, (x - i + 1) * (y - j + 1));
                    }
                }
            }
        }
    }
    printf("%d", ans);
    return 0;
}
int Max(int aa, int bb)
{
    return aa > bb ?aa : bb;
}
