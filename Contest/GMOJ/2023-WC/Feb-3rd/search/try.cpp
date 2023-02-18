#include <cstdio>
#include <cstring>
#define int unsigned long long

/* Constant */
const int N = 2e3;
const int LEN = 1e3;
const int base = 1145141;
const int M = 2e6 + 1;

/* Declaration */
signed main();
int GetHash(int, int);
void Swap(int&, int&);
void Qsort(int, int);
bool Cmp(int, int);

/* Variable */
char tmp[LEN + 1];

int hash[LEN + 1];
int cnt[M][2];
int base_pow[LEN + 1];

/* Definition */
signed main()
{
  freopen("in.txt", "r", stdin);
  base_pow[0] = 1;
  for (int i = 1; i <= LEN; ++i)
    base_pow[i] = base_pow[i - 1] * base;
  int n, m, l;
  scanf("%lld%lld%lld", &n, &m, &l);
  int len;
  int ans = 0;
  int sum;
  int cnt_tot = 0;
  for (int i = 1; i <= n; ++i)
  {
    scanf("%s", tmp);
    len = strlen(tmp);
    for (int j = 1; j <= len; ++j)
      hash[j] = hash[j - 1] * base + tmp[j - 1];
    for (int j = 1; j <= len - l + 1; ++j)
    {
      sum = GetHash(j, j + l - 1);
      cnt[++cnt_tot][0] = sum;
      cnt[cnt_tot][1] = i;
    }
  }
  Qsort(1, cnt_tot);
  int num = 0;
  int last = 1;
  for (int i = 1; i <= cnt_tot; ++i)
  {
    if (cnt[i][0] == cnt[i - 1][0] && cnt[i][1] == cnt[i - 1][1])
      continue;
    if (cnt[i][0] == cnt[last][0])
    {
      ++num;
    }
    else
    {
      if (num >= m)
      {
        ++ans;
      }
      num = 1;
      last = i;
    }
  }
  if (num >= m)
    ++ans;
  printf("%lld", ans);
  return 0;
}
int GetHash(int l, int r)
{
  return hash[r] - hash[l - 1] * base_pow[r - l + 1];
}
void Qsort(int l, int r)
{
  int i = l, j = r;
  int mid = (l + r) >> 1;
  while (i <= j)
  {
    while (Cmp(i, mid))
      ++i;
    while (Cmp(mid, j))
      --j;
    if (i <= j)
    {
      Swap(cnt[i][0], cnt[j][0]);
      Swap(cnt[i][1], cnt[j][1]);
      if (i == mid)
        mid = j;
      else if (j == mid)
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
  if (cnt[_x][0] == cnt[_y][0])
  {
    return cnt[_x][1] < cnt[_y][1];
  }
  return cnt[_x][0] < cnt[_y][0];
}
