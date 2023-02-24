#include <cstdio>

/* Constant */
const int N = 1e5;
const int MAXPOINTNUM = 2e5 + 5;
const int INF = 1 << 29;

/* Class */
class Graph
{
  public:
    int head[MAXPOINTNUM * 2 + 1];
    int nxt[MAXPOINTNUM * 4 +1];
    int to[MAXPOINTNUM * 4 + 1];
    int dis[MAXPOINTNUM * 4 + 1];
    int cost[MAXPOINTNUM * 4 + 1];
    int tot;
    Graph()
    {
      tot = 1;
    }
    void Add(int _u, int _v, int _w, int _c)
    {
//      printf("%d %d %d %d\n", _u, _v, _w, _c);
      ++tot;
      nxt[tot] = head[_u];
      to[tot] = _v;
      dis[tot] = _w;
      cost[tot] = _c;
      head[_u] = tot;
      return;
    }
};
class Graph2
{
  public:
    int head[MAXPOINTNUM * 2 + 1];
    int nxt[MAXPOINTNUM * 4 +1];
    int to[MAXPOINTNUM * 4 + 1];
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
bool Bfs(int, int);
int Dfs(int, int);
int GetMaxFlow(int, int);
int Min(int, int);
void Output(int);

/* Variable */
int rd[MAXPOINTNUM * 2 + 1];
Graph G;
Graph2 TP;
int current_arc[MAXPOINTNUM + 1];
int queue[MAXPOINTNUM * 2 + 1];
bool vis[MAXPOINTNUM + 1];
bool pd[MAXPOINTNUM + 1];
int dis[MAXPOINTNUM + 1];
int point_num;
int chos[N + 1];
int was_chos[N + 1]; 
int f[N + 1];
int s[N + 1];

/* Definition */
int main()
{
  freopen("cereal.in", "r", stdin);
  freopen("cereal.out", "w", stdout);
  int n, m;
  scanf("%d%d", &n, &m);
  point_num = n + m + 2;
  for (int i = 1; i <= n; ++i)
    G.Add(1, i + 1, 1, 0), G.Add(i + 1, 1, 0, 0);
  for (int i = 1; i <= n; ++i)
  {
    scanf("%d%d", &f[i], &s[i]);
    G.Add(i + 1, f[i] + n + 1, 1, 0);
    G.Add(f[i] + n + 1, i + 1, 0, 0);
    G.Add(i + 1, s[i] + n + 1, 1, 1);
    G.Add(s[i] + n + 1, i + 1, 0, 1);
  }
  for (int i = 1; i <= m; ++i)
  {
    G.Add(i + n + 1, n + m + 2, 1, 0);
    G.Add(n + m + 2, i + n + 1, 0, 0);
  }
  printf("%d\n", n - GetMaxFlow(1, point_num));
  for (int i = 2; i <= n + 1; ++i)
  {
    for (int j = G.head[i]; j; j = G.nxt[j])
    {
      if (G.to[j] < i)
        continue;
      if (!G.dis[j])
      {
        chos[i - 1] = G.to[j] - n - 1;
        was_chos[G.to[j] - n - 1] = i - 1;
      }
    }
  }
  for (int i = 1; i <= n; ++i)
  {
    if (chos[i] == s[i])
    {
      ++rd[i];
      TP.Add(was_chos[f[i]], i);
    }
  }
  for (int i = 1; i <= n; ++i)
    vis[i] = false;
  for (int i = 1; i <= n; ++i)
  {
    if (!chos[i])
      continue;
    if (!rd[i])
      Output(i);
  }
  for (int i = 1; i <= n; ++i)
  {
    if (!chos[i])
      printf("%d\n", i);
  }
  return 0;
}
int GetMaxFlow(int st, int ed) // Network Max Flow
{
  int ret = 0;
  while (Bfs(st, ed))
  {
    for (int i = 1; i <= point_num; ++i)
      current_arc[i] = G.head[i];
    ret += Dfs(1, INF);
  }
  return ret;
}
bool Bfs(int _st, int _ed) // Network Flow Bfs
{
  int now;
  int head = 0, tail = 1;
  for (int i = 1; i <= point_num; ++i)
  {
    dis[i] = INF;
  }
  queue[1] = _st;
  dis[_st] = 0;
  vis[_st] = true;
  while (head <= tail)
  {
    ++head;
    now = queue[head];
    vis[now] = false;
    for (int i = G.head[now]; i; i = G.nxt[i])
    {
      if (G.dis[i] <= 0)
        continue;
      if (dis[now] + G.cost[i] < dis[G.to[i]])
      {
        dis[G.to[i]] = dis[now] + G.cost[i];
        if (!vis[G.to[i]])
          queue[++tail] = G.to[i], vis[G.to[i]] = true;
      }
    }
  }
  return dis[_ed] != INF;
}
int Dfs(int now, int flow) // Network Flow Dfs
{
  if (now == point_num)
    return flow;
  if (!flow)
    return 0;
  int f;
  int ret = 0;
  pd[now] = true;
  for (int i = current_arc[now]; i; i = G.nxt[i])
  {
    if (G.dis[i] > 0 && dis[G.to[i]] == dis[now] + G.cost[i] && !pd[G.to[i]])
    {
      f = Dfs(G.to[i], Min(flow, G.dis[i]));
      G.dis[i] -= f;
      G.dis[i ^ 1] += f;
      current_arc[now] = i;
      flow -= f;
      ret += f;
      if (!flow)
      {
        pd[now] = false;
        return ret;
      }
    }
  }
  pd[now] = false;
  return ret;
}
int Min(int _x, int _y)
{
  return _x < _y ? _x : _y;
}
void Output(int x)
{
  if (vis[x])
    return;
  printf("%d\n", x);
  vis[x] = true;
  for (int i = TP.head[x]; i; i = TP.nxt[i])
  {
    --rd[TP.to[i]];
    if (!rd[TP.to[i]])
    {
      Output(TP.to[i]);
    }
  }
  return;
} 
