/* Expected score: 60 */

#include <cstdio>

/* Constant */
const int N = 4000;
const int exp = 1e-7;

/* Class */
class Point
{
  public:
    int x;
    int y;
};

/* Declaration */
int main();

void Qsort(int, int);
template <typename T> void Swap(T&, T&);

int Cmp(double, double);

/* Variable */
double jd[N * N / 2 + 1][2];
Point p[N + 1];
bool vis[N + 1];

/* Definition */
int main()
{
  freopen("chess.in", "r", stdin);
  freopen("chess.out", "w", stdout);
  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i)
  {
    scanf("%d%d", &p[i].x, &p[i].y);
  }
  if (k >= n)
  {
    printf("-1");
    return 0;
  }
  int cnt = 0;
  for (int i = 1; i <= n; ++i)
  {
    for (int j = i + 1; j <= n; ++j)
    {
      ++cnt;
      jd[cnt][0] = (p[i].x - p[j].x) / 2.0 + p[i].x;
      jd[cnt][1] = (p[i].y - p[j].y) / 2.0 + p[i].y;
    }
  }
  if (n & 1)
    for (int i = 1; i <= n; ++i)
      jd[++cnt][0] = p[i].x, jd[cnt][1] = p[i].y, vis[cnt] = true;
  Qsort(1, cnt);
  int num = 1;
  int ans = 0;
  int last = 1;
  bool pd = vis[1];
  for (int i = 2; i <= cnt; ++i)
  {
    if (Cmp(jd[i][0], jd[last][0]) == 0 && Cmp(jd[i][1], jd[last][1]) == 0)
    {
      ++num;
      if (vis[i] == true)
        pd = true;
    }
    else
    {
      if (n & 1)
      {
//        if ((n / 2 - num) * 2 + (!pd) <= k)
          if (n - (num * 2 - pd) <= k)
            ++ans;
      }
      else
      {
//        if ((n / 2 - num) * 2 <= k)
          if (n - num * 2 <= k)
            ++ans;
      }
      last = i;
      num = 0;
      pd = false;
    }
  }
  if (num)
  {
    if (n & 1)
    {
//      if ((n / 2 - num) * 2 + (!pd) <= k)
        if (n - (num * 2 - pd) <= k)
        ++ans;
    }
    else
    {
//      if ((n / 2 - num) * 2 <= k)
        if (n - num * 2 <= k)
        ++ans;
    }
  }
  printf("%d", ans);
  return 0;
}
int Cmp(double _x, double _y)
{
  if (_x > _y)
  {
    if (_x - _y <= exp)
      return 0;
    return 1;
  }
  if (_y - _x <= exp)
    return 0;
  return -1;
}
void Qsort(int l, int r)
{
  int i = l, j = r;
  int mid = l + r >> 1;
  while (i <= j)
  {
    while (Cmp(i, mid) < 0)
      ++i;
    while (Cmp(mid, j) < 0)
      --j;
    if (i <= j)
    {
      Swap(jd[i][0], jd[j][0]);
      Swap(jd[i][1], jd[j][1]);
      Swap(vis[i], vis[j]);
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
