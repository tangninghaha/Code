#include <cstdio>
#include <cstdlib>

/* Constant */
const int N = 20;

/* Declaration */
int main();
void Dfs(int);
void Init();

/* Variable */
int n, t;
int a[N + 1];
long long c[N][N];
bool vis[N + 1];
bool pd;

/* Definition */
void Init()
{
  c[0][0] = 1;
  for (int i = 1; i < 20; ++i)
  {
    for (int j = 0; j <= i; ++j)
    {
      c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
    }
  }
  return;
}
int main()
{
  Init();
  for (int i = 10; i <= 10; ++i)
  {
    n = i;
    for (int j = 1000; j <= 2000; ++j)
    {
      t = j;
      printf("%d %d:\n", n, t);
      pd = false;
      Dfs(1);
    }
  }
}
void Dfs(int _x)
{
  if (_x > n)
  {
    int sum = 0;
    for (int i = 1; i <= n; ++i)
    {
      sum += c[n - 1][i - 1] * a[i];
    }
    if (sum == t)
    {
      for (int i = 1; i <= n; ++i)
        printf("%d ", a[i]);
      printf("\n");
      pd = true;
    }
    return;
  }
  for (int i = 1; i <= n; ++i)
  {
    if (!vis[i])
    {
      a[_x] = i;
      vis[i] = true;
      Dfs(_x + 1);
      vis[i] = false;
      if (pd)
        return;
    }
  }
}
