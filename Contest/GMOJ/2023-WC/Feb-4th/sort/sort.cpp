#include <cstdio>

/* Constant */
const int N = 1e5;

/* Declaration */
int main();
void Qsort(int, int);
void Swap(int&, int&);
bool Cmp(int, int);

/* Variable */
int a[N + 1], bh[N + 1], tmp[N + 1];

/* Definition */
int main()
{
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
  {
    scanf("%d", &a[i]);
    tmp[i] = a[i];
    bh[i] = i;
  }
  Qsort(1, n);
  int temp;
  long long ans = 0;
  for (int i = 1; i <= n; ++i)
  {
    while (tmp[i] < tmp[bh[i]])
    {
      temp = bh[bh[i]];
      Swap(a[temp], a[bh[i]]);
      ans += a[temp] + a[bh[i]];
      bh[bh[i]] = bh[i];
      bh[i] = temp;
    }
  }
  printf("%lld", ans);
  return 0;
}
void Qsort(int l, int r)
{
  int i = l, j = r;
  int mid = l + r >> 1;
  while (i <= j)
  {
    while (Cmp(i, mid))
      ++i;
    while (Cmp(mid, j))
      --j;
    if (i <= j)
    {
      Swap(tmp[i], tmp[j]);
      Swap(bh[i], bh[j]);
      if (mid == i)
        mid = j;
      else if (mid == j)
        mid = i;
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
bool Cmp(int _x, int _y)
{
  if (tmp[_x] == tmp[_y])
    return bh[_x] < bh[_y];
  return tmp[_x] < tmp[_y];
}
