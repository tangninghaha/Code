#include <cstdio>
#include <cstring>

/* Constant */
const int N = 2e5 + 5;
const int M = 1e5 + 5;
const int LEN = 100;

const int mod = 999983;
const int base = 233;

/* Graph */
class Graph
{
  public:
    int head[2 * N + 1];
    int nxt[4 * M + N * 2 + 1];
    int to[4 * M + N * 2 + 1];
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

void Dfs(int _x, int c);

int GetFa(int _x);

/* Variable */
Graph G;

int color[2 * N + 1];
int fa[N + 1];
int size[N + 1];

int bh[mod];
bool pd;
int n;
int add_edge[M + 1][3];
bool vis[2 * N + 1];

char tmp1[LEN + 1], tmp2[LEN + 1], rel[LEN + 1];

/* Definition */
void Dfs(int _x, int c)
{
  vis[_x] = true;
  if (color[_x] && c != color[_x])
  {
    pd = true;
    return;
  }
  if (color[_x])
    return;
  color[_x] = c;
  for (int i = G.head[_x]; i; i = G.nxt[i])
  {
    if (c == 2)
      Dfs(G.to[i], 1);
    else
      Dfs(G.to[i], 2);
    if (pd)
      return;
  }
  return;
}
int GetFa(int _x)
{
  if (fa[_x] == _x)
    return _x;
  return fa[_x] = GetFa(fa[_x]);
}
int main()
{
  freopen("in.txt", "r", stdin);
  int m, q;
  scanf("%d%d", &m, &q);
  int len1, len2;
  long long sum;
  for (int i = 1; i <= m; ++i)
  {
    scanf("%s%s%s", tmp1, tmp2, rel);
    len1 = strlen(tmp1);
    len2 = strlen(tmp2);
    sum = 0;
    for (int j = 0; j < len1; ++j)
    {
      sum = sum * base + tmp1[j];
      sum %= mod;
    }
    if (!bh[sum])
      bh[sum] = ++n;
    add_edge[i][0] = bh[sum];
    sum = 0;
    for (int j = 0; j < len2; ++j)
    {
      sum = sum * base % mod + tmp2[j];
      sum %= mod;
    }
    if (!bh[sum])
      bh[sum] = ++n;
    add_edge[i][1] = bh[sum];
    if (rel[0] == 'p')
      add_edge[i][2] = 0;
    else
      add_edge[i][2] = 1;
  }

  for (int i = 1; i <= n; ++i)
    fa[i] = i, size[i] = 1;
  int u, v;
  for (int i = 1; i <= n; ++i)
    G.Add(i, i + n), G.Add(i + n, i);
  for (int i = 1; i <= m; ++i)
  {
    u = add_edge[i][0], v = add_edge[i][1];
    if (add_edge[i][2])
      G.Add(u, v), G.Add(v, u);
    else
      G.Add(u + n, v), G.Add(v, u + n), G.Add(v + n, u), G.Add(u, v + n);
    if (GetFa(u) != GetFa(v))
    {
      if (size[u] < size[v])
      {
        u = GetFa(u);
        v = GetFa(v);
        fa[u] = v;
        size[v] += size[u];
      }
      else
      {
        u = GetFa(u);
        v = GetFa(v);
        fa[v] = u;
        size[u] += size[v];
      }
    }
  }
  for (int i = 1; i <= n; ++i)
  {
    if (!vis[i])
    {
      Dfs(i, 1);
    }
  }
  if (pd)
  {
    printf("Waterloo");
    return 0;
  }
  for (int i = 1; i <= q; ++i)
  {
    scanf("%s%s", tmp1, tmp2);
    len1 = strlen(tmp1), len2 = strlen(tmp2);
    sum = 0;
    for (int j = 0; j < len1; ++j)
    {
      sum = sum * base % mod + tmp1[j];
      sum %= mod;
    }
    u = bh[sum];
    sum = 0;
    for (int j = 0; j < len2; ++j)
    {
      sum = sum * base % mod + tmp2[j];
      sum %= mod;
    }
    v = bh[sum];
    if (u == 0 || v == 0)
    {
      printf("unknown\n");
      continue;
    }
    if (GetFa(u) != GetFa(v))
    {
      printf("unknown\n");
      continue;
    }
    if (color[u] == color[v])
    {
      printf("parallel\n");
    }
    else
    {
      printf("intersect\n");
    }
  }
  return 0;
}
