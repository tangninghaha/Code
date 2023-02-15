#include <stdio.h>
const int N = 1e8;
int ans[11] = {0, 6954793, 13694682, 20238658, 26602369, 32796782, 38832914, 44720629, 50471934, 56087100, 61574510};
int ff(long long x);
int main()
{
    freopen("number.in", "r", stdin);
//    freopen("number.out", "w", stdout);
    int n;
    scanf("%lld", &n);
    long long anss = 0;
    int f, flast = 0;
    for (long long i = 1; i <= n; ++i)
    {
        if (i % 10) 
        {
            f = flast + 1;
            if (!(i % f))
            {
                ++anss;
            }
        }
        else
        {
            f = ff(i);
            if (!(i % f))
            {
                ++anss;
            }
        }
        flast = f;
    }
    printf("%lld", anss);
}
int ff(long long x)
{
    int ret = 0;
    while(x)
    {
        ret += x % 10;
        x /= 10;
    }
    return ret;
}
