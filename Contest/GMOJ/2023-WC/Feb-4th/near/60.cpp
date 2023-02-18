#include <cstdio>

/* Constant */
const int N = 1e6;

/* Class */
class SegementTree
{
  public:
    int mx[(N << 2) + 1];
    int mi[(N << 2) + 1];

    int Max(int _a, int _b)
    {
      return _a > _b ? _a : _b;
    }
    int Min(int _a, int _b)
    {
      return _a < _b ? _a : _b;
    }
    void Build(int l, int r, int k)
    {
      if (l == r)
      {
        mx[k] = 0;
        mi[k] = N + 1;
        return;
      }
      int mid = l + r >> 1;
      Build(l, mid, k * 2);
      Build(mid + 1, r, k * 2 + 1);
      mx[k] = Max(mx[k * 2], mx[k * 2 + 1]);
      mi[k] = Min(mi[k * 2], mi[k * 2 + 1]);
      return;
    }
    void Update(int l, int r, int x, int k)
    {
      if (l == x && r == x)
      {
        mx[k] = l;
        mi[k] = l;
        return;
      }
      int mid = l + r >> 1;
      if (x <= mid)
        Update(l, mid, x, k * 2);
      if (x > mid)
        Update(mid + 1, r, x, k * 2 + 1);
      mx[k] = Max(mx[k * 2], mx[k * 2 + 1]);
      mi[k] = Min(mi[k * 2], mi[k * 2 + 1]);
      return;
    }
    int GetMax(int l, int r, int x, int y, int k)
    {
      if (x <= l && r <= y)
        return mx[k];
      int mid = l + r >> 1;
      int ret = 0;
      if (x <= mid)
        ret = Max(ret, GetMax(l, mid, x, y, k * 2));
      if (y > mid)
        ret = Max(ret, GetMax(mid + 1, r, x, y, k * 2 + 1));
      return ret;
    }
    int GetMin(int l, int r, int x, int y, int k)
    {
      if (x <= l && r <= y)
        return mi[k];
      int mid = l + r >> 1;
      int ret = N + 1;
      if (x <= mid)
        ret = Min(ret, GetMin(l, mid, x, y, k * 2));
      if (y > mid)
        ret = Min(ret, GetMin(mid + 1, r, x, y, k * 2 + 1));
      return ret;
    }
};

/* Declaration */
int main();

void Qsort(int, int);
void Swap(int&, int&);

/* Variable */
int p[N + 1], b[N + 1], rk[N + 1], bh[N + 1];
SegementTree T;

/* Definition */
void Qsort(int l, int r)
{
  int i = l, j = r;
  int mid = p[l + r >> 1];
  while (i <= j)
  {
    while (p[i] < mid)
      ++i;
    while (p[j] > mid)
      --j;
    if (i <= j)
    {
      Swap(p[i], p[j]);
      Swap(b[i], b[j]);
      Swap(bh[i], bh[j]);
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
void Swap(int& _a, int& _b)
{
  int temp = _a;
  _a = _b;
  _b = temp;
  return;
}
int main()
{
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
  {
    scanf("%d%d", &p[i], &b[i]);
    bh[i] = i;
  }
  Qsort(1, n);
  for (int i = 1; i <= n; ++i)
    rk[bh[i]] = i;
  int pre, nxt;
  long long sum = 0;
  long long ans = 0;
  T.Build(1, n, 1);
  for (int i = 1; i <= n; ++i)
  {
    pre = 0;
    nxt = N + 1;
    if (rk[i] > 1)
      pre = T.GetMax(1, n, 1, rk[i] - 1, 1);
    if (rk[i] < n)
      nxt = T.GetMin(1, n, rk[i] + 1, n, 1);
    if (pre != 0)
    {
      sum += b[rk[i]] ^ b[pre];
    }
    if (nxt != N + 1)
    {
      sum += b[rk[i]] ^ b[nxt];
    }
    if (pre != 0 && nxt != N + 1)
    {
      sum -= b[pre] ^ b[nxt];
    }
    T.Update(1, n, rk[i], 1);
    ans ^= sum;
  }
  printf("%lld", ans);
  return 0;
}
