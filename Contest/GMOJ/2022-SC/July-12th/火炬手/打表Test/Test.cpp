#include <stdio.h>
#include <cmath>
bool Pd(long long x);
int GetMin(int n)
{
    for (long long i = 1; i <= 1000000000; ++i)
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
