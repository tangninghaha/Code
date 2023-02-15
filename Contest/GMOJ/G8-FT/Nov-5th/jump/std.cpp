#include <cstdio>
#include <cmath>

/* Constant */
const int MAXN = 1005;
const int INF = 1e9 + 555;

/* Declaration */
int main();
template <typename T> T Max(T, T);

/* Variable */
long long dp[MAXN][2];
int l[MAXN]; // 以i为结尾的横跳段对应的开头
long long sum[MAXN];
long long point[MAXN]; // 以i为结尾的横跳段的最大分数
int a[MAXN];

/* Definition */
int main()
{
    int t;
    scanf("%d", &t);
    for (int fot = 1; fot <= t; ++fot)
    {
        int n, k;
        for (int i = 1; i <= n; ++i)
        {
            dp[i][0] = INF;
            point[i] = 0;
            l[i] = i;
            sum[i] = 0;
        }
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &a[i]);
            dp[i][1] = a[i];
            sum[i] = sum[i - 1] + a[i];
        }

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= i; ++j)
            {
                if (sum[i] - sum[j - 1] >= point[i])
                {
                    point[i] = sum[i] - sum[j - 1];
                    l[i] = j;
                }
            }
        }
        long long times;
        long long ans = 0;
        dp[1][0] = 0;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j < i; ++j)
            {
                times = Max(dp[j][0], (long long)ceil(-1.0 * (sum[i] - sum[j]) / point[j]));
                if (times & 1)
                {
                    ++times;
                }
                if (dp[i][0] >= times)
                {
                    dp[i][0] = times;
                    if (sum[i] - sum[j] < 0)
                        dp[i][1] = Max(dp[i][1], ((long long)ceil(-1.0 * (sum[i] - sum[j] + dp[j][1]))) / point[j] * point[j] + (sum[i] - sum[j]) + dp[j][1]);
                    else
                        dp[i][1] = Max(dp[i][1], dp[j][1] + sum[i] - sum[j]);
                }
            }
            ans = Max(ans, (k - dp[i][0] - 1) * point[i] + dp[i][1]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
template <typename T> T Max(T _a, T _b)
{
    return _a > _b ? _a : _b;
}
