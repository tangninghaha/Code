#include <cstdio>
#include <cstdlib>
#include <ctime>

/* Declaration */
int main();

/* Definition */
int main()
{
    freopen("lalo.in", "w", stdout);
    srand(time(0));
    int n = 100;
    int m = 200;
    printf("%d %d\n", n, m);
    int num = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (i == 1 && j == 1)
            {
                printf("E");
                continue;
            }
            if (i == n && j == n)
            {
                printf("X");
                continue;
            }
            if (rand() % 500 == 1 && num < 16)
            {
                printf("G");
                ++num;
            }
            else
            {
                printf("-");
            }
        }
        printf("\n");
    }
    return 0;
}
