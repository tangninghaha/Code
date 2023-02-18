#include <cstdio>

/* Constant */
const int N = 1e5;
const int K = 20;
const double exp = 1e-8;

/* Class */
class Point
{
  public:
    int x;
    int y;
};
bool operator< (Point _a, Point _b)
{
  return _a.x == _b.x ? (_a.y < _b.y) : (_a.x < _b.x);
}

/* Declaration */
int main();
void Qsort(int, int);
template <typename T> void Swap(T&, T&);

int Cmp(double);
double Abs(double);

/* Variable */
Point p[N + 1];
double used[K * K + 1][2];

/* Definition */
int main()
{
  freopen("chess.in", "r", stdin);
  freopen("chess.out", "w", stdout);
  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i)
    scanf("%d%d", &p[i].x, &p[i].y);
  if (n <= k)
  {
    printf("-1");
    return 0;
  }
  Qsort(1, n);
  double mid_x, mid_y;
  double now_x, now_y;
  int ans = 0;
  int mis;
  int l, r;
  int cnt = 0;
  bool pd;
  for (int st = 1; st <= k + 1; ++st)
  {
    for (int ed = n; ed >= n - k; --ed)
    {
      mid_x = (p[st].x + p[ed].x) / 2.0;
      mid_y = (p[st].y + p[ed].y) / 2.0;
      pd = false;
      for (int i = 1; i <= cnt; ++i)
        if (Cmp(mid_x - used[i][0]) == 0 && Cmp(mid_y - used[i][1]) == 0)
        {
          pd = true;
          break;
        }
      if (pd)
        continue;
      used[++cnt][0] = mid_x;
      used[cnt][1] = mid_y;
      mis = st + n - ed - 1;
      l = st + 1;
      r = ed - 1;
      while (l <= r)
      {
        now_x = (p[l].x + p[r].x) / 2.0;
        now_y = (p[l].y + p[r].y) / 2.0;
        if (Cmp(now_x - mid_x) == 0 && Cmp(now_y - mid_y) == 0)
        {
          ++l;
          --r;
        }
        else
        {
          ++mis;
          ++l;
        }
      }
      if (mis <= k)
      {
        ++ans;
      }
    }
  }
  printf("%d", ans);
  return 0;
}
int Cmp(double _x)
{
  if (Abs(_x) <= exp)
    return 0;
  return _x < 0 ? -1 : 1;
}
void Qsort(int l, int r)
{
  int i = l, j = r;
  Point mid = p[(l + r) >> 1];
  while (i <= j)
  {
    while (p[i] < mid)
      ++i;
    while (mid < p[j])
      --j;
    if (i <= j)
    {
      Swap(p[i], p[j]);
      ++i;
      --j;
    }
  }
  if (i < r) Qsort(i, r);
  if (l < j) Qsort(l, j);
  return;
}
template <typename T> void Swap(T& _x, T& _y)
{
  T tmp = _x;
  _x = _y;
  _y = tmp;
  return;
}
double Abs(double _x)
{
  return _x < 0 ? -_x : _x;
}
