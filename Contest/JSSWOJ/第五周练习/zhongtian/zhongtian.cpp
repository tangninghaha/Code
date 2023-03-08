#include <cstdio>
#include <cmath>
#include <algorithm>

/* Declaration */
int main();
long long Gcd(long long, long long);
void Exgcd(long long a, long long b, long long& _x, long long& _y);

/* Definition */
int main()
{
  freopen("in.txt", "r", stdin);
  long long n, m, l;
  scanf("%lld%lld%lld", &n, &m, &l);

  long long num1, num2;
  long long g = Gcd(l + m, - l - n);
  if ((n - m) % g != 0)
  {
    printf("0");
    return 0;
  }
  if (n - m == 0)
  {
  	printf("%lld", n / l);
  	return 0;
  }
  long long k = (n - m) / g;
  Exgcd(l + m, - l - n, num1, num2);
  num1 *= k;
  num2 *= k;
  long long tx = (- l - n) / g, ty = (l + m) / g;
  printf("%lld %lld %lld\n", l + m, - l - n, n - m);
  printf("%lld %lld\n", num1, num2);
  printf("%lld %lld %lld\n", g, tx, ty);
  long long minx = (num1 % tx + tx) % tx;
  if (!minx)
    minx += tx;
  long long kx = (minx - num1) / tx;
  ty = -ty;
  long long miny = (num2 % ty + ty) % ty;
  if (!miny)
    miny += ty;
  long long ky = (miny - num2) / ty;

  printf("%lld %lld\n", minx, miny);
  printf("%lld %lld\n", kx, ky);
  // printf("%lld", (maxx - minx) / tx + 1);

  return 0;
}
long long Gcd(long long _a, long long _b)
{
  if (!_b)
    return _a;
  return Gcd(_b, _a % _b);
}
void Exgcd(long long a, long long b, long long& _x, long long& _y)
{
  if (!b)
  {
    _x = 1;
    _y = 0;
    return;
  }
  Exgcd(b, a % b, _x, _y);
  long long tmp = _x;
  _x = _y;
  _y = tmp - a / b * _y;
}
// 9956 20673 761
