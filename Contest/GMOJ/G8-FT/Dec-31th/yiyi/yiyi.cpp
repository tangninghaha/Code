#include <cstdio>

/* Declaration */
int main();

/* Definition */
int main()
{
    freopen("yiyi.in", "r", stdin);
    freopen("yiyi.out", "w", stdout);
    int t;
    scanf("%d", &t);
    long long a, b, c;
    long long sum;
    for (int fot = 1; fot <= t; ++fot)
    {
        scanf("%lld%lld%lld", &a, &b, &c);
        sum = b + c * 2;
        if (!a && !b && !c)
        {
            printf("Second\n");
        }
        else if (sum % 3)
        {
            if ((a + b + c) & 1)
            {
                printf("Second\n");
            }
            else
            {
                printf("First\n");
            }
        }
        else
        {
            if ((a + b + c) & 1)
            {
                printf("Second\n");
            }
            else
            {
                printf("First\n");
            }
        }
    }
}
