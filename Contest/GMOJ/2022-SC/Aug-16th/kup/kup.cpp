#include <cstdio>
#include <ctime>
#include <stdlib.h>

/* Constant */
const int MAXN = 2e3 + 5;

/* Declaration */
int main();
void FileIO();
long long Read();

/* Variable */
long long s[MAXN][MAXN];
long long a[MAXN][MAXN];

/* Definition */
int main()
{
    srand((unsigned)time(0));
    FileIO();
    long long k;
    int n;
    scanf("%lld%d", &k, &n);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            a[i][j] = Read();
            s[i][j] = s[i][j - 1] + s[i - 1][j] - s[i - 1][j - 1] + a[i][j];
        }
    }
    long long sum;
    long long k2 = k * 2;
    if (n <= 60)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                for (int x = i; x <= n; ++x)
                {
                    for (int y = j; y <= n; ++y)
                    {
                        sum = s[x][y] - s[i - 1][y] - s[x][j - 1] + s[i - 1][j - 1];
                        if (k <= sum && sum <= k2)
                        {
                            printf("%d %d %d %d", i, j, x, y);
                            return 0;
                        }
                    }
                }
            }
        }
    }
    else
    {
        double t = clock() / CLOCKS_PER_SEC;
        int i, j, x, y;
        while (t < 0.9)
        {
            i = rand() % n + 1;
            j = rand() % n + 1;
            x = rand() % (n - i + 1) + i;
            y = rand() % (n - i + 1) + i;
            // printf("%d %d %d %d\n", i, j, x, y);
            sum = s[x][y] - s[i - 1][y] - s[x][j - 1] + s[i - 1][j - 1];
            if (k <= sum && sum <= k2)
            {
                printf("%d %d %d %d", i, j, x, y);
                return 0;
            }
            t = clock() / CLOCKS_PER_SEC;
        }
    }
    printf("%d %d %d %d", 0, 0, 0, 0);
    return 0;
}
void FileIO()
{
    freopen("kup.in", "r", stdin);
    freopen("kup.out", "w", stdout);
    return;
}
long long Read()
{
    long long ret = 0;
    char tmp = getchar();
    while (tmp < '0' || tmp > '9')
        tmp = getchar();
    while (tmp >= '0' && tmp <= '9')
    {
        ret = ret * 10 + tmp - '0';
        tmp = getchar();
    }
    return ret;
}
