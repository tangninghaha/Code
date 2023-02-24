#include <cstdio>

/* Constant */
const int N = 100;
const int H = 1000;
const long long mod = 1e9 + 7;

/* Declaration */
int main();

/* Variable */
int h[N + 1];
long long f[N + 1][H + 1];
long long s[N + 1][H + 1];

/* Definition */
int main()
{
  freopen("drought.in", "r", stdin);
  freopen("drought.out", "w", stdout);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
  {
    scanf("%d", &h[i]);
  }
  if (!(n & 1))
  {
    for (int i = 0; i <= h[1]; ++i)
      f[1][i] = 1;
    for (int i = 1; i < n; ++i)
    {
      s[i][0] = f[1][0] % mod;
      for (int j = 0; j <= h[i]; ++j)
      {
        s[i][j] = s[i][j - 1] + f[i][j];
        s[i][j] %= mod;
      }
      for (int j = 0; j <= h[i + 1]; ++j)
      {
        f[i + 1][j] += s[i][h[i + 1] - j];
        f[i + 1][j] %= mod;
        if (j != 0)
          s[i + 1][j] = s[i + 1][j - 1] + f[i + 1][j];
        else
          s[i + 1][j] = f[i + 1][j];
      }
    }
    printf("%lld", f[n][0]);
    return 0;
  }
}
