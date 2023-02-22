#include <cstdio>

/* Constant */
const int N = 2e5 + 5;

/* Class */
class pr
{
  public:
    int y_cut_x;
    int x;
};
bool operator<(pr _a, pr _b)
{
  if (_a.y_cut_x == _b.y_cut_x)
    return _a.x < _b.x;
  return _a.y_cut_x < _b.y_cut_x;
}
class color
{
  public:
    int rk;
    int c;
};
bool operator<(color _a, color _b)
{
  if (_a.c == _b.c)
  {
    return _a.rk < _b.rk;
  }
  return _a.c < _b.c; 
}

/* Declaration */
int main();
template<typename T> void Qsort(int, int, T*);
template<typename T> void Swap(T&, T&);

/* Variable */
pr a[N + 1];
color c[N + 1];
int st[N + 1];
int ed[N + 1];
int cnt;

/* Definition */
template<typename T> void Swap(T& _a, T& _b)
{
  T tmp = _a;
  _a = _b;
  _b = tmp;
  return;
}
template<typename T> void Qsort(int l, int r, T* _a)
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
  if (i < r)
    Qsort(i, r, _a);
  if (l < j)
    Qsort(l, j, _a);
  return;
}
int main()
{
  freopen("jewel.in", "r", stdin);
  freopen("jewel.out", "w", stdout);
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
  {
    scanf("%d", &c[i].c);
    c[i].rk = i;
  }
  Qsort(1, n, c);
  int last = -1e9 - 1;
  int num = 0;
  for (int i = 1; i <= n; ++i)
  {
    if (c[i].c != last)
    {
      ++num;
      last = c[i].c;
    }
    c[i].c = num;
  }
  for (int i = 1; i <= n; ++i)
  {
    if (c[i].c == c[i - 1].c)
    {
      ++cnt;
      a[cnt].x = c[i - 1].rk;
      a[cnt].y_cut_x = c[i].rk - c[i - 1].rk;
    }
  }
  Qsort(1, cnt, a);
  last = 0;
  for (int i = 1; i <= cnt; ++i)
  {
    if (a[i].y_cut_x != last)
    {
      ed[last] = i - 1;
      last = a[i].y_cut_x;
      st[a[i].y_cut_x] = i;
    }
  }
  ed[last] = cnt;
  int l, r;
  int lbound, rbound;
  int mid;
  bool pd;
  bool pdd;
  for (int i = 1; i <= m; ++i)
  {
    scanf("%d%d", &l, &r);
    pdd = false;
    for (int j = 1; j <= last; ++j)
    {
      lbound = st[j];
      rbound = ed[j];
      pd = false;
      while (lbound <= rbound)
      {
        mid = lbound + rbound >> 1;
        if (a[mid].x >= l)
        {
          if (a[mid].x + a[mid].y_cut_x <= r)
          {
            pd = true;
            break;
          }
          rbound = mid - 1;
        }
        else
        {
          lbound = mid + 1;
        }
      }
      if (pd)
      {
        printf("%d\n", j);
        pdd = true;
        break;
      }
    }
    if (!pdd)
    {
      printf("-1\n");
    }
  }
}
