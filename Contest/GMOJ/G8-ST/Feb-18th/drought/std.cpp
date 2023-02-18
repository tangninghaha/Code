#include <cstdio>

/* Constant */
const int N = 100;
const int H = 1000;
const int mod = 1e9 + 7;

/* Declaration */
int main();

/* Variable */
int h[N + 1];
long long f[N + 1][H];

/* Definition */
int main()
{
  freopen("drough.in", "r", stdin);
  freopen("drough.out", "w", stdout);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
  {
    scanf("%d", &h[i]);
  }
  if (!(n & 1))
  {
    f[0][0] = 1;
    for (int i = 1; i <= n; ++i)
      for (int j = 0; j <= h[i]; ++j)
        for (int k = 0; k <= j; ++k)
          f[i][j - k] += f[i - 1][k], f[i][j - k] %= mod;
    printf("%lld", f[n][0]);
    return 0;
  }
}
