#include <cstdio>
#include <string>
#define int long long

/* Constant */
const int N = 1e5;
const int M = 2e5;

/* Class */
class dsu_node
{
  public:
    int fa;
};

class edge
{
  public:
    bool type;
    int u;
    int v;
    int w;
};
bool operator<(const edge& _a, const edge& _b)
{
  return _a.w < _b.w;
}

class question
{
  public:
    int bh;
    int num;
};
bool operator<(const question& _a, const question& _b)
{
  return _a.num < _b.num;
}

/* Declaration */
signed main();
void Input();
void Sovle();
void Output();

void Work(int, int, long long, long long, edge*, int, int, int, int);

template <typename T> void Qsort(int, int, T*);
template <typename T> void Swap(T&, T&);

void Merge(int, int);
int GetFa(int);
void Reset(int);

void FileIO(std::string);

/* Variable */
edge typea[M + 1];
edge typeb[M + 1];

int fa[N + 1], size[N + 1];
dsu_node dsu2[N + 1];

int n, a_num, b_num, q;
long long ans[N + 1];

int dsu_rec[N + 1][2], dsu_rec_tot;

edge e1[M + 1];
edge tmp[M + 1];
bool vis[M + 1];
bool tmp_vis[M + 1];

question Q[N + 1];

/* Definition */
void FileIO(std::string file_name)
{
  freopen((file_name + ".in").c_str(), "r", stdin);
  freopen((file_name + ".out").c_str(), "w", stdout);
  return;
}
signed main()
{
  FileIO("graph");
  Input();
  Sovle();
  Output();
  return 0;
}

int GetFa(int _x)
{
  if (fa[_x] == _x)
    return _x;
  return GetFa(fa[_x]);
}
int GetFa2(int _x)
{
  if (dsu2[_x].fa == _x)
    return _x;
  return dsu2[_x].fa = GetFa2(dsu2[_x].fa);
}
void Merge(int _a, int _b)
{
  _a = GetFa(_a);
  _b = GetFa(_b);
  if (_a == _b)
    return; 
  if (size[_a] < size[_b])
  {
    fa[_a] = _b;
    size[_b] += size[_a];
    ++dsu_rec_tot;
    dsu_rec[dsu_rec_tot][0] = _a;
    dsu_rec[dsu_rec_tot][1] = _b;
  }
  else
  {
    fa[_b] = _a;
    size[_a] += size[_b];
    ++dsu_rec_tot;
    dsu_rec[dsu_rec_tot][0] = _b;
    dsu_rec[dsu_rec_tot][1] = _a;
  }
  return;
}
void Reset(int _x)
{
  for (int i = dsu_rec_tot; i > _x; --i)
  {
    fa[dsu_rec[i][0]] = dsu_rec[i][0];
    size[dsu_rec[i][1]] -= size[dsu_rec[i][0]];
  }
  dsu_rec_tot = _x;
  return;
}

template <typename T> void Qsort(int l, int r, T* _a)
{
  T mid = _a[l + r >> 1];
  int i = l, j = r;
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
};

void Work(int l, int r, long long num1, long long num2, edge* e, int len, int c, int chos_tot1, int chos_tot2)
{
  if (l > r)
    return;
  int mid = l + r >> 1;
  int last = dsu_rec_tot;
  for (int i = 1; i <= len; ++i)
  {
    if (e[i].type) e[i].w -= c;
    else e[i].w += c;
    vis[i] = false;
  }
  num1 -= (long long)chos_tot1 * c;
  num2 += (long long)chos_tot2 * c;
  Qsort(1, len, e);
  int cnt = 0;
  long long sum = 0;
//  if (l == 1 && r == q)
//  {
//    for (int i = 1; i <= len; ++i)
//    {
//      printf("%lld %lld %lld\n", e[i].u, e[i].v, e[i].w, e[i].type == 1 ? '+' : '-');
//    }
//    printf("\n");
//  }
  int u, v;
  int chos_tot = chos_tot1 + chos_tot2;
  for (int i = 1; i <= len; ++i)
  {
    if (chos_tot + cnt == n - 1)
      break;
    u = GetFa(e[i].u);
    v = GetFa(e[i].v);
    if (u != v)
    {
      Merge(u, v);
      ++cnt;
      sum += e[i].w;
      vis[i] = true;
    }
  }
  ans[Q[mid].bh] = num1 + num2 + sum;

  Reset(last);
  int e_tot = 0;
  sum = 0;
//  cnt = 0;
  for (int i = 1; i <= len; ++i)
  {
    tmp[i] = e[i];
    tmp_vis[i] = vis[i];
  }
  for (int i = 1; i <= len; ++i)
  {
    if (!tmp_vis[i] && tmp[i].type)
      e[++e_tot] = tmp[i], vis[e_tot] = tmp_vis[i];
    else if (tmp_vis[i] && !tmp[i].type)
      e[++e_tot] = tmp[i], vis[e_tot] = tmp_vis[i];
  }
  int r_st = e_tot;
  for (int i = 1; i <= len; ++i)
  {
    if (!tmp_vis[i] && !tmp[i].type)
      e[++e_tot] = tmp[i], vis[e_tot] = tmp_vis[i];
    else if (tmp_vis[i] && tmp[i].type)
      e[++e_tot] = tmp[i], vis[e_tot] = tmp_vis[i];
  }
  int cnt1 = 0, cnt2 = 0;
//  for (int i = 1; i <= len; ++i)
//  {
//    if (vis[i] && e[i].type)
//    {
//      ++cnt1;
//      atd[cnt1] = e[i];
//    }
//  }
//  for (int i = 1; i <= len; ++i)
//  {
//    if (vis[i] && !e[i].type)
//    {
//      ++cnt2;
//      atd[cnt1 + cnt2] = e[i];
//    }
//  }
  for (int i = r_st + 1; i <= len; ++i)
  {
    if (!e[i].type)
      continue;
    u = GetFa(e[i].u);
    v = GetFa(e[i].v);
    Merge(u, v);
    sum += e[i].w;
    ++cnt1;
  }
  Work(l, mid - 1, num1 + sum, num2, e, r_st, Q[mid].num - Q[(l + mid - 1) >> 1].num, chos_tot1 + cnt1, chos_tot2);

  Reset(last);
  sum = 0;
//  cnt = 0;

  for (int i = 1; i <= r_st; ++i)
  {
    if (e[i].type)
      continue;
    u = GetFa(e[i].u);
    v = GetFa(e[i].v);
    Merge(u, v);
    sum += e[i].w;
    ++cnt2;
  }
  Work(mid + 1, r, num1, num2 + sum, e + r_st, len - r_st, Q[mid].num - Q[(mid + 1 + r) >> 1].num, chos_tot1, chos_tot2 + cnt2);
  for (int i = 1; i <= len; ++i)
  {
    if (e[i].type) e[i].w += c;
    else e[i].w -= c;
    vis[i] = false;
  }
//  Reset(last);
  return;
}
void Input()
{
  scanf("%lld%lld%lld%lld", &n, &a_num, &b_num, &q);
  int u, v, w;
  for (int i = 1; i <= a_num; ++i)
  {
    scanf("%lld%lld%lld", &u, &v, &w);
    typea[i].u = u;
    typea[i].v = v;
    typea[i].w = w;
    typea[i].type = true;
  }
  for (int i = 1; i <= b_num; ++i)
  {
    scanf("%lld%lld%lld", &u, &v, &w);
    typeb[i].u = u;
    typeb[i].v = v;
    typeb[i].w = w;
  }
  for (int i = 1; i <= q; ++i)
  {
    scanf("%lld", &Q[i].num);
    Q[i].bh = i;
  }
  return;
}
void Sovle()
{
  Qsort(1, q, Q);
  Qsort(1, a_num, typea);
  Qsort(1, b_num, typeb);

  int cnt = 0;
  int u, v;
  for (int i = 1; i <= n; ++i)
    dsu2[i].fa = i;
  for (int i = 1; i <= a_num; ++i)
  {
    if (cnt == n - 1)
      break;
    if (GetFa2(typea[i].u) != GetFa2(typea[i].v))
    {
      u = GetFa2(typea[i].u);
      v = GetFa2(typea[i].v);
      dsu2[u].fa = v;
      ++cnt;
      vis[i] = true;
    }
  }
  cnt = 0;
  for (int i = 1; i <= a_num; ++i)
    if (vis[i])
      typea[++cnt] = typea[i];

  cnt = 0;
  for (int i = 1; i <= n; ++i)
    dsu2[i].fa = i;
  for (int i = 1; i <= b_num; ++i)
    vis[i] = false;
  for (int i = 1; i <= b_num; ++i)
  {
    if (cnt == n - 1)
      break;
    if (GetFa2(typeb[i].u) != GetFa2(typeb[i].v))
    {
      u = GetFa2(typeb[i].u);
      v = GetFa2(typeb[i].v);
      dsu2[u].fa = v;
      ++cnt;
      vis[i] = true;
    }
  }
  cnt = 0;
  for (int i = 1; i <= b_num; ++i)
    if (vis[i])
      typeb[++cnt] = typeb[i];
  a_num = n - 1;
  b_num = n - 1;
  for (int i = 1; i <= a_num; ++i)
    e1[i] = typea[i];
  for (int i = 1; i <= b_num; ++i)
    e1[i + a_num] = typeb[i];
  for (int i = 1; i <= n; ++i)
    fa[i] = i, size[i] = 1;
  Work(1, q, 0, 0, e1, a_num + b_num, 0 - Q[(1 + q) >> 1].num, 0, 0);
  return;
}
void Output()
{
  for (int i = 1; i <= q; ++i)
  {
    printf("%lld\n", ans[i]);
  }
}
