#include <cstdio>

/* Constant */
const int N = 1e5;
const int Q = 2e5;

/* Class */
class Graph
{
  public:
    int head[N + 1];
    int nxt[Q * 2 + 1];
    int to[Q * 2 + 1];
    bool pd[Q * 2 + 1];
    int tot;
    void Add(int _u, int _v)
    {
      ++tot;
      pd[tot] = true;
      nxt[tot] = head[_u];
      to[tot] = _v;
      head[_u] = tot;
      return;
    }
};

/* Declaration */
int main();
void Dfs(int, int);

/* Variable */
bool pd[N + 1];
bool sta[N + 1];
Graph G;
char type[Q + 1];
int x[Q + 1];
int y[Q + 1];
int ans[N + 1];

/* Definition */
int main()
{
  freopen("farm.in", "r", stdin);
//  freopen("farm.out", "w", stdout);
  int n, q;
  scanf("%d%d", &n, &q);
  char tmp = getchar();
  for (int i = 1; i <= n; ++i)
  	pd[i] = true;
  for (int i = 1; i <= q; ++i)
  {
    while (tmp != 'D' && tmp != 'A' && tmp != 'R')
    {
      tmp = getchar();
    }
    type[i] = tmp;
    if (type[i] == 'D')
    {
      scanf("%d", &x[i]);
      pd[x[i]] = false;
    }
    else if (type[i] == 'A')
    {
      scanf("%d%d", &x[i], &y[i]);
      G.Add(x[i], y[i]);
      G.Add(y[i], x[i]);
    }
    else
    {
      scanf("%d", &x[i]);
      G.pd[x[i] * 2 - 1] = G.pd[x[i] * 2] = false;
    }
    tmp = getchar();
  }
  for (int i = 1; i <= n; ++i)
    if (pd[i])
      Dfs(i, q);
  for (int i = q; i >= 1; --i)
  {
    if (type[i] == 'D')
    {
      if (sta[x[i]])
        continue;
      Dfs(x[i], i - 1);
    }
    else
    {
      if (type[i] == 'R')
      {
        G.pd[x[i] * 2 - 1] = G.pd[x[i] * 2] = true;
        if (sta[G.to[x[i] * 2 - 1]] && sta[G.to[x[i] * 2]])
          continue;
        if (!sta[G.to[x[i] * 2 - 1]] && !sta[G.to[x[i] * 2]])
          continue;
        Dfs(G.to[x[i] * 2 - 1], i - 1);
        Dfs(G.to[x[i] * 2], i - 1);
      }
    }
  }
  for (int i = 1; i <= n; ++i)
    printf("%d\n", ans[i]);
}
void Dfs(int _x, int _ans)
{
  if (sta[_x])
   return;
  sta[_x] = true;
  if (!ans[_x])
    ans[_x] = _ans;
  for (int i = G.head[_x]; i; i = G.nxt[i])
  {
    if (!G.pd[i])
      continue;
    Dfs(G.to[i], _ans);
  }
}
