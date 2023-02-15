#include <cstdio>
const long long mod = 1e9 + 7;
int main()
{
    long long ans = 0;
    long long n, m;
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            for (int k = i; k <= n; ++k)
            {
                for (int l = j; l <= m; ++l)
                {
                    ans += (((k - i + 1) % mod) * ((l - j + 1) % mod));
                    ans %= mod;
                }
            }
        }
    }
    printf("%lld", ans);
}
