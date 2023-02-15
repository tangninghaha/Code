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
        t = 1;
        for (int i = 1; i <= n; ++i)
        {
            a[i] = i;
        }
        do
        {
            ++t;
            for (int i = 1; i <= p; ++i)
            {
                more[(i + 1) % 4] = a[sum[(i - 1) % 4] + 1];
            }
            for (int i = 1; i <= 4; ++i)
            {
                for (int j = 1; j < g[i]; ++j)
                {
                    a[sum[i - 1] + j] = a[sum[i - 1] + j + 1];
                }
                a[sum[i]] = more[i % 4];
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
