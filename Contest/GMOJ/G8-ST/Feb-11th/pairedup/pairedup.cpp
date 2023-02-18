#include <cstdio>

/* Constant */
const int N = 1e5;
const int INF = 1 << 29;

/* Declaration */
int main();
long long Max(long long, long long);
int Min(int, int);

/* Variable */
int x[N + 2], y[N + 1];
int ub[N + 1];
long long f[N + 2];

/* Definition */
int Min(int _a, int _b)
{
  return _a < _b ? _a : _b;
}
long long Max(long long _a, long long _b)
{
  return _a > _b ? _a : _b;
}
int main()
{
  freopen("pairedup.in", "r", stdin);
  freopen("pairedup.out", "w", stdout);
  int t, n, k;
  scanf("%d%d%d", &t, &n, &k);
  for (int i = 1; i <= n; ++i)
  {
    scanf("%d%d", &x[i], &y[i]);
  }
  long long ans = 0;
  if (t & 1)
  {
    if (n & 1)
    {
      bool pd = false;
      int minn = INF;
      for (int i = 1; i <= n + 1; ++i)
      {
        if (x[i] - x[i - 1] > k)
        {
          ans += minn;
          minn = INF;
          pd = false;
        }
        if (i == n + 1)
          break;
        pd = !pd;
        if (pd)
          minn = Min(minn, y[i]);
        else if (x[i + 1] - x[i - 1] <= k)
          minn = Min(minn, y[i]);
      }
      printf("%lld", ans);
    }
    else
    {
      printf("0");
    }
  }
  else
  {
    int j = n + 1;
    for (int i = n; i >= 1; --i)
    {
      while (x[j - 1] - x[i] > k)
        --j;
      ub[i] = j;
    }
    bool pd = false;
    for (int i = n; i >= 1; --i)
    {
      if (x[i] - x[i + 1] > k)
      {
        pd = false;
      }
      pd = !pd;
      if (pd)
          f[i] = Max(f[i + 1], f[ub[i]] + y[i]);
      else
        f[i] = f[i + 1];
    }
    printf("%lld", f[1]);
  }
  return 0;
}
