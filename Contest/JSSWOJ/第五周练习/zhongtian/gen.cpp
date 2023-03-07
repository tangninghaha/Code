#include <cstdio>
#include <cstdlib>
#include <ctime>
long long Gcd(long long _a, long long _b)
{
  if (!_b)
    return _a;
  return Gcd(_b, _a % _b);
}
int main()
{
  srand(time(0));
  long long a, b, c;
  while (Gcd(c + a, c + b) % (a - b) != 0)
  {
    a = rand() % 100000 + 1;
    b = rand() % 100000 + 1;
    if (a == b) 
      ++b;
    c = rand() % a + 1;
    while (c > a / 2 || c > b / 2)
      c = rand() % a + 1;
  }
  printf("%lld %lld %lld", a, b, c);
  return 0;
}
