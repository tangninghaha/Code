/* 树剖版本，没打完 */
#include <cstdio>

/* Constant */
const int N = 5e4;

/* Class */
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
class TreeNode
{
  public:
    int maxn;
    int minn;
    int ans1;
    int ans2;
};
class SegementTree
{
  public:
    TreeNode tr[N << 2 + 1];
    
    void Build(int, int, int);
    TreeNode GetSum(int, int, int, int, int);
};

/* Declaration */
int main();

void Dfs1(int);
void Dfs2(int, int);
int GetLca(int, int);

void Swap(int&, int&);

TreeNode operator+(TreeNode, TreeNode);

int Max(int, int);
int Min(int, int);

/* Variable */
int c[N + 1];
Graph G;

int fa[N + 1];
int dep[N + 1];
int top[N + 1];
int size[N + 1];
int heavy_son[N + 1];
int dfn[N + 1];
int dfn_cnt;
int rk[N + 1];

SegementTree T;

/* Definition */
void SegementTree::Build(int l, int r, int k)
{
  if (l == r)
  {
    tr[k].maxn = c[rk[l]];
    tr[k].minn = c[rk[l]];
    tr[k].ans1 = tr[k].ans2 = 0;
    return;
  }
  int mid = l + r >> 1;
  Build(l, mid, k * 2);
  Build(mid + 1, r, k * 2 + 1);
  tr[k] = tr[k * 2] + tr[k * 2 + 1];
}
TreeNode SegementTree::GetSum(int l, int r, int s, int t, int k)
{
  if (s <= l && r <= t)
  {
    return tr[k];
  }
  int mid = l + r >> 1;
  TreeNode ret = {0, INF, 0, 0};
  if (s <= mid) ret = ret + GetSum(l, mid, s, t, k * 2);
  if (t > mid) ret = ret + GetSum(mid + 1, r, s, t, k * 2 + 1);
  return ret;
}
TreeNode operator+(TreeNode _a, TreeNode _b)
{
  TreeNode ret;
  ret.maxn = Max(_a.maxn, _b.maxn);
  ret.minn = Min(_a.minn, _b.minn);
  ret.ans1 = Max(Max(_a.ans1, _b.ans1), _b.maxn - _a.minn);
  ret.ans2 = Max(Max(_a.ans2, _b.ans2), _a.maxn - _b.minn);
  return ret;
}

void Dfs1(int _x)
{
  dep[_x] = dep[fa[_x]] + 1;
  size[_x] = 1;
  for (int i = G.head[_x]; i; i = G.nxt[i])
  {
    if (G.to[i] == fa[_x])
      continue;
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
  ++dfn_cnt;
  dfn[_x] = dfn_cnt;
  rk[dfn[_x]] = _x;
  top[_x] = _top;
  if (heavy_son[_x]) Dfs2(heavy_son[_x], top);
  for (int i = G.head[_x]; i; i = G.nxt[i])
  {
    if (G.to[i] == heavy_son[_x] || G.to[i] == fa[_x])
      continue;
    Dfs2(G.to[i], G.to[i]);
  }
  return;
}
int GetLca(int _x, int _y)
{
  while (top[_x] != top[_y])
  {
    if (dep[top[_x]] < dep[top[_y]]) Swap(_x, _y);
    _x = fa[top[_x]];
  }
  return dep[_x] < dep[_y] ? _x : _y;
}
void Swap(int& _a, int& _b)
{
  int tmp = _a;
  _a = _b;
  _b = tmp;
  return;
}
int Max(int _a, int _b)
{
  return _a > _b ? _a : _b;
}
int Min(int _a, int _b)
{
  return _a < _b ? _a : _b;
}
