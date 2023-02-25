#include <cstdio>

/* Constant */
const int N = 50;
const int L = 7;
const int S = 256;
const int INF = 1 << 29;

/* Declaration */
int main();
void Init();
int Min(int, int);
int GetZeroSum(int);
int lowbit(int);

/* Variable */
int f[N + 1][N + 1][S];
char tmp[N + 1];
int twom[8];
int sta[N + 1];

/* Definition */
void Init()
{
  twom[0] = 1;
  for (int i = 1; i <= 7; ++i) twom[i] = twom[i - 1] << 1;
}
int main()
{
  freopen("xlite.in", "r", stdin);
//  freopen("xlite.out", "w", stdout);
  Init();
  int n, l;
  scanf("%d%d", &n, &l);
  long long start = 0;
  scanf("%s", tmp + 1);
  for (int i = 1; i <= n; ++i)
    start <<= 1, start += tmp[i] - '0', sta[i] = tmp[i] - '0';
  long long fork = 0;
  scanf("%s", tmp + 1);
  for (int i = 1; i <= l; ++i)
    fork <<= 1, fork += tmp[i] - '0';

  if (n < l)
  {
    printf("%d", 0);
    return 0;
  }

  long long nxt;
  for (int i = 0; i <= n - l + 1; ++i)
    for (int j = 0; j <= i; ++j)
      for (int s = 0; s < twom[l]; ++s)
        f[i][j][s] = INF;
  f[0][0][start >> n - l] = 0;
  int ch;
  for (int i = 0; i <= n - l; ++i)
  {
    if (i == n - l)
      fork &= (twom[l - 1] - 1);
    for (int j = 0; j <= i; ++j)
      for (int s = 0; s < twom[l]; ++s)
      {
        ch = s & 1;
        nxt = ((s & (twom[l - 1] - 1)) << 1) + sta[i + l];
        f[i + 1][j + ((sta[i + 1] == 1) ^ ch)][nxt] = Min(f[i + 1][j + ((sta[i + 1] == 1) ^ ch)][nxt], f[i][j][s]);
        f[i + 1][j + ((sta[i + 1] == 0) ^ ch)][nxt ^ fork] = Min(f[i + 1][j + ((sta[i + 1] == 0) ^ ch)][nxt ^ fork], f[i][j][s] + 1);
      }
  }
  int ans = INF, times = INF;
  int temp;
  for (int j = 0; j <= n - l + 1; ++j)
  {
    for (int s = 0; s < twom[l]; ++s)
    {
      temp = j + GetZeroSum(s);
      if (temp < ans && f[n - l + 1][j][s] != INF)
      {
        ans = temp;
        times = f[n - l + 1][j][s];
      }
      else if (temp == ans && f[n - l + 1][j][s] < times)
      {
        times = f[n - l + 1][j][s];
      }
    }
  }
  printf("%d", times);
  return 0;
}
int Min(int _a, int _b)
{
  return _a < _b ? _a : _b;
}
int GetZeroSum(int _x)
{
  int ret = 0;
  while (_x)
    _x -= lowbit(_x), ++ret;
  return ret;
}
int lowbit(int _x)
{
  return _x & -_x;
}
