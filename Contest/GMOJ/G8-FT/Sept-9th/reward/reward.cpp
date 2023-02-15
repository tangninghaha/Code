#include <cstdio>

/* Declaration */
int main();
void FileIO();
long long qpow(long long a, long long b, const long long mod);

/* Definition */
void FileIO()
{
    freopen("reward.in", "r", stdin);
    freopen("reward.out", "w", stdout);
}
int main()
{
    FileIO();
    long long n, m;
    long long p;
    scanf("%lld%lld%lld", &n, &m, &p);
    long long ans = 1;
    const long long mod = p;
    bool pd = false;
    long long pjc = 0;
    if (n + m < p)
    {
        for (int i = 2; i <= n + m; ++i)
        {
            ans *= i;
            ans %= mod;
        }
    }
    else
    {
        for (int i = 1; i < p; ++i)
        {
            ans *= i;
            ans %= mod;
        }
        pd = true;
        pjc = ans;
    }
    long long div_num = 1;
    if (n < p)
    {
        for (int i = 1; i <= n; ++i)
        {
            div_num *= i;
            div_num %= mod;
        }
    }
    else
    {
        if (pd)
        {
            div_num = pjc;
        }
        else
        {
            for (int i = 1; i < p; ++i)
            {
                div_num *= i;
                div_num %= mod;
            }
            pd = true;
            pjc = div_num;
        }
    }
    ans = ans * (qpow(div_num, mod - 2, mod) % mod);
    ans %= mod;
    div_num = 1;
    if (m < p)
    {
        for (int i = 1; i <= m; ++i)
        {
            div_num *= i;
            div_num %= mod;
        }
    }
    else
    {
        if (pd)
        {
            div_num = pjc;
        }
        else
        {
            for (int i = 1; i < p; ++i)
            {
                div_num *= i;
                div_num %= mod;
            }
            pd = true;
            pjc = div_num;
        }
    }
    ans = ans * (qpow(div_num, mod - 2, mod) % mod);
    ans %= mod;
    printf("%lld", ans);
    return 0;
}
long long qpow(long long a, long long b, const long long mod)
{
    if (!b)
        return 1;
    if (b == 1)
        return a;
    long long ret = qpow(a, b / 2, mod) % mod;
    if (b & 1)
    {
        ret = ret * ret;
        ret %= mod;
        ret *= a;
        ret %= mod;
    }
    else
    {
        ret = ret * ret;
        ret %= mod;
    }
    return ret;
}
