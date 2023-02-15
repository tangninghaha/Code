#include <stdio.h>
#include <cmath>
#include <stdlib.h>
int GetMin(int n);
bool Pd(long long x);
int main()
{
    int n;
    scanf("%d", &n);
    int ret = GetMin(n);
    if (ret == -1) return -1;
    printf("%d", ret);
//    PrimeSon(ret);
//    printf("\n");
//    system("pause");
    return 0;
}
int GetMin(int n)
{
    for (long long i = 1; i <= 10000000000; ++i)
    {
        if (Pd(n * i))
        {
            return i;
        }
    }
    return -1;
}
bool Pd(long long x)
{
    while (x)
    {
        if (x % 10 != 0 && x %10 != 1)
        {
            return false;
        }
        x /= 10;
    }
    return true;
}
