#include <cstdio>

/* Constant */
const int N = 5000;

/* Declaration */
int main();

void Qsort(int, int);
void Swap(int&, int&);

int Gcd(int, int);

/* Variable */
int a[N];

/* Definition */
int main()
{
  freopen("algebraic.in", "r", stdin);
  freopen("algebraic.out", "w", stdout);
  int t;
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
  {
    scanf("%d", &a[i]);
  }
  Qsort(1, n);
  scanf("%d", &t);
  int k;
  int g;
  long long ans = 0;
  int first, second;
  int x;
  for (int i = 1; i <= t; ++i)
  {
    ans = 0;
    scanf("%d", &k);
    if (!k)
    {
      for (int j = 1; j <= n; ++j)
      {
        ans += (long long)a[j] * a[j];
      }
      printf("%lld\n", ans);
      continue; 
    }
    g = Gcd(k, n);
    for (int j = 1; j <= g; ++j)
    {
      first = a[j * (n / g)];
      x = j * (n / g) - 1;
      ans += (long long)first * a[x];
      if (n / g >= 3)
        ans += (long long)first * a[x - 1];
      first = a[x];
      second = a[x - 1];
      x -= 2;
      for (int l = 3; l < n / g; ++l)
      {
        ans += (long long)first * a[x];
        first = second;
        second = a[x];
        --x;
      }
      if (n / g >= 3) ans += (long long)first * second;
    }
    if (n / g == 2)
      printf("%lld\n", ans * 2);
    else
      printf("%lld\n", ans);
  }
  return 0;
}
void Qsort(int l, int r)
{
  int mid = a[l + r >> 1];
  int i = l, j = r;
  while (i <= j)
  {
    while (a[i] < mid)
      ++i;
    while (a[j] > mid)
      --j;
    if (i <= j)
    {
      Swap(a[i], a[j]);
      ++i;
      --j;
    }
  }
  if (i < r) Qsort(i, r);
  if (l < j) Qsort(l, j);
  return;
}
void Swap(int& _a, int& _b)
{
  int tmp = _a;
  _a = _b;
  _b = tmp;
  return;
}
int Gcd(int _x, int _y)
{
  if (!_y) return _x;
  return Gcd(_y, _x % _y);
}
