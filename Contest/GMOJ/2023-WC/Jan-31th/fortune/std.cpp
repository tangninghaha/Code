#include <cstdio>

/* Constant */
const int N = 80;
const long long INF = (long long)1 << 62;

/* Declaration */
int main();
long long Max(long long, long long);

/* Variable */
long long f[N + 2][N + 1][N * (N + 1) / 2 + 1];
long long x[N + 1], y[N + 1], z[N + 1];

/* Definition */
int main()
{
  freopen("fortune.in", "r", stdin);
  freopen("fortune.out", "w", stdout);
  long long t;
  long long n;
  scanf("%lld", &t);
  scanf("%lld", &t);
  for (int fot = 1; fot <= t; ++fot)
  {
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%lld%lld%lld", &x[i], &y[i], &z[i]);
    int limit = n * (n + 1) / 2;
    for (int i = 0; i <= n + 1; ++i)
    {
      for (int j = 0; j <= n; ++j)
      {
        for (int k = 0; k <= limit; ++k)
        {
          f[i][j][k] = -INF;
        }
      }
    }
    f[n][0][0] = 0;
    long long ans = 0;
    for (int i = n; i >= 1; --i)
    {
      for (int j = 0; j <= n - i + 1; ++j)
      {
        for (int k = 0; k <= limit; ++k)
        {
          f[i - 1][j + 1][k + j + 1] = Max(f[i - 1][j + 1][k + j + 1], f[i][j][k] + x[i]);
          f[i - 1][j][k + j] = Max(f[i - 1][j][k + j], f[i][j][k] + y[i] * j);
          f[i - 1][j][k + j] = Max(f[i - 1][j][k + j], f[i][j][k] + z[i] * k);
          ans = Max(ans, Max(f[i - 1][j][k + j], f[i - 1][j + 1][k + j + 1]));
//          printf("Hello, world");
        }
      }
    }
    printf("%lld\n", ans);
  }
}
long long Max(long long _a, long long _b)
{
  return _a > _b ? _a : _b;
}
