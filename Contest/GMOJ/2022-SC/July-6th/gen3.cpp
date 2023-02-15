#include <stdio.h>
#include <stdlib.h>
#include <ctime>

int main()
{
    srand(time(0));
//    freopen("data3.in", "w", stdout);
    int n = 100, m = 10000, k = 10;
    printf("%d %d %d\n", n, m, k);
//    for (int i = 1; i <= n; ++i)
//    {
//        for (int j = 1; j <= n; ++j)
//        {
//            if (i != j)
//            {
//                printf("%d %d %d\n", i, j, rand() % n + 1);
//            }
//        }
//    }
    int u, v, w;
    for (int i = 1; i <= m; ++i)
    {
        u = rand() % n + 1, v = rand() % n + 1;
        w = rand() % m + 1;
        while (u == v)
        {
            u = rand() % n + 1;
        }
        printf("%d %d %d\n", u, v, w);
    }
    return 0;
}
