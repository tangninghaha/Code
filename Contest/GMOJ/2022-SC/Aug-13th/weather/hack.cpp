#include <cstdio>

int main()
{
    freopen("hack.txt", "w", stdout);
    int n = 1e6, d = 3e4;
    printf("%d %d\n", n, d);
    for (int i = 1; i <= n; ++i)
    {
        if (i != n)
            printf("1000 ");
    }
}
