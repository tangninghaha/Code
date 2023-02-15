#include <cstdio>

/* Constant */
const int MAXN = 85;

/* Declaration */
int main();
bool Check(int n);

/* Variable */
int sum[5];
int a[MAXN];
int g[5];
int more[5];
void JiuZhen(int x);

/* Definition */
int main()
{
    int p;
    int n;
    long long t;
    scanf("%d%d%d%d%d", &g[1], &g[2], &g[3], &g[4], &p);
    while (g[1] | g[2] | g[3] | g[4] | p)
    {
        n = g[1] + g[2] + g[3] + g[4];
        for (int i = 1; i <= 4; ++i)
        {
            sum[i] = sum[i - 1] + g[i];
        }
        t = 0;
        for (int i = 1; i <= n; ++i)
        {
            a[i] = i;
        }
        do
        {
            ++t;
            for (int i = 1; i <= p; ++i)
            {
                JiuZhen((i - 1) % 4 + 1);
            }
        }while(!Check(n));
        printf("%lld\n", t);
        scanf("%d%d%d%d%d", &g[1], &g[2], &g[3], &g[4], &p);
    }
    return 0;
}
bool Check(int n)
{
    for (int i = 1; i <= n; ++i)
    {
        if (a[i] != i)
            return false;
    }
    return true;
}
void JiuZhen(int x)
{
    if (x != 4)
    {
        int tmp = a[sum[x - 1] + 1];
        for (int i = sum[x - 1] + 1; i <= sum[x]; ++i)
        {
            a[i] = a[i + 1];
        }
        a[sum[x] + 1] = tmp;
    }
    else
    {
        int tmp = a[sum[3] + 1];
        for (int i = sum[3] + 1; i >= sum[1] + 1; --i)
        {
            a[i] = a[i - 1];
        }
        a[sum[1]] = tmp;
    }
    return;
}
