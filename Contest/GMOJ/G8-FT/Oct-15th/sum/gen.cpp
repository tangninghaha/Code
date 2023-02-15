#include <cstdio>

/* Constant */
const int MAXN = 5e6;

/* Declaration */
int main();

/* Definition */
int main()
{
    freopen("sum.in", "w", stdout);
    int n = 100;
    printf("%d\n", n);
    for (int i = 1; i <= 100; ++i)
    {
        printf("%d %d %d\n", 1, MAXN, i);
    }
    return 0;
}
