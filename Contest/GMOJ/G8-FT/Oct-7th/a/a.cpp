#include <cstdio>

/* Constant */
const int MAXP = 2005;
const int mod = 998244353;
const long long INF = 1e15;

/* Declaration */
int main();
long long GetAns(int, int, const int);
long long Dfs(int, int, const int);
int Abs(int);
long long Min(long long _a, long long _b);

/* Variable */
bool vis[MAXP];
long long power[MAXP * MAXP + MAXP];

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
    for (int i = 1; i < P; ++i)
    {
        for (int j = 1; j < P; ++j)
        {
            sum = GetAns(i, j, P);
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
long long GetAns(int x, int y, const int P)
{
    for (int i = 0; i < P; ++i)
    {
        vis[i] = false;
    }
    return Dfs(x, y, P);
}
long long Dfs(int x, int y, const int P)
{
    if (x == y)
    {
        return 0;
    }
    if (vis[x])
    {
        return -1;
    }
    vis[x] = true;
    long long ret = 0;
    int z;
    long long t = INF;
    for (int c = 0; c < P; ++c)
    {
        z = x + c;
        if (z < P)
        {
            ret = Dfs(x * z % P, y, P);
            if (ret != -1)
            {
                t = Min(Abs(x - z) + ret, t);
            }
        }
        z = x - c;
        if (z >= 1)
        {
            ret = Dfs(x * z % P, y, P);
            if (ret != -1)
            {
                t = Min(Abs(x - z) + ret, t);
            }
        }
    }
    vis[x] = false;
    if (t == INF)
        return -1;
    return t;
}
int Abs(int _x)
{
    return _x > 0 ? _x : -_x;
}
long long Min(long long _a, long long _b)
{
    return _a < _b ? _a : _b;
}
