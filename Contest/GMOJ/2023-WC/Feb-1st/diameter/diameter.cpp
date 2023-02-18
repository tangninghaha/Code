#include <cstdio>

/* Constant */
const int N = 5e4;
const int INF = 1 << 30;

/* Class */
class Graph
{
  public:
    int head[N + 1];
    int nxt[N * 2 + 1];
    int to[N * 2 + 1];
    int dis[N * 2 + 1];
    int tot;
    void Add(int _u, int _v, int _w)
    {
      ++tot;
//      printf("%d %d %d\n", _u, _v, _w);
      nxt[tot] = head[_u];
      to[tot] = _v;
      dis[tot] = _w;
      head[_u] = tot;
      return;
    }
};

/* Declaration */
int main();
void Dfs1(int, int);
void Dfs2(int, int, int);
int Dfs3(int, int);
void Dfs4(int, int);

int Max(int, int);

/* Variable */
int maxn[N + 1];
int maxn2[N + 1];
int maxno[N + 1];
bool vis[N + 1];

int add[N + 1];

Graph G;

int ans;

/* Definition */
int main()
{
  freopen("diameter.in", "r", stdin);
  freopen("diameter.out", "w", stdout); 
  int n, m, l;
  scanf("%d%d%d", &n, &m, &l);
  int u, v, w;
  for (int i = 1; i <= m; ++i)
  {
    scanf("%d%d%d", &u, &v, &w);
    G.Add(u + 1, v + 1, w);
    G.Add(v + 1, u + 1, w);
  }
  for (int i = 1; i <= n; ++i)
    if (!vis[i])
      Dfs1(i, 0);
  for (int i = 1; i <= n; ++i)
    vis[i] = false;
  for (int i = 1; i <= n; ++i)
    if (!vis[i])
      Dfs2(i, 0, 0);

  int root = 0;
  for (int i = 1; i <= n; ++i)
    vis[i] = false;
  int ret;
  int cnt = 0;
  for (int i = 1; i <= n; ++i)
    if (!vis[i])
    {
      ret = Dfs3(i, 0);
      ++cnt;
      add[cnt] = ret;
      if (maxn[ret] > maxn[root] || root == 0)
        root = ret;
    }
  for (int i = 1; i <= cnt; ++i)
    if (add[i] != root)
      G.Add(add[i], root, l), G.Add(root, add[i], l);
//  printf("%d\n", cnt);

  for (int i = 1; i <= n; ++i)
    maxn[i] = maxn2[i] = 0, vis[i] = false;
  Dfs4(root, 0);
  printf("%d", ans);
  return 0;
}
void Dfs1(int _x, int fa)
{
  vis[_x] = true;
  for (int i = G.head[_x]; i; i = G.nxt[i])
  {
    if (G.to[i] == fa)
      continue;
    Dfs1(G.to[i], _x);
    if (maxn[G.to[i]] + G.dis[i] >= maxn[_x])
    {
      maxn2[_x] = maxn[_x];
      maxn[_x] = maxn[G.to[i]] + G.dis[i];
    }
    else if (maxn[G.to[i]] + G.dis[i] > maxn2[_x])
      maxn2[_x] = maxn[G.to[i]] + G.dis[i];
  }
  return;
}
void Dfs2(int _x, int fa, int from_dis)
{
  vis[_x] = true;
  if (maxn[_x] + from_dis == maxn[fa])
    maxno[_x] = Max(maxno[fa] + from_dis, maxn2[fa] + from_dis);
  else
    maxno[_x] = Max(maxno[fa] + from_dis, maxn[fa] + from_dis);
  for (int i = G.head[_x]; i; i = G.nxt[i])
  {
    if (G.to[i] == fa)
      continue;
    Dfs2(G.to[i], _x, G.dis[i]);
  }
  maxn[_x] = Max(maxn[_x], maxno[_x]);
  return;
}
int Dfs3(int _x, int fa)
{
  vis[_x] = true;
  int now_max = _x;
  int ret;
  for (int i = G.head[_x]; i; i = G.nxt[i])
  {
    if (G.to[i] == fa)
      continue;
    ret = Dfs3(G.to[i], _x);
    if (maxn[ret] < maxn[now_max])
      now_max = ret;
  }
  return now_max;
}
void Dfs4(int _x, int fa)
{
  vis[_x] = true;
  for (int i = G.head[_x]; i; i = G.nxt[i])
  {
    if (G.to[i] == fa)
      continue;
    Dfs4(G.to[i], _x);
    if (maxn[G.to[i]] + G.dis[i] >= maxn[_x])
    {
      maxn2[_x] = maxn[_x];
      maxn[_x] = maxn[G.to[i]] + G.dis[i];
    }
    else if (maxn[G.to[i]] + G.dis[i] >= maxn2[_x])
      maxn2[_x] = maxn[G.to[i]] + G.dis[i];
  }
  ans = Max(ans, maxn[_x] + maxn2[_x]);
  return;
}

int Max(int _x, int _y)
{
  return _x > _y ? _x : _y;
}
