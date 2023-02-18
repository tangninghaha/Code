#include <cstdio>

/* Constant */
const int N = 5e4;
const int K = 16;
const int INF = 1 << 29;

/* Class */
class Node
{
  public:
    int minn;
    int maxn;
    int ans;
};
class Graph
{
  public:
    int head[N + 1];
    int nxt[2 * N + 1];
    int to[2 * N + 1];
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

void Init(int);
int GetAns(int, int);
int GetLca(int, int);

Node Merge1(Node, Node);
Node Merge2(Node, Node);

void Swap(int&, int&);

int Min(int, int);
int Max(int, int);

/* Variable */
int c[N + 1];
Node bz1[N + 1][K];
Node bz2[N + 1][K];
int fa[N + 1][K];
int dep[N + 1];

int log_2[N + 1];

Node z[N + 1];

Graph G;

/* Definition */
int main()
{
  freopen("road.in", "r", stdin);
  freopen("road.out", "w", stdout);
  for (int i = 2; i <= N; ++i)
  {
    log_2[i] = log_2[i >> 1] + 1;
  }
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
  {
    scanf("%d", &c[i]);
  }
  int x, y;
  for (int i = 1; i < n; ++i)
  {
    scanf("%d%d", &x, &y);
    G.Add(x, y);
    G.Add(y, x);
  }
  Init(1);
  int q;
  scanf("%d", &q);
  for (int i = 1;  i <= q; ++i)
  {
    scanf("%d%d", &x, &y);
    printf("%d\n", GetAns(x, y));
  }
  return 0;
}
void Init(int _x)
{
  dep[_x] = dep[fa[_x][0]] + 1;
  bz1[_x][0] = bz2[_x][0] = {c[_x], c[_x], 0};
  for (int i = 1; i < K; ++i)
    bz2[_x][i].minn = bz1[_x][i].minn = INF;
  for (int i = 1; i <= log_2[dep[_x]]; ++i)
  {
    fa[_x][i] = fa[fa[_x][i - 1]][i - 1];
  }
  for (int i = 1; i <= log_2[dep[_x]]; ++i)
  {
    bz1[_x][i] = Merge1(bz1[fa[_x][i - 1]][i - 1], bz1[_x][i - 1]);
  }
  for (int i = 1; i <= log_2[dep[_x]]; ++i)
  {
    bz2[_x][i] = Merge2(bz2[fa[_x][i - 1]][i - 1], bz2[_x][i - 1]);
  }
  for (int i = G.head[_x]; i; i = G.nxt[i])
  {
    if (G.to[i] == fa[_x][0])
      continue;
    fa[G.to[i]][0] = _x;
    Init(G.to[i]);
  }
  return;
}
int GetAns(int st, int ed)
{
  int lca = GetLca(st, ed);
  int now = st;
  int cdep;
  Node ans1 = bz1[st][0];
  while (now != lca)
  {
    cdep = dep[now] - dep[lca];
    ans1 = Merge1(bz1[now][log_2[cdep]], ans1);
    now = fa[now][log_2[cdep]];
  }
  ans1 = Merge1(bz1[lca][0], ans1);
  now = ed;
  int top = 0;
  while (now != lca)
  {
    cdep = dep[now] - dep[lca];
    ++top;
    z[top] = bz2[now][log_2[cdep]];
    now = fa[now][log_2[cdep]];
  }
  while (top)
  {
    ans1 = Merge2(ans1, z[top]);
    --top;
  }
  return ans1.ans;
}
int GetLca(int u, int v)
{
  int lca;
  while (dep[u] != dep[v])
  {
    if (dep[u] < dep[v])
    {
      v = fa[v][log_2[dep[v] - dep[u]]];
    }
    else
    {
      u = fa[u][log_2[dep[u] - dep[v]]];
    }
  }
  for (int i = log_2[dep[u]]; i >= 0; --i)
  {
    if (u == v)
      break;
    if (fa[u][i] != fa[v][i])
    {
      u = fa[u][i];
      v = fa[v][i];
    }
  }
  if (u == v)
    lca = u;
  else
    lca = fa[u][0];
  return lca;
}
Node Merge1(Node tmp, Node now)
{
  Node ret;
  ret.minn = Min(tmp.minn, now.minn);
  ret.maxn = Max(tmp.maxn, now.maxn);
  ret.ans = Max(Max(tmp.ans, now.ans), tmp.maxn - now.minn);
  return ret;
}
Node Merge2(Node tmp, Node now)
{
  Node ret;
  ret.minn = Min(tmp.minn, now.minn);
  ret.maxn = Max(tmp.maxn, now.maxn);
  ret.ans = Max(Max(tmp.ans, now.ans), now.maxn - tmp.minn);
  return ret;
}
void Swap(int& _a, int& _b)
{
  int tmp = _a;
  _a = _b;
  _b = tmp;
  return;
}
int Min(int _a, int _b)
{
  return _a < _b ? _a : _b;
}
int Max(int _a, int _b)
{
  return _a > _b ? _a : _b;
}
