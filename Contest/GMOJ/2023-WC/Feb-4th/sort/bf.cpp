#include <cstdio>
#include <algorithm>

/* Constant */
const int N = 10;
const int S = 1e8;

/* Declaration */
int main();
void Dfs(int, long long);
void Swap(int&, int&);
long long Min(long long, long long);

/* Variable */
long long ans = (long long) 1 << 60;
int a[N + 1];
int x[N + 1];
long long vis[S];
bool pdd[S];
int from[S];
int n;

/* Definition */
void Swap(int& _a, int& _b)
{
  int temp = _a;
  _a = _b;
  _b = temp;
  return;
}
void print(int _x)
{
  while (_x)
  {
    printf("%d <- ", _x);
    _x = from[_x];
  }
}
int main()
{
  scanf("%d", &n);
  int sum = 0;
  for (int i = 1; i <= n; ++i)
  {
    scanf("%d", &a[i]);
    sum = sum * 10 + i;
  }
  Dfs(sum, 0);
  printf("%lld", ans);
  return 0;
}
void Dfs(int s, long long _x)
{
  if (pdd[s] && _x >= vis[s])
    return;
  vis[s] = _x;
  pdd[s] = true;
  bool pd = false;
  int tmp = s;
  for (int i = 1; i <= n; ++i)
  {
    x[n - i + 1] = tmp % 10;
    tmp /= 10;
  }
  for (int i = 1; i < n; ++i)
    if (a[x[i]] > a[x[i + 1]])
    {
      pd = true;
      break;
    }
  if (!pd)
    return void(ans = Min(ans, _x));
  for (int i = 1; i <= n; ++i)
  {
    for (int j = i + 1; j <= n; ++j)
    {
      Swap(x[i], x[j]);
      tmp = 0;
      for (int k = 1; k <= n; ++k)
        tmp = tmp * 10 + x[k];
      if (_x + a[x[i]] + a[x[j]] == 90699 && tmp == 652341)
        printf("!");
      if (vis[tmp] >= _x + a[x[i]] + a[x[j]])
        from[tmp] = s;
      Dfs(tmp, _x + a[x[i]] + a[x[j]]);
      tmp = s;
      for (int k = 1; k <= n; ++k)
      {
        x[n - k + 1] = tmp % 10;
        tmp /= 10;
      }
    }
  }
  return;
}
long long Min(long long _a, long long _b)
{
  return _a < _b ? _a : _b;
}
