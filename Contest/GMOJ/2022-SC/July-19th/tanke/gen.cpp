#include <stdio.h>
int main()
{
    freopen("in.txt", "w", stdout);
    int n = 700, q = 1e9 + 7;
    printf("%d %d\n", n, q);
    for (int i = 1; i <= n; ++i)
    {
        printf("%d %d\n", i, i);
    }
    return 0;
}
