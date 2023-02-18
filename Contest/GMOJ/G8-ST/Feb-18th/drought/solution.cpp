#include <cstdio>

/* Constant */
const int N = 100;
const int H = 1000;
const int VALUE = 100000;
const int mod = 1e9 + 7;

/* Declaration */
int main();
int Max(int, int);

/* Variable */
long long f[2][VALUE + 1];
long long g[2][VALUE + 1];
int h[N + 1];

/* Definition */
int main()
{
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
  {
    scanf("%d", &h[i]);
  }
  int half_n = n / 2;
  int num, now;
  int last_max = 0, now_max = 0, last_last_max = 0;
  f[0][0] = 1;
  for (int i = 1; i <= half_n; ++i)
  {
    num = i * 2 - 1;
    now = i & 1;
    now_max = 0;
    for (int j = 0; j <= last_last_max; ++j)
      f[now][j] = 0;
    for (int j = 0; j <= last_max; ++j)
    {
      for (int k = 0; k <= h[num]; ++k)
      {
        if (j + k > VALUE)
          break;
        now_max = Max(now_max, j + k);
        f[now][j + k] += f[!now][j];
        f[now][j + k] %= mod;
      }
    }
    last_last_max = last_max;
    last_max = now_max;
  }
  g[0][0] = 1;
  last_max = 0, last_last_max = 0, now_max = 0;
  for (int i = 1; i <= half_n; ++i)
  {
    num = i * 2;
    now = i & 1;
    now_max = 0;
    for (int j = 0; j <= last_last_max; ++j)
      g[now][j] = 0;
    for (int j = 0; j <= last_max; ++j)
    {
      for (int k = 0; k <= h[num]; ++k)
      {
        if (j + k > VALUE)
          break;
        now_max = Max(now_max, j + k);
        g[now][j + k] += g[!now][j];
        g[now][j + k] %= mod;
      }
    }
    last_last_max = last_max;
    last_max = now_max;
  }
  if (n & 1)
  {
    for (int i = 0; i <= last_max; ++i)
    {
    }
    printf("0");
  }
  else
  {
    long long ans = 0;
    for (int i = 0; i <= last_max; ++i)
    {
      ans += g[0][i] * f[0][i] % mod;
      ans %= mod;
    }
    printf("%lld", ans);
  }
  return 0;
}
int Max(int _a, int _b)
{
  return _a > _b ? _a : _b;
}
