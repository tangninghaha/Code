#include <stdio.h>

const int MAXN = 1e4 + 5;
long long f[MAXN][2][2];
int a[MAXN];
const long long INF = 1e17;

int Abs(int x);
void FileIO();
long long Min(long long aa, long long bb);
int main();
long long Pow2(int x);
long long Sovle(int n, int m);

void FileIO()
{
    freopen("change.in", "r", stdin);
    freopen("change.out", "w", stdout);
    return;
}
int main()
{
    FileIO();
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }
    a[n + 1] = a[1];
    printf("%lld", Sovle(n, m));
    return 0;
}
long long Min(long long aa, long long bb)
{
    return aa < bb ? aa : bb;
}
long long Pow2(int x)
{
    return (long long) x * x;
}
long long Sovle(int n, int m)
{
    long long ans = INF;
    for (int k = 0; k <= 1; ++k)
    {
        for (int i = 1; i <= n + 1; ++i)
        {
            for (int j = 0; j <= 1; ++j)
            {
                for (int x = 0; x <= 1; ++x)
                {
                    f[i][j][x] = INF;
                }
            }
        }
        f[1][k][0] = 0;
        for (int i = 2; i <= n + 1; ++i)
        {
            if (a[i] > a[i - 1])
            {
                f[i][0][0] = f[i - 1][0][0] + a[i] - a[i - 1];
                f[i][1][0] = f[i - 1][1][0] + Pow2(a[i] - a[i - 1]);
                f[i][0][1] = Min(f[i - 1][0][1] + a[i] - a[i - 1], 
                                Min(f[i - 1][1][0], f[i - 1][1][1])
                                + Pow2(a[i] - a[i - 1]) + m);
                f[i][1][1] = Min(f[i - 1][1][1] + Pow2(a[i] - a[i - 1]), 
                                Min(f[i - 1][0][0], f[i - 1][0][1])
                                + a[i] - a[i - 1] + m);
            }
            else if (a[i] < a[i - 1])
            {
                f[i][0][0] = f[i - 1][0][0] + Pow2(a[i - 1] - a[i]);
                f[i][1][0] = f[i - 1][1][0] + a[i - 1] - a[i];
                f[i][0][1] = Min(f[i - 1][0][1] + Pow2(a[i - 1] - a[i]),
                                 Min(f[i - 1][1][0], f[i - 1][1][1])
                                  + a[i - 1] - a[i] + m);
                f[i][1][1] = Min(f[i - 1][1][1] + a[i - 1] - a[i], 
                                 Min(f[i - 1][0][0], f[i - 1][0][1])
                                  + Pow2(a[i - 1] - a[i]) + m);
            }
        }
        ans = Min(ans, Min(f[n + 1][k][1] - m, f[n + 1][k][0]));
    }
    return ans;
}
