#include <cstdio>

const int MAXN = 3e5 + 5;

int main();
long long Max(long long, long long);

int l[MAXN], r[MAXN];
int in[MAXN], out[MAXN];

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d", &l[i], &r[i]);
        ++in[l[i]];
        ++out[r[i] + 1];
    }
    for (int i = 1; i <= 3e5; ++i)
    {
        in[i] += in[i - 1];
        out[i] += out[i - 1];
    }
    int lbound, rbound, mid, ed;
    long long ans = 0;
    for (int st = 1; st <= 3e5; ++st)
    {
        lbound = 1, rbound = 3e5 - st + 1;
        while (lbound <= rbound)
        {
            mid = (lbound + rbound) >> 1;
            ed = st + mid - 1;
            if (in[ed] - in[st - 1])
            {
                rbound = mid - 1;
            }
            else if (out[ed] - out[st - 1])
            {
                rbound = mid - 1;
            }
            else
            {
                ans = Max(ans, (long long)(ed - st + 1) * (in[st - 1] - out[st - 1]));
                lbound = mid + 1;
            }
        }
    }
    printf("%lld", ans);
    return 0;
}
long long Max(long long _a, long long _b)
{
    return _a > _b ? _a : _b;
}
