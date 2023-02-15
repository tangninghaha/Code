#include <cstdio>

/* Constant */
const int INF = 1e8 + 9;
const int MAXN = 105;

/* Declaration */
void FileIO();
int main();
int Abs(int x_);
int Min(int a_, int b_);

/* Variable */
int f[MAXN][MAXN];
int sum[MAXN][MAXN];
int s[MAXN];
int m[MAXN];

/* Definition */
void FileIO()
{
    freopen("climate.in", "r", stdin);
    freopen("climate.out", "w", stdout);
    return;
}
int main()
{
    FileIO();
    int n, e;
    scanf("%d%d", &n, &e);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &m[i]);
    }
    int num;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = i + 1; j <= n; ++j)
        {
            num = m[i] + m[j];
            for (int k = i + 1; k <= j - 1; ++k)
            {
                sum[i][j] += Abs(2 * m[k] - num);
            }
        }
    }
    int ans1 = n + 1, ans2 = INF;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j <= n; ++j)
        {
            f[i][j] = INF;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        f[i][1] = 0;
        for (int j = 1; j < i; ++j)
        {
            f[i][1] += 2 * Abs(m[j] - m[i]);
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = i + 1; j <= n; ++j)
        {
            s[i] += 2 * Abs(m[j] - m[i]);
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= i; ++j)
        {
            for (int k = 1; k < i; ++k)
            {
                f[i][j] = Min(f[i][j], f[k][j - 1] + sum[k][i]);
                if (j < ans1 && f[i][j] + s[i] <= e)
                {
                    ans1 = Min(ans1, j);
                    ans2 = f[i][j] + s[i];
                }
                else if (j == ans1 && f[i][j] + s[i] < ans2)
                {
                    ans2 = f[i][j] + s[i];
                }
            }
        }
    }
    printf("%d %d", ans1, ans2);
    return 0;
}
int Abs(int x_)
{
    return x_ < 0 ? -x_ : x_;
}
int Min(int a_, int b_)
{
    return a_ < b_ ? a_ : b_;
}
