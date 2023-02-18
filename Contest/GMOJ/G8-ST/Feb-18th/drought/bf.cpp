#include <cstdio>

/* Constant */
const int N = 100;
const int mod = 1e9 + 7;

/* Declaration */
int main();
void Dfs(int, int);

/* Variable */
int h[N + 1];
int a[N + 1];
int n;
long long ans;

/* Definition */
int main()
{
  freopen("drough.in", "r", stdin);
  freopen("drough.out", "w", stdout);
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &h[i]);
  Dfs(1, 0);
  printf("%lld", ans);
  return 0;
}
void Dfs(int _x, int last)
{
  if (_x > n)
  {
    int sum1 = 0, sum2 = 0;
    for (int i = 1; i <= n; ++i)
      if (i & 1)
        sum1 += a[i];
      else
        sum2 += a[i];
    if (n & 1 && sum1 < sum2)
        return;
    if (!(n & 1) && sum1 != sum2)
        return;
    for (int i = 1; i <= n; ++i)
      if (a[i] < sum1 - sum2)
        return;
    ++ans;
    ans %= mod;
    return;
  }
  for (int i = last; i <= h[_x]; ++i)
  {
    a[_x] = i;
    Dfs(_x + 1, i - last);
  }
  return;
}
