#include <stdio.h>
#include <stdlib.h>
#include <ctime>
int vis[10001];
int main()
{
    srand((unsigned)time(0));
    int n = 10000;
    printf("%d\n", n);
    for (int i = 1; i <= n; ++i)
    {
        int t = rand() % n + 1;
        while (vis[t])
            t = rand() % n + 1;
        vis[t] = true;
        printf("%d\n", t);
    }
    return 0;
}
