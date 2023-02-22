#include <cstdio>
#include <algorithm>

/* Constant */
const int N = 1000;
const int M = 5e4;

/* Class */
class Graph
{
  public:
    int head[N + 1];
    int nxt[M * 2 + 1];
    int to[M * 2 + 1];
    int dis[M * 2 + 1];
    int tot;
    void Add(int _u, int _v, int _w)
    {
      ++tot;
      nxt[tot] = head[_u];
      to[tot] = _v;
      dis[tot] = _w;
      head[_u] = tot;
      return;
    }
};
class Edge
{
  public:
    int a;
    int b;
    int c;
};
bool operator<(Edge _a, Edge _b)
{
  return _a.c < _b.c;
}

/* Declaration */
int main();
int Dfs(int, int, bool);

/* Variable */
Edge e[M + 1];
Graph G;
unsigned short f[N + 1][M + 1];

/* Definition */
int main()
{
  freopen("bridge.in", "r", stdin);
  freopen("bridge.out", "w", stdout); 
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i)
  {
    scanf("%d%d%d", &e[i].a, &e[i].b, &e[i].c);
  }
  std::sort(e + 1, e + m + 1);
  int last = -1, num = 0;
  for (int i = 1; i <= m; ++i)
  {
    if (e[i].c != last)
      last = e[i].c, ++num;
    e[i].c = num;
  }
  for (int i = 1; i <= m; ++i)
  {
    G.Add(e[i].a, e[i].b, e[i].c);
    G.Add(e[i].b, e[i].a, e[i].c);
  }
  int ans = 0;
  for (int i = 1; i <= n; ++i)
    ans = std::max(Dfs(i, 0, 1), ans);
  printf("%d", ans);
  return 0;
}
int Dfs(int now, int mx, bool flag)
{
  if (f[now][mx])
    return f[now][mx];
  int ret = 0, ans = 0;
  for (int i = G.head[now]; i; i = G.nxt[i])
  {
    if (G.dis[i] > mx || flag)
    {
      ret = Dfs(G.to[i], G.dis[i], false) + 1;
      ans = std::max(ans, ret);
    }
  }
  f[now][mx] = ans;
  return ans;
}
