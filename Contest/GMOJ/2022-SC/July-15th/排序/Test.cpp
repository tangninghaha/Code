#include <stdio.h>
int main()
{
    freopen("sort.in", "w", stdout);
    int n = 100000;
    printf("%d\n", n);
    for (int i = 1; i <= n; ++i)
    {
        printf("%d\n", n - i + 1);
    }
    return 0;
}
