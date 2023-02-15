#include <cstdio>

/* Constant */
const int MAXN = 1e6 + 5;

/* Declaration */
int main();
int Gcd(int, int);

/* Variable */
int a[MAXN];

/* Definition */
int main()
{
    freopen("interval.in", "r", stdin);
    freopen("interval.out", "w", stdout);
    int t;
    scanf("%d", &t);
    int n;
    bool pd;
    int ans, sum;
    for (int fot = 1; fot <= t; ++fot)
    {
        pd = false;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &a[i]);
        }
        for (int i = 2; i <= n; ++i)
        {
            if (a[i] == a[i - 1])
            {
                pd = true;
                break;
            }
            if (i == 2)
                ans = a[i] - a[i - 1];
            else
                ans = Gcd(ans, a[i] - a[i - 1]);
        }
        if (pd)
        {
            pd = false;
            for (int i = 2; i <= n; ++i)
            {
                if (a[i] != a[i - 1])
                {
                    pd = true;
                    break;
                }
            }
            if (pd)
            {
                printf("-1\n");
                continue;
            }
            else
            {
                printf("0\n");
                continue;
            }
        }
        sum = 0;
        for (int i = 2; i <= n; ++i)
        {
            sum += (a[i] - a[i - 1]) / ans - 1;
        }
        printf("%d\n", sum);
    }
    return 0;
}
int Gcd(int _a, int _b)
{
    if (!_b)
    {
        return _a;
    }
    return Gcd(_b, _a % _b);
}
