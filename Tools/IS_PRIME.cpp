#include <cmath>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    long long x;
    scanf("%lld", &x);
    for (long long i = 2; i <= sqrt(x); ++i)
    {
        if(!(x % i))
        {
            printf("NO\n");
            system("pause");
            return 0;
        }
    }
    printf("YES\n");
    system("pause");
    return 0;
}
