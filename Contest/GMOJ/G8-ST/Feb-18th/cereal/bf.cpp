#include <cstdio>
#include <cstring>

/* Constant */
const int N = 100;

/* Declaration */
int main();
void Dfs(int);

/* Variable */
int a[N + 1];
int f[N + 1];
int s[N + 1];
int pd[N + 1];
int n;
int ans[N + 1];
bool vis[N + 1];
int ans_num = 1 << 29;

/* Definition */
int main()
{
  int m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
  {
    scanf("%d%d", &f[i], &s[i]);
  }
  Dfs(1);
  printf("%d\n", ans_num);
  for (int i = 1; i <= n; ++i)
  {
    printf("%d\n", ans[i]);
  }
  return 0;
}
void Dfs(int _x)
{
  if (_x > n)
  {
    memset(vis, 0, sizeof(vis));
    int num = 0;
    for (int i = 1; i <= n; ++i)
    {
      if (!vis[f[a[i]]])
        vis[f[a[i]]] = true;
      else if (!vis[s[a[i]]])
        vis[s[a[i]]] = true;
      else
        ++num;
    }
    if (num < ans_num)
    {
      ans_num = num;
      for (int i = 1; i <= n; ++i)
        ans[i] = a[i];
    }
    return;
  }
  for (int i = 1; i <= n; ++i)
  {
    if (!pd[i])
    {
      a[_x] = i;
      pd[i] = true;
      Dfs(_x + 1);
      pd[i] = false;
    }
  }
}
