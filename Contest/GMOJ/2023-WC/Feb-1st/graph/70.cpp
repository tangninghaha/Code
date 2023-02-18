/* Expected score: 70 */

#include <cstdio>
#define int long long

/* Constant */
const int N = 1e5;
const int M = 2e5;
const int INF = 2e16 + 7;

/* Class */
class bian
{
  public:
    int from;
    int to;
    int dis;
    int type;
};
bool operator<(bian _a, bian _b)
{
  return _a.dis < _b.dis;
}

class ques
{
  public:
    int num;
    int bh;
};
bool operator<(ques _a, ques _b)
{
  return _a.num < _b.num;
}

/* Declaration */
int GetFa(int);
signed main();

template <typename T> void Qsort(int, int, T*);
template <typename T> void Swap(T&, T&);

/* Variable */
bian typeA[M + 1];
bian typeB[M + 1];

bian tmp[M + 1];

bool vis[M + 1];

int fa[N + 1];

int a_num, b_num;
int n, q;

long long ans_A;
long long ans_B;

ques Q[N + 1];

long long ans[N + 1];

/* Definition */
signed main()
{
  freopen("graph.in", "r", stdin);
  freopen("graph.out", "w", stdout);
  scanf("%lld%lld%lld%lld", &n, &a_num, &b_num, &q);
  for (int i = 1; i <= a_num; ++i)
  {
    scanf("%lld%lld%lld", &typeA[i].from, &typeA[i].to, &typeA[i].dis);
  }
  for (int i = 1; i <= b_num; ++i)
    scanf("%lld%lld%lld", &typeB[i].from, &typeB[i].to, &typeB[i].dis);

  int x;
  bool pdd = false;
  bool no_pdd = false;
  for (int i = 1; i <= q; ++i)
  {
    scanf("%lld", &x);
    if (x > 4e8)
      no_pdd = true;
    Q[i].num = x;
    Q[i].bh = i;
  }
  Qsort(1, q, Q);
  for (int i = 1; i <= a_num; ++i)
    typeA[i].dis += Q[1].num;
  for (int i = 1; i <= b_num; ++i)
    typeB[i].dis -= Q[1].num;

  Qsort(1, a_num, typeA);
  Qsort(1, b_num, typeB);

  // Kuskal
  int u, v;
  int cnt = 0;
  for (int i = 1; i <= n; ++i)
    fa[i] = i;
  for (int i = 1; i <= a_num; ++i)
  {
    if (cnt == n - 1)
      break;
    if (GetFa(typeA[i].from) != GetFa(typeA[i].to))
    {
      ++cnt;
      ans_A += typeA[i].dis;
      u = GetFa(typeA[i].from);
      v = GetFa(typeA[i].to);
      fa[u] = v;
      vis[i] = true;
    }
  }
  cnt = 0;
  for (int i = 1; i <= a_num; ++i)
    if (vis[i])
      typeA[++cnt] = typeA[i];
  a_num = cnt;

  cnt = 0;
  for (int i = 1; i <= n; ++i)
    fa[i] = i;
  for (int i = 1; i <= b_num; ++i)
    vis[i] = false;
  for (int i = 1; i <= b_num; ++i)
  {
    if (cnt == n - 1)
      break;
    if (GetFa(typeB[i].from) != GetFa(typeB[i].to))
    {
      ++cnt;
      ++ans_B;
      u = GetFa(typeB[i].from);
      v = GetFa(typeB[i].to);
      fa[u] = v;
      vis[i] = true;
    }
  }
  cnt = 0;
  for (int i = 1; i <= b_num; ++i)
    if (vis[i])
      typeB[++cnt] = typeB[i];
  b_num = cnt;
  int tmp_tot = a_num + b_num;
  int a_zz = 1, b_zz = 1;
  typeA[n].dis = INF;
  typeB[n].dis = INF;
  for (int i = 1; i <= tmp_tot; ++i)
  {
    if (typeA[a_zz].dis < typeB[b_zz].dis)
      tmp[i] = typeA[a_zz++], tmp[i].type = 0;
    else
      tmp[i] = typeB[b_zz++], tmp[i].type = 1;
    if (a_zz > a_num && b_zz == 1)
      pdd = true;
  }
  int c;
  Q[0].num = Q[1].num;
  for (int i = 1; i <= q; ++i)
  {
    c = Q[i].num - Q[i - 1].num;
    ans_A += (long long)c * a_num;
    if (pdd && !no_pdd)
    {
      ans[Q[i].bh] = ans_A;
      continue;
    }

    for (int j = 1; j <= tmp_tot; ++j)
    {
      if (tmp[j].type)
        tmp[j].dis -= c;
      else
        tmp[j].dis += c;
    }
    for (int j = 1; j <= n; ++j)
      fa[j] = j;
    cnt = 0;
    for (int j = 1; j <= tmp_tot; ++j)
    {
      if (tmp[j].type)
      {
        for (int k = j - 1; k >= 1; --k)
        {
          if (!tmp[k].type && tmp[k].dis > tmp[k + 1].dis)
          {
            Swap(tmp[k + 1], tmp[k]);
          }
          else
            break;
        }
      }
    }

    for (int j = 1; j <= tmp_tot; ++j)
    {
      if (cnt == n - 1)
        break;
      if (GetFa(tmp[j].from) != GetFa(tmp[j].to))
      {
        ++cnt;
        ans[Q[i].bh] += tmp[j].dis;
        u = GetFa(tmp[j].from);
        v = GetFa(tmp[j].to);
        fa[u] = v;
      }
    }
  }
  for (int i = 1; i <= q; ++i)
  {
    printf("%lld\n", ans[i]);
  }
  return 0;
}
int GetFa(int _x)
{
  if (fa[_x] == _x)
    return _x;
  return fa[_x] = GetFa(fa[_x]);
}
template <typename T> void Qsort(int l, int r, T* _a)
{
  int i = l, j = r;
  T mid = _a[l + r >> 1];
  while (i <= j)
  {
    while (_a[i] < mid)
      ++i;
    while (mid < _a[j])
      --j;
    if (i <= j)
    {
      Swap(_a[i], _a[j]);
      ++i;
      --j;
    }
  }
  if (i < r) Qsort(i, r, _a);
  if (l < j) Qsort(l, j, _a);
  return;
}
template <typename T> void Swap(T& _a, T& _b)
{
  T temp = _a;
  _a = _b;
  _b = temp;
  return;
}
