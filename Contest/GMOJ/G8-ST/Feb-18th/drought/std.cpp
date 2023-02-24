#include <cstdio>
#include <cstring>

/* Constant */
const int N = 105;
const int H = 1005;
const long long mod = 1e9 + 7;

/* Declaration */
int main();

/* Variable */
int h[N + 1];
long long f[N + 1][H + 1];
long long s[N + 1][H + 1];
int yh[N + 1];

/* Definition */
int main()
{
  freopen("drough.in", "r", stdin);
//  freopen("drough.out", "w", stdout);
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
      for (int j = 0; j <= h[i + 1]; ++j)
      {
        s[i][j] = s[i][j - 1] + f[i][j];
        s[i][j] %= mod;
      }
      for (int j = 0; j <= h[i + 1]; ++j)
      {
        f[i + 1][j] += s[i][h[i + 1] - j];
        f[i + 1][j] %= mod;
      }
    }
    printf("%lld", f[n][0]);
    return 0;
  }
  else
  {
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
      yh[i] = h[i];
  	for (int k = 0; k <= H; ++k)
  	{
  	  memset(f, 0, sizeof(f));
  	  memset(s, 0, sizeof(s));
  	  for (int i = 1; i <= n; ++i)
  	  {
  	    h[i] = yh[i] - k;
      }
      for (int i = 0; i <= h[1]; ++i)
        f[1][i] = 1;
      for (int i = 1; i < n; ++i)
      {
        s[i][0] = f[1][0] % mod;
        for (int j = 0; j <= h[i + 1]; ++j)
        {
          s[i][j] = (s[i][j - 1] + f[i][j]);
          s[i][j] %= mod;
        }
        for (int j = 0; j <= h[i + 1]; ++j)
        {
          f[i + 1][j] += s[i][h[i + 1] - j];
          f[i + 1][j] %= mod;
        }
      }
  	  ans += f[n][0];
  	  ans %= mod;
	  }
	  printf("%lld", ans);
    return 0;
  } 
}
