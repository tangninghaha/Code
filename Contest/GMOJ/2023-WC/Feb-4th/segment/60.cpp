#include <cstdio>

/* Constant */
const int N = 5e5;

/* Class */
class SegmentTree
{
  public:
    int tr[(N << 2) + 1];
    int lazy[(N << 2) + 1];

    void DownLazy(int _x)
    {
      lazy[_x * 2] = lazy[_x];
      lazy[_x * 2 + 1] = lazy[_x];
      tr[_x * 2] = lazy[_x];
      tr[_x * 2 + 1] = lazy[_x];
      lazy[_x] = 0;
      return;
    }
    void Update(int l, int r, int s, int t, int x, int k)
    {
      if (s <= l && r <= t)
      {
        tr[k] = x;
        lazy[k] = x;
        return;
      }
      if (lazy[k])
        DownLazy(k);
      int mid = l + r >> 1;
      if (s <= mid)
        Update(l, mid, s, t, x, k * 2);
      if (t > mid)
        Update(mid + 1, r, s, t, x, k * 2 + 1);
      return;
    }
    void GetAns(int l, int r, int k, int* ans)
    {
      if (l == r)
        return void(ans[l] = tr[k]);
      int mid = l + r >> 1;
      GetAns(l, mid, k * 2, ans);
      GetAns(mid + 1, r, k * 2 + 1, ans);
      return;
    }
};
class Graph
{
  public:
    int head[N + 1];
    int to[N + 1];
    int nxt[N + 1];
    int tot;
    void Add(int _u, int _v)
    {
      ++tot;
      to[tot] = _v;
      nxt[tot] = head[_u];
      head[_u] = tot;
      return;
    }
};

/* Declaration */
int main();
void Dfs1(int);
void Dfs2(int, int);
void UpdateColor(int, int, int);

/* Variable */
Graph G;
SegmentTree T;

// Tree Link Divide
int fa[N + 1];
int top[N + 1];
int dep[N + 1];
int heavy_son[N + 1];
int size[N + 1];
int dfn[N + 1];
int dfn_cnt;
int rk[N + 1];

int ans[N + 1];
int n, m;

/* Definition */
void Dfs1(int _x)
{
  dep[_x] = dep[fa[_x]] + 1;
  size[_x] = 1;
  for (int i = G.head[_x]; i; i = G.nxt[i])
  {
    fa[G.to[i]] = _x;
    Dfs1(G.to[i]);
    size[_x] += size[G.to[i]];
    if (size[G.to[i]] > size[heavy_son[_x]])
      heavy_son[_x] = G.to[i];
  }
  return;
}
void Dfs2(int _x, int _top)
{
  dfn[_x] = ++dfn_cnt;
  rk[_x] = dfn[_x];
  top[_x] = _top;
  if (heavy_son[_x])
    Dfs2(heavy_son[_x], _top);
  for (int i = G.head[_x]; i; i = G.nxt[i])
  {
    if (G.to[i] == heavy_son[_x])
      continue;
    Dfs2(G.to[i], G.to[i]);
  }
  return;
}
void UpdateColor(int _x, int _y, int c)
{
  int u = top[_x], v = top[_y];
  while (u != v)
  {
    if (dep[u] < dep[v])
    {
      T.Update(1, n, dfn[v], dfn[_y], c, 1);
      _y = fa[v];
      v = top[_y];
    }
    else
    {
      T.Update(1, n, dfn[u], dfn[_x], c, 1);
      _x = fa[u];
      u = top[_x];
    }
  }
  if (_x != _y)
  {
    if (dep[_x] < dep[_y])
      T.Update(1, n, dfn[_x] + 1, dfn[_y], c, 1);
    else
      T.Update(1, n, dfn[_y] + 1, dfn[_x], c, 1);
  }
  return;
}
int main()
{
  freopen("in.txt", "r", stdin);
  scanf("%d%d", &n, &m);
  int x;
  for (int i = 2; i <= n; ++i)
  {
    scanf("%d", &x);
    G.Add(x, i);
  }
  Dfs1(1);
  Dfs2(1, 1);
  int u, v, c;
  for (int i = 1; i <= m; ++i)
  {
    scanf("%d%d%d", &u, &v, &c);
    UpdateColor(u, v, c);
  }
  T.GetAns(1, n, 1, ans);
  for (int i = 2; i <= n; ++i)
  {
    printf("%d\n", ans[rk[i]]);
  }
  return 0;
}
