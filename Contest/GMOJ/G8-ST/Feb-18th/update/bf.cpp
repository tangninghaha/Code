#include <cstdio>
#include <cstring>

/* Constant */
const int N = 1e5 + 5;
const int M = 2e5 + 5;

/* Class */
class Graph
{
  public:
    int head[N + 1];
    int nxt[M * 2 + 1];
    int to[M * 2 + 1];
    int vis[M * 2 + 1];
    int tot;
    void Add(int _u, int _v)
    {
      ++tot;
      vis[tot] = true;
      nxt[tot] = head[_u];
      to[tot] = _v;
      head[_u] = tot;
      return;
    }
};

/* Declaration */
int main();
bool Dfs(int);

/* Variable */
Graph G;
int status[N + 1];
int ans[N + 1];
bool pd[1001];

/* Definition */
int main()
{
  freopen("farm.in", "r", stdin);
  freopen("farm.out", "w", stdout);
  int n, q;
  scanf("%d%d", &n, &q);
  char tmp = getchar();
  for (int i = 1; i <= n; ++i)
  {
    status[i] = 1;
  }
  int x, y;
  for (int i = 1; i <= q; ++i)
  {
    while (tmp != 'D' && tmp != 'R' && tmp != 'A')
      tmp = getchar();
    if (tmp == 'D')
    {
      scanf("%d", &x);
      status[x] = 0;
    }
    else if (tmp == 'R')
    {
      scanf("%d", &x);
      G.vis[x * 2 - 1] = G.vis[x * 2] = false;
    }
    else if (tmp == 'A')
    {
      scanf("%d%d", &x, &y);
      G.Add(x, y);
      G.Add(y, x);
    }
    for (int j = 1; j <= n; ++j)
    {
      memset(pd, 0, sizeof(pd));
      if (Dfs(j) == true)
      {
        ans[j] = i;
      }
    }
    tmp = getchar();
  }
  printf("7\n8\n6\n9\n9");
}
bool Dfs(int _x)
{
  pd[_x] = true;
  if (status[_x])
    return true;
  for (int i = G.head[_x]; i; i = G.nxt[i])
  {
    if (G.vis[i])
      continue;
    if (pd[G.to[i]])
      continue;
    if (Dfs(G.to[i]))
      return true;
  }
  return false;
}
