#include <cstdio>

/* Constant */
const int N = 100;
const int H = 1000;

/* Declaration */
int main()
{
  long long ans = 0;
  long long sum = 0;
  for (int i = 1; i <= N; ++i)
  {
    ans += ((long long)sum + H) * H;
    sum += H;
  }
  printf("%lld", ans);
  return 0;
}
