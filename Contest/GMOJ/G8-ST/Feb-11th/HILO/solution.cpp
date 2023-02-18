#include <cstdio>

/* Constant */
const int N = 2e5;
const int INF = 1 << 29;

/* Class */
class Change
{
  public:
    int num;
    int time;
    int type; // 0: skip1 -> HI, 1: HI -> LO, 2: LO -> skip2
};
bool operator<(Change _a, Change _b)
{
  if (_a.time == _b.time)
  {
    if (_a.num == _b.num)
      return _a.type < _b.type;
    else
      return _a.num < _b.num;
  }
  return _a.time < _b.time;
}
class SegmentTree
{
  public:
    int tr_mx[N << 2];
    int tr_mi[N << 2];

    int Min(int _a, int _b)
    {
      return _a < _b ? _a : _b;
    }
    int Max(int _a, int _b)
    {
      return _a > _b ? _a : _b;
    }
    void Build(int l, int r, int k)
    {
      if (l == r)
      {
        tr_mx[k] = 0;
        tr_mi[k] = INF;
        return;
      }
      int mid = l + r >> 1;
      Build(l, mid, k * 2);
      Build(mid + 1, r, k * 2 + 1);
      tr_mx[k] = Max(tr_mx[k * 2], tr_mx[k * 2 + 1]);
      tr_mi[k] = Min(tr_mi[k * 2], tr_mi[k * 2 + 1]);
      return;
    }
    void Update(int l, int r, int x, int k)
    {
      if (l == r)
      {
        tr_mx[k] = tr_mi[k] = x;
        return;
      }
      int mid = l + r >> 1;
      if (x <= mid)
        Update(l, mid, x, k * 2);
      else
        Update(mid + 1, r, x, k * 2 + 1);
      tr_mx[k] = Max(tr_mx[k * 2], tr_mx[k * 2 + 1]);
      tr_mi[k] = Min(tr_mi[k * 2], tr_mi[k * 2 + 1]);
      return;
    }
    void Update2(int l, int r, int x, int k)
    {
      if (l == r)
      {
        tr_mx[k] = 0;
        tr_mi[k] = INF;
        return;
      }
      int mid = l + r >> 1;
      if (x <= mid)
        Update2(l, mid, x, k * 2);
      else
        Update2(mid + 1, r, x, k * 2 + 1);
      tr_mx[k] = Max(tr_mx[k * 2], tr_mx[k * 2 + 1]);
      tr_mi[k] = Min(tr_mi[k * 2], tr_mi[k * 2 + 1]);
      return;
    }
    int GetMax(int l, int r, int s, int t, int k)
    {
      if (s <= l && r <= t)
        return tr_mx[k];
      int mid = l + r >> 1;
      int ret = 0;
      if (s <= mid)
        ret = Max(ret, GetMax(l, mid, s, t, k * 2));
      if (t > mid)
        ret = Max(ret, GetMax(mid + 1, r, s, t, k * 2 + 1));
      return ret;
    }
    int GetMin(int l, int r, int s, int t, int k)
    {
      if (s <= l && r <= t)
        return tr_mi[k];
      int mid = l + r >> 1;
      int ret = INF;
      if (s <= mid)
        ret = Min(ret, GetMin(l, mid, s, t, k * 2));
      if (t > mid)
        ret = Min(ret, GetMin(mid + 1, r, s, t, k * 2 + 1));
      return ret;
    }
};

/* Declaration */
int main();
void Qsort(int, int);
template <typename T> void Swap(T&, T&);

/* Variable */
int ans[N + 1];
int a[N + 1];
Change c[N * 3 + 2];
SegmentTree T;
int status[N + 1];
bool vis[N + 1];
bool pd[N + 1];

/* Definition */
int main()
{
  freopen("hilo.in", "r", stdin);
  freopen("hilo.out", "w", stdout);
  int n;
  scanf("%d", &n);
  T.Build(1, n, 1);
  int change_tot = 0;
  for (int i = 1; i <= n; ++i)
  {
    scanf("%d", &a[i]);
    ++change_tot;
    c[change_tot].num = i;
    c[change_tot].time = a[i];
    c[change_tot].type = 1;
  }
  int x;
  for (int i = 1; i <= n; ++i)
  {
    x = T.GetMax(1, n, 1, a[i], 1);
    ++change_tot;
    c[change_tot].num = i;
    c[change_tot].time = x;
    c[change_tot].type = 0;
    x = T.GetMin(1, n, a[i], n, 1);
    if (x != INF)
    {
      ++change_tot;
      c[change_tot].num = i;
      c[change_tot].time = x;
      c[change_tot].type = 2;
    }
    T.Update(1, n, a[i], 1);
  }
  Qsort(1, change_tot);
  T.Build(1, n, 1);
  int last = 0;
  c[0].time = -1;
  int pre, nxt;
  for (int i = 1; i <= n; ++i)
    status[i] = -1;
  int sum = 0;
  c[change_tot + 1].time = INF;

  for (int i = 1; i <= change_tot + 1; ++i)
  {
    if (c[i].time != c[last].time)
    {
//      for (int j = 1; j <= n; ++j)
//        if (status[j] != -1)
//          printf("%s", status[j] == 0 ? "HI" : "LO");
//      printf("\n");
      if (last != 0)
      {
        ans[c[last].time] = sum;
        pd[c[last].time] = true;
      }
      last = i;
    }
    if (i == change_tot + 1)
      break;
    if (c[i].type == 0)
    {
      pre = 0, nxt = INF;
      if (c[i].num > 1)
        pre = T.GetMax(1, n, 1, c[i].num - 1, 1);
      if (c[i].num < n)
        nxt = T.GetMin(1, n, c[i].num + 1, n, 1);
      if (pre != 0 && nxt != INF)
        if (status[pre] == 0 && status[nxt] == 1)
          --sum;
      if (nxt != INF)
        if (status[nxt] == 1)
          ++sum;
      status[c[i].num] = 0;
      T.Update(1, n, c[i].num, 1);
    }
    else if (c[i].type == 1)
    {
      if (status[c[i].num] == -1)
      {
        T.Update(1, n, c[i].num, 1);
        if (pre != 0 && nxt != INF)
          if (status[pre] == 0 && status[nxt] == 1)
            --sum;
      }
      pre = 0, nxt = INF;
      if (c[i].num > 1)
        pre = T.GetMax(1, n, 1, c[i].num - 1, 1);
      if (c[i].num < n)
        nxt = T.GetMin(1, n, c[i].num + 1, n, 1);
      if (nxt != INF)
        if (status[nxt] == 1)
          --sum;
      if (pre != 0)
        if (status[pre] == 0)
          ++sum;
      status[c[i].num] = 1;
    }
    else if (c[i].type == 2)
    {
      pre = 0, nxt = INF;
      if (c[i].num > 1)
        pre = T.GetMax(1, n, 1, c[i].num - 1, 1);
      if (c[i].num < n)
        nxt = T.GetMin(1, n, c[i].num + 1, n, 1);
      if (pre != 0)
        if (status[c[i].num] == 1 && status[pre] == 0)
          --sum;
      if (nxt != INF)
        if (status[c[i].num] == 0 && status[nxt] == 1)
          --sum;
      if (pre != 0 && nxt != INF)
        if (status[pre] == 0 && status[nxt] == 1)
          ++sum;
      status[c[i].num] = -1;
      T.Update2(1, n, c[i].num, 1);
    }
  }
  int last_ans = 0;
  for (int i = 0; i <= n; ++i)
  {
    if (!pd[i])
      printf("%d\n", last_ans);
    else
    {
      printf("%d\n", ans[i]);
      last_ans = ans[i];
    }
  }
  return 0;
}
void Qsort(int l, int r)
{
  int i = l, j = r;
  Change mid = c[l + r >> 1];
  while (i <= j)
  {
    while (c[i] < mid)
      ++i;
    while (mid < c[j])
      --j;
    if (i <= j)
    {
      Swap(c[i], c[j]);
      ++i;
      --j;
    }
  }
  if (i < r)
    Qsort(i, r);
  if (l < j)
    Qsort(l, j);
  return;
}
template <typename T> void Swap(T& _a, T& _b)
{
  T tmp = _a;
  _a = _b;
  _b = tmp;
  return;
}
