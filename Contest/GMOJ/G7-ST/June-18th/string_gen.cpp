#include <stdio.h>

int main()
{
    freopen("string.in", "w", stdout);
    int n = 100, k = 5;
    printf("%d %d\n", n, k);
    for (int i = 1; i <= n; i++)
    {
        printf("a");
    }
    printf("\n");
    for (int i = 1; i <= n; i++)
    {
        if (i <= k)
            printf("b");
        else
            printf ("a");
    }
}
