#include <cstdio>
#define int long long

/* Constant */
const int N = 100;

/* Declaration */
signed main();
bool Sovle(long long);

/* Variable */
int a[N + 1];
int b[N + 1];
long long c[N + 1];
int n;
long long t1, t2;

/* Definition */
signed main()
{
  int tt;
  scanf("%lld", &tt);
  for (int fot = 1; fot <= tt; ++fot)
  {
    scanf("%lld%lld%lld", &n, &t1, &t2);
    for (int i = 1; i <= n; ++i)
      scanf("%lld%lld%lld", &a[i], &b[i], &c[i]);
  
    long long lbound = 2, rbound = t1 + t2;
    long long mid;
    long long ans = 0;
    while (lbound <= rbound)
    {
      mid = lbound + rbound >> 1;
      if (Sovle(mid))
      {
        ans = mid;
        lbound = mid + 1;
      }
      else
      {
        rbound = mid - 1;
      }
    }
    printf("%lld\n", t1 + t2 - ans);
  }
  return 0;
}
bool Sovle(long long s)
{
  long long lbound = s - t2, rbound = t1;
  if (rbound > s - 1)
    rbound = s - 1;
  long long x, y;
  bool pd1, pd2;
  if (lbound <= 0)
    lbound = 1;
  while (lbound <= rbound)
  {
    x = lbound + rbound >> 1;
    y = s - x;
    pd1 = false;
    pd2 = false;
    for (int i = 1; i <= n; ++i)
    {
      if (x * a[i] + y * b[i] > c[i])
      {
        if (a[i] > b[i])
          pd1 = true;
        else
          pd2 = true;
        break;
      }
    }
    if (pd1)
    {
      rbound = x - 1;
    }
    else if (pd2)
    {
      lbound = x + 1;
    }
    else
    {
      return true;
    }
  }
  return false;
}
