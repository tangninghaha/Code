#include <cstdio>
int main()
{
  long long n, m, l;
  scanf("%lld%lld%lld", &n, &m, &l);
  long long ans = 0;
  for (long long i = 1; i <= n / l; ++i)
  {
    long long tmp = i * l + i * m + m - n;
    if (tmp <= 0)
      continue;
    if (tmp % (l + n) == 0)
    {
      long long b = (i * (l + m) + m - n) / (l + n);
      if (b > m / l)
        continue;
      printf("%lld\n", i);
      ++ans;
    }
  }
  printf("%lld", ans);
}
