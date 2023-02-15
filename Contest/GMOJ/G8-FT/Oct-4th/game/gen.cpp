#include <cstdio>
#include <cmath>

int main()
{
    int n = 4;
    printf("%d\n", n);
    int realn = pow(2, n);
    for (int i = 1; i <= realn; ++i)
    {
        for (int j = 1; j <= realn; ++j)
        {
            if (i == j)
            {
                printf("0 ");
            }
            else
            {
                printf("50 ");
            }
        }
        printf("\n");
    }
    return 0;
}
