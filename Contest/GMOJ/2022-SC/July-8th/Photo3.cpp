#include <stdio.h>
#define INF 1000000010
const int MAXN = 2e5 + 5;
int maxn[MAXN], minn[MAXN];
int queue[MAXN];
int f[MAXN];
int max(int a, int b);
int min(int a, int b);
int main()
{
    freopen("photo.in", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n + 2; ++i)
    {
        minn[i] = i;
    }
    int l, r;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &l, &r);
        maxn[r + 1] = max(maxn[r + 1], l);
        minn[r] = min(minn[r], l);
    }
    for (int i = 1; i <= n + 1; ++i)
    {
        maxn[i] = max(maxn[i], maxn[i - 1]);
    }
    for (int i = n; i >= 1; --i)
    {
        if (minn[i + 1] <= i)
            minn[i] = min(minn[i], minn[i + 1]);
    }
    int head = 1, tail = 1;
    queue[1] = 0;
    int ans = -1;
    int x;
    for (int i = 1; i <= n; ++i)
    {
        x = queue[tail];
//        ed = min(minn[i] - 1, i - 1);
        while (queue[tail] < minn[i] - 1)
        {
            ++x;
            while (f[queue[tail]] < f[x] && head <= tail)
                --tail;
            ++tail;
            queue[tail] = x;
        }
        while (queue[head] < maxn[i] && head <= tail)
            ++head;
        if (head <= tail && f[queue[head]] != -1)
        {
            f[i] = f[queue[head]] + 1;
        }
        else
        {
            f[i] = -1;
        }
    }
    for (int i = maxn[n + 1]; i <= n; ++i)
    {
        ans = max(ans, f[i]);
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
