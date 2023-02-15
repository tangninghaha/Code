#include <stdio.h>
#include <cmath>
int main()
{
    double ans = 0;
    long long n = 1e7;
    for (int i = 1; i <= n; ++i)
    {
        ans += 1.0 / i;
    }
    printf("%.11lf", ans - (double)log(n));
}
