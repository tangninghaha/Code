#include <cstdio>

int main()
{
    long long ans = 0;
    int n;
    while (scanf("%d", &n) != EOF)
    {
        ans += n * (n - 1) / 2;
    }
    printf("%lld", ans);
}
