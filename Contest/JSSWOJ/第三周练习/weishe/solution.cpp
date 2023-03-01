#include <cstdio>
#include <cstring>

/* Constant */
const int N = 200;

/* Class */
class Graph
{
  public:
    int head[N + 1];
    int to[N * 2 + 1];
    int nxt[N * 2 + 1];
    bool vis[N * 2 + 1];
    int tot;
    void Add(int _u, int _v)
    {
      ++tot;
      to[tot] = _v;
      nxt[tot] = head[_u];
      head[_u] = tot;
      vis[tot] = true;
      return;
    }
};

/* Declaration */
int main();
int GetD(int, int, long long&);
int Max(int, int);

/* Variable */
Graph G;
int f[2][N + 1];

/* Definition */
int main()
{
  int n;
  scanf("%d", &n);
  int u, v;
  for (int i = 1; i < n; ++i)
    scanf("%d%d", &u, &v), G.Add(u, v), G.Add(v, u);
  long long ans = 0, sum = 0;
  long long sum1, sum2;
  for (int i = 1; i < n; ++i)
  {
    G.vis[i * 2 - 1] = G.vis[i * 2] = false;
    memset(f, 0, sizeof(0));
    sum1 = 0;
    sum2 = 0;
    GetD(G.to[i * 2 - 1], 0, sum1);
    GetD(G.to[i * 2], 0, sum2);
    --sum1;
    --sum2;
    sum = sum1 * sum2;
    if (sum > ans)
      ans = sum;
    G.vis[i * 2 - 1] = G.vis[i * 2] = true;
  }
  printf("%lld", ans);
  return 0;
}
int GetD(int _x, int fa, long long& d)
{
  int ret;
  f[0][_x] = 0;
  for (int i = G.head[_x]; i; i = G.nxt[i])
  {
    if (!G.vis[i] || G.to[i] == fa)
      continue;
    ret = GetD(G.to[i], _x, d);
    if (ret >= f[0][_x])
      f[1][_x] = f[0][_x], f[0][_x] = ret;
    else if (ret > f[1][_x])
      f[1][_x] = ret;
  }
  d = Max(d, f[0][_x] + f[1][_x] + 1);
  return f[0][_x] + 1;
}
int Max(int _a, int _b)
{
  return _a > _b ? _a : _b; 
}
