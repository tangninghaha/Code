#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    srand((unsigned)time(0));
    int n;
    n = rand() % 1000 + 1;
    printf("%d\n", n);
    for (int i = 1; i <= n; ++i)
    {
        printf("%d ", rand() % 10000 + 1);
    }
    return 0;
}
