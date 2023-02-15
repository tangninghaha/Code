#include <cstdio>

/* Constant */
char winner[2][6] = {{'F', 'i', 'r', 's', 't'}, {'S', 'e', 'c', 'o', 'n', 'd'}};

/* Declaration */
int main();
long long Min(long long, long long);

/* Definition */
int main()
{
    freopen("yiyi.in", "r", stdin);
    freopen("yiyi.out", "w", stdout);
    int t;
    scanf("%d", &t);
    long long a, b, c;
    for (int i = 1; i <= t; ++i)
    {
        scanf("%lld%lld%lld", &a, &b, &c);
        a &= 1;
        if (b < 2 && c < 2)
        {
            if (!b)
            {
                if (!c)
                {
                    printf("%s\n", winner[1]);
                }
                else
                {
                    printf("%s\n", winner[a]);
                }
            }
            else
            {
                if (!c)
                {
                    printf("%s\n", winner[a]);
                }
                else
                {
                    printf("%s\n", winner[a]);
                }
            }
            continue;
        }
        if (b < 2 || c < 2)
        {
            if (!a)
            {
                if (b < 2)
                {
                    if (!b)
                    {
                        printf("%s\n", winner[1]);
                    }
                    else
                    {
                        printf("%s\n", winner[0]);
                    }
                }
                else if (c < 2)
                {
                    if (!c)
                    {
                        printf("%s\n", winner[1]);
                    }
                    else
                    {
                        printf("%s\n", winner[0]);
                    }
                }
            }
            else
            {
                if (c)
                    printf("%s\n", winner[1]);
                else
                    printf("%s\n", winner[0]);
            }
            continue;
        }
        if (!a)
        {
            if ((b - 2 < c && b >= 2) || (c - 2 < b && c >= 2))
            {
                printf("%s\n", winner[0]);
            }
            else
            {
                printf("%s\n", winner[1]);
            }
        }
        else
        {
            if ((b - 2 >= c && b >= 2) || (c - 2 >= b && c >= 2))
            {
                printf("%s\n", winner[0]);
            }
            else
            {
                printf("%s\n", winner[1]);
            }
        }
    }
}
long long Min(long long _a, long long _b)
{
    return _a < _b ? _a : _b;
}
