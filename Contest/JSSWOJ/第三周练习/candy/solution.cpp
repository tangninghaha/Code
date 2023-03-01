#include <cstdio>

/* Constant */
const int N = 5000;
const int mod = 1e9 + 7;

/* Declaration */
int main();

/* Variable */
int f[N + 1][N + 1];
int sum[N + 1];
int flag[N + 1];

/* Definition */
int main()
{
  int n, x1, x2;
  scanf("%d%d%d", &n, &x1, &x2);
  int tmp;
  for (int i = 1; i <= x1; ++i)
    scanf("%d", &tmp), ++tmp, flag[tmp] = 1, flag[tmp + 1] = 2;
  for (int i = 1; i <= x2; ++i)
    scanf("%d", &tmp), ++tmp, flag[tmp] = 2, flag[tmp + 1] = 1;
  sum[1] = 1;
  for (int i = 2; i <= n; ++i)
  {
    for (int j = 1; j <= i; ++j)
      if (!flag[i])
        f[i][j] = sum[i - 1];
      else if (flag[i] == 1)
        f[i][j] = ((sum[i - 1] - sum[j - 1]) % mod + mod) % mod;
      else
        f[i][j] = sum[j - 1];
    sum[0] = f[i][0];
    for (int j = 1; j <= i; ++j)
      sum[j] = (sum[j - 1] + f[i][j]) % mod;
  }
  printf("%d", sum[n]);
  return 0;
}
