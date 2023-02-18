#include <cstdio>

/* Constant */
const int N = 5e5;

/* Class */
class Graph
{
  public:
    int head[N + 1];
    int nxt[N + 1];
    int to[N + 1];
    int tot;
    void Add(int _u, int _v)
    {
      ++tot;
      nxt[tot] = head[_u];
      to[tot] = _v;
      head[_u] = tot;
      return;
    }
};

/* Declaration */
int main();
int GetFa(int);
void Bfs(int);
void Sovle(int);

/* Variable */
Graph G;

int ans[N + 1];
int dsu_fa[N + 1];
int fa[N + 1], dep[N + 1];
int c_u[N + 1], c_v[N + 1], c_c[N + 1];
int queue[N + 1];

/* Definition */
int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  int n, q;
  scanf("%d%d", &n, &q);
  for (int i = 2; i <= n; ++i)
  {
    scanf("%d", &fa[i]);
    G.Add(fa[i], i);
  }
  for (int i = 1; i <= q; ++i)
  {
    scanf("%d%d%d", &c_u[i], &c_v[i], &c_c[i]);
  }
  Bfs(1);
  for (int i = q; i >= 1; --i)
  {
    Sovle(i);
  }
  for (int i = 2; i <= n; ++i)
  {
    printf("%d\n", ans[i]);
  }
  return 0;
}
void Bfs(int _x)
{
  int head = 0, tail = 1;
  queue[1] = _x;
  int now;
  while (head < tail)
  {
    ++head;
    now = queue[head];
    dep[now] = dep[fa[now]] + 1;
    for (int i = G.head[now]; i; i = G.nxt[i])
    {
      ++tail;
      queue[tail] = G.to[i];
    }
  }
}
void Sovle(int _x)
{
  int u = c_u[_x], v = c_v[_x];
  int lca;
  while (u != v)
  {
    while (dep[u] != dep[v])
    {
      if (dep[u] < dep[v])
      {
        if (!ans[v])
          ans[v] = c_c[_x];
        v = fa[v];
      }
      else if (dep[u] > dep[v])
      {
        if (!ans[u])
          ans[u] = c_c[_x];
        u = fa[u];
      }
    }
    while (u != v && dep[u] == dep[v])
    {
      if (!ans[u])
        ans[u] = c_c[_x];
      if (!ans[v])
        ans[v] = c_c[_x];
      u = fa[u];
      v = fa[v];
    }
  }
  lca = u;
  for (int i = G.head[c_u[_x]]; i; i = G.nxt[i])
  {
    fa[G.to[i]] = lca;
  }
  for (int i = G.head[c_v[_x]]; i; i = G.nxt[i])
  {
    fa[G.to[i]] = lca;
  }
  return;
}
