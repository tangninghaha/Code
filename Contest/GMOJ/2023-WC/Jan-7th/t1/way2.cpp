#include <cstdio>

/* Constant */
const int MAXN = 1e9 + 5;
const int N = 1e6 + 1;

/* Declaration */
int main();

/* Variable */
int pd[N];
long long sum[N];

/* Definition */
int main()
{
    int n, m;
    long long a, b, c;
    long long x;
    scanf("%lld", &x);
    scanf("%lld%lld%lld", &a, &b, &c);
    scanf("%d%d", &n, &m);
    const long long mod = m;
    a %= mod;
    b %= mod;
    c %= mod;
    x %= mod;
    long long nxt;
    for (int i = 1; i <= n; ++i)
    {
        nxt = a * x;
        nxt %= mod;
        nxt *= x;
        nxt %= mod;
        nxt += (b * x) % mod;
        nxt %= mod;
        nxt += c;
        nxt %= mod;
        x = nxt;
    }
    printf("%lld", x);
    return 0;
}
