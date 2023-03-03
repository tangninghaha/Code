#include <cstdio>

/* Constant */
const int N = 1e5;
const long long INF = (long long)1 << 50;

/* Declaration */
int main();
long long Max(long long, long long);
int Min(int, int);
long long Sovle(long long*, long long*, int);

/* Variable */
long long x[N + 2], y[N + 1];
int ub[N + 1];
long long f[N + 2];
int t, n, k;

/* Definition */
long long Min(long long _a, long long _b)
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
//  freopen("pairedup.out", "w", stdout);
  scanf("%d%d%d", &t, &n, &k);
  for (int i = 1; i <= n; ++i)
  {
    scanf("%lld%lld", &x[i], &y[i]);
  }
  long long ans = 0;
  int last = 1;
  x[n + 1] = x[n] + 1 + k;
  for (int i = 2; i <= n + 1; ++i)
  {
    if (x[i] - x[i - 1] > k)
    {
      if (n & 1)
        ans += Sovle(x + last - 1, y + last - 1, i - last);
      else
        ans += Sovle(x + last - 1, y + last - 1, ub + last - 1, i - last);
      last = i;
    }
  }
  printf("%lld", ans);
  return 0;
}
long long Sovle(long long* _x, long long* _y, int len)
{
  if (!(len & 1))
    return 0;
  long long ret = INF;
  for (int i = 1; i <= len; ++i)
  {
    if (i & 1)
      ret = Min(ret, _y[i]);
    else if (_x[i + 1] - _x[i - 1] <= k)
      ret = Min(ret, _y[i]);
  }
  return ret;
}
long long Sovle2(long long* _x, long long* _y, int* _ub, int len)
{
  int last = 1;
  for (int i = 1; i <= len; ++i)
  {
    while (_x[last] - _x[i] <= k && last <= len)
      ++last;
    _ub[i] = last;
  }
  for (int i = 1; i <= len; ++i)
  {
    for (int j = 1; j <= len; ++j)
    {
      f[i][j] = 
    }
  }
}
