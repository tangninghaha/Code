#include <cstdio>
#include <cstdlib>

/* Constant */
const int N = 20;

/* Declaration */
int main();
void Dfs(int, int);
void Init();
void Qsort(int, int, int);
void Swap(long long&, long long&);
int GetMin(int, int);
int GetMax(int, int);

/* Variable */
int n, t;
int a[N + 1];
long long c[N][N];
long long mx[N][N][2];
bool vis[N + 1];
bool pd;

/* Definition */
void Init()
{
  c[0][0] = 1;
  mx[0][0][0] = 1;
  mx[0][0][1] = 0;
  for (register int i = 1; i < 20; ++i)
  {
    for (register int j = 0; j <= i; ++j)
      c[i][j] = c[i - 1][j - 1] + c[i - 1][j], mx[i][j][0] = c[i][j], mx[i][j][1] = j;
    Qsort(0, i, i);
  }
  return;
}
void Swap(long long& _a, long long& _b)
{
  long long tmp = _a;
  _a = _b;
  _b = tmp;
  return;
}
void Qsort(int l, int r, int x)
{
  register int i = l, j = r;
  int mid = mx[x][l + r >> 1][0];
  while (i <= j)
  {
    while (mx[x][i][0] < mid)
      ++i;
    while (mx[x][j][0] > mid)
      --j;
    if (i <= j)
    {
      Swap(mx[x][i][0], mx[x][j][0]);
      Swap(mx[x][i][1], mx[x][j][1]);
      ++i;
      --j;
    }
  }
  if (i < r)
    Qsort(i, r, x);
  if (l < j)
    Qsort(l, j, x);
  return;
}
int main()
{
  //freopen("easy.in", "r", stdin);
  //freopen("easy.out", "w", stdout);
  Init();
  scanf("%d%d", &n, &t);
  while (n && t)
  {
    pd = false;
    Dfs(1, 0);
    scanf("%d%d", &n, &t);
  }
  return 0;
}
void Dfs(int _x, int sum)
{
  if (sum > t)
    return;
  int tmp1 = GetMin(_x, sum);
  int tmp2 = GetMax(_x, sum);
  if (t < tmp1 || t > tmp2)
    return;
  if (_x > n)
  {
    if (sum == t)
    {
      for (int i = 1; i <= n; ++i)
        printf("%d ", a[i]);
      printf("\n");
      pd = true;
    }
    return;
  }
  int st;
  if (_x <= n / 2 + 1)
    st = 1;
  else
    st = a[n - _x + 1] + 1;
  for (register int i = st; i <= n; ++i)
  {
    if (!vis[i])
    {
      a[_x] = i;
      vis[i] = true;
      Dfs(_x + 1, sum + i * c[n - 1][_x - 1]);
      vis[i] = false;
      if (pd)
        return;
    }
  }
  return;
}
int GetMin(int _x, int sum)
{
  int x = 0;
  int ret = 0;
  for (register int i = n; i >= 1; --i)
  {
    if (vis[i])
      continue;
    while (mx[n - 1][x][1] < _x - 1 && x < n)
      ++x;
    ret += mx[n - 1][x][0] * i;
    ++x;
  }
  return ret + sum;
}
int GetMax(int _x, int sum)
{
  int x = 0;
  int ret = 0;
  for (register int i = 1; i <= n; ++i)
  {
    if (vis[i])
      continue;
    while (mx[n - 1][x][1] < _x - 1 && x < n)
      ++x;
    ret += mx[n - 1][x][0] * i;
    ++x;
  }
  return ret + sum;
}
