#include <cstdio>

/* Constant */
const int N = 1000;
const int M = 1000;

/* Declaration */
int main();
long long Dfs(int, int, const int);
int Min(int, int);

/* Variable */
int n, m, t;
int b[N + 1];
int c[N + M + 1][N + M + 1];
int s[N + M + 1][N + M + 1];
long long sum[M + 2];

/* Definition */
int main()
{
//  freopen("babylon.in", "r", stdin);
//  freopen("babylon.out", "w", stdout);
  int p;
  scanf("%d%d%d%d", &n, &t, &m, &p);
  const int mod = p;
  for (int i = 1; i <= t; ++i)
    scanf("%d", &b[i]);
  for (int i = t; i >= 1; --i)
    sum[i] = sum[i + 1] + b[i];

  long long ans = 0;
  c[0][0] = 1;
  for (int i = 1; i <= n + m; ++i)
    for (int j = 0; j <= i; ++j)
      (c[i][j] = c[i - 1][j - 1] + c[i - 1][j]) %= mod, (s[i][j] = s[i][j - 1] + c[i][j]) %= mod;
  for (int i = 1; i <= m; ++i)
    (ans += s[n - t + i - 1][n - t] * Dfs(1, m - i, p)) %= mod;
  (++ans) %= mod;
  printf("%lld", ans);
  return 0;
}
long long Dfs(int x, int num, const int mod)
{
  if (sum[x] < num)
    return 0;
  if (x > t)
    return 0;
  if (!num)
    return 1;
  if (num < 0)
    return 0;
  int ed = Min(num, b[x]);
  long long ret = 0;
  for (int i = 0; i <= ed; ++i)
    (ret += Dfs(x + 1, num - i, mod)) %= mod;
  return ret % mod;
}
int Min(int _a, int _b)
{
  return _a < _b ? _a : _b;
}
