#include <stdio.h>
#include <ctime>
#include <stdlib.h>
const int MAXX = 1e6;
bool pd[MAXX + 1];
int main()
{
    srand(time(0));
    int seed = rand() % 114514;
    srand(time(0) + seed);
    int n = 15, m = 15;
    int tot = 0, k = 5;
    printf("%d %d\n", n, m);
    int t;
    int vis;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            vis = rand() % 50;
            if (!vis && tot < k)
            {
                printf("%d ", 0);
                ++tot;
            }
            else
            {
                t = rand() % MAXX + 1;
                while (pd[t])
                {
                    t = rand() % MAXX + 1;
                }
                pd[t] = true;
                printf("%d ", t);
            }
        }
        printf("\n");
    }
}
