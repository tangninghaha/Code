#include <cstdio>
#include <cstring>

/* Constant */
const int MAXP = 2005;
const int mod = 998244353;
const long long INF = 1e15;

/* Declaration */
int main();
int Abs(int);
long long Min(long long _a, long long _b);
long long cost(int x, int y, const int);
int Gcd(int x, int y);
void Exgcd(int x, int y, int&, int&);

/* Variable */
long long power[MAXP * MAXP + MAXP];
long long f[MAXP][MAXP];

/* Definition */
int main()
{
    int P;
    int t;
    scanf("%d%d", &P, &t);
    power[0] = 1;
    for (int i = 1; i <= P * P + P; ++i)
    {
        power[i] = power[i - 1] * t;
        power[i] %= mod;
    }
    long long sum, ans = 0;
    memset(f, 127 / 3, sizeof(f));
    for (int i = 1; i < P; ++i)
    {
        for (int j = 1; j < P; ++j)
        {
            for (int k = 1; k < j; ++k)
            {
                f[i][j] = Min(f[i][j], f[i][k] + cost(i, k, P));
            }
            sum = f[i][j];
            // printf("%lld ", sum);
            sum %= mod;
            sum *= power[(i - 1) * (P - 1) + j - 1];
            sum %= mod;
            ans += sum;
            ans %= mod;
        }
        // printf("\n");
        // printf("-");
    }
    printf("%lld", ans);
    return 0;
}
int Abs(int _x)
{
    return _x > 0 ? _x : -_x;
}
long long Min(long long _a, long long _b)
{
    return _a < _b ? _a : _b;
}
long long cost(int x, int y, const int P)
{
    if (Gcd(x, y) != 1)
        return INF;
    int ret = 0, tmp;
    Exgcd(x, y, ret, tmp);
    return Abs(x - ret);
}
int Gcd(int x, int y)
{
    if (!y)
        return x;
    return Gcd(y, x % y);
}
void Exgcd(int x, int y, int &a, int &b)
{
    if (!b)
    {
        a = 1;
        return;
    }
    int tmp = a;
    a = b;
    b = tmp - x / y * b;
    return;
}
