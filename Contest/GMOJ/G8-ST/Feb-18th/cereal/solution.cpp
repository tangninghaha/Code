#include <cstdio>

/* Constant */
const int N = 1e5;

/* Declaration */
int main();
void Swap(int&, int&);

/* Variable */
int a[N + 1];
int f[N + 1];
int s[N + 1];
int vis[N + 1];
int chos[N + 1];

/* Definition */
int main()
{
  freopen("cereal.in", "r", stdin);
  freopen("cereal.out", "w", stdout);
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%d%d", &f[i], &s[i]);
  int num = 0;
  for (int i = 1; i <= n; ++i)
  {
    a[i] = i;
    if (!vis[f[i]])
      chos[i] = 1, vis[f[i]] = i;
    else if (!vis[s[i]])
      chos[i] = 2, vis[s[i]] = i;
    else
      chos[i] = -1, ++num;
  }
  int tmp;
  bool pd;
  for (int i = 1; i <= n; ++i)
  {
    if (chos[a[i]] == 1 && vis[s[a[i]]] == false)
    {
      tmp = -1;
      pd = false;
      for (int j = i + 1; j <= n; ++j)
      {
        if (chos[a[j]] == -1 && (f[a[j]] == f[a[i]] || (chos[f[a[j]]] < i && f[a[i]] == s[a[j]])))
        {
          if (vis[s[a[j]]] == 0 && tmp == -1)
          {
            tmp = j;
            continue;
          }
          vis[s[a[i]]] = j;
          chos[a[i]] = 2;
          if (f[a[j]] == f[a[i]])
            chos[a[j]] = 1;
          else
            chos[a[j]] = 2;
          --num;
          Swap(a[i], a[j]);
          pd = true;
          break;
        }
      }
      if (!pd && tmp != -1)
      {
        vis[s[a[i]]] = tmp;
        chos[a[i]] = 2;
        chos[a[tmp]] = 1;
        --num;
        Swap(a[i], a[tmp]);
      }
    }
  }
  printf("%d", num);
  for (int i = 1; i <= n; ++i)
  {
    printf("\n%d", a[i]);
  }
  return 0;
}
void Swap(int& _a, int& _b)
{
  int tmp = _a;
  _a = _b;
  _b = tmp;
  return;
}
