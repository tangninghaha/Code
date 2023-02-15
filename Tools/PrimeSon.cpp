#include <stdio.h>
#include <math.h>
#include <stdlib.h>
void PrimeSon(long long n);
int main()
{
    long long n;
    scanf("%lld", &n);
    PrimeSon(n);
    printf("\n");
    system("pause");
    return 0;
}

void PrimeSon(long long n)
{
    int x = n;
    printf("%d=", x);
    bool pd = false;
    for (long long i = 2; i <= sqrt(n); ++i)
    {
        if (!(x % i))
        {
            int k = 0;
            while (!(x % i))
            {
                x /= i;
                ++k;
            }
            if (pd)
                printf("*");
            printf("%lld^%d", i, k);
            pd = true;
        }
    }
    if (x != 1)
    {
        if (pd)
            printf("*");
        printf("%d^%d", x, 1);
    }
    return;
}
