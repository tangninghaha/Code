#include <cstdio>

/* Constant */
const int mod = 1e9 + 7;

/* Declaration */
int main();

/* Definition */
int main()
{
    int n;
    scanf("%d", &n);
    long long sum = 1;
    for (int i = 1; i <= n; ++i)
    {
        sum *= i;
        sum %= mod;
    }
    printf("%lld", sum);
    return 0;
}
