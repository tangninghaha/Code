#include <cstdio>

/* Constant */
const int MAXN = 1e5 + 5;
const int mod = 1e9 + 7;

/* Declaration */
int main();
long long qpow(int, int);

/* Variable */
int a[MAXN];

/* Definition */
int main()
{
    freopen("queries.in", "r", stdin);
    freopen("queries.out", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }
    char tmp;
    int l, r, x;
    long long ans = 0;
    for (int i = 1; i <= m; ++i)
    {
        ans = 0;
        tmp = getchar();
        while (tmp != '=' && tmp != '?')
        {
            tmp = getchar();
        }
        scanf("%d%d%d", &l, &r, &x);
        if (tmp == '=')
        {
            for (int i = l; i <= r; ++i)
            {
                a[i] = x;
            }
        }
        else
        {
            for (int i = l; i <= r; ++i)
            {
                ans += (long long)a[i] * qpow(i - l + 1, x);
                ans %= mod;
            }
            printf("%lld\n", ans);
        }
    }
    return 0;
}
long long qpow(int _a, int _b)
{
    if (!_b)
        return 1;
    if (_b == 1)
        return _a;
    long long ret = qpow(_a, _b / 2) % mod;
    if (_b & 1)
    {
        return (((ret * ret) % mod) * _a) % mod;
    }
    else
    {
        return ((ret * ret) % mod);
    }
    return 0;
}
