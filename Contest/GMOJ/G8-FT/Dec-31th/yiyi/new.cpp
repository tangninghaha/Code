#include <cstdio>

/* Constant */
char winner[2][6] = {{'F', 'i', 'r', 's', 't'}, {'S', 'e', 'c', 'o', 'n', 'd'}};

/* Declaration */
int main();
long long Min(long long, long long);
int Sovle(long long, long long);

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
        if (a)
            printf("%s\n", winner[!Sovle(b, c)]);
        else
            printf("%s\n", winner[Sovle(b, c)]);
    }
}
long long Min(long long _a, long long _b)
{
    return _a < _b ? _a : _b;
}
int Sovle(long long b, long long c)
{
    int tb = b;
    int tc = c;
    int x;
    if (b)
    {
        --tb;
        x = Min(tb, tc);
        tb -= x;
        tc -= x;
        if (tc)
        {
            return 1;
        }
    }
}
