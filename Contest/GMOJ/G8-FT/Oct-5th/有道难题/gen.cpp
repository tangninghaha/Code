#include <cstdio>
#include <cstdlib>
#include <ctime>

/* Declaration */
int main();

/* Definition */
int main()
{
    srand(time(0));
    int t = rand() % 100 + 1;
    for (int T = 1; T <= t; ++T)
    {
        long long n = 0;
        int x = rand() % 25 + 1;
        for (int i = 1; i <= x; ++i)
        {
            n += rand() % 2;
            n <<= 1;
        }
        if (!n)
            continue;
        printf("%lld\n", n);
    }
    printf("0");
    return 0;
}
