#include <stdio.h>
#include <math.h>
const double r = 0.5772157149;
int main()
{
    long long n, m;
    scanf("%lld%lld", &n, &m);
    if (n <= 5e7)
    {
        double ans = 0;
        for (int i = 1; i <= n; ++i)
        {
            ans += 1.0 / (2 * i);
        }
        printf("%.0lf", ceil(ans * m - 1.0));
    }
    else
    {
        double g;
        g = log(n) + r;
        g /= 2;
        printf("%.0lf", ceil(g * m - 1));
    }
    return 0;
}
