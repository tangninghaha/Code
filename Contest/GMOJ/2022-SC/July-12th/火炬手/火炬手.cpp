#include <stdio.h>
#include <cmath>
void GetAns();
int n;
const int N = 19;
int main()
{
    scanf("%d", &n);
    GetAns();
    return 0;
}
void GetAns()
{
    long long end = pow(2, N) - 1, num;
    bool pd = false;
    for (long long s = 1; s <= end; ++s)
    {
        num = s;
        long long t = 0;
        for (int i = 1; i <= N; ++i)
        {
            t *= 10;
            t += num & 1;
            num >>= 1;
        }
        long long k = 0;
        for (int i = 1; i <= N; ++i)
        {
            k *= 10;
            k += t % 10;
            t /= 10;
        }
        if (!(k % n))
        {
            pd = true;
            printf("%lld", k / n);
            return;
        }
    }
    if (!pd)
    {
        printf("No solution!");
    }
    return;
}
