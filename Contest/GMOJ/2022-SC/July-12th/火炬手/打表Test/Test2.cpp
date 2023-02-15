#include <stdio.h>
#include <cmath>
void PrimeSon(int n)
{
    int x = n;
//    printf("%d=", x);
    bool pd = false;
    for (int i = 2; i <= sqrt(n); ++i)
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
//                printf("+");
//            printf("%d^%d", i, k);
            pd = true;
        }
    }
    if (x != 1)
    {
//        if (pd)
//            printf("+");
//        printf("%d^%d", x, 1);
    }
    return;
}
